// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// Sound
#pragma region

namespace NCsSound
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsSound::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Enum Settings
			if (Settings->ECsSound_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsSound>();
				const FString& EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsSound>();

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

						checkf(!EMCsSound::Get().IsValidEnum(Name), TEXT("%s: Sound (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsSound::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Sound (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsSound::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsSound::Get().Create(Name, true);
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
				for (TSoftObjectPtr<UDataTable>& SoftObjectPtr : Settings->Sounds)
				{
					// Check DataTable of Projectiles
					TSoftObjectPtr<UDataTable> DT_SoftObject = SoftObjectPtr;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct	  = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
						{
							// Set if the Row Struct has the properties Name and DisplayName
	
							FStrProperty* NameProperty		  = CastField<FStrProperty>(RowStruct->FindPropertyByName(FName("Name")));
							NameProperty					  = NameProperty ? NameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
							FStrProperty* DisplayNameProperty = CastField<FStrProperty>(RowStruct->FindPropertyByName(FName("DisplayName")));
							DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty: CastField<FStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

							if (NameProperty &&
								DisplayNameProperty)
							{
								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;
									const uint8* RowPtr = Pair.Value;

									const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
									const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

									checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Sound Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

									checkf(!EMCsSound::Get().IsValidEnum(Name), TEXT("%s: Sound (Name): %s already exists (declared in native)."), *Context, *Name);

									if (!DisplayName.IsEmpty())
									{
										checkf(!EMCsSound::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Sound (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

										EMCsSound::Get().Create(Name, DisplayName, true);
									}
									else
									{
										EMCsSound::Get().Create(Name, true);
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

#pragma endregion Sound

// SoundPriority
#pragma region

namespace NCsSoundPriority
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, VeryLow, "Very Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, Low);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, High);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, VeryHigh, "Very High");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, ECsSoundPriority_MAX, "MAX");
	}
}

#pragma endregion SoundPriority

// SoundDeallocateMethod
#pragma region

namespace NCsSoundDeallocateMethod
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundDeallocateMethod, LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundDeallocateMethod, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundDeallocateMethod, ECsSoundDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSoundDeallocateMethod_MAX;
}

#pragma endregion SoundDeallocateMethod