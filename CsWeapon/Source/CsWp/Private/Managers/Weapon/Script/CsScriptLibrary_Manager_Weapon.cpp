// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Script/CsScriptLibrary_Manager_Weapon.h"
#include "CsWp.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
// Weapon
#include "CsWeaponClass.h"
#include "CsWeaponPooled.h"
#include "Payload/CsPayload_WeaponImplSlice.h"
// Pool
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
// Log
#include "Utility/CsWpLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Weapon)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_Weapon)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Weapon, GetClassByType)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Weapon, GetClassByClassType)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Weapon, AddClassByType)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Weapon, AddClassByClassType)
	// Spawn
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Weapon, Spawn)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_Manager_Weapon::UCsScriptLibrary_Manager_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Class
#pragma region

UClass* UCsScriptLibrary_Manager_Weapon::GetClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(GetClassByType);

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	if (FCsWeaponClass* Weapon = CsWeaponManagerLibrary::GetSafeWeapon(Ctxt, WorldContextObject, Type, Log))
	{
		return Weapon->GetClass();
	}
	return nullptr;
}

UClass* UCsScriptLibrary_Manager_Weapon::GetClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(GetClassByClassType);

	void(*Log)(const FString&) = &NCsWeapon::FLog::Warning;

	if (FCsWeaponClass* Weapon = CsWeaponManagerLibrary::GetSafeWeapon(Ctxt, WorldContextObject, Type, Log))
	{
		return Weapon->GetClass();
	}
	return nullptr;
}

bool UCsScriptLibrary_Manager_Weapon::AddClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type, TSubclassOf<UObject> Class)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(AddClassByType);

	if (UClass* C = Cast<UClass>(Class.Get()))
	{
		return CsWeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, C->ClassDefaultObject);
	}
	return CsWeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, Class);
}

bool UCsScriptLibrary_Manager_Weapon::AddClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type, TSubclassOf<UObject> Class)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(AddClassByClassType);

	if (UClass* C = Cast<UClass>(Class.Get()))
	{
		return CsWeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, C->ClassDefaultObject);
	}
	return CsWeaponManagerLibrary::SafeAddClass(Ctxt, WorldContextObject, Type, Class);
}

#pragma endregion Class

// Spawn
#pragma region

UObject* UCsScriptLibrary_Manager_Weapon::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Weapon& Payload, int32& OutIndex)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(Spawn);

	OutIndex = INDEX_NONE;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return nullptr;

	// Try to allocate a native payload
	if (!CsWeaponManagerLibrary::SafeIsActive(Ctxt, WorldContextObject))
		return nullptr;

	using PayloadType = NCsWeapon::NPayload::IPayload;
	using PayloadImplType = NCsWeapon::NPayload::NImpl::FImpl;
	using PayloadSliceType = NCsWeapon::NPayload::NImplSlice::FImplSlice;

	const FECsWeapon& Type	= Payload.Type;

	PayloadType* P = CsWeaponManagerLibrary::AllocatePayloadChecked(Ctxt, WorldContextObject, Type);

	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, P);

	const FCsWeaponPooled* WpPooled = CsWeaponManagerLibrary::SpawnChecked(Type, WorldContextObject, Type, P);

	UObject* O = WpPooled->GetSafeObject();

	if (!O)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Weapon of type: %s is NOT a UObject."), *Ctxt, Type.ToChar());
		return nullptr;
	}

	OutIndex = WpPooled->GetCache()->GetIndex();
	return WpPooled->GetSafeObject();
}

#pragma endregion Spawn