// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/Script/CsScriptLibrary_DamageEvent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Event/CsLibrary_DamageEvent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_DamageEvent)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_DamageEvent)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetDamage);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetInstigator);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetCauser);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetDamageDirection);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetHitType);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetOrigin);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetHitResult);
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_DamageEvent, GetIgnoreObjects);
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_DamageEvent::UCsScriptLibrary_DamageEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UCsScriptLibrary_DamageEvent::GetDamage(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetDamage);

	return CsDamageEventLibrary::GetSafeDamage(Ctxt, Object);
}

UObject* UCsScriptLibrary_DamageEvent::GetInstigator(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetInstigator);

	return CsDamageEventLibrary::GetSafeInstigator(Ctxt, Object);
}

UObject* UCsScriptLibrary_DamageEvent::GetCauser(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetCauser);

	return CsDamageEventLibrary::GetSafeCauser(Ctxt, Object);
}

FVector UCsScriptLibrary_DamageEvent::GetDamageDirection(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetDamageDirection);

	return CsDamageEventLibrary::GetSafeDamageDirection(Ctxt, Object);
}

FECsHitType UCsScriptLibrary_DamageEvent::GetHitType(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetHitType);

	return CsDamageEventLibrary::GetSafeHitType(Ctxt, Object);
}

FHitResult UCsScriptLibrary_DamageEvent::GetOrigin(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetOrigin);

	return CsDamageEventLibrary::GetSafeOrigin(Ctxt, Object);
}

FHitResult UCsScriptLibrary_DamageEvent::GetHitResult(const FString& Context, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetHitResult);

	return CsDamageEventLibrary::GetSafeHitResult(Ctxt, Object);
}

bool UCsScriptLibrary_DamageEvent::GetIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetIgnoreObjects);

	return CsDamageEventLibrary::GetSafeIgnoreObjects(Ctxt, Object, OutObjects);
}