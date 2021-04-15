// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/Script/CsScriptLibrary_Manager_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerFX
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_FX, FindObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_FX, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_FX::UCsScriptLibrary_Manager_FX(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_FX::FindObject(const FString& Context, UObject* WorldContextObject, const FECsFX& Type, const int32& Index)
{
	using namespace NCsScriptLibraryManagerFX::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FindObject : Context;

	typedef NCsFX::NManager::FLibrary FXManagerLibrary;

	UObject* ContextRoot = FXManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return nullptr;
#endif // #if WITH_EDITOR

	if (!EMCsFX::Get().IsValidEnum(Type))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());
		return nullptr;
	}

	UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

	if (Index < 0 || Index >= Manager_FX->GetPoolSize(Type))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Index: %d is NOT [0, %d] Inclusive."), *Context, Index, Manager_FX->GetPoolSize(Type));
		return nullptr;
	}
	
	const FCsFXActorPooled* FXPooled = Manager_FX->FindObject(Type, Index);

	if (FXPooled)
	{
		return FXPooled->GetSafeObject();
	}
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_FX::Spawn(const FString& Context, UObject* WorldContextObject, const FCsPayload_FX& Payload)
{
	using namespace NCsScriptLibraryManagerFX::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	typedef NCsFX::NManager::FLibrary FXManagerLibrary;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UObject* ContextRoot = FXManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return INDEX_NONE;
#endif // #if WITH_EDITOR

	UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

	typedef NCsFX::NPayload::FImpl PayloadImplType;

	const FECsFX& Type			 = Payload.FX.Type;
	PayloadImplType* PayloadImpl = Manager_FX->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, PayloadImpl);

	const FCsFXActorPooled* FXPooled = Manager_FX->Spawn(Type, PayloadImpl);

	return FXPooled->GetCache()->GetIndex();
}