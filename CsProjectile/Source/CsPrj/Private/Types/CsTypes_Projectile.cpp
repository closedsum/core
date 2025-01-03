// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Data
#include "Data/CsLibrary_Data.h"
	// Settings
#include "Settings/CsLibrary_ProjectileSettings.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"
// Utility
#include "Utility/CsPrjPopulateEnumMapFromSettings.h"
#include "Utility/CsPrjLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Projectile)

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
	namespace NCached
	{
		namespace Str
		{
			const FString Projectile = TEXT("Projectile");
		}

		namespace Name
		{
			const FName Projectiles = FName("Projectiles");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsProjectile::NCached;

		typedef NCsProjectile::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_Projectile();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_Projectile();
		Payload.EnumName				 = Str::Projectile;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsProjectile::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsProjectile::NCached;

		typedef FCsPrjPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::Projectiles;
		Payload.EnumName				 = Str::Projectile;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsProjectile::FLog::Warning;

		FCsPrjPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsProjectile::NSettings::FLibrary SettingsLibrary;

		EMCsProjectile::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsProjectile_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsProjectile_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion Projectile

// FCsData_ECsProjectile
#pragma region

bool FCsData_ECsProjectile::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Value)
	return true;
}

bool FCsData_ECsProjectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Value)
	return true;
}

#pragma endregion FCsData_Projectile

// FCsDataNoPropertyView_ECsProjectile
#pragma region

bool FCsDataNoPropertyView_ECsProjectile::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Value)
	return true;
}

bool FCsDataNoPropertyView_ECsProjectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Value)
	return true;
}

#pragma endregion FCsDataNoPropertyView_ECsProjectile

// ProjectileClass
#pragma region

namespace NCsProjectileClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString ProjectileClass = TEXT("ProjectileClass");
		}

		namespace Name
		{
			const FName ProjectileClasses = FName("ProjectileClasses");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsProjectileClass::NCached;

		typedef NCsProjectile::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_ProjectileClass();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_ProjectileClass();
		Payload.EnumName				 = Str::ProjectileClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsProjectile::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsProjectileClass::NCached;

		typedef FCsPrjPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::ProjectileClasses;
		Payload.EnumName				 = Str::ProjectileClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsProjectile::FLog::Warning;

		FCsPrjPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsProjectile::NSettings::FLibrary SettingsLibrary;

		EMCsProjectileClass::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsProjectileClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsProjectileClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion ProjectileClass

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

// FCsData_ProjectilePtr
#pragma region

namespace NCsDataProjectilePtr
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsData_ProjectilePtr, Unload);
		}
	}
}

#define USING_NS_CACHED using namespace NCsDataProjectilePtr::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsDataProjectilePtr::NCached; \
	const FString& Context = Str::__FunctionName

UObject* FCsData_ProjectilePtr::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data is NOT Valid."), *Context))
		return nullptr;
	}

	UObject* O = Data.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data at Path: %s."), *Context, *(Path.ToString())))
		return nullptr;
	}

	UClass* Class = Cast<UClass>(O);

	if (!Class)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s with Class: %s is NOT of type UClass."), *Context, *(Data->GetName()), *(Data->GetClass()->GetName())))
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object for Class: %s."), *Context, *(Class->GetName())))
	}
	return DOb;
}

UObject* FCsData_ProjectilePtr::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data is NOT Valid."), *Context))
		return nullptr;
	}

	UObject* O = Data.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data at Path: %s."), *Context, *(Path.ToString())))
	}
	return O;
}

void FCsData_ProjectilePtr::Unload()
{
	SET_CONTEXT(Unload);

	Data.ResetWeakPtr();

	if (IsValid(Data_Internal))
	{
		if (CsDataLibrary::SafeScriptImplements(Context, Data_Internal, nullptr))
			CsDataLibrary::Script_UnloadChecked(Context, Data_Internal);
		else
			CsDataLibrary::UnloadChecked(Context, Data_Internal);
	}

	Data_Internal = nullptr;
	Data_Class = nullptr;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsData_ProjectilePtr