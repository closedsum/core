// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsLibrary_EnumStruct.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Settings
#include "Settings/CsLibrary_DataSettings.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Engine
#include "Engine/DataTable.h"

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NPopulate
		{
			const FName FLibrary::NamePropertyName = FName("Name");
			const FName FLibrary::DisplayNamePropertyName = FName("DisplayName");

			UObject* FLibrary::GetDataRootSetImpl(const FString& Context, UObject* ContextRoot)
			{
				// Check context to determine how to load DataRootSetImpl
				if (CsGameInstanceLibrary::IsSafe(ContextRoot))
				{
					return CsDataManagerLibrary::GetDataRootSetImplChecked(Context, ContextRoot);
				}
				else
				{
					// TODO: NOTE: Should this be checked?
					typedef NCsData::NSettings::FLibrary SettingsLibrary;

					TSoftClassPtr<UObject> SoftObject = SettingsLibrary::GetDataRootSet();
					UClass* Class					  = SoftObject.LoadSynchronous();
					return Class ? Class->GetDefaultObject() : nullptr;
				}
			}

			const FCsDataRootSet* FLibrary::GetDataRootSet(const FString& Context, UObject* ContextRoot)
			{
				return GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);
			}

			UDataTable* FLibrary::GetDataTable(const FString& Context, const UObject* ContextRoot, const TSoftObjectPtr<UDataTable>& DT_SoftObject)
			{
				// Check context to determine how to load the DataTable
				if (CsGameInstanceLibrary::IsSafe(ContextRoot))
				{
					return CsDataManagerLibrary::GetDataTableChecked(Context, ContextRoot, DT_SoftObject);
				}
				else
				{
					return DT_SoftObject.LoadSynchronous();
				}
			}

			UDataTable* FLibrary::GetDataTable(const FString& Context, const FName& DataTableName)
			{
				const FCsDataRootSet* DataRootSet = GetDataRootSet(Context, nullptr);

				if (!DataRootSet)
					return nullptr;

				return DataRootSet->GetDataTableChecked(Context, DataTableName);
			}

			using PayloadType = NCsEnum::NStruct::NPopulate::FLibrary::FFromDataTable::FPayload;

			void FLibrary::FromDataTable(const FString& Context, PayloadType& Payload)
			{
				UDataTable* DataTable		= Payload.DataTable ? Payload.DataTable : GetDataTable(Context, Payload.ContextRoot, Payload.DataTableSoftObject);
				const FString& EnumName		= Payload.EnumName;
				void(*Log)(const FString&)  = Payload.Log;

				const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
				{
					// Set if the Row Struct has the properties Name and DisplayName

					FStrProperty* NameProperty		  = CastField<FStrProperty>(RowStruct->FindPropertyByName(NamePropertyName));
					NameProperty					  = NameProperty ? NameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(NamePropertyName));
					FStrProperty* DisplayNameProperty = CastField<FStrProperty>(RowStruct->FindPropertyByName(DisplayNamePropertyName));
					DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(DisplayNamePropertyName));

					if (NameProperty &&
						DisplayNameProperty)
					{
						if (RowMap.Num() == CS_EMPTY)
						{
							CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
						}

						const FName Name_NewRow = FName("NewRow");

						for (const TPair<FName, uint8*>& Pair : RowMap)
						{
							const FName& RowName = Pair.Key;
							const uint8* RowPtr  = Pair.Value;

							const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
							const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

							// If Making a New Row, skip
							if (RowName == Name_NewRow &&
								Name.IsEmpty() &&
								DisplayName.IsEmpty())
							{
								continue;
							}

							checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);
							checkf(!Payload.IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

							if (!DisplayName.IsEmpty())
							{
								checkf(!Payload.IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

								Payload.CreateCustom(Name, DisplayName, true);
							}
							else
							{
								Payload.Create(Name, true);
							}
						}
					}
					else
					{
						CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()))));
					}
				}
			}

			void FLibrary::FromDataTable_RowAsName(const FString& Context, PayloadType Payload)
			{
				UDataTable* DataTable		= Payload.DataTable ? Payload.DataTable : GetDataTable(Context, Payload.ContextRoot, Payload.DataTableSoftObject);
				const FString& EnumName		= Payload.EnumName;
				void(*Log)(const FString&)  = Payload.Log;

				const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
				{
					if (RowMap.Num() == CS_EMPTY)
					{
						CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
					}

					const FName Name_NewRow = FName("NewRow");
					FString Name;
					FString DisplayName;

					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						const FName& RowName = Pair.Key;
						const uint8* RowPtr  = Pair.Value;

						Name		= RowName.ToString();
						DisplayName = Name;

						// If Making a New Row, skip
						if (RowName == Name_NewRow &&
							Name.IsEmpty() &&
							DisplayName.IsEmpty())
						{
							continue;
						}

						checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);
						checkf(!Payload.IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

						if (!DisplayName.IsEmpty())
						{
							checkf(!Payload.IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

							Payload.CreateCustom(Name, DisplayName, true);
						}
						else
						{
							Payload.Create(Name, true);
						}
					}
				}
			}
		}
	}
}

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			void(*FLibrary::ConditionalAddLayout)(const FName& /*EnumName*/, const TArray<FName>& /*Names*/, UDataTable* /*DataTable*/) = nullptr;

			void(*FLibrary::AddPropertyChange)(const FName& /*EnumName*/, UStruct* /*EnumStruct*/) = nullptr;

			void FLibrary::CheckChange()
			{
				
			}
		}
	}
}