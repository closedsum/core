// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Library
#include "Library/CsLibrary_Property.h"
#include "Data/CsLibrary_Data.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
#pragma once

class UObject;
class UDataTable;

namespace NCsPooledObject
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSCORE_API const FString Type;
				}

				namespace Name
				{
					extern CSCORE_API const FName Data;
				}
			}

			/**
			*/
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData
			{
				static_assert(std::is_abstract<InterfaceDataType>(), "NCsPooledObject::NManager::NHandler::TData: InterfaceDataType MUST be abstract.");

				static_assert(!std::is_abstract<DataContainerType>(), "NCsPooledObject::NManager::NHandler::TData: DataContainerType IS abstract.");

			public:

				TData() :
					Outer(nullptr),
					MyRoot(nullptr),
					DataMap(),
					DataTableRowByPathMap(),
					EmulatedDataMap(),
					EmulatedDataInterfaceMap(),
					EmulatedDataInterfaceImplMap(),
					Log(nullptr)
				{
				}

				virtual ~TData()
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
				*
				* @param Context
				*/
				virtual void PopulateDataMapFromSettings(const FString& Context)
				{
					// Reset appropriate containers
					ResetDataContainers();

					TArray<UDataTable*> DataTables;
					TArray<TSoftObjectPtr<UDataTable>> DataTableSoftObjects;

					GetDatasDataTablesChecked(Context, DataTables, DataTableSoftObjects);

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

			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
					checkf(0, TEXT("%s::GetDatasDataTablesChecked: Failed to implement method."), *(Outer->GetName()));
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
					using namespace NCached;

					const UScriptStruct* RowStruct = DataTable->GetRowStruct();

					// Data
					FStructProperty* DataProperty = FCsLibrary_Property::FindStructPropertyByName<DataContainerType>(RowStruct, Name::Data);

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

							UObject* O = DataPtr->Get();

							checkf(O, TEXT("%s: Failed to get data from DataTable: %s Row: %s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));

							ICsData* Data = Cast<ICsData>(O);

							checkf(Data, TEXT("%s: Data: %s with Class: %s does NOT implement interface: ICsData."), *Context, *(O->GetName()), *(O->GetClass()->GetName()));

							InterfaceDataType* IData = NCsData::FLibrary::GetInterfaceChecked<InterfaceDataType>(Context, Data->_getIData());

							DataMap.Add(RowName, IData);
						}
					}
				}

			public:

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
					using namespace NCached;

					check(EnumMap::Get().IsValidEnumChecked(Context, Str::Type, Type));

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

			protected:

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
		}
	}
}