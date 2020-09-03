// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Library
#include "Library/CsLibrary_Property.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
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

/**
*/
template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumClassType>
class TCsManager_PooledObject_ClassHandler
{
public:

	TCsManager_PooledObject_ClassHandler() :
		Outer(nullptr),
		MyRoot(nullptr),
		ClassByTypeMap(),
		ClassByClassTypeMap(),
		Log(nullptr)
	{
	}

	virtual ~TCsManager_PooledObject_ClassHandler()
	{
		Shutdown();
	}

public:

	/** */
	UObject* Outer;

	/** */
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

	virtual void PopulateClassMapFromSettings(const FString& Context)
	{
		using namespace NCsManagerPooledObjectClassHandlerCached;

		// Reset appropriate containers
		ResetClassContainers();

		// Get Classes DataTable
		{
			UDataTable* DataTable = nullptr;
			TSoftObjectPtr<UDataTable> DataTableSoftObject(nullptr);

			GetClassesDataTableChecked(Context, DataTable, DataTableSoftObject);

			const UScriptStruct* RowStruct = DataTable->GetRowStruct();

			// Get the Property named "Class" if it exists.
			FStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<InterfaceUStructContainerType>(RowStruct, Name::Class);

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
				uint8* RowPtr	     = Manager_Data->GetDataTableRow(DataTableSoftObject, RowName);

				if (!RowPtr)
					continue;

				// If Property named "Class" exists, cache the class.
				if (ClassProperty)
				{
					InterfaceUStructContainerType* StructPtr = ClassProperty->ContainerPtrToValuePtr<InterfaceUStructContainerType>(RowPtr);

					checkf(StructPtr, TEXT("%s: StructPtr is NULL. Failed to get pointer from Property: Class of type EnumClassType."), *Context);

					UObject* O = StructPtr->Get();

					checkf(O, TEXT("%s: Failed to get character from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));

					InterfacePooledContainerType& PooledContainer = ClassByClassTypeMap.Add(RowName);

					PooledContainer.SetObject(O);
				}
			}
		}
		// Get Datas DataTable
		{
			TArray<UDataTable*> DataTables;
			TArray<TSoftObjectPtr<UDataTable>> DataTableSoftObjects;

			GetDatasDataTablesChecked(Context, DataTables, DataTableSoftObjects);

			const int32 Count = DataTables.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				UDataTable* DataTable								  = DataTables[I];
				const TSoftObjectPtr<UDataTable>& DataTableSoftObject = DataTableSoftObjects[I];

				const UScriptStruct* RowStruct = DataTable->GetRowStruct();

				// Get the Property named "Class" if it exists.
				FStructProperty* ClassProperty = FCsLibrary_Property::FindStructPropertyByName<EnumClassType>(RowStruct, Name::Class);

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
					uint8* RowPtr		 = Manager_Data->GetDataTableRow(DataTableSoftObject, RowName);

					if (!RowPtr)
						continue;

					// If Property named "Class" exists, cache the class.
					if (ClassProperty)
					{
						EnumClassType* StructPtr = ClassProperty->ContainerPtrToValuePtr<EnumClassType>(RowPtr);

						checkf(StructPtr, TEXT("%s: StructPtr is NULL. Failed to get pointer from Property: Class of type EnumClassType."), *Context);

						InterfacePooledContainerType* ContainerPtr = ClassByClassTypeMap.Find(StructPtr->GetFName());

						checkf(ContainerPtr, TEXT("%s: ContainerPtr is NULL. Failed to find class of class type: %s"), *Context, StructPtr->ToChar());

						InterfacePooledContainerType& PooledContainer = ClassByTypeMap.Add(RowName);

						PooledContainer.SetObject(ContainerPtr->GetObject());
					}
				}
			}
		}
	}

protected:

	virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
	{
		checkf(0, TEXT("%s::GetClassesDataTableChecked: Failed to implement method."), *(Outer->GetName()));
	}

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject)
	{
		checkf(0, TEXT("%s::GetDatasDataTablesChecked: Failed to implement method."), *(Outer->GetName()));
	}

public:

	template<typename EnumMap, typename EnumType>
	FORCEINLINE InterfacePooledContainerType* GetClassByType(const FString& Context, const EnumType& Type)
	{
		checkf(EnumMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return ClassByTypeMap.Find(Type.GetFName());
	}

	template<typename EnumMap, typename EnumType>
	FORCEINLINE InterfacePooledContainerType* GetClassByTypeChecked(const FString& Context, const EnumType& Type)
	{
		InterfacePooledContainerType* Ptr = GetClassByType<EnumMap, EnumType>(Context, Type);

		checkf(Ptr, TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar());

		return Ptr;
	}

	template<typename EnumClassMap>
	FORCEINLINE InterfacePooledContainerType* GetClassByClassType(const FString& Context, const EnumClassType& Type)
	{
		checkf(EnumClassMap::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());

		return ClassByClassTypeMap.Find(Type.GetFName());
	}

	template<typename EnumClassMap>
	FORCEINLINE InterfacePooledContainerType* GetClassByClassTypeChecked(const FString& Context, const EnumClassType& Type)
	{
		InterfacePooledContainerType* Ptr = GetClassByClassType<EnumClassMap>(Context, Type);

		checkf(Ptr, TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar());

		return Ptr;
	}

protected:

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