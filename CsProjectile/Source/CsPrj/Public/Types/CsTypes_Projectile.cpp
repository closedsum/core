// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile.h"
#include "CsPrj.h"

// Data
#include "Data/CsPrjGetDataRootSet.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsProjectileSettings.h"
// Utility
#include "Utility/CsPrjLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsPrjPopulateEnumMapFromSettings.h"
// Projectile
#include "Payload/CsPayload_ProjectilePooledImpl.h"

// ProjectileRelevance
#pragma region

namespace NCsProjectileRelevance
{
	namespace Ref
	{
		typedef EMCsProjectileRelevance EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(RealVisible, "Real Visible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(RealInvisible, "Real Invisible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Fake);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileRelevance_MAX, "MAX");
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

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsProjectileSettings, EMCsProjectile, FECsProjectile>(Context, Str::Projectile, &NCsProjectile::FLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsPrjDataRootSet* DataRootSet = FCsPrjPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet->Projectiles)
		{
			FCsPopulateEnumMapFromSettings::FromDataTable<EMCsProjectile>(Context, ContextRoot, Projectiles.Projectiles, Str::Projectile, &NCsProjectile::FLog::Warning);
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

		EMCsProjectile::Get().ClearUserDefinedEnums();

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

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsProjectileSettings, EMCsProjectileClass, FECsProjectileClass>(Context, Str::ProjectileClass, &NCsProjectile::FLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsPrjDataRootSet* DataRootSet = FCsPrjPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsProjectileClass>(Context, ContextRoot, DataRootSet->ProjectileClasses, Str::ProjectileClass, &NCsProjectile::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

		EMCsProjectileClass::Get().ClearUserDefinedEnums();

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
}

#pragma endregion ProjectileClass

// ProjectileState
#pragma region

namespace NCsProjectileState
{
	namespace Ref
	{
		typedef EMCsProjectileState EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Active);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(DeActivating);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(InActive);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileState_MAX, "MAX");
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
		typedef EMCsProjectileDeActivate EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Collision);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Movement);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Mesh);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileDeActivate_MAX, "MAX");
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
		typedef EMCsProjectileMovement EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Simulated);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Function);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileMovement_MAX,"MAX");
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
		typedef EMCsProjectileMovementFunctionType EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Linear);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Sine);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileMovementFunctionType_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovementFunctionType_MAX;
}

#pragma endregion ProjectileMovementFunctionType

// ProjectileData
#pragma region

namespace NCsProjectileData
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(Projectile, "ICsData_Projectile");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileCollision, "ICsData_Projectile_Collision");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileStaticMeshVisual, "ICsData_Projectile_VisualStaticMesh");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileTrailVisual, "ICsData_Projectile_VisualTrail");
}

#pragma endregion ProjectileData

// FCsPayload_Projectile
#pragma region

#define PayloadType NCsProjectile::NPayload::FImplPooled
void FCsPayload_Projectile::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->Instigator = Instigator;
	Payload->Owner = Owner;
	Payload->Parent = Parent;
	//Payload->Time = Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->Location = Location;
	Payload->Direction = Direction;
}

bool FCsPayload_Projectile::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsPayload_Projectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsPayload_Projectile