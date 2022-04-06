// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Text/CsUserWidget_TextPooledImpl.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
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
// Component
#include "Components/TextBlock.h"

// Cached
#pragma region

namespace NCsUserWidgetTextPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, OnConstructObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, Allocate);
		}
	}
}

#pragma endregion Cached

UCsUserWidget_TextPooledImpl::UCsUserWidget_TextPooledImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	MyText(nullptr)
{
}

// UObject Interface
#pragma region
void UCsUserWidget_TextPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}
}

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
void UCsUserWidget_TextPooledImpl::OnConstructObject(const ConstructParamsType& Params)
{
#undef ConstructParamsType

	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::OnConstructObject;

	ConstructCache();

	SetVisibility(ESlateVisibility::Collapsed);
	SetIsEnabled(false);
}

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region

void UCsUserWidget_TextPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Update;

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

#define PayloadType NCsPooledObject::NPayload::IPayload
void UCsUserWidget_TextPooledImpl::Allocate(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CacheImpl->Allocate(Payload);

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	typedef NCsUserWidget::NPayload::IPayload UserWidgetPayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	UserWidgetPayloadType* UserWidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<UserWidgetPayloadType>(Context, Payload);

	SetVisibility(UserWidgetPayload->GetVisibility());
	SetIsEnabled(true);

	Handle_AddToViewport(UserWidgetPayload);
}

void UCsUserWidget_TextPooledImpl::Deallocate()
{
	SetVisibility(ESlateVisibility::Collapsed);
	SetIsEnabled(false);

	typedef NCsUserWidget::NPayload::EChange ChangeType;

	// Keep in viewport
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AddedToViewport) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport))
	{
		// Do Nothing
	}
	else
	{
		RemoveFromViewport();
	}

	PreserveChangesToDefaultMask = 0;

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject


void UCsUserWidget_TextPooledImpl::ConstructCache()
{
	typedef NCsUserWidget::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

#define UserWidgetPayloadType NCsUserWidget::NPayload::IPayload
void UCsUserWidget_TextPooledImpl::Handle_AddToViewport(UserWidgetPayloadType* Payload)
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
			AddToViewport();
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