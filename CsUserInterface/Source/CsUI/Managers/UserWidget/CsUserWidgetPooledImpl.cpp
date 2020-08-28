// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsUserWidgetPooledImpl.h"
#include "CsUI.h"

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
// UserWidget
#include "Managers/UserWidget/Cache/CsCache_UserWidgetImpl.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImpl.h"
#include "Blueprint/UserWidget.h"

// Cached
#pragma region

namespace NCsUserWidgetPooledImplCached
{
	namespace Str
	{
		const FString Update = TEXT("UCsUserWidgetPooledImpl::Update");
		const FString Allocate = TEXT("UCsUserWidgetPooledImpl::Allocate");
	}
}

#pragma endregion Cached

UCsUserWidgetPooledImpl::UCsUserWidgetPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region
void UCsUserWidgetPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
}

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region

void UCsUserWidgetPooledImpl::OnConstructObject()
{
	ConstructCache();

	UObject* MyOuter = GetOuter();

	checkf(MyOuter, TEXT("UCsUserWidgetPooledImpl::OnConstructObject: Outer is NULL. No Outer set for %s."), *(GetName()));

	UCsManager_UserWidget* Manager_UserWidget = Cast<UCsManager_UserWidget>(MyOuter);

	checkf(Manager_UserWidget, TEXT("UCsUserWidgetPooledImpl::OnConstructObject: Outer for %s is NOT of type: UCsManager_UserWidget."), *(GetName()));

	UWorld* World = Manager_UserWidget->GetWorld();

	checkf(World, TEXT("UCsUserWidgetPooledImpl::OnConstructObject: World is NULL. No World associated with Manager_UserWidget."));

	/*
	FActorSpawnParameters Params;

	FX = World->SpawnActor<ANiagaraActor>(ANiagaraActor::StaticClass(), Params);

	checkf(FX, TEXT("UCsFXActorPooledImpl::OnConstructObject: Failed to spawn FX of type: ANiagaraActor."));
	*/
}

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region

void UCsUserWidgetPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsUserWidgetPooledImplCached;

	const FString& Context = Str::Update;

	FCsCache_UserWidgetImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_UserWidgetImpl>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

ICsPooledObjectCache* UCsUserWidgetPooledImpl::GetCache() const
{
	return Cache;
}

void UCsUserWidgetPooledImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsUserWidgetPooledImplCached;

	const FString& Context = Str::Allocate;

	FCsCache_UserWidgetImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_UserWidgetImpl>(Context, Cache);

	CacheImpl->Allocate(Payload);

	//CacheImpl->SetUserWidget(UserWidget);

	ICsPayload_UserWidget* UserWidgetPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_UserWidget>(Context, Payload);

	// TODO: Payload should have SlateVisibility
	//UserWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//UserWidget->SetIsEnabled(true);
}

void UCsUserWidgetPooledImpl::Deallocate()
{
	//UserWidget->SetIsEnabled(false);
	//UserWidget->SetVisibility(ESlateVisibility::Collapsed);
}

#pragma endregion ICsPooledObject


void UCsUserWidgetPooledImpl::ConstructCache()
{
	Cache = new FCsCache_UserWidgetImpl();
}