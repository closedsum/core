// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Library
#include "Library/CsLibrary_Property.h"
#include "Data/CsLibrary_Data.h"
#include "Managers/Data/CsLibrary_Manager_Data.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
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
				* @param Context	The calling context.
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

				/**
				* 
				* 
				* @param Context	The calling context.
				*/
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
					typedef NCsProperty::FLibrary PropertyLibrary;

					FStructProperty* DataProperty = PropertyLibrary::FindStructPropertyByName<DataContainerType>(RowStruct, Name::Data);

					if (!DataProperty)
					{
						Log(FString::Printf(TEXT("%s: Failed to find StructProperty: Data in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
					}

					// Check which rows from the DataTable have been loaded
					typedef NCsData::NManager::FLibrary DataManagerLibrary;

					UObject* ContextRoot		  = DataManagerLibrary::GetContextRootChecked(Context, MyRoot);
					UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

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

							typedef NCsData::FLibrary DataLibrary;

							InterfaceDataType* IData = DataLibrary::GetChecked<InterfaceDataType>(Context, O);

							DataMap.Add(RowName, IData);
						}
					}
				}

			public:

				template<typename DataSliceType>
				DataSliceType* SafeConstructData(const FString& Context, const FName& Name)
				{
					static_assert(!std::is_abstract<DataSliceType>(), "NCsPooledObject::NManager::NHandler::TData: DataSliceType IS abstract.");

					static_assert(std::is_base_of<InterfaceDataType, DataSliceType>(), "NCsPooledObject::NManager::NHandler::TData: DataSliceType is NOT a child of: InterfaceDataType.");

					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					if (EmulatedDataMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data has already been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					if (EmulatedDataInterfaceMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Emulated Interface Map has already been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					// Construct the slice
					DataSliceType* Data = new DataSliceType();

					EmulatedDataMap.Add(Name, Data);
					// Construct Map to store all slices
					DataInterfaceMapType* EmulatedInterfaceMap = new DataInterfaceMapType();

					EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

					FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();
					// Add slice as type InterfaceDataType
					InterfaceMap->Add<InterfaceDataType>(DataSliceType::Name, static_cast<InterfaceDataType*>(Data));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Data->SetInterfaceMap(InterfaceMap);
					// Store a reference to the slice 
					TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
					InterfaceImplMap.Add(DataSliceType::Name, Data);
					// Add the "base" slice to the map of all data.
					DataMap.Add(Name, Data);

					return Data;
				}

				template<typename DataSliceType, typename InterfaceType>
				DataSliceType* AddSafeDataSlice(const FString& Context, const FName& Name)
				{
					static_assert(!std::is_abstract<DataSliceType>(), "NCsPooledObject::NManager::NHandler::TData: DataSliceType IS abstract.");

					static_assert(std::is_base_of<InterfaceType, DataSliceType>(), "NCsPooledObject::NManager::NHandler::TData: DataSliceType is NOT a child of: InterfaceType.");

					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					if (!EmulatedDataMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data has NOT been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					if (!EmulatedDataInterfaceMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Emulated Interface Map has NOT been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					// Construct the slice
					DataSliceType* Data = new DataSliceType();

					DataInterfaceMapType* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
					FCsInterfaceMap* InterfaceMap			   = EmulatedInterfaceMap->GetInterfaceMap();
					// Add slice as type InterfaceDataType
					InterfaceMap->Add<InterfaceDataType>(DataSliceType::Name, static_cast<InterfaceDataType*>(Data));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Data->SetInterfaceMap(InterfaceMap);
					// Store a reference to the slice 
					TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
					InterfaceImplMap.Add(DataSliceType::Name, Data);

					return Data;
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

				FORCEINLINE InterfaceDataType* GetDataChecked(const FString& Context, const FName& Name)
				{
					InterfaceDataType* Ptr = GetData(Context, Name);

					checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString()));

					return Ptr;
				}

				FORCEINLINE InterfaceDataType* GetSafeData(const FString& Context, const FName& Name)
				{
					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					InterfaceDataType* Ptr = GetData(Context, Name);

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString())));
					}
					return Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceDataType* GetData(const FString& Context, const EnumType& Type)
				{
					using namespace NCached;

					check(EnumMap::Get().IsValidEnumChecked(Context, Str::Type, Type));

					return GetData(Context, Type.GetFName());
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceDataType* GetDataChecked(const FString& Context, const EnumType& Type)
				{
					InterfaceDataType* Ptr = GetData<EnumMap, EnumType>(Context, Type);

					checkf(Ptr, TEXT("%s: Failed to find a Data associated with Type: %s."), *Context, Type.ToChar());

					return Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceDataType* GetSafeData(const FString& Context, const EnumType& Type)
				{
					if (!EnumMap::Get().IsValidEnum(Type))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar()));
						return nullptr;
					}

					InterfaceDataType* Ptr = GetData<EnumMap, EnumType>(Context, Type);

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Data associated with Type: %s."), *Context, Type.ToChar()));
					}
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