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
			EMCsFX::Get().ClearUserDefinedEnums();

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString& EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

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

// FXPriority
#pragma region

namespace NCsFXPriority
{
	namespace Ref
	{
		typedef EMCsFXPriority EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Low);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(High);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXPriority_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXPriority_MAX;
}

#pragma endregion FXPriority

// FXDeallocateMethod
#pragma region

namespace NCsFXDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsFXDeallocateMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXDeallocateMethod_MAX;
}

#pragma endregion FXDeallocateMethod

// FXAttachPoint
#pragma region

namespace NCsFXAttachPoint
{
	namespace Ref
	{
		typedef EMCsFXAttachPoint EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Bone);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Socket);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXAttachPoint_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXAttachPoint_MAX;
}

#pragma endregion FXAttachPoint

// FCsFX
#pragma region

bool FCsFX::IsValidChecked(const FString& Context) const
{
	// Check FX is Valid.
	check(GetChecked(Context));
	// Check Type is Valid
	check(EMCsFX::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

#pragma endregion FCsFX