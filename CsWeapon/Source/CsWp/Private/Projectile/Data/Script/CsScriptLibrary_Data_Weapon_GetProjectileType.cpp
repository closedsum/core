// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Script/CsScriptLibrary_Data_Weapon_GetProjectileType.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
// Data
#include "Data/Types/CsData_GetProjectileType.h"
// Weapon
#include "CsWeapon.h"
// Log
#include "Utility/CsWpLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data_Weapon_GetProjectileType)

// Cached
#pragma region

namespace NCsScriptLibraryDataWeaponGetProjectileType
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Weapon_GetProjectileType, GetProjectileType);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Weapon_GetProjectileType::UCsScriptLibrary_Data_Weapon_GetProjectileType(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const FECsProjectile& UCsScriptLibrary_Data_Weapon_GetProjectileType::GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type)
{
	using namespace NCsScriptLibraryDataWeaponGetProjectileType::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetProjectileType : Context;

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData WeaponDataType;

	WeaponDataType* Data = WeaponManagerLibrary::GetSafeData(Ctxt, WorldContextObject, Type);

	if (!Data)
	{
		return EMCsProjectile::Get().GetMAX();
	}

	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	ICsData_GetProjectileType* Data_GetProjectileType = WeaponDataLibrary::GetSafeInterfaceChecked<ICsData_GetProjectileType>(Ctxt, Data);

	if (!Data_GetProjectileType)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT implement interface: ICsData_GetProjectileType."), *Ctxt, Type.ToChar()));
		return EMCsProjectile::Get().GetMAX();
	}
	return Data_GetProjectileType->GetProjectileType();
}