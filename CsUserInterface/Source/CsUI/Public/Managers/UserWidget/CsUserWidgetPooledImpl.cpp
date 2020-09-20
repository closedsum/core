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
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, OnConstructObject);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, Update);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, Allocate);
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

void UCsUserWidgetPooledImpl::OnConstructObject(const FCsManagerPooledObjectConstructParams& Params)
{
	using namespace NCsUserWidgetPooledImplCached;

	const FString& Context = Str::OnConstructObject;

	ConstructCache();

	// Create the UserWidget from Params.TypeName

		// Get the Manager_UserWidget
	UObject* MyOuter = GetOuter();

	checkf(MyOuter, TEXT("%s: Outer is NULL. No Outer set for %s."), *Context, *(GetName()));

	UCsManager_UserWidget* Manager_UserWidget = Cast<UCsManager_UserWidget>(MyOuter);

	checkf(Manager_UserWidget, TEXT("%s: Outer for %s is NOT of type: UCsManager_UserWidget."), *Context, *(GetName()));

	UWorld* World = Manager_UserWidget->GetWorld();

	checkf(World, TEXT("%s: World is NULL. No World associated with Manager_UserWidget."), *Context);

		// Get the UserWidget Type
	const FName& TypeName = Params.TypeName;

	checkf(TypeName != NAME_None, TEXT("%s: TypeName = None is NOT Valid."), *Context);

	const FECsUserWidget& UserWidgetType = EMCsUserWidget::Get().GetEnum(TypeName);
		
		// Get the Class
	FCsUserWidgetPtr* UserWidgetPtr = Manager_UserWidget->GetUserWidgetChecked(Context, UserWidgetType);

	UClass* Class = UserWidgetPtr->GetClass();

	checkf(Class, TEXT("%s: Failed to get Class from UserWidgetPtr of type: %s."), *Context, UserWidgetType.ToChar());

		// Create the Widget
	UserWidget = CreateWidget(World, Class);

	checkf(UserWidget, TEXT("%s: Failed to create UserWidget with Class: %s of type: %s."), *Context, *(Class->GetName()), UserWidgetType.ToChar());

	UserWidget->SetVisibility(ESlateVisibility::Collapsed);
	UserWidget->SetIsEnabled(false);
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

void UCsUserWidgetPooledImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsUserWidgetPooledImplCached;

	const FString& Context = Str::Allocate;

	FCsCache_UserWidgetImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_UserWidgetImpl>(Context, Cache);

	CacheImpl->Allocate(Payload);

	ICsPayload_UserWidget* UserWidgetPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_UserWidget>(Context, Payload);

	UserWidget->SetVisibility(UserWidgetPayload->GetVisibility());
	UserWidget->SetIsEnabled(true);
}

void UCsUserWidgetPooledImpl::Deallocate()
{
	UserWidget->SetVisibility(ESlateVisibility::Collapsed);
	UserWidget->SetIsEnabled(false);

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject


void UCsUserWidgetPooledImpl::ConstructCache()
{
	Cache = new FCsCache_UserWidgetImpl();
}