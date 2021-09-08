// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByLabel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, MoveByInterp);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterials);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SpawnBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SpawnByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetDistanceSq);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetDistanceSq2D);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetNormalAtoB);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetNormal2DAtoB);
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

AActor* UCsScriptLibrary_Actor::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTag : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

bool UCsScriptLibrary_Actor::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnyByTags : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutActors);
}

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

FCsRoutineHandle UCsScriptLibrary_Actor::MoveByInterp(const FString& Context, const UObject* WorldContextObject, const FCsMoveByInterp_Params& Params)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveByInterp : Context;

	FCsMoveByInterp_Params* ParamsPtr = const_cast<FCsMoveByInterp_Params*>(&Params);

	ParamsPtr->ConditionalSetSafeMoveObject(Context, WorldContextObject);
	ParamsPtr->ConditionalSetSafeDestinationObject(Context, WorldContextObject);

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsActor::FLibrary ActorLibrary;
	typedef NCsMovement::NTo::NInterp::NParams::FResource ParamsResourceType;
	typedef NCsMovement::NTo::NInterp::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = ActorLibrary::Get().AllocateMoveByInterpParams();
	ParamsType* Parms				   = ParmsContainer->Get();

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

// Spawn
#pragma region

AActor* UCsScriptLibrary_Actor::SpawnBySoftObjectPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SpawnBySoftObjectPath : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::SafeSpawn(Ctxt, WorldContextObject, Path);
}

AActor* UCsScriptLibrary_Actor::SpawnByStringPath(const FString& Context, const UObject* WorldContextObject, const FString& Path)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SpawnByStringPath : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::SafeSpawn(Ctxt, WorldContextObject, Path);
}

#pragma endregion Spawn

// Distance
#pragma region

float UCsScriptLibrary_Actor::GetDistanceSq(const FString& Context, AActor* A, AActor* B)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDistanceSq : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeDistanceSq(Ctxt, A, B);
}

float UCsScriptLibrary_Actor::GetDistanceSq2D(const FString& Context, AActor* A, AActor* B)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDistanceSq2D : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeDistanceSq2D(Ctxt, A, B);
}

#pragma endregion Distance

// Normal
#pragma region

bool UCsScriptLibrary_Actor::GetNormalAtoB(const FString& Context, AActor* A, AActor* B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetNormalAtoB : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeNormalAtoB(Ctxt, A, B, OutNormal, OutDistanceSq, OutDistance);
}

bool UCsScriptLibrary_Actor::GetNormal2DAtoB(const FString& Context, AActor* A, AActor* B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetNormal2DAtoB : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeNormal2DAtoB(Ctxt, A, B, OutNormal, OutDistanceSq, OutDistance);
}

#pragma endregion Normal