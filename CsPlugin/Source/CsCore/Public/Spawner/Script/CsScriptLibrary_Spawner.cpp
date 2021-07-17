// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Script/CsScriptLibrary_Spawner.h"
#include "CsCore.h"

// Spawner
#include "Spawner/CsSpawnerImpl.h"

namespace NCsScriptLibrarySpawner
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Spawner, SetParams_DefaultImpl);
		}
	}
}

UCsScriptLibrary_Spawner::UCsScriptLibrary_Spawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Spawner::SetParams_DefaultImpl(const FString& Context, UObject* Spawner, const FCsSpawnerParamsImpl& Params)
{
	using namespace NCsScriptLibrarySpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetParams_DefaultImpl : Context;

	if (!Spawner)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner is NULL."), *Ctxt);
	}

	if (!Spawner->GetClass()->ImplementsInterface(UCsSpawner::StaticClass()))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT implement the interface: ICsSpawner."), *Ctxt, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
		return false;
	}

	ICsSpawner* Interface = Cast<ICsSpawner>(Spawner);

	if (!Interface)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT implement the interface: ICsSpawner natively (c++). Implementing a script based interface is currently NOT supported."), *Ctxt, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
		return false;
	}

	ACsSpawnerImpl* Impl = Cast<ACsSpawnerImpl>(Spawner);

	if (!Impl)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT derive from ACsSpawnerImpl. Currently this is the ONLY supported parent class."), *Ctxt, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
		return false;
	}

	typedef NCsSpawner::NParams::FImpl  ParamsType;

	ParamsType* ParamsImpl = Params.ConstructParamsImpl();

	Impl->SetParams(Ctxt, ParamsImpl, &ParamsType::Deconstruct, &ParamsType::IsValidChecked);
	return true;
}