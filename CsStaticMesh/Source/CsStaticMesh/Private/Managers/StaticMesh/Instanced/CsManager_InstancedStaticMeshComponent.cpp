// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Instanced/CsManager_InstancedStaticMeshComponent.h"
#include "CsStaticMesh.h"

// CVars
//#include "Managers/StaticMesh/CsCVars_Manager_StaticMeshActor.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/StaticMesh/Instanced/CsSettings_Manager_InstancedStaticMeshComponent.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/StaticMesh/Instanced/CsGetManagerInstancedStaticMeshComponent.h"
// Component
#include "Components/InstancedStaticMeshComponent.h"
// World
#include "Engine/World.h"

// Cached
#pragma region

namespace NCsManagerInstancedStaticMeshComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsManager_InstancedStaticMeshComponent, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsManager_InstancedStaticMeshComponent, Initialize);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// static initializations

ACsManager_InstancedStaticMeshComponent::ACsManager_InstancedStaticMeshComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	DefaultSceneRoot(nullptr),
	Components(),
	Internal()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetHiddenInGame(false);

	RootComponent = DefaultSceneRoot;
}

#define USING_NS_CACHED using namespace NCsManagerInstancedStaticMeshComponent::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerInstancedStaticMeshComponent::NCached; \
	const FString& Context = Str::__FunctionName
#define WorldLibrary NCsWorld::FLibrary

// UObject Interface
#pragma region

void ACsManager_InstancedStaticMeshComponent::BeginDestroy()
{
	Super::BeginDestroy();

	CleanUp();
}

#pragma endregion UObject Interface

// Singleton
#pragma region

/*static*/ ACsManager_InstancedStaticMeshComponent* ACsManager_InstancedStaticMeshComponent::Get(const UObject* InRoot)
{
	return Get_GetManagerInstancedStaticMeshComponent(InRoot)->GetManager_InstancedStaticMeshComponent();
}

/*static*/ ACsManager_InstancedStaticMeshComponent* ACsManager_InstancedStaticMeshComponent::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerInstancedStaticMeshComponent* GetManagerISMC = GetSafe_GetManagerInstancedStaticMeshComponent(Context, InRoot, Log))
		return GetManagerISMC->GetManager_InstancedStaticMeshComponent();
	return nullptr;
}

/*static*/ bool ACsManager_InstancedStaticMeshComponent::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerInstancedStaticMeshComponent(InRoot)->GetManager_InstancedStaticMeshComponent() != nullptr;
}

/*static*/ void ACsManager_InstancedStaticMeshComponent::Init(UObject* InRoot, TSubclassOf<ACsManager_InstancedStaticMeshComponent> ManagerInstancedStaticMeshComponentClass)
{
	SET_CONTEXT(Init);

	ICsGetManagerInstancedStaticMeshComponent* GetManagerISMC = Get_GetManagerInstancedStaticMeshComponent(InRoot);

	ACsManager_InstancedStaticMeshComponent* Manager_ISMC = GetManagerISMC->GetManager_InstancedStaticMeshComponent();

	if (!Manager_ISMC)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, InRoot);

		Manager_ISMC = World->SpawnActor<ACsManager_InstancedStaticMeshComponent>(ManagerInstancedStaticMeshComponentClass, FTransform3d::Identity);

		GetManagerISMC->SetManager_InstancedStaticMeshComponent(Manager_ISMC);

		Manager_ISMC->SetMyRoot(InRoot);
		Manager_ISMC->Initialize();
	}
	else
	{
		UE_LOG(LogCsStaticMesh, Warning, TEXT("ACsManager_InstancedStaticMeshComponent::Init: Init has already been called."));
	}
}

/*static*/ void ACsManager_InstancedStaticMeshComponent::Shutdown(UObject* InRoot)
{
	ICsGetManagerInstancedStaticMeshComponent* GetManagerISMC = Get_GetManagerInstancedStaticMeshComponent(InRoot);
	ACsManager_InstancedStaticMeshComponent* Manager_ISMC	  = GetManagerISMC->GetManager_InstancedStaticMeshComponent();

	if (Manager_ISMC)
		Manager_ISMC->CleanUp();

	GetManagerISMC->SetManager_InstancedStaticMeshComponent(nullptr);
}

/*static*/ bool ACsManager_InstancedStaticMeshComponent::HasShutdown(const UObject* InRoot)
{
	return Get_GetManagerInstancedStaticMeshComponent(InRoot)->GetManager_InstancedStaticMeshComponent() == nullptr;
}

/*static*/ ICsGetManagerInstancedStaticMeshComponent* ACsManager_InstancedStaticMeshComponent::Get_GetManagerInstancedStaticMeshComponent(const UObject* InRoot)
{
	checkf(InRoot, TEXT("ACsManager_InstancedStaticMeshComponent::Get_GetManagerInstancedStaticMeshComponent: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("ACsManager_InstancedStaticMeshComponent::Get_GetManagerInstancedStaticMeshComponent: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("ACsManager_InstancedStaticMeshComponent::Get_GetManagerInstancedStaticMeshComponent: Manager_Singleton is NULL."));

	ICsGetManagerInstancedStaticMeshComponent* GetManagerISMC = Cast<ICsGetManagerInstancedStaticMeshComponent>(Manager_Singleton);

	checkf(GetManagerISMC, TEXT("ACsManager_InstancedStaticMeshComponent::Get_GetManagerInstancedStaticMeshComponent: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerStaticMeshActor."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerISMC;
}

/*static*/ ICsGetManagerInstancedStaticMeshComponent* ACsManager_InstancedStaticMeshComponent::GetSafe_GetManagerInstancedStaticMeshComponent(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerInstancedStaticMeshComponent>(Manager_Singleton);
}

void ACsManager_InstancedStaticMeshComponent::Initialize()
{
	SET_CONTEXT(Initialize);

	DefaultSceneRoot->SetWorldTransform(FTransform3d::Identity);

	const FCsSettings_Manager_InstancedStaticMeshComponent& Settings = FCsSettings_Manager_InstancedStaticMeshComponent::Get();

	CS_IS_VALID_CHECKED(Settings);

	const int32& PoolSize = Settings.PoolSize;

	Components.Reset(PoolSize);
	Internal.CreatePool(PoolSize);
	
	typedef NCsStaticMesh::NInstanced::NComponent::FResource ResourceType;

	const TArray<ResourceType*>& Resources = Internal.GetPool();

	for (int32 I = 0; I < PoolSize; ++I)
	{
		FName ComponentName = FName(FString::Printf(TEXT("InstancedStaticMeshComponentPooled_%d"), I));
		UInstancedStaticMeshComponent* Component = NewObject<UInstancedStaticMeshComponent>(this, ComponentName);

		Component->RegisterComponent();
		Component->SetNotifyRigidBodyCollision(false);
		Component->SetGenerateOverlapEvents(false);
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Component->SetHiddenInGame(true);
		Component->SetCastShadow(false);
		Component->SetReceivesDecals(false);
		Component->bUseAsOccluder = false;
		Component->SetComponentTickEnabled(false);
		Component->SetWorldTransform(FTransform3d::Identity);
		Component->SetRelativeTransform(FTransform3d::Identity);
		Component->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);;

		Components.Add(Component);

		ResourceType* C = Resources[I];
		C->Set(Component);
	}

	bInitialized = true;
}

/*static*/ bool ACsManager_InstancedStaticMeshComponent::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void ACsManager_InstancedStaticMeshComponent::CleanUp()
{
	Internal.Shutdown();
	Components.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void ACsManager_InstancedStaticMeshComponent::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef WorldLibrary