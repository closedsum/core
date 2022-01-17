// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/Script/CsScriptLibrary_DamageEvent.h"
#include "CsDmg.h"

// Library
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Cached
#pragma region

namespace NCsScriptLibraryDamageEvent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetDamage);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetInstigator);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetCauser);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetHitType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetOrigin);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetHitResult);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_DamageEvent, GetIgnoreObjects);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_DamageEvent::UCsScriptLibrary_DamageEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UCsScriptLibrary_DamageEvent::GetDamage(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDamage : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeDamage(Ctxt, Object);
}

UObject* UCsScriptLibrary_DamageEvent::GetInstigator(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetInstigator : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeInstigator(Ctxt, Object);
}

UObject* UCsScriptLibrary_DamageEvent::GetCauser(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetCauser : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeCauser(Ctxt, Object);
}

FECsHitType UCsScriptLibrary_DamageEvent::GetHitType(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetHitType : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeHitType(Ctxt, Object);
}

FHitResult UCsScriptLibrary_DamageEvent::GetOrigin(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetOrigin : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeOrigin(Ctxt, Object);
}

FHitResult UCsScriptLibrary_DamageEvent::GetHitResult(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetHitResult : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeHitResult(Ctxt, Object);
}

bool UCsScriptLibrary_DamageEvent::GetIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects)
{
	using namespace NCsScriptLibraryDamageEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetIgnoreObjects : Context;

	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	return DamageEventLibrary::GetSafeIgnoreObjects(Ctxt, Object, OutObjects);
}