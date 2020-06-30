// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FX
#pragma region

namespace NCsFX
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsFX::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

				if (Enums.Num() > CS_EMPTY)
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsFX::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsFX::Get().Create(Name, true);
						}
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
				}
			}

			// DataTable
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
			{
				for (TSoftObjectPtr<UDataTable>& SoftObjectPtr : Settings->FXs)
				{
					// Check DataTable of Projectiles
					TSoftObjectPtr<UDataTable> DT_SoftObject = SoftObjectPtr;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct	  = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
						{
							// Set if the Row Struct has the properties Name and DisplayName
	
							UStrProperty* NameProperty		  = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("Name")));
							NameProperty					  = NameProperty ? NameProperty : Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
							UStrProperty* DisplayNameProperty = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("DisplayName"))); 
							DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty: Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

							if (NameProperty &&
								DisplayNameProperty)
							{
								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;
									const uint8* RowPtr = Pair.Value;

									const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
									const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

									checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != FX Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

									checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

									if (!DisplayName.IsEmpty())
									{
										checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

										EMCsFX::Get().Create(Name, DisplayName, true);
									}
									else
									{
										EMCsFX::Get().Create(Name, true);
									}
								}
							}
							else
							{
								UE_LOG(LogCs, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
	}
}

#pragma endregion FX

// FxPriority
#pragma region

namespace ECsFxPriority
{
	namespace Ref
	{
		CSCORE_API const Type Low = EMCsFxPriority::Get().Add(Type::Low, TEXT("Low"));
		CSCORE_API const Type Medium = EMCsFxPriority::Get().Add(Type::Medium, TEXT("Medium"));
		CSCORE_API const Type High = EMCsFxPriority::Get().Add(Type::High, TEXT("High"));
		CSCORE_API const Type ECsFxPriority_MAX = EMCsFxPriority::Get().Add(Type::ECsFxPriority_MAX, TEXT("ECsFxPriority_MAX"), TEXT("MAX"));
	}
}

#pragma endregion FxPriority