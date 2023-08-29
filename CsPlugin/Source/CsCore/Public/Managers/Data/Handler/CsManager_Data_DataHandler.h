// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Library
	// Manager
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Data
#include "Data/CsLibrary_Data.h"
	// Common
#include "Library/CsLibrary_Property.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Containers
#include "Containers/CsGetPersistentObjects.h"
#endif // #if WITH_EDITOR

class UObject;
class UDataTable;

namespace NCsData
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
				static_assert(std::is_abstract<InterfaceDataType>(), "NCsData::NManager::NHandler::TData: InterfaceDataType MUST be abstract.");

				static_assert(!std::is_abstract<DataContainerType>(), "NCsData::NManager::NHandler::TData: DataContainerType IS abstract.");

			public:

				TData() :
					Outer(nullptr),
					MyRoot(nullptr),
					DataMap(),
					DataTableRowByPathMap(),
					ImplDataMap(),
					ImplDataInterfaceMap(),
					ImplDataSliceByNameMap(),
					ImplDataDeconstructByNameMap()
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

			public:

				FORCEINLINE const TMap<FName, InterfaceDataType*>& GetDataMap() const { return DataMap; }

			protected:

				TMap<FName, UObject*> DataAsUObjectMap;

				// <Path, <RowName, RowPtr>>
				TMap<FSoftObjectPath, TMap<FName, uint8*>> DataTableRowByPathMap;

				/** <DataName, InterfacePtr> */
				TMap<FName, InterfaceDataType*> ImplDataMap;

			public:

				FORCEINLINE const TMap<FName, InterfaceDataType*>& GetImplDataMap() const { return ImplDataMap; }

			protected:

				/** <DataName, InterfaceMapPtr> */
				TMap<FName, DataInterfaceMapType*> ImplDataInterfaceMap;

				/** <DataName, <InterfaceImplName, InterfaceImplPtr>> */
				TMap<FName, TMap<FName, void*>> ImplDataSliceByNameMap;

				/** <DataName, <InterfaceImplName, DeconstructFnPtr>> */
				TMap<FName, TMap<FName, void(*)(void*)>> ImplDataDeconstructByNameMap;

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

				void PopulateDataMapFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
				{
					using namespace NCached;

					const UScriptStruct* RowStruct = DataTable->GetRowStruct();

					// Data
					typedef NCsProperty::FLibrary PropertyLibrary;

					FStructProperty* DataProperty = PropertyLibrary::FindStructPropertyByName<DataContainerType>(RowStruct, Name::Data);

					if (!DataProperty)
					{	
						FCsLog::Warning(FString::Printf(TEXT("%s: Failed to find StructProperty: Data in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
					}

					// Check which rows from the DataTable have been loaded	
				#if WITH_EDITOR
					typedef NCsWorld::FLibrary WorldLibrary;

					if (WorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
					{
						if (ICsGetPersistentObjects* GetPersistentObjects = Cast<ICsGetPersistentObjects>(MyRoot))
						{
							GetPersistentObjects->GetPersistentObjects().Add(DataTable);
						}
					}
				#endif // #if WITH_EDITOR

					const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						const FName& RowName = Pair.Key;
						uint8* RowPtr		 = nullptr;

					#if WITH_EDITOR
						if (WorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
						{
							RowPtr = Pair.Value;
						}
						else
					#endif // #if WITH_EDITOR
						{
							typedef NCsData::NManager::FLibrary DataManagerLibrary;

							RowPtr = DataManagerLibrary::GetSafeDataTableRow(Context, MyRoot, DataTableSoftObject, RowName, nullptr);
						}

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

						#if WITH_EDITOR
							if (WorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
							{
								if (ICsGetPersistentObjects* GetPersistentObjects = Cast<ICsGetPersistentObjects>(MyRoot))
								{
									GetPersistentObjects->GetPersistentObjects().Add(O);
								}
							}
						#endif // #if WITH_EDITOR

							typedef NCsData::FLibrary DataLibrary;

							InterfaceDataType* IData = DataLibrary::GetChecked<InterfaceDataType>(Context, O);

							DataMap.Add(RowName, IData);
						}
					}
				}

			public:

				template<typename DataSliceType, typename EnumMapType>
				DataSliceType* SafeConstructData(const FString& Context, const FString& Name, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					static_assert(!std::is_abstract<DataSliceType>(), "NCsData::NManager::NHandler::TData: DataSliceType IS abstract.");

					static_assert(std::is_base_of<InterfaceDataType, DataSliceType>(), "NCsData::NManager::NHandler::TData: DataSliceType is NOT a child of: InterfaceDataType.");

					const FName Name_Internal = FName(*Name);

					if (Name.IsEmpty())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name is EMPTY."), *Context));
						return nullptr;
					}

					if (Name_Internal == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					if (ImplDataMap.Find(Name_Internal))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data has already been created for %s."), *Context, *Name));
						return nullptr;
					}

					if (ImplDataInterfaceMap.Find(Name_Internal))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Impl Interface Map has already been created for %s."), *Context, *Name));
						return nullptr;
					}

					if (EnumMapType::Get().IsValidEnum(Name_Internal))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s::%s already exists."), *Context, *(EnumMapType::Get().GetEnumName()), *Name));
						return nullptr;
					}

					// Construct the slice
					DataSliceType* Data = new DataSliceType();

					ImplDataMap.Add(Name_Internal, Data);
					// Construct Map to store all slices
					DataInterfaceMapType* ImplInterfaceMap = new DataInterfaceMapType();

					ImplDataInterfaceMap.Add(Name_Internal, ImplInterfaceMap);

					FCsInterfaceMap* InterfaceMap = ImplInterfaceMap->GetInterfaceMap();
					// Add slice as type InterfaceDataType
					InterfaceMap->Add<InterfaceDataType>(DataSliceType::Name, static_cast<InterfaceDataType*>(Data));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Data->SetInterfaceMap(InterfaceMap);
					// Store a reference to the slice 
					TMap<FName, void*>& InterfaceImplMap = ImplDataSliceByNameMap.FindOrAdd(Name_Internal);
					InterfaceImplMap.Add(DataSliceType::Name, Data);
					// Add the "base" slice to the map of all data.
					DataMap.Add(Name_Internal, Data);
					// Add deconstruct function pointer for slice.
					TMap<FName, void(*)(void*)>& ImplDataDeconstructMap = ImplDataDeconstructByNameMap.FindOrAdd(Name_Internal);
					ImplDataDeconstructMap.Add(DataSliceType::Name, &DataSliceType::Deconstruct);
					// Add Enum with name: Name.
					EnumMapType::Get().Create(Name, true);

					return Data;
				}

				template<typename DataSliceType, typename InterfaceDataSliceType>
				DataSliceType* AddSafeDataSlice(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					static_assert(!std::is_abstract<DataSliceType>(), "NCsData::NManager::NHandler::TData: DataSliceType IS abstract.");

					static_assert(std::is_abstract<InterfaceDataSliceType>(), "NCsData::NManager::NHandler::TData: InterfaceDataSliceType is NOT abstract.");

					static_assert(std::is_base_of<InterfaceDataSliceType, DataSliceType>(), "NCsData::NManager::NHandler::TData: DataSliceType is NOT a child of: InterfaceDataSliceType.");

					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					if (!ImplDataMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data has NOT been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					if (!ImplDataInterfaceMap.Find(Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Emulated Interface Map has NOT been created for %s."), *Context, *(Name.ToString())));
						return nullptr;
					}

					// Construct the slice
					DataSliceType* Data = new DataSliceType();

					DataInterfaceMapType* ImplInterfaceMap = ImplDataInterfaceMap[Name];
					FCsInterfaceMap* InterfaceMap		   = ImplInterfaceMap->GetInterfaceMap();
					// Add slice as type InterfaceDataType
					InterfaceMap->Add<InterfaceDataSliceType>(DataSliceType::Name, static_cast<InterfaceDataSliceType*>(Data));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Data->SetInterfaceMap(InterfaceMap);
					// Store a reference to the slice 
					TMap<FName, void*>& InterfaceImplMap = ImplDataSliceByNameMap.FindOrAdd(Name);
					InterfaceImplMap.Add(DataSliceType::Name, Data);
					// Add deconstruct function pointer for slice.
					TMap<FName, void(*)(void*)>& ImplDataDeconstructMap = ImplDataDeconstructByNameMap.FindOrAdd(Name);
					ImplDataDeconstructMap.Add(DataSliceType::Name, &DataSliceType::Deconstruct);

					return Data;
				}

				FORCEINLINE InterfaceDataType* GetData(const FString& Context, const FName& Name)
				{
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

					// Check implemented data
					if (InterfaceDataType** ImplDataPtr = ImplDataMap.Find(Name))
						return *ImplDataPtr;

					// Check data
					if (InterfaceDataType** DataPtr = DataMap.Find(Name))
						return *DataPtr;

					return nullptr;
				}

				FORCEINLINE const InterfaceDataType* GetData(const FString& Context, const FName& Name) const
				{
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

					// Check implemented data
					if (const InterfaceDataType* const * ImplDataPtr = ImplDataMap.Find(Name))
						return *ImplDataPtr;

					// Check data
					if (const InterfaceDataType* const * DataPtr = DataMap.Find(Name))
						return *DataPtr;

					return nullptr;
				}

				FORCEINLINE InterfaceDataType* GetDataChecked(const FString& Context, const FName& Name)
				{
					InterfaceDataType* Ptr = GetData(Context, Name);

					checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString()));

					return Ptr;
				}

				FORCEINLINE const InterfaceDataType* GetDataChecked(const FString& Context, const FName& Name) const
				{
					const InterfaceDataType* Ptr = GetData(Context, Name);

					checkf(Ptr, TEXT("%s: Failed to find a Data associated with Name: %s."), *Context, *(Name.ToString()));

					return Ptr;
				}

				FORCEINLINE InterfaceDataType* GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning)
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

				FORCEINLINE const InterfaceDataType* GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning) const
				{
					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					const InterfaceDataType* Ptr = GetData(Context, Name);

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
				FORCEINLINE const InterfaceDataType* GetData(const FString& Context, const EnumType& Type) const
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
				FORCEINLINE const InterfaceDataType* GetDataChecked(const FString& Context, const EnumType& Type) const
				{
					const InterfaceDataType* Ptr = GetData<EnumMap, EnumType>(Context, Type);

					checkf(Ptr, TEXT("%s: Failed to find a Data associated with Type: %s."), *Context, Type.ToChar());

					return Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceDataType* GetSafeData(const FString& Context, const EnumType& Type, void(*Log)(const FString&) = &FCsLog::Warning)
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

				template<typename EnumMap, typename EnumType>
				FORCEINLINE const InterfaceDataType* GetSafeData(const FString& Context, const EnumType& Type, void(*Log)(const FString&) = &FCsLog::Warning) const
				{
					if (!EnumMap::Get().IsValidEnum(Type))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar()));
						return nullptr;
					}

					const InterfaceDataType* Ptr = GetData<EnumMap, EnumType>(Context, Type);

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Data associated with Type: %s."), *Context, Type.ToChar()));
					}
					return Ptr;
				}

				FORCEINLINE DataInterfaceMapType* GetSafeDataInterfaceMap(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					InterfaceDataType* Data = GetSafeData(Context, Name, Log);

					if (!Data)
						return nullptr;

					DataInterfaceMapType** Ptr = ImplDataInterfaceMap.Find(Name);

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find DataInterfaceMap for Data with Name: %s."), *Context, *(Name.ToString())));
					}
					return *Ptr;
				}

				FORCEINLINE const DataInterfaceMapType* GetSafeDataInterfaceMap(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning) const
				{
					if (Name == NAME_None)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return nullptr;
					}

					const InterfaceDataType* Data = GetSafeData(Context, Name, Log);

					if (!Data)
						return nullptr;

					const DataInterfaceMapType* const* Ptr = ImplDataInterfaceMap.Find(Name);

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find DataInterfaceMap for Data with Name: %s."), *Context, *(Name.ToString())));
					}
					return *Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE const EnumType& GetTypeChecked(const FString& Context, const InterfaceDataType* Data) const
				{
					for (const TPair<FName, InterfaceDataType*>& Pair : DataMap)
					{
						if (Data == Pair.Value)
						{
							return EnumMap::Get().GetEnum(Pair.Key);
						}
					}
					checkf(0, TEXT("%s: Failed to get Type associated with Data."), *Context);
					return EnumMap::Get().GetMAX();
				}

				void RemapDataMap(const FString& Context)
				{
					typedef NCsData::FLibrary DataLibrary;

					for (const TPair<FName, UObject*>& Pair : DataAsUObjectMap)
					{
						const FName& EntryName = Pair.Key;
						UObject* O			   = Pair.Value;

						InterfaceDataType* IData = DataLibrary::GetChecked<InterfaceDataType>(Context, O);

						DataMap[EntryName] = IData;
					}
				}

			protected:

				void ResetDataContainers()
				{
					for (TPair<FName, TMap<FName, void*>>& DataPair : ImplDataSliceByNameMap)
					{
						const FName& DataName				= DataPair.Key;
						TMap<FName, void*> InterfaceImplMap = DataPair.Value;

						for (TPair<FName, void*>& ImplPair : InterfaceImplMap)
						{
							const FName& ImplName = ImplPair.Key;

							void(*DeconstructImpl)(void*) = ImplDataDeconstructByNameMap[DataName][ImplName];

							checkf(DeconstructImpl, TEXT("Failed to find DeconstructImpl for DataName: %s InterfaceImplName: %s."), *(DataName.ToString()), *(ImplName.ToString()));

							DeconstructImpl(ImplPair.Value);

							ImplPair.Value = nullptr;
						}
					}
					ImplDataMap.Reset();
					ImplDataSliceByNameMap.Reset();

					for (TPair<FName, DataInterfaceMapType*>& Pair : ImplDataInterfaceMap)
					{
						DataInterfaceMapType* Ptr = Pair.Value;
						delete Ptr;
						Pair.Value = nullptr;
					}
					ImplDataInterfaceMap.Reset();

					DataMap.Reset();
					DataTableRowByPathMap.Reset();
				}
			};
		}
	}
}