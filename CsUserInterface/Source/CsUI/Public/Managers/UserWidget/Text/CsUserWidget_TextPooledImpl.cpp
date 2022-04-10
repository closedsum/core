// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Text/CsUserWidget_TextPooledImpl.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Widget.h"
// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// UserWidget
#include "Managers/UserWidget/Cache/CsCache_UserWidgetImpl.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_Text.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, Handle_AddToViewport);
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
	CurrentZOrder(0),
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

	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
	typedef NCsUserWidget::NPayload::IPayload WidgetPayloadType;

	WidgetPayloadType* WidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<WidgetPayloadType>(Context, Payload);

	SetVisibility(WidgetPayload->GetVisibility());
	SetIsEnabled(true);

	// NOTE: FUTURE: Add ability to "attach" / follow to the Parent object.
	//				 Add Handle_AddToCanvasPanelSlot

	Handle_AddToViewport(WidgetPayload);

	SetPositionInViewport(WidgetPayload->GetPosition());

	typedef NCsUserWidget::NPayload::NText::IText TextPayloadType;

	TextPayloadType* TextPayload = PooledPayloadLibrary::GetInterfaceChecked<TextPayloadType>(Context, Payload);

	MyText->SetText(TextPayload->GetText());
}

void UCsUserWidget_TextPooledImpl::Deallocate()
{
	SetVisibility(ESlateVisibility::Collapsed);
	SetIsEnabled(false);

	Handle_RemoveFromViewport();

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

	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Handle_AddToViewport;

	typedef NCsUserWidget::NPayload::EChange ChangeType;

	// If ADD to viewport, Mark the change
	if (Payload->ShouldAddToViewport())
	{
		const int32& ZOrder = Payload->GetZOrder();

		// If ALREADY added to viewport, Do Nothing
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AddedToViewport) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport))
		{
			// If ZOrder is the SAME, Do Nothing
			if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::ZOrder) &&
				CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::ZOrder) &&
				CurrentZOrder == ZOrder)
			{
				// Do Nothing
			}
			else
			{
				RemoveFromViewport();

				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* Player = PlayerLibrary::GetFirstLocalChecked(Context, this);

				AddToScreen(Player, ZOrder);
			}
		}
		else
		{
			typedef NCsPlayer::FLibrary PlayerLibrary;

			ULocalPlayer* Player = PlayerLibrary::GetFirstLocalChecked(Context, this);

			AddToScreen(Player, ZOrder);
		}

		CurrentZOrder = ZOrder;

		// Mark the change
		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::ZOrder);
	}
	// Clear change
	else
	{
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::ZOrder);
	}
}

void UCsUserWidget_TextPooledImpl::Handle_RemoveFromViewport()
{
	typedef NCsUserWidget::NPayload::EChange ChangeType;

	const uint32 Mask = PreserveChangesToDefaultMask & ChangesToDefaultMask;

	// Keep in viewport
	if (CS_TEST_BITFLAG(Mask, ChangeType::AddedToViewport))
	{
		// Do Nothing
	}
	else
	{
		RemoveFromViewport();
		CurrentZOrder = 0;
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::ZOrder);
	}
}