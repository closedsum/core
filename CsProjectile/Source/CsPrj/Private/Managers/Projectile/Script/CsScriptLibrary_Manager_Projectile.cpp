// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Script/CsScriptLibrary_Manager_Projectile.h"
#include "CsPrj.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Projectile)

// Cached
#pragma region

namespace NCsScriptLibraryManagerProjectile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, Get);
			// Settings
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, GetTypeToSetAsArray);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, SetTypeMapKeyValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, AddPoolParams);
			// Allocate / Deallocate
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, QueueDeallocateAll);
			// Pool
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, FindObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, HasPool);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, GetPool);
			// Spawn
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Projectile, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Projectile::UCsScriptLibrary_Manager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

UCsManager_Projectile* UCsScriptLibrary_Manager_Projectile::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return CsPrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

// Settings
#pragma region

bool UCsScriptLibrary_Manager_Projectile::GetTypeToSetAsArray(const FString& Context, const UObject* WorldContextObject, TArray<FECsProjectile>& OutTypes)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTypeToSetAsArray : Context;

	UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetSafe(Context, WorldContextObject);

	if (!Manager_Projectile)
		return false;

	const TSet<FECsProjectile>& TypeToSet = Manager_Projectile->GetTypeToSet();

	OutTypes.Reset(FMath::Max(OutTypes.Max(), TypeToSet.Num()));

	for (const FECsProjectile& Type : TypeToSet)
	{
		OutTypes.Add(Type);
	}
	return true;
}

void UCsScriptLibrary_Manager_Projectile::SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Key, const FECsProjectile& Value)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetTypeMapKeyValue : Context;

	CsPrjManagerLibrary::SafeSetAndAddTypeMapKeyValue(Context, WorldContextObject, Key, Value);
}

bool UCsScriptLibrary_Manager_Projectile::AddPoolParams(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddPoolParams : Context;

	return CsPrjManagerLibrary::SafeAddPoolParams(Ctxt, WorldContextObject, Type, PoolParams);
}

#pragma endregion Settings

// Allocate / Deallocate
#pragma region

bool UCsScriptLibrary_Manager_Projectile::QueueDeallocateAll(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::QueueDeallocateAll : Context;

	return CsPrjManagerLibrary::SafeQueueDeallocateAll(Ctxt, WorldContextObject);
}

#pragma endregion Allocate / Deallocate

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_Projectile::FindObject(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const int32& Index)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FindObject : Context;

	UObject* ContextRoot = CsPrjManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return nullptr;
#endif // #if WITH_EDITOR

	if (!EMCsProjectile::Get().IsValidEnum(Type))
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Type: %s is NOT Valid."), *Ctxt, Type.ToChar());
		return nullptr;
	}

	UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(ContextRoot);

	if (Index < 0 || Index >= Manager_Projectile->GetPoolSize(Type))
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s: Index: %d is NOT [0, %d] Inclusive."), *Ctxt, Index, Manager_Projectile->GetPoolSize(Type));
		return nullptr;
	}

	const FCsProjectilePooled* ProjectilePooled = Manager_Projectile->FindObject(Type, Index);

	if (ProjectilePooled)
	{
		return ProjectilePooled->GetSafeObject();
	}
	return nullptr;
}

bool UCsScriptLibrary_Manager_Projectile::HasPool(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::HasPool : Context;

	return CsPrjManagerLibrary::SafeHasPool(Ctxt, WorldContextObject, Type);
}

bool UCsScriptLibrary_Manager_Projectile::GetPool(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, TArray<UObject*>& OutPool)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPool : Context;

	return CsPrjManagerLibrary::GetSafePool(Ctxt, WorldContextObject, Type, OutPool);
}

#pragma endregion Pool

// Spawn
#pragma region

UObject* UCsScriptLibrary_Manager_Projectile::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Projectile& Payload, int32& OutIndex)
{
	using namespace NCsScriptLibraryManagerProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	OutIndex = INDEX_NONE;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return nullptr;

	// Try to allocate a native payload
	UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return nullptr;

	typedef NCsProjectile::NPayload::IPayload PayloadType;
	typedef NCsProjectile::NPayload::FImpl PayloadImplType;
	typedef NCsProjectile::NPayload::FImplSlice PayloadSliceType;

	const FECsProjectile& Type	= Payload.Type;

	PayloadType* IPayload = Manager_Projectile->AllocatePayload(Type);

	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, IPayload);

	const FCsProjectilePooled* PrjPooled = Manager_Projectile->Spawn(Type, IPayload);

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