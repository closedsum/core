// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Cached
#pragma region

namespace NCsManagerPooledObjectDataHandlerCached
{
	namespace Name
	{
		extern CSCORE_API const FName Data;
	}
}

#pragma endregion Cached

class UObject;
class UDataTable;

/**
*/
template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
class TCsManager_PooledObject_DataHandler
{
public:

	TCsManager_PooledObject_DataHandler() :
		MyRoot(nullptr),
		DataMap(),
		DataTableRowByPathMap(),
		EmulatedDataMap(),
		EmulatedDataInterfaceMap(),
		EmulatedDataInterfaceImplMap(),
		GetDatasDataTablesChecked_Impl(),
		Log(nullptr)
	{
	}

	virtual ~TCsManager_PooledObject_DataHandler()
	{
		Shutdown();
	}

public:

	UObject* MyRoot;

	void Shutdown()
	{
		ResetDataContainers();
	}

protected:

	// <EntryName, Data>
	TMap<FName, InterfaceDataType*> DataMap;

	// <Path, <RowName, RowPtr>>
	TMap<FSoftObjectPath, TMap<FName, uint8*>> DataTableRowByPathMap;

	/** <DataName, InterfacePtr> */
	TMap<FName, InterfaceDataType*> EmulatedDataMap;

	/** <DataName, InterfaceMapPtr> */
	TMap<FName, DataInterfaceMapType*> EmulatedDataInterfaceMap;

	/** <DataName, <InterfaceImplName, InterfaceImplPtr>> */
	TMap<FName, TMap<FName, void*>> EmulatedDataInterfaceImplMap;

public:

	/**
	*
	*/
	TBaseDelegate<void, const FString& /*Context*/, TArray<UDataTable*>& /*OutDataTables*/, TArray<TSoftObjectPtr<UDataTable>>& /*OutDataTableSoftObjects*/> GetDatasDataTablesChecked_Impl;

	/**
	*
	*
	* @param Context
	*/
	virtual void PopulateDataMapFromSettings(const FString& Context)
	{
		// Reset appropriate containers
		ResetDataContainers();

		checkf(GetDatasDataTablesChecked_Impl.IsBound(), TEXT("%s: GetDatasDataTablesChecked_Impl is NOT bound."), *Context);

		TArray<UDataTable*> DataTables;
		TArray<TSoftObjectPtr<UDataTable>> DataTableSoftObjects;

		GetDatasDataTablesChecked_Impl.Execute(Context, DataTables, DataTableSoftObjects);

		const int32 Count = DataTables.Num();

		checkf(Count > 0, TEXT("%s: Failed to find any DataTables."), *Context);

		for (int32 I = 0; I < Count; ++I)
		{
			UDataTable* DataTable								  = DataTables[I];
			const TSoftObjectPtr<UDataTable>& DataTableSoftObject = DataTableSoftObjects[I];

			// Emulated
			if (HasEmulatedDataInterfaces(Context, I))
			{
				CreateEmulatedDataFromDataTable(Context, I, DataTable, DataTableSoftObject);
			}
			// "Normal" / Non-Emulated
			else
			{
				PopulateDataMapFromDataTable(Context, I, DataTable, DataTableSoftObject);
			}
		}
	}

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
	{
	}

	/**
	*
	*
	* @param Context
	* @param Index
	* return
	*/
	virtual bool HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const 
	{
		return false;
	}

	/**
	*
	*
	* @param Context
	* @param Index
	* @param DataTable
	* @param DataTableSoftObjectPath
	*/
	virtual void CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
	}

	virtual bool DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
	{
		return false;
	}

	void PopulateDataMapFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
		using namespace NCsManagerPooledObjectDataHandlerCached;

		const UScriptStruct* RowStruct = DataTable->GetRowStruct();

		// Data
		UStructProperty* DataProperty = FCsLibrary_Property::FindStructPropertyByName<DataContainerType>(RowStruct, Name::Data);

		if (!DataProperty)
		{
			Log(FString::Printf(TEXT("%s: Failed to find StructProperty: Data in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
		}

		// Check which rows from the DataTable have been loaded

		UWorld* World				  = MyRoot->GetWorld();
		UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

		const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName = Pair.Key;
			uint8* RowPtr		 = Manager_Data->GetDataTableRow(DataTableSoftObject, RowName);

			if (!RowPtr)
				continue;

			TMap<FName, uint8*>& Map = DataTableRowByPathMap.FindOrAdd(DataTableSoftObject.ToSoftObjectPath());
			Map.Add(RowName, RowPtr);

			// Data
			if (DataProperty)
			{
				DataContainerType* DataPtr = DataProperty->ContainerPtrToValuePtr<DataContainerType>(RowPtr);

				UObject* Data = DataPtr->Get();

				checkf(Data, TEXT("%s: Failed to get data from DataTable: %s Row: %s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));

				InterfaceDataType* IData = Cast<InterfaceDataType>(Data);

				checkf(IData, TEXT("%s: Data: %s with Class: %s does NOT implement interface: DataType."), *Context, *(Data->GetName()), *(Data->GetClass()->GetName()));

				DataMap.Add(RowName, IData);
			}
		}
	}

	InterfaceDataType* GetData(const FString& Context, const FName& Name)
	{
		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

		// Check emulated data
		if (InterfaceDataType** EmuDataPtr = EmulatedDataMap.Find(Name))
			return *EmuDataPtr;

		// Check data
		if (InterfaceDataType** DataPtr = DataMap.Find(Name))
			return *DataPtr;

		return nullptr;
	}

	template<typename EnumMap, typename EnumType>
	FORCEINLINE InterfaceDataType* GetData(const FString& Context, const EnumType& Type)
	{
		checkf(EnumMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return GetData(Context, Type.GetFName());
	}

	FORCEINLINE InterfaceDataType* GetDataChecked(const FString& Context, const FName& Name)
	{
		InterfaceDataType* Ptr = GetData(Context, Name);

		checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString()));

		return Ptr;
	}

	template<typename EnumMap, typename EnumType>
	FORCEINLINE InterfaceDataType* GetDataChecked(const FString& Context, const EnumType& Type)
	{
		InterfaceDataType* Ptr = GetData<EnumMap, EnumType>(Context, Type);

		checkf(Ptr, TEXT("%s: Failed to find a Data associated with Type: %s."), *Context, Type.ToChar());

		return Ptr;
	}

	void ResetDataContainers()
	{
		for (TPair<FName, TMap<FName, void*>>& DataPair : EmulatedDataInterfaceImplMap)
		{
			TMap<FName, void*> InterfaceImplMap = DataPair.Value;

			for (TPair<FName, void*>& ImplPair : InterfaceImplMap)
			{
				const bool Success = DeconstructEmulatedData(ImplPair.Key, ImplPair.Value);

				checkf(Success, TEXT("Failed to deconstruct emulated data @ DataName: %s InterfaceImplName: %s."), *(DataPair.Key.ToString()), *(ImplPair.Key.ToString()));

				ImplPair.Value = nullptr;
			}
		}
		EmulatedDataMap.Reset();
		EmulatedDataInterfaceImplMap.Reset();

		for (TPair<FName, DataInterfaceMapType*>& Pair : EmulatedDataInterfaceMap)
		{
			DataInterfaceMapType* Ptr = Pair.Value;
			delete Ptr;
			Pair.Value = nullptr;
		}
		EmulatedDataInterfaceMap.Reset();

		DataMap.Reset();
		DataTableRowByPathMap.Reset();
	}

// Log
#pragma region
public:

	void(*Log)(const FString&);

#pragma endregion Log
};