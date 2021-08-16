// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Script/CsScriptLibrary_Manager_Damage.h"
#include "CsCore.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Damage, ProcessData);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Damage::UCsScriptLibrary_Manager_Damage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Manager_Damage::ProcessData(const FString& Context, const UObject* WorldContextObject, UObject* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	using namespace NCsScriptLibraryManagerDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ProcessData : Context;

	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;


	return false;
}