// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActorPooledImpl.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// WidgetActor
#include "Managers/WidgetActor/Cache/CsCache_WidgetActorImpl.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"
// Components
#include "Components/CsWidgetComponent.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

// Cached
#pragma region

namespace NCsWidgetActorPooledImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(BeginPlay, "ACsWidgetActorPooledImpl::BeginPlay");
		CS_DEFINE_CACHED_STRING(Update, "ACsWidgetActorPooledImpl::Update");
		CS_DEFINE_CACHED_STRING(Allocate, "ACsWidgetActorPooledImpl::Allocate");
	}
}

#pragma endregion Cached

ACsWidgetActorPooledImpl::ACsWidgetActorPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Widget Component
	WidgetComponent = ObjectInitializer.CreateDefaultSubobject<UCsWidgetComponent>(this, TEXT("WidgetComponent"));
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//WidgetComponent->SetCollisionObjectType(CS_COLLISION_PROJECTILE);
	WidgetComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WidgetComponent->SetGenerateOverlapEvents(false);
	WidgetComponent->bReturnMaterialOnMove = true;
	WidgetComponent->SetNotifyRigidBodyCollision(false);
	WidgetComponent->PrimaryComponentTick.bStartWithTickEnabled = false;

	WidgetComponent->Deactivate();

	RootComponent = WidgetComponent;
}

// UObject Interface
#pragma region

void ACsWidgetActorPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsWidgetActorPooledImpl::BeginPlay()
{
	using namespace NCsWidgetActorPooledImplCached;

	const FString& Context = Str::BeginPlay;

	Super::BeginPlay();

	WidgetComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();
}

#pragma endregion AActor Interface

// AActor Interface
#pragma region

void ACsWidgetActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

void ACsWidgetActorPooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsWidgetActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsWidgetActorPooledImplCached;

	const FString& Context = Str::Update;

	FCsCache_WidgetActorImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_WidgetActorImpl>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

void ACsWidgetActorPooledImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsWidgetActorPooledImplCached;

	const FString& Context = Str::Allocate;

	// Get / Assign UserWidget
	ICsPayload_WidgetActor* WidgetActorPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_WidgetActor>(Context, Payload);
	{
		// Passing reference to UserWidget
		if (UUserWidget* UserWidget = WidgetActorPayload->GetUserWidget())
		{
			WidgetComponent->SetWidget(UserWidget);
		}
		// Passing UserWidgetPooledType
		else
		{
			// Get "slice" ICsPayload_WidgetActorUserWidget
			ICsPayload_WidgetActorUserWidget* WidgetActorUserWidgetPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_WidgetActorUserWidget>(Context, Payload);

				// Get type
			const FECsUserWidgetPooled& UserWidgetPooledType = WidgetActorUserWidgetPayload->GetUserWidgetPooledType();

			checkf(EMCsUserWidgetPooled::Get().IsValidEnum(UserWidgetPooledType), TEXT("%s: UserWidgetPooledType: %s is NOT Valid from Payload(ICsPayload_WidgetActor)->GetUserWidgetPooledType()."), *Context, UserWidgetPooledType.ToChar());
				// Get payload (ICsPayload_UserWidget)
			ICsPayload_UserWidget* UserWidgetPayload = WidgetActorUserWidgetPayload->GetUserWidgetPayload();

			checkf(UserWidgetPayload, TEXT("%s: UserWidgetPayload is NULL from Payload(ICsPayload_WidgetActorUserPayload)->GetUserWidgetPayload()."), *Context)
				// "Spawn" / allocate UserWidget
			UCsManager_UserWidget* UManager_UserWidget = UCsManager_UserWidget::Get(GetWorld()->GetGameState());

			UserWidgetPooled = const_cast<FCsUserWidgetPooled*>(UManager_UserWidget->Spawn(UserWidgetPooledType, UserWidgetPayload));

			WidgetComponent->SetWidget(UserWidgetPooled->GetUserWidget());
		}	
	}

	FCsCache_WidgetActorImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_WidgetActorImpl>(Context, Cache);

	CacheImpl->Allocate(Payload);

	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);

	WidgetComponent->Activate();
	WidgetComponent->SetHiddenInGame(false);
	WidgetComponent->SetComponentTickEnabled(true);

	// If the Parent is set, attach the WidgetComponent to the Parent
	if (UObject* Parent = Payload->GetParent())
	{
		USceneComponent* ComponentToAttachTo = nullptr;

		// Actor
		if (AActor* Actor = Cast<AActor>(Parent))
		{
			ComponentToAttachTo = Actor->GetRootComponent();
		}
		// SceneComponent
		else
		{
			ComponentToAttachTo = Cast<USceneComponent>(Parent);
		}

		if (ComponentToAttachTo)
		{
			AttachToComponent(ComponentToAttachTo, NCsAttachmentTransformRules::ToRule(WidgetActorPayload->GetAttachmentTransformRule()), WidgetActorPayload->GetBone());

			const FTransform& Transform = WidgetActorPayload->GetTransform();
			const int32& TransformRules = WidgetActorPayload->GetTransformRules();
		
			// Location | Rotation | Scale
			if (TransformRules == NCsTransformRules::All)
			{
				SetActorRelativeTransform(Transform);
			}
			else
			{
				// Location
				if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Location))
				{
					SetActorRelativeLocation(Transform.GetLocation());
				}
				// Rotation
				if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Rotation))
				{
					SetActorRelativeRotation(Transform.GetRotation().Rotator());
				}
				// Scale
				if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Scale))
				{
					SetActorRelativeScale3D(Transform.GetScale3D());
				}
			}
		}
		// NO Component, set the World Transform of the WidgetComponent
		else
		{
			SetActorTransform(WidgetActorPayload->GetTransform());
		}
	}
	// NO Parent, set the World Transform of the WidgetComponent
	else
	{
		SetActorTransform(WidgetActorPayload->GetTransform());
	}
}

void ACsWidgetActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsWidgetActorPooledImpl::Deallocate_Internal()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	WidgetComponent->SetComponentTickEnabled(false);
	WidgetComponent->Deactivate();

	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	// "Free" Widget
	if (UserWidgetPooled)
	{
		UserWidgetPooled->GetCache()->QueueDeallocate();
	}
	UserWidgetPooled = nullptr;
	WidgetComponent->SetWidget(nullptr);
}

void ACsWidgetActorPooledImpl::ConstructCache()
{
	Cache = new FCsCache_WidgetActorImpl();
}