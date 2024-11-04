// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_StaticMesh.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Mesh
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
// Component
#include "Components/StaticMeshComponent.h"

namespace NCsStaticMesh
{
	using LogClassType = NCsCore::NLibrary::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

	// Load
	#pragma region

	UStaticMesh* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return CsObjectLibrary::LoadChecked<UStaticMesh>(Context, Path);
	}

	UStaticMesh* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UStaticMesh>(Context, Path, Log);
	}

	UStaticMesh* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		return CsObjectLibrary::LoadChecked<UStaticMesh>(Context, Path);
	}

	UStaticMesh* FLibrary::SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsObjectLibrary::SafeLoad<UStaticMesh>(Context, Path, Log);
	}

	#pragma endregion Load

	// Is
	#pragma region
	
	bool FLibrary::IsStaticMeshComponent(const UActorComponent* Component)
	{
		return Cast<UStaticMeshComponent>(Component) != nullptr;
	}
		
	#pragma endregion Is

	// Set
	#pragma region

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Component, UStaticMesh* Mesh)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		CS_IS_PTR_NULL_CHECKED(Mesh)

		Component->SetStaticMesh(Mesh);
	}

	#pragma endregion Set

	// Spawn
	#pragma region

	AStaticMeshActor* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const UStaticMeshComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		AStaticMeshActor* Actor = CsWorldLibrary::SpawnChecked<AStaticMeshActor>(Context, WorldContext);
			
		CopyChecked(Context, Component, Actor);
		return Actor;	
	}

	AStaticMeshActor* FLibrary::SpawnByActorComponentChecked(const FString& Context, const UObject* WorldContext, const UActorComponent* Component)
	{
		return SpawnChecked(Context, WorldContext, CS_CONST_CAST_CHECKED(Component, UActorComponent, UStaticMeshComponent));
	}

	#pragma endregion Spawn

	// Copy
	#pragma region
	
	void FLibrary::CopyChecked(const FString& Context, const UStaticMeshComponent* From, AStaticMeshActor* To)
	{
		CS_IS_PENDING_KILL_CHECKED(From)
		CS_IS_PENDING_KILL_CHECKED(To)

		UStaticMeshComponent* ToComponent = To->GetStaticMeshComponent();

		// TODO: Check for Collision Profile is "Custom"
		ECollisionEnabled::Type CollisionEnabled = From->GetCollisionEnabled();
		
		ToComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		To->Tags = From->ComponentTags;

		// TODO: Get information from From somehow?
		To->SetMobility(EComponentMobility::Movable);

		// Orientation
		To->SetActorLocationAndRotation(From->GetComponentLocation(), From->GetComponentQuat());
		To->SetActorScale3D(From->GetComponentScale());

		// Mesh
		CS_IS_PENDING_KILL_CHECKED(From->GetStaticMesh());

		ToComponent->SetStaticMesh(From->GetStaticMesh());
		
		// Materials
		if (!From->OverrideMaterials.IsEmpty())
		{
			CsMaterialLibrary::SetChecked(Context, ToComponent, From->OverrideMaterials);
		}

		// Collision
		ToComponent->SetCollisionResponseToChannels(From->GetCollisionResponseToChannels());
		ToComponent->SetCollisionObjectType(From->GetCollisionObjectType());
		if (FBodyInstance* BodyInstance = From->GetBodyInstance())
			ToComponent->SetNotifyRigidBodyCollision(BodyInstance->bNotifyRigidBodyCollision);
		ToComponent->SetGenerateOverlapEvents(From->GetGenerateOverlapEvents());

		ToComponent->SetCollisionEnabled(CollisionEnabled);

		// Visibility
		To->SetActorHiddenInGame(From->bHiddenInGame);
	}

	#pragma endregion Copy

	// Destroy
	#pragma region
	
	void FLibrary::SimulateDestroyChecked(const FString& Context, UStaticMeshComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		Component->SetVisibleFlag(false);
		Component->SetHiddenInGame(true);
		
		CsMaterialLibrary::ClearOverrideChecked(Context, Component);

		Component->SetStaticMesh(nullptr);
		Component->SetComponentTickEnabled(false);
		Component->Deactivate();
	}

	void FLibrary::SimulateDestroyByActorComponentChecked(const FString& Context, UActorComponent* Component)
	{
		SimulateDestroyChecked(Context, CS_CAST_CHECKED(Component, UActorComponent, UStaticMeshComponent));
	}

	#pragma endregion Destroy
}