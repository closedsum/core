// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/Script/CsScriptLibrary_Manager_Projectile.h"
#include "CsPrj.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerProjectile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, SetTypeMapKeyValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Projectile::UCsScriptLibrary_Manager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Settings
#pragma region

void UCsScriptLibrary_Manager_Projectile::SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Key, const FECsProjectile& Value)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetTypeMapKeyValue : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	PrjManagerLibrary::SafeSetAndAddTypeMapKeyValue(Context, WorldContextObject, Key, Value);
}

#pragma endregion Settings

// Spawn
#pragma region

int32 UCsScriptLibrary_Manager_Projectile::Spawn(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Projectile, const FCsPayload_Projectile& Payload)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return INDEX_NONE;

	typedef NCsProjectile::NPayload::FImpl PayloadImplType;

	const FECsProjectile& Type	 = Payload.Type;
	PayloadImplType* PayloadImpl = Manager_Projectile->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, PayloadImpl);

	const FCsProjectilePooled* PrjPooled = Manager_Projectile->Spawn(Type, PayloadImpl);

	return PrjPooled->GetCache()->GetIndex();
}

#pragma endregion Spawn