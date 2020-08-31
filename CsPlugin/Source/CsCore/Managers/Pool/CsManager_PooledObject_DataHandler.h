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

template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
class TCsManager_PooledObject_DataHandler
{
public:

	TCsManager_PooledObject_DataHandler() :
		MyRoot(nullptr),
		EmulatedDataMap(),
		EmulatedDataInterfaceMap(),
		EmulatedDataInterfaceImplMap(),
		GetDatasDataTableChecked_Impl(),
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
	TBaseDelegate<void, const FString& /*Context*/, UDataTable*& /*OutDataTable*/, TSoftObjectPtr<UDataTable>& /*OutDataTableSoftObject*/> GetDatasDataTableChecked_Impl;

	virtual void PopulateDataMapFromSettings(const FString& Context)
	{
		// Reset appropriate containers
		ResetDataContainers();

		checkf(GetDatasDataTableChecked_Impl.IsBound(), TEXT("%s: GetDatasDataTableChecked_Impl is NOT bound."), *Context);

		UDataTable* DataTable = nullptr;
		TSoftObjectPtr<UDataTable> DT_SoftObject(nullptr);

		GetDatasDataTableChecked_Impl.Execute(Context, DataTable, DT_SoftObject);

		// Emulated
		if (HasEmulatedDataInterfaces())
		{
			CreateEmulatedDataFromDataTable(DT, DT_SoftObject);
		}
		// "Normal" / Non-Emulated
		else
		{
			PopulateDataMapFromDataTable(DT, DT_SoftObject);
		}
	}

	virtual bool HasEmulatedDataInterfaces() const 
	{
		return false;
	}

	virtual void CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
	}

	virtual bool DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
	{
		return false;
	}

	void PopulateDataMapFromDataTable(const FString& Context, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
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

				DataType* IData = Cast<DataType>(Data);

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
	InterfaceDataType* GetData(const FString& Context, const EnumType& Type)
	{
		checkf(EnumMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return GetData(Type.GetFName());
	}

	InterfaceDataType* GetDataChecked(const FString& Context, const FName& Name)
	{
		InterfaceDataType* Ptr = GetData(Context, Name);

		checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString()));

		return Ptr;
	}

	template<typename EnumMap, typename EnumType>
	InterfaceDataType* GetDataChecked(const FString& Context, const EnumType& Type)
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
				DeconstructEmulatedData(ImplPair.Key, ImplPair.Value);

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
		DataTables.Reset(DataTables.Max());
		DataTableRowByPathMap.Reset();
	}

// Log
#pragma region
public:

	void(*Log)(const FString&);

#pragma endregion Log
};