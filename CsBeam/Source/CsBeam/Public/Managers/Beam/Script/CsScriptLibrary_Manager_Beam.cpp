// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/Script/CsScriptLibrary_Manager_Beam.h"
#include "CsBeam.h"

// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
// Managers
#include "Managers/Beam/CsManager_Beam.h"
// Beam
#include "Payload/CsPayload_BeamImpl.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerBeam
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Beam, SetTypeMapKeyValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Beam, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Beam::UCsScriptLibrary_Manager_Beam(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Settings
#pragma region

void UCsScriptLibrary_Manager_Beam::SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsBeam& Key, const FECsBeam& Value)
{
	using namespace NCsScriptLibraryManagerBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetTypeMapKeyValue : Context;

	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;

	BeamManagerLibrary::SafeSetAndAddTypeMapKeyValue(Context, WorldContextObject, Key, Value);
}

#pragma endregion Settings

// Spawn
#pragma region

int32 UCsScriptLibrary_Manager_Beam::Spawn(const FString& Context, const UObject* WorldContextObject, const FECsBeam& Beam, const FCsPayload_Beam& Payload)
{
	using namespace NCsScriptLibraryManagerBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UCsManager_Beam* Manager_Beam = BeamManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Beam)
		return INDEX_NONE;

	typedef NCsBeam::NPayload::FImpl PayloadImplType;

	const FECsBeam& Type		 = Payload.Type;
	PayloadImplType* PayloadImpl = Manager_Beam->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, WorldContextObject, PayloadImpl);

	const FCsBeamPooled* BeamPooled = Manager_Beam->Spawn(Type, PayloadImpl);

	return BeamPooled->GetCache()->GetIndex();
}

#pragma endregion Spawn