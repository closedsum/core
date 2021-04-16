// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Actor/Script/CsScriptLibrary_Actor.h"
#include "CsCore.h"

// Library
#include "Actor/CsLibrary_Actor.h"

// Cached
#pragma region

namespace NCsScriptLibraryActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetRootComponent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetRole);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByLabel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, MoveByInterp);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterials);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Actor::UCsScriptLibrary_Actor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Actor::SetRootComponent(const FString& Context, AActor* Actor, USceneComponent* Component)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetRootComponent : Context;

	if (!Actor)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Actor is NULL."), *Ctxt);
		return;
	}

	if (!Component)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Component is NULL. Use ClearRootComponent."), *Ctxt);
		return;
	}
	Actor->SetRootComponent(Component);
}

void UCsScriptLibrary_Actor::SetRole(const FString& Context, AActor* Actor, const ENetRole& Role)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetRole : Context;

	if (!Actor)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Actor is NULL."), *Ctxt);
		return;
	}
	Actor->SetRole(Role);
}

// Get
#pragma region

AActor* UCsScriptLibrary_Actor::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByName : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

AActor* UCsScriptLibrary_Actor::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByLabel : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

// Move
#pragma region

FCsRoutineHandle UCsScriptLibrary_Actor::MoveByInterp(const FString& Context, UObject* WorldContextObject, FCsMoveByInterp_Params& Params)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveByInterp : Context;

	Params.ConditionalSetSafeMoveObject(Context, WorldContextObject);
	Params.ConditionalSetSafeDestinationObject(Context, WorldContextObject);

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsActor::FLibrary ActorLibrary;
	typedef NCsMovement::NTo::NInterp::NParams::FResource ParamsResourceType;
	typedef NCsMovement::NTo::NInterp::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = ActorLibrary::Get().AllocateMoveByInterpParams();
	ParamsType* Parms = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return ActorLibrary::SafeMoveByInterp(Ctxt, WorldContextObject, ParmsContainer);
}

#pragma endregion Move

// Material
#pragma region

void UCsScriptLibrary_Actor::SetMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetMaterial : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	ActorLibrary::SetSafeMaterial(Ctxt, Actor, Material, Index);
}

void UCsScriptLibrary_Actor::SetMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetMaterials : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	ActorLibrary::SetSafeMaterials(Ctxt, Actor, Materials);
}

#pragma endregion Material