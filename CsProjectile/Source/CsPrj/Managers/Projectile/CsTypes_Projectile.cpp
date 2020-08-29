// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsPrj.h"

// Data
#include "Data/CsPrjGetDataRootSet.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsProjectileSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

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
	namespace Str
	{
		const FString Projectile = TEXT("Projectile");
	}

	const FCsPrjDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsPrjDataRootSet, ICsPrjGetDataRootSet, UCsProjectileSettings>(Context, ContextRoot);
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsProjectileSettings, EMCsProjectile, FECsProjectile>(Context, Str::Projectile, &Log);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsPrjDataRootSet* DataRootSet = GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet->Projectiles)
		{
			FCsPopulateEnumMapFromSettings::FromDataTable<EMCsProjectile>(Context, ContextRoot, Projectiles.Projectiles, Str::Projectile, &Log);
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

#if WITH_EDITOR
		EMCsProjectile::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsProjectile_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsProjectile_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}

	void Log(const FString& Str)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s"), *Str);
	}
}

#pragma endregion Projectile

// ProjectileClass
#pragma region

namespace NCsProjectileClass
{
	namespace Str
	{
		const FString ProjectileClass = TEXT("ProjectileClass");
	}

	const FCsPrjDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsPrjDataRootSet, ICsPrjGetDataRootSet, UCsProjectileSettings>(Context, ContextRoot);
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsProjectileSettings, EMCsProjectileClass, FECsProjectileClass>(Context, Str::ProjectileClass, &Log);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsPrjDataRootSet* DataRootSet = GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsProjectileClass>(Context, ContextRoot, DataRootSet->ProjectileClasses, Str::ProjectileClass, &Log);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

#if WITH_EDITOR
		EMCsProjectileClass::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}

	void Log(const FString& Str)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s"), *Str);
	}
}

#pragma endregion ProjectileClass

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

// ProjectileData
#pragma region

namespace NCsProjectileData
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, Projectile, "ICsData_Projectile");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileCollision, "ICsData_ProjectileCollision");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileStaticMeshVisual, "ICsData_ProjectileStaticMeshVisual");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileTrailVisual, "ICsData_ProjectileTrailVisual");
}

#pragma endregion ProjectileData