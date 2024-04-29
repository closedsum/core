// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/CsUserWidgetPooledImpl.h"
#include "CsUI.h"

// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
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

namespace NCsUserWidgetPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, OnConstructObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidgetPooledImpl, Allocate);
		}
	}
}

#pragma endregion Cached

UCsUserWidgetPooledImpl::UCsUserWidgetPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Shutdown
	bShutdown(false),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	UserWidget(nullptr)
{
}

// UObject Interface
#pragma region

void UCsUserWidgetPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
void UCsUserWidgetPooledImpl::OnConstructObject(const ConstructParamsType& Params)
{
#undef ConstructParamsType

	using namespace NCsUserWidgetPooledImpl::NCached;

	const FString& Context = Str::OnConstructObject;

	ConstructCache();

	// Create the UserWidget from Params.TypeName

		// Get the Manager_UserWidget
	UObject* MyOuter = GetOuter();

	checkf(MyOuter, TEXT("%s: Outer is NULL. No Outer set for %s."), *Context, *(GetName()));

	UCsManager_UserWidget* Manager_UserWidget = Cast<UCsManager_UserWidget>(MyOuter);

	checkf(Manager_UserWidget, TEXT("%s: Outer for %s is NOT of type: UCsManager_UserWidget."), *Context, *(GetName()));

	UWorld* World = Manager_UserWidget->GetMyRoot()->GetWorld();

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
	using namespace NCsUserWidgetPooledImpl::NCached;

	const FString& Context = Str::Update;

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsShutdown
#pragma region

void UCsUserWidgetPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}

	if (IsValid(UserWidget))
	{
		UserWidget->MarkAsGarbage();
		UserWidget = nullptr;
	}
	bShutdown = true;
}

#pragma endregion ICsShutdown

// ICsPooledObject
#pragma region

#define PayloadType NCsPooledObject::NPayload::IPayload
void UCsUserWidgetPooledImpl::Allocate(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsUserWidgetPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CacheImpl->Allocate(Payload);

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	typedef NCsUserWidget::NPayload::IPayload UserWidgetPayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	UserWidgetPayloadType* UserWidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<UserWidgetPayloadType>(Context, Payload);

	UserWidget->SetVisibility(UserWidgetPayload->GetVisibility());
	UserWidget->SetIsEnabled(true);

	Handle_AddToViewport(UserWidgetPayload);
}

void UCsUserWidgetPooledImpl::Deallocate()
{
	UserWidget->SetVisibility(ESlateVisibility::Collapsed);
	UserWidget->SetIsEnabled(false);

	typedef NCsUserWidget::NPayload::EChange ChangeType;

	// Keep in viewport
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AddedToViewport) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport))
	{
		// Do Nothing
	}
	else
	{
		UserWidget->RemoveFromParent();
	}

	PreserveChangesToDefaultMask = 0;

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void UCsUserWidgetPooledImpl::ConstructCache()
{
	typedef NCsUserWidget::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

#define UserWidgetPayloadType NCsUserWidget::NPayload::IPayload
void UCsUserWidgetPooledImpl::Handle_AddToViewport(UserWidgetPayloadType* Payload)
{
#undef UserWidgetPayloadType

	typedef NCsUserWidget::NPayload::EChange ChangeType;

	// If ADD to viewport, Mark the change
	if (Payload->ShouldAddToViewport())
	{
		// If ALREADY added to viewport, Do Nothing
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AddedToViewport) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport))
		{
			// Do Nothing
		}
		else
		{
			UserWidget->AddToViewport();
		}
		// Mark the change
		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
	}
	// Clear change
	else
	{
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
	}
}