// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsPrj.h"

// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Settings
#include "Settings/CsProjectileSettings.h"

// ProjectileRelevance
#pragma region

namespace NCsProjectileRelevance
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealVisible, "Real Visible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealInvisible, "Real Invisible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileRelevance, Fake);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, ECsProjectileRelevance_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileRelevance_MAX;
}

#pragma endregion ProjectileRelevance

// Projectile
#pragma region

namespace NCsProjectile
{
	void PopulateEnumMapFromSettings(const FString& Context)
	{
		if (UCsProjectileSettings* Settings = GetMutableDefault<UCsProjectileSettings>())
		{
			bool PopulatedEnumMap = false;
			 
			// Check DataTable of Projectiles
			TSoftObjectPtr<UDataTable> Projectiles = Settings->Projectiles;

			if (UDataTable* DataTable = Projectiles.LoadSynchronous())
			{
				const UScriptStruct* RowStruct = DataTable->GetRowStruct();

				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

				// See if the Row Struct derives from FCsProjectileEntry
				if (RowStruct->IsChildOf(FCsProjectileEntry::StaticStruct()))
				{
#if WITH_EDITOR
					EMCsProjectile::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						const FName& Name				= Pair.Key;
						const FCsProjectileEntry* Entry = reinterpret_cast<const FCsProjectileEntry*>(Pair.Value);

						checkf(Entry->Name.Compare(Name.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Projectile Name (%s != %s)."), *Context, *(Entry->Name), *(Name.ToString()));

						checkf(!EMCsProjectile::Get().IsValidEnum(Entry->Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *(Entry->Name));

						if (!Entry->DisplayName.IsEmpty())
						{
							checkf(!EMCsProjectile::Get().IsValidEnumByDisplayName(Entry->DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *(Entry->DisplayName));

							EMCsProjectile::Get().Create(Entry->Name, Entry->DisplayName, true);
						}
						else
						{
							EMCsProjectile::Get().Create(Entry->Name, true);
						}
					}
					PopulatedEnumMap = true;
				}
				// Set if the Row Struct has the properties Name and DisplayName
				else
				{
					UStrProperty* NameProperty		  = Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
					UStrProperty* DisplayNameProperty = Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

					if (NameProperty &&
						DisplayNameProperty)
					{
#if WITH_EDITOR
						EMCsProjectile::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

						for (const TPair<FName, uint8*>& Pair : RowMap)
						{
							const FName& RowName = Pair.Key;
							const uint8* RowPtr  = Pair.Value;

							const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
							const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

							checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Projectile Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

							checkf(!EMCsProjectile::Get().IsValidEnum(Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *Name);

							if (!DisplayName.IsEmpty())
							{
								checkf(!EMCsProjectile::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

								EMCsProjectile::Get().Create(Name, DisplayName, true);
							}
							else
							{
								EMCsProjectile::Get().Create(Name, true);
							}
						}
						PopulatedEnumMap = true;
					}
				}

				if (!PopulatedEnumMap)
				{
					checkf(0, TEXT("%s: DataTable: %s with Row Struct: %s does NOT derive from FRsProjectileEntry nor has the FString properties: Name and DisplayName."), *Context, *(DataTable->GetName()), *(RowStruct->GetName()));
				}
			}

			if (!PopulatedEnumMap)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsProjectile>();

				if (Enums.Num() > CS_EMPTY)
				{
					const FString EnumSettingsPath = Settings->GetSettingsEnumPath<FECsProjectile>();

#if WITH_EDITOR
					EMCsProjectile::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name		   = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCsPrj, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsProjectile::Get().IsValidEnum(Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsProjectile::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsProjectile::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsProjectile::Get().Create(Name, true);
						}
					}
				}
			}
		}
	}
}

#pragma endregion Projectile

// ProjectileState
#pragma region

namespace NCsProjectileState
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, Active);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, DeActivating);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, InActive);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileState, ECsProjectileState_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileState_MAX;
}

#pragma endregion ProjectileState

// ProjectileDeActivate
#pragma region

namespace NCsProjectileDeActivate
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Collision);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Movement);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Mesh);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileDeActivate, ECsProjectileDeActivate_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileDeActivate_MAX;
}

#pragma endregion ProjectileDeActivate

// ProjectileMovement
#pragma region

namespace NCsProjectileMovement
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Simulated);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Function);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovement, ECsProjectileMovement_MAX,"MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovement_MAX;
}

#pragma endregion ProjectileMovement

// ProjectileMovementFunctionType
#pragma region

namespace NCsProjectileMovementFunctionType
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Linear);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Sine);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovementFunctionType, ECsProjectileMovementFunctionType_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovementFunctionType_MAX;
}

#pragma endregion ProjectileMovementFunctionType
