// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

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

UObject* UCsScriptLibrary_Manager_Projectile::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Projectile& Payload, int32& OutIndex)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	OutIndex = INDEX_NONE;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return nullptr;

	// Try to allocate a native payload
	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return nullptr;

	typedef NCsProjectile::NPayload::FImpl PayloadImplType;

	const FECsProjectile& Type	 = Payload.Type;
	PayloadImplType* PayloadImpl = Manager_Projectile->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, PayloadImpl);

	const FCsProjectilePooled* PrjPooled = Manager_Projectile->Spawn(Type, PayloadImpl);

	UObject* O = PrjPooled->GetSafeObject();

	if (!O)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Projectile of type: %s is NOT a UObject."), *Ctxt, Type.ToChar());
		return nullptr;
	}

	OutIndex = PrjPooled->GetCache()->GetIndex();
	return PrjPooled->GetSafeObject();
}

#pragma endregion Spawn