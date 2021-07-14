// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Script/CsScriptLibrary_Manager_Weapon.h"
#include "CsWp.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
// Weapon
#include "CsWeapon.h"
// Log
#include "Utility/CsWpLog.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerWeapon
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Weapon, GetClassByType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Weapon, GetClassByClassType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Weapon, AddClassByType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Weapon, AddClassByClassType);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Weapon::UCsScriptLibrary_Manager_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Class
#pragma region

UClass* UCsScriptLibrary_Manager_Weapon::GetClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type)
{
	using namespace NCsScriptLibraryManagerWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetClassByType : Context;

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

	if (FCsWeapon* Weapon = WeaponManagerLibrary::GetSafeWeapon(Ctxt, WorldContextObject, Type, Log))
	{
		return Weapon->GetClass();
	}
	return nullptr;
}

UClass* UCsScriptLibrary_Manager_Weapon::GetClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type)
{
	using namespace NCsScriptLibraryManagerWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetClassByClassType : Context;

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

	if (FCsWeapon* Weapon = WeaponManagerLibrary::GetSafeWeapon(Ctxt, WorldContextObject, Type, Log))
	{
		return Weapon->GetClass();
	}
	return nullptr;
}

bool UCsScriptLibrary_Manager_Weapon::AddClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type, TSubclassOf<UObject> Class)
{
	using namespace NCsScriptLibraryManagerWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddClassByType : Context;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

	if (UClass* C = Cast<UClass>(Class.Get()))
	{
		return WeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, C->ClassDefaultObject);
	}
	return WeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, Class);
}

bool UCsScriptLibrary_Manager_Weapon::AddClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type, TSubclassOf<UObject> Class)
{
	using namespace NCsScriptLibraryManagerWeapon::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddClassByClassType : Context;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

	if (UClass* C = Cast<UClass>(Class.Get()))
	{
		return WeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, C->ClassDefaultObject);
	}
	return WeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, Class);
}

#pragma endregion Class