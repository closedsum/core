// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/Script/CsScriptLibrary_Manager_Sound.h"

// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Sound)

// Cached
#pragma region

namespace NCsScriptLibraryManagerSound
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Sound, FindObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Sound, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Sound::UCsScriptLibrary_Manager_Sound(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_Sound::FindObject(const FString& Context, UObject* WorldContextObject, const FECsSound& Type, const int32& Index)
{
	using namespace NCsScriptLibraryManagerSound::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FindObject : Context;

	const FCsSoundPooled* SoundPooled = CsSoundManagerLibrary::FindSafeObject(Ctxt, WorldContextObject, Type, Index);

	if (SoundPooled)
	{
		return SoundPooled->GetSafeObject();
	}
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_Sound::Spawn(const FString& Context, UObject* WorldContextObject, const FCsPayload_Sound& Payload, const FTransform& Transform)
{
	using namespace NCsScriptLibraryManagerSound::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UCsManager_Sound* Manager_Sound = CsSoundManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	typedef NCsSound::NPayload::NImpl::FImpl PayloadImplType;

	const FECsSound& Type		 = Payload.Sound.Type;
	PayloadImplType* PayloadImpl = Manager_Sound->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, PayloadImpl);

	const FTransform& T = PayloadImpl->Transform;

	PayloadImpl->Transform.SetTranslation(Transform.GetTranslation() + T.GetTranslation());
	PayloadImpl->Transform.SetRotation(Transform.GetRotation() + T.GetRotation());
	PayloadImpl->Transform.SetScale3D(Transform.GetScale3D() * T.GetScale3D());

	const FCsSoundPooled* SoundPooled = Manager_Sound->Spawn(Type, PayloadImpl);

	return SoundPooled->GetCache()->GetIndex();
}