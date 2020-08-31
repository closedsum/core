// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Cached
#pragma region

namespace NCsManagerPooledObjectClassHandlerCached
{
	namespace Name
	{
		extern CSCORE_API const FName Class;
	}
}

#pragma endregion Cached

class UObject;
class UDataTable;

template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
class TCsManager_PooledObject_ClassHandler
{
public:

	TCsManager_PooledObject_ClassHandler() :
		MyRoot(nullptr),
		ClassByTypeMap(),
		ClassByClassTypeMap(),
		GetClassesDataTableChecked_Impl(),
		GetDatasDataTableChecked_Impl(),
		Log(nullptr)
	{
	}

	virtual ~TCsManager_PooledObject_ClassHandler()
	{
		Shutdown();
	}

public:

	UObject* MyRoot;

	void Shutdown()
	{
		ResetClassContainers();
	}

// Class
#pragma region
protected:

	/** */
	TMap<FName, InterfacePooledContainerType> ClassByTypeMap;

	/** */
	TMap<FName, InterfacePooledContainerType> ClassByClassTypeMap;

public:

	/**
	*
	*/
	TBaseDelegate<void, const FString& /*Context*/, UDataTable*& /*OutDataTable*/, TSoftObjectPtr<UDataTable>& /*OutDataTableSoftObject*/> GetClassesDataTableChecked_Impl;

	/**
	*
	*/
	TBaseDelegate<void, const FString& /*Context*/, UDataTable*& /*OutDataTable*/, TSoftObjectPtr<UDataTable>& /*OutDataTableSoftObject*/> GetDatasDataTableChecked_Impl;

	virtual void PopulateClassMapFromSettings(const FString& Context)
	{
		using namespace NCsManagerPooledObjectClassHandlerCached;

		// Reset appropriate containers
		ResetClassContainers();

		// Get Classes DataTable
		{
			checkf(GetClassesDataTableChecked_Impl.IsBound(), TEXT("%s: GetClassesDataTableChecked_Impl is NOT bound."), *Context);

			UDataTable* DataTable = nullptr;
			TSoftObjectPtr<UDataTable> DT_SoftObject(nullptr);

			GetClassesDataTableChecked_Impl.Execute(Context, DataTable, DT_SoftObject);

			const UScriptStruct* RowStruct = DataTable->GetRowStruct();

			// Get the Property named "Class" if it exists.
			UStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<InterfaceUStructContainerType>(RowStruct, Name::Class);

			if (!ClassProperty)
			{
#if !UE_BUILD_SHIPPING
				Log(FString::Printf(TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
#endif // #if !UE_BUILD_SHIPPING
				return;
			}

			// Cache any class related information that is loaded.
			UWorld* World				  = MyRoot->GetWorld();
			UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

			const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName = Pair.Key;
				uint8* RowPtr	     = Manager_Data->GetDataTableRow(DT_SoftObject, RowName);

				if (!RowPtr)
					continue;

				// If Property named "Class" exists, cache the class.
				if (ClassProperty)
				{
					InterfaceUStructContainerType* StructPtr = ClassProperty->ContainerPtrToValuePtr<InterfaceUStructContainerType>(RowPtr);

					checkf(StructPtr, TEXT("%s: StructPtr is NULL."), *Context);

					UObject* O = StructPtr->Get();

					checkf(O, TEXT("%s: Failed to get character from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));

					InterfacePooledContainerType& PooledContainer = ClassByClassTypeMap.Add(RowName);

					PooledContainer.SetObject(O);
				}
			}
		}
		// Get Datas DataTable
		{
			checkf(GetDatasDataTableChecked_Impl.IsBound(), TEXT("%s: GetDatasDataTableChecked_Impl is NOT bound."), *Context);

			UDataTable* DataTable = nullptr;
			TSoftObjectPtr<UDataTable> DT_SoftObject(nullptr);

			GetDatasDataTableChecked_Impl.Execute(Context, DataTable, DT_SoftObject);

			const UScriptStruct* RowStruct = DataTable->GetRowStruct();

			// Get the Property named "Class" if it exists.
			UStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<EnumType>(RowStruct, Name::Class);

			if (!ClassProperty)
			{
#if !UE_BUILD_SHIPPING
				Log(FString::Printf(TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
#endif // #if !UE_BUILD_SHIPPING
				return;
			}

			// Cache any class related information that is loaded.
			UWorld* World				  = MyRoot->GetWorld();
			UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

			const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName = Pair.Key;
				uint8* RowPtr		 = Manager_Data->GetDataTableRow(DT_SoftObject, RowName);

				if (!RowPtr)
					continue;

				// If Property named "Class" exists, cache the class.
				if (ClassProperty)
				{
					EnumType* StructPtr = ClassProperty->ContainerPtrToValuePtr<EnumType>(RowPtr);

					checkf(StructPtr, TEXT("%s: StructPtr is NULL."), *Context);

					InterfacePooledContainerType* ContainerPtr = ClassByClassTypeMap.Find(StructPtr->GetFName());

					checkf(ContainerPtr, TEXT("%s: "), *Context);

					InterfacePooledContainerType& PooledContainer = ClassByTypeMap.Add(RowName);

					PooledContainer.SetObject(ContainerPtr->GetObject());
				}
			}
		}
	}

	template<typename EnumMap>
	InterfacePooledContainerType* GetClassByType(const FString& Context, const EnumType& Type)
	{
		checkf(EnumMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return ClassByTypeMap.Find(Type.GetFName());
	}

	template<typename EnumClassMap, typename EnumClassType>
	InterfacePooledContainerType* GetClassByClassType(const FString& Context, const EnumClassType& Type)
	{
		checkf(EnumClassMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return ClassByClassTypeMap.Find(Type.GetFName());
	}

	template<typename EnumClassMap, typename EnumClassType>
	InterfacePooledContainerType* GetClassByClassTypeChecked(const FString& Context, const EnumClassType& Type)
	{
		InterfacePooledContainerType* Ptr = GetClassByClassType<EnumClassMap, EnumClassType>(Context, Type);

		checkf(Ptr, TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar());

		return Ptr;
	}

	void ResetClassContainers()
	{
		ClassByTypeMap.Reset();
		ClassByClassTypeMap.Reset();
	}

#pragma endregion Class

// Log
#pragma region
public:

	void(*Log)(const FString&);

#pragma endregion Log
};