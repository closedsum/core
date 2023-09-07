// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Script/CsScriptLibrary_Manager_Damage.h"
#include "CsDmg.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerDamage
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Damage, GetData);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Damage, GetDataByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Damage, ProcessData);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Damage::UCsScriptLibrary_Manager_Damage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UObject* UCsScriptLibrary_Manager_Damage::GetData(const FString& Context, const UObject* WorldContextObject, const FECsDamageData& Type)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetData : Context;

	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

	return DamageManagerLibrary::GetSafeDataAsObject(Context, WorldContextObject, Type);
}

UObject* UCsScriptLibrary_Manager_Damage::GetDataByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataByName : Context;

	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

	return DamageManagerLibrary::GetSafeDataAsObject(Context, WorldContextObject, Name);
}

bool UCsScriptLibrary_Manager_Damage::ProcessData(const FString& Context, const UObject* WorldContextObject, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ProcessData : Context;

	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

	return DamageManagerLibrary::SafeProcessData(Context, WorldContextObject, DataName, Instigator, Causer, HitResult);
}