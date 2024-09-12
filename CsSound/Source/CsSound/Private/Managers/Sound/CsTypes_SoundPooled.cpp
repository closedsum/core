// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "CsSound.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsSoundSettings.h"
// DataTable
#include "Engine/DataTable.h"
// Sound
#include "Sound/SoundBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_SoundPooled)

// Sound
#pragma region

namespace NCsSound
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsSoundSettings* Settings = GetMutableDefault<UCsSoundSettings>())
		{
			EMCsSound::Get().ClearUserDefinedEnums();

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
							UE_LOG(LogCsSound, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
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
					UE_LOG(LogCsSound, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
				}
			}

			// DataTable
			if (Settings->ECsSound_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
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
								UE_LOG(LogCsSound, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCsSound, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
	}
}

#pragma endregion Sound

// FCsSound
#pragma region

USoundBase* FCsSound::SafeLoad(const FString& Context) const
{
	if (!Sound.ToSoftObjectPath().IsValid())
	{
		UE_LOG(LogCsSound, Warning, TEXT("%s: Sound is NULL or the Path is NOT Valid."), *Context);
		return nullptr;
	}

	TSoftObjectPtr<USoundBase> SoftObject = Sound;

	USoundBase* S = SoftObject.LoadSynchronous();

	if (!S)
	{
		UE_LOG(LogCsSound, Warning, TEXT("%s: Failed to load Sound @ %s."), *Context, *(Sound.ToSoftObjectPath().ToString()));
	}
	return S;
}

bool FCsSound::IsValidChecked(const FString& Context) const
{
	// Check Sound is Valid.
	check(GetChecked(Context));
	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSound, Type)
	
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(DurationMultiplier, 1.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(FadeInTime, 0.0f)

	if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(LifeTime, FadeInTime)
	}

	if (!Transform.Equals(FTransform3f::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

bool FCsSound::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Sound Path is Valid.
	if (!Sound.ToSoftObjectPath().IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Sound is NULL."), *Context));
		return false;
	}
	// Check Sound is Valid.
	if (!Sound_Internal)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Sound has NOT been loaded from Path @ %s."), *Context, *(Sound.ToSoftObjectPath().ToString())));
		return false;
	}
	// Check Type is Valid.
	if (!EMCsSound::Get().IsValidEnum(Type))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s Type: %s is NOT Valid."), *Context, Type.ToChar()));
		return false;
	}

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(DurationMultiplier, 1.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(FadeInTime, 0.0f)

	if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(LifeTime, FadeInTime)
	}

	if (!Transform.Equals(FTransform3f::Identity) &&
		TransformRules == 0)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
		return false;
	}
	return true;
}

void FCsSound::Reset()
{
	Sound = nullptr;
	Sound_LoadFlags = 0;
	Sound_Internal = nullptr;
	Type = EMCsSound::Get().GetMAX();
	Attenuation = nullptr;
	Attenuation_LoadFlags = 0;
	Attenuation_Internal = nullptr;
	DeallocateMethod = ECsSoundDeallocateMethod::Complete;
	LifeTime = 0.0f;
	DurationMultiplier = 1.0f;
	AttachmentTransformRules = FCsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 7; // NCsTransformRules::All
	Transform = FTransform3f::Identity;
}

#pragma endregion FCsSound

// SoundPayloadChange
#pragma region

namespace NCsSoundPayloadChange
{
	namespace Ref
	{
		typedef EMCsSoundPayloadChange EnumMapType;

		CSSOUND_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSSOUND_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSSOUND_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSSOUND_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSSOUND_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
	}

	CSSOUND_API const int32 None = 0;
	CSSOUND_API const int32 All = 31; // 1 + 2 + 4 + 8 + 16
}

#pragma endregion SoundPayloadChange