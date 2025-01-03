// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Misc.h"
// Library
	// Manager
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Common
#include "Library/CsLibrary_Property.h"
// Engine
#include "Engine/DataTable.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Containers
#include "Containers/CsGetPersistentObjects.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

#pragma endregion Cached

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
				namespace Name
				{
					extern CSDATA_API const FName Class;
				}
			}

			/**
			*/
			template<typename InterfaceContainerType, typename InterfaceUStructContainerType, typename EnumClassType>
			class TClass
			{
			public:

				TClass() :
					Outer(nullptr),
					MyRoot(nullptr),
					ClassByTypeMap(),
					ClassByClassTypeMap()
				{
				}

				virtual ~TClass()
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
				TMap<FName, InterfaceContainerType> ClassByTypeMap;

				/** */
				TMap<FName, InterfaceContainerType> ClassByClassTypeMap;

			public:

				virtual void PopulateClassMapFromSettings(const FString& Context)
				{
					using namespace NCached;

					// Reset appropriate containers
					ResetClassContainers();

					// Get Classes DataTable
					{
						UDataTable* DataTable = nullptr;
						TSoftObjectPtr<UDataTable> DataTableSoftObject(nullptr);

						GetClassesDataTableChecked(Context, DataTable, DataTableSoftObject);

						const UScriptStruct* RowStruct = DataTable->GetRowStruct();

						// Get the Property named "Class" if it exists.

						FStructProperty* ClassProperty = CsPropertyLibrary::FindStructPropertyByName<InterfaceUStructContainerType>(RowStruct, Name::Class);

						if (!ClassProperty)
						{
						#if !UE_BUILD_SHIPPING
							NCsData::FLog::Warning(FString::Printf(TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
						#endif // #if !UE_BUILD_SHIPPING
							return;
						}

						// Cache any class related information that is loaded.
					#if WITH_EDITOR
						if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
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
							if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
							{
								RowPtr = Pair.Value;
							}
							else
						#endif // #if WITH_EDITOR
							{
								RowPtr = CsDataManagerLibrary::GetSafeDataTableRow(Context, MyRoot, DataTableSoftObject, RowName, nullptr);
							}

							if (!RowPtr)
								continue;

							// If Property named "Class" exists, cache the class.
							if (ClassProperty)
							{
								InterfaceUStructContainerType* StructPtr = ClassProperty->ContainerPtrToValuePtr<InterfaceUStructContainerType>(RowPtr);

								checkf(StructPtr, TEXT("%s: StructPtr is NULL. Failed to get pointer from Property: Class of type EnumClassType."), *Context);

								UObject* O = StructPtr->Get();

								checkf(O, TEXT("%s: Failed to get character from DataTable: %s: Row: %s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));

							#if WITH_EDITOR
								if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
								{
									if (ICsGetPersistentObjects* GetPersistentObjects = Cast<ICsGetPersistentObjects>(MyRoot))
									{
										GetPersistentObjects->GetPersistentObjects().Add(O);
									}
								}
							#endif // #if WITH_EDITOR

								InterfaceContainerType& Container = ClassByClassTypeMap.Add(RowName);

								Container.SetObject(O);
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

							FStructProperty* ClassProperty = CsPropertyLibrary::FindStructPropertyByName<EnumClassType>(RowStruct, Name::Class);

							if (!ClassProperty)
							{
							#if !UE_BUILD_SHIPPING
								NCsData::FLog::Warning(FString::Printf(TEXT("%s: Failed to find StructProperty: Class in DataTable: %s with Struct: %s"), *Context, *(DataTable->GetName()), *(RowStruct->GetName())));
							#endif // #if !UE_BUILD_SHIPPING
								return;
							}

							// Cache any class related information that is loaded.
						#if WITH_EDITOR
							if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
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
								uint8* RowPtr = nullptr;

							#if WITH_EDITOR
								if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
								{
									RowPtr = Pair.Value;
								}
								else
							#endif // #if WITH_EDITOR
								{
									RowPtr = CsDataManagerLibrary::GetSafeDataTableRow(Context, MyRoot, DataTableSoftObject, RowName, nullptr);
								}

								if (!RowPtr)
									continue;

								// If Property named "Class" exists, cache the class.
								if (ClassProperty)
								{
									EnumClassType* StructPtr = ClassProperty->ContainerPtrToValuePtr<EnumClassType>(RowPtr);

									checkf(StructPtr, TEXT("%s: StructPtr is NULL. Failed to get pointer from Property: Class of type EnumClassType."), *Context);

									InterfaceContainerType* ContainerPtr = ClassByClassTypeMap.Find(StructPtr->GetFName());

									checkf(ContainerPtr, TEXT("%s: ContainerPtr is NULL. Failed to find class of class type: %s"), *Context, StructPtr->ToChar());

									InterfaceContainerType& Container = ClassByTypeMap.Add(RowName);

								#if WITH_EDITOR
									if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(MyRoot))
									{
										if (ICsGetPersistentObjects* GetPersistentObjects = Cast<ICsGetPersistentObjects>(MyRoot))
										{
											GetPersistentObjects->GetPersistentObjects().Add(ContainerPtr->GetObject());
										}
									}
								#endif // #if WITH_EDITOR

									Container.SetObject(ContainerPtr->GetObject());
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
				FORCEINLINE InterfaceContainerType* GetClassByType(const FString& Context, const EnumType& Type)
				{
					check(EnumMap::Get().IsValidEnumChecked(Context, Type));

					return ClassByTypeMap.Find(Type.GetFName());
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceContainerType* GetClassByTypeChecked(const FString& Context, const EnumType& Type)
				{
					InterfaceContainerType* Ptr = GetClassByType<EnumMap, EnumType>(Context, Type);

					checkf(Ptr, TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar());

					return Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE InterfaceContainerType* GetSafeClassByType(const FString& Context, const EnumType& Type, void(*Log)(const FString&) = &NCsData::FLog::Warning)
				{
					if (!EnumMap::Get().IsValidEnum(Type))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar()));
						return nullptr;
					}

					InterfaceContainerType* Ptr = ClassByTypeMap.Find(Type.GetFName());

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar()));
					}
					return Ptr;
				}

				template<typename EnumClassMap>
				FORCEINLINE InterfaceContainerType* GetClassByClassType(const FString& Context, const EnumClassType& Type)
				{
					check(EnumClassMap::Get().IsValidEnumChecked(Context, Type));

					return ClassByClassTypeMap.Find(Type.GetFName());
				}

				template<typename EnumClassMap>
				FORCEINLINE InterfaceContainerType* GetClassByClassTypeChecked(const FString& Context, const EnumClassType& Type)
				{
					InterfaceContainerType* Ptr = GetClassByClassType<EnumClassMap>(Context, Type);

					checkf(Ptr, TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar());

					return Ptr;
				}

				template<typename EnumClassMap>
				FORCEINLINE InterfaceContainerType* GetSafeClassByClassType(const FString& Context, const EnumClassType& Type, void(*Log)(const FString&) = &NCsData::FLog::Warning)
				{
					if (!EnumClassMap::Get().IsValidEnum(Type))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar()));
						return nullptr;
					}

					InterfaceContainerType* Ptr = ClassByClassTypeMap.Find(Type.GetFName());

					if (!Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find a Class associated with Type: %s."), *Context, Type.ToChar()));
					}
					return Ptr;
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE void AddClassByTypeChecked(const FString& Context, const EnumType& Type, UObject* Class)
				{
					InterfaceContainerType* Ptr = GetClassByType<EnumMap, EnumType>(Context, Type);

					checkf(!Ptr, TEXT("%s: Class associated with Type: %s ALREADY exists."), *Context, Type.ToChar());

					checkf(Class, TEXT("%s: Class is NULL."), *Context);

					InterfaceContainerType& Container = ClassByTypeMap.Add(Type.GetFName());

					Container.SetObject(Class);
				}

				template<typename EnumMap, typename EnumType>
				FORCEINLINE bool SafeAddClassByType(const FString& Context, const EnumType& Type, UObject* Class, void(*Log)(const FString&) = &NCsData::FLog::Warning)
				{
					InterfaceContainerType* Ptr = GetSafeClassByType<EnumMap, EnumType>(Context, Type, nullptr);

					if (Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Class associated with Type: %s ALREADY exists."), *Context, Type.ToChar()));
						return false;
					}

					if (!Class)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Class is NULL."), *Context));
						return false;
					}

					InterfaceContainerType& Container = ClassByTypeMap.Add(Type.GetFName());

					Container.SetObject(Class);
					return true;
				}

				template<typename EnumClassMap>
				FORCEINLINE void AddClassByClassTypeChecked(const FString& Context, const EnumClassType& Type, UObject* Class)
				{
					InterfaceContainerType* Ptr = GetClassByClassType<EnumClassMap, EnumClassType>(Context, Type);

					checkf(!Ptr, TEXT("%s: Class associated with Class Type: %s ALREADY exists."), *Context, Type.ToChar());

					checkf(Class, TEXT("%s: Class is NULL."), *Context);

					InterfaceContainerType& Container = ClassByClassTypeMap.Add(Type.GetFName());

					Container.SetObject(Class);
				}

				template<typename EnumClassMap>
				FORCEINLINE bool SafeAddClassByClassType(const FString& Context, const EnumClassType& Type, UObject* Class, void(*Log)(const FString&) = &NCsData::FLog::Warning)
				{
					InterfaceContainerType* Ptr = GetSafeClassByClassType<EnumClassMap>(Context, Type, nullptr);

					if (Ptr)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Class associated with Class Type: %s ALREADY exists."), *Context, Type.ToChar()));
						return false;
					}

					if (!Class)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Class is NULL."), *Context));
						return false;
					}

					InterfaceContainerType& Container = ClassByClassTypeMap.Add(Type.GetFName());

					Container.SetObject(Class);
					return true;
				}

			protected:

				void ResetClassContainers()
				{
					ClassByTypeMap.Reset();
					ClassByClassTypeMap.Reset();
				}

			#pragma endregion Class
			};
		}
	}
}