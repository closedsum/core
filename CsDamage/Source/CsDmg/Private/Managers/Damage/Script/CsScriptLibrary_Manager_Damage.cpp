// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Script/CsScriptLibrary_Manager_Damage.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Damage)

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

	return CsDamageManagerLibrary::GetSafeDataAsObject(Context, WorldContextObject, Type);
}

UObject* UCsScriptLibrary_Manager_Damage::GetDataByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataByName : Context;

	return CsDamageManagerLibrary::GetSafeDataAsObject(Context, WorldContextObject, Name);
}

bool UCsScriptLibrary_Manager_Damage::ProcessData(const FString& Context, const UObject* WorldContextObject, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ProcessData : Context;

	return CsDamageManagerLibrary::SafeProcessData(Context, WorldContextObject, DataName, Instigator, Causer, HitResult);
}