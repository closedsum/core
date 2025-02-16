// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Script/CsScriptLibrary_Manager_Projectile.h"
#include "CsPrj.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Payload/CsLibrary_Payload_Projectile.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Projectile)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_Projectile)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, Get)
	// Settings
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, GetTypeToSetAsArray)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, SetTypeMapKeyValue)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, AddPoolParams)
	// Allocate / Deallocate
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, QueueDeallocateAll)
	// Pool
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, FindObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, HasPool)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, GetPool)
	// Spawn
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_Projectile, Spawn)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_Manager_Projectile::UCsScriptLibrary_Manager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

UCsManager_Projectile* UCsScriptLibrary_Manager_Projectile::Get(const FString& Context, const UObject* WorldContextObject)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(Get);

	return CsPrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

// Settings
#pragma region

bool UCsScriptLibrary_Manager_Projectile::GetTypeToSetAsArray(const FString& Context, const UObject* WorldContextObject, TArray<FECsProjectile>& OutTypes)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(GetTypeToSetAsArray);

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
	CS_SET_CTXT_AS_FUNCTION_NAME(SetTypeMapKeyValue);

	CsPrjManagerLibrary::SafeSetAndAddTypeMapKeyValue(Context, WorldContextObject, Key, Value);
}

bool UCsScriptLibrary_Manager_Projectile::AddPoolParams(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(AddPoolParams);

	return CsPrjManagerLibrary::SafeAddPoolParams(Ctxt, WorldContextObject, Type, PoolParams);
}

#pragma endregion Settings

// Allocate / Deallocate
#pragma region

bool UCsScriptLibrary_Manager_Projectile::QueueDeallocateAll(const FString& Context, const UObject* WorldContextObject)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(QueueDeallocateAll);

	return CsPrjManagerLibrary::SafeQueueDeallocateAll(Ctxt, WorldContextObject);
}

#pragma endregion Allocate / Deallocate

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_Projectile::FindObject(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const int32& Index)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(FindObject);

	UObject* ContextRoot = CsPrjManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return nullptr;
#endif // #if WITH_EDITOR

	//CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsProjectile, FECsProjectile, Type)
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
	CS_SET_CTXT_AS_FUNCTION_NAME(HasPool);

	return CsPrjManagerLibrary::SafeHasPool(Ctxt, WorldContextObject, Type);
}

bool UCsScriptLibrary_Manager_Projectile::GetPool(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, TArray<UObject*>& OutPool)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(GetPool);

	return CsPrjManagerLibrary::GetSafePool(Ctxt, WorldContextObject, Type, OutPool);
}

#pragma endregion Pool

// Spawn
#pragma region

UObject* UCsScriptLibrary_Manager_Projectile::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Projectile& Payload, int32& OutIndex)
{
	CS_SET_CTXT_AS_FUNCTION_NAME(Spawn);

	OutIndex = INDEX_NONE;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return nullptr;

	// Try to allocate a native payload
	UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return nullptr;

	using PayloadType = NCsProjectile::NPayload::IPayload;
	using PayloadImplType = NCsProjectile::NPayload::NImpl::FImpl;
	using PayloadSliceType = NCsProjectile::NPayload::NImplSlice::FImplSlice;

	const FECsProjectile& Type	= Payload.Type;

	PayloadType* P = CsPrjManagerLibrary::AllocatePayloadChecked(Ctxt, WorldContextObject, Type);

	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, P);

	const FCsProjectilePooled* PrjPooled = CsPrjManagerLibrary::SpawnChecked(Type, WorldContextObject, P);

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