// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/Script/CsScriptLibrary_Actor.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Actor/CsLibrary_Actor.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Actor
#include "GameFramework/Actor.h" // TODO: Move to Library

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
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetAllOfClass);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetByLabel);
			// Has
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, HasTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, HasTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, HasTagChecked);
			// Component
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetComponentByTag);
			// Visibility
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetHiddenInGame);
			// Orientation
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetQuat);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, RotateByPitch);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, RotateByYaw);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, RotateByRoll);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetMaterials);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SpawnBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SpawnByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetDistanceSq);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetDistanceSq2D);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, IsDistanceSq2D_LessThanOrEqual);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetNormalAtoB);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetNormal2DAtoB);
		}
	}
}

#pragma endregion Cached

#define USING_NS_CACHED using namespace NCsScriptLibraryActor::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryActor::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning;
#define LogError &NCsCore::NLibrary::FLog::Error
#define ActorLibrary NCsActor::FLibrary
#define MathLibrary NCsMath::FLibrary

UCsScriptLibrary_Actor::UCsScriptLibrary_Actor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Actor::SetRootComponent(const FString& Context, AActor* Actor, USceneComponent* Component)
{
	CONDITIONAL_SET_CTXT(SetRootComponent);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Actor)

	if (!Component)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Component is NULL. Use ClearRootComponent."), *Ctxt);
		return;
	}
	Actor->SetRootComponent(Component);
}

void UCsScriptLibrary_Actor::SetRole(const FString& Context, AActor* Actor, const ENetRole& Role)
{
	CONDITIONAL_SET_CTXT(SetRole);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Actor)
	Actor->SetRole(Role);
}

// Get
#pragma region

bool UCsScriptLibrary_Actor::GetAllOfClass(const FString& Context, const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors)
{
	CONDITIONAL_SET_CTXT(GetAllOfClass);

	return ActorLibrary::GetSafeAllOfClass(Ctxt, WorldContextObject, ActorClass, OutActors);
}

AActor* UCsScriptLibrary_Actor::GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return ActorLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

AActor* UCsScriptLibrary_Actor::GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(GetByTags);

	return ActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

bool UCsScriptLibrary_Actor::GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return ActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutActors);
}

AActor* UCsScriptLibrary_Actor::GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return ActorLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

AActor* UCsScriptLibrary_Actor::GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return ActorLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

// Has
#pragma region

bool UCsScriptLibrary_Actor::HasTags(const FString& Context, const AActor* Actor, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(HasTags);

	return ActorLibrary::SafeHasTags(Ctxt, Actor, Tags);
}

bool UCsScriptLibrary_Actor::HasTag(const FString& Context, const AActor* Actor, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(HasTag);

	return ActorLibrary::SafeHasTag(Ctxt, Actor, Tag);
}

bool UCsScriptLibrary_Actor::HasTagChecked(const FString& Context, const AActor* Actor, const FName& Tag, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(HasTagChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(ActorLibrary::HasTagChecked(Ctxt, Actor, Tag), ActorLibrary::SafeHasTag(Ctxt, Actor, Tag, OutSuccess, LogError));
}

#pragma endregion Has

// Component
#pragma region

UActorComponent* UCsScriptLibrary_Actor::GetComponentByTag(const FString& Context, const AActor* Actor, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetComponentByTag);

	return ActorLibrary::GetSafeComponentByTag(Ctxt, Actor, Tag);
}

#pragma endregion Component

// Visibility
#pragma region

bool UCsScriptLibrary_Actor::SetHiddenInGame(const FString& Context, AActor* Actor, const bool& NewHidden, const bool& ApplyToAttachChildren)
{
	CONDITIONAL_SET_CTXT(SetHiddenInGame);

	return ActorLibrary::SetSafeHiddenInGame(Context, Actor, NewHidden, ApplyToAttachChildren);
}

#pragma endregion Visibility

// Orientation
#pragma region

FQuat UCsScriptLibrary_Actor::GetQuat(const FString& Context, AActor* Actor)
{
	CONDITIONAL_SET_CTXT(GetQuat);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_RET_VALUE2(Actor, FQuat::Identity)

	return Actor->GetActorQuat();
}

bool UCsScriptLibrary_Actor::RotateByPitch(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport /*=ETeleportType::None*/)
{
	CONDITIONAL_SET_CTXT(RotateByPitch);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Actor)

	FQuat Q = Actor->GetActorQuat();

	MathLibrary::RotateByPitchDegrees(Q, Degrees);

	return Actor->SetActorRotation(Q, Teleport);
}

bool UCsScriptLibrary_Actor::RotateByYaw(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport /*=ETeleportType::None*/)
{
	CONDITIONAL_SET_CTXT(RotateByYaw);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Actor)

	FQuat Q = Actor->GetActorQuat();

	MathLibrary::RotateByYawDegrees(Q, Degrees);

	return Actor->SetActorRotation(Q, Teleport);
}

bool UCsScriptLibrary_Actor::RotateByRoll(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport /*=ETeleportType::None*/)
{
	CONDITIONAL_SET_CTXT(RotateByRoll);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Actor)

	FQuat Q = Actor->GetActorQuat();

	MathLibrary::RotateByRollDegrees(Q, Degrees);

	return Actor->SetActorRotation(Q, Teleport);
}

#pragma endregion Orientation

// Material
#pragma region

void UCsScriptLibrary_Actor::SetMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index)
{
	CONDITIONAL_SET_CTXT(SetMaterial);

	ActorLibrary::SetSafeMaterial(Ctxt, Actor, Material, Index);
}

void UCsScriptLibrary_Actor::SetMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials)
{
	CONDITIONAL_SET_CTXT(SetMaterials);

	ActorLibrary::SetSafeMaterials(Ctxt, Actor, Materials);
}

#pragma endregion Material

// Spawn
#pragma region

AActor* UCsScriptLibrary_Actor::SpawnBySoftObjectPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(SpawnBySoftObjectPath);

	return ActorLibrary::SafeSpawn(Ctxt, WorldContextObject, Path);
}

AActor* UCsScriptLibrary_Actor::SpawnByStringPath(const FString& Context, const UObject* WorldContextObject, const FString& Path)
{
	CONDITIONAL_SET_CTXT(SpawnByStringPath);

	return ActorLibrary::SafeSpawn(Ctxt, WorldContextObject, Path);
}

#pragma endregion Spawn

// Distance
#pragma region

float UCsScriptLibrary_Actor::GetDistanceSq(const FString& Context, AActor* A, AActor* B)
{
	CONDITIONAL_SET_CTXT(GetDistanceSq);

	return ActorLibrary::GetSafeDistanceSq(Ctxt, A, B);
}

float UCsScriptLibrary_Actor::GetDistanceSq2D(const FString& Context, AActor* A, AActor* B)
{
	CONDITIONAL_SET_CTXT(GetDistanceSq2D);

	return ActorLibrary::GetSafeDistanceSq2D(Ctxt, A, B);
}

bool UCsScriptLibrary_Actor::IsDistanceSq2D_LessThanOrEqual(const FString& Context, AActor* A, AActor* B, const float& R)
{
	CONDITIONAL_SET_CTXT(IsDistanceSq2D_LessThanOrEqual);

	return ActorLibrary::SafeIsDistanceSq2D_LessThanOrEqual(Ctxt, A, B, R);
}

#pragma endregion Distance

// Normal
#pragma region

bool UCsScriptLibrary_Actor::GetNormalAtoB(const FString& Context, AActor* A, AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance)
{
	CONDITIONAL_SET_CTXT(GetNormalAtoB);

	return ActorLibrary::GetSafeNormalAtoB(Ctxt, A, B, OutNormal, OutDistanceSq, OutDistance);
}

bool UCsScriptLibrary_Actor::GetNormal2DAtoB(const FString& Context, AActor* A, AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance)
{
	CONDITIONAL_SET_CTXT(GetNormal2DAtoB);

	return ActorLibrary::GetSafeNormal2DAtoB(Ctxt, A, B, OutNormal, OutDistanceSq, OutDistance);
}

#pragma endregion Normal

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SET_LOG_WARNING
#undef LogError
#undef ActorLibrary
#undef MathLibrary