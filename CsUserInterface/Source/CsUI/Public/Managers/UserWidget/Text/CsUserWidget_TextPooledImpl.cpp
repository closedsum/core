// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Text/CsUserWidget_TextPooledImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/UserWidget/CsLibrary_Manager_UserWidget.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
	// Common
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Widget.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
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

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_TextPooledImpl)

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsUserWidget_TextPooledImpl, Handle_AddToViewport);
		}
	}
}

#pragma endregion Cached

UCsUserWidget_TextPooledImpl::UCsUserWidget_TextPooledImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	// Shutdown
	bShutdown(false),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	SetPositionInViewport_ID(INDEX_NONE),
	CurrentZOrder(0),
	MyText(nullptr)
{
}

using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
using PayloadType = NCsUserWidget::NPayload::IPayload;
using ChangeType = NCsUserWidget::NPayload::EChange;
using CacheImplType = NCsUserWidget::NCache::NImpl::FImpl;

// UObject Interface
#pragma region

void UCsUserWidget_TextPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region


void UCsUserWidget_TextPooledImpl::OnConstructObject(const ConstructParamsType& Params)
{
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

	// TODO: Move to Batch call
	
	// World
	/*
	if (PositionType == NCsUserWidget::EPosition::World)
	{
		typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

		if (OffsetType == NCsUserWidget::EPosition::Screen)
		{
			FVector2D Pos;
			const bool Result = ViewportLibrary::ProjectWorldToScreenChecked(Context, this, Position, Pos);

			Pos += FVector2D(Offset);

			SetPositionInViewport(Pos);
		}
		else
		if (OffsetType == NCsUserWidget::EPosition::World)
		{
			FVector2D Pos;
			const bool Result = ViewportLibrary::ProjectWorldToScreenChecked(Context, this, Position + Offset, Pos);

			SetPositionInViewport(Pos);
		}
	}
	*/
}

#pragma endregion ICsUpdate

// ICsShutdown
#pragma region

void UCsUserWidget_TextPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}
	bShutdown = true;
}

#pragma endregion ICsShutdown

// ICsPooledObject
#pragma region

void UCsUserWidget_TextPooledImpl::Allocate(PooledPayloadType* Payload)
{
	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CacheImpl->Allocate(Payload);

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	PayloadType* WidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	SetVisibility(WidgetPayload->GetVisibility());
	SetIsEnabled(true);

	// NOTE: FUTURE: Add ability to "attach" / follow to the Parent object.
	//				 Add Handle_AddToCanvasPanelSlot

	Handle_AddToViewport(WidgetPayload);

	const NCsUserWidget::EPosition& PositionType = WidgetPayload->GetPositionType();
	const NCsUserWidget::EPosition& OffsetType	 = WidgetPayload->GetOffsetType();

	// Screen
	if (PositionType == NCsUserWidget::EPosition::Screen)
	{
		SetPositionInViewport(FVector2d(CsMathLibrary::Convert(WidgetPayload->GetPosition())));
	}
	// World
	else
	if (PositionType == NCsUserWidget::EPosition::World)
	{
		typedef NCsUserWidget::NManager::NSetPositionInViewports::FLibrary SetPositionInViewportsLibrary;

		SetPositionInViewport_ID = SetPositionInViewportsLibrary::AllocateChecked(Context, this, this);

		typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

		FVector3f WorldPosition = WidgetPayload->GetPosition();
		FVector2f Offset	    = FVector2f::ZeroVector;

		if (OffsetType == NCsUserWidget::EPosition::Screen)
		{
			Offset = FVector2f(WidgetPayload->GetOffset());
		}
		else
		if (OffsetType == NCsUserWidget::EPosition::World)
		{
			WorldPosition += WidgetPayload->GetOffset();
		}

		SetPositionInViewportsLibrary::UpdateWorldPositionAndOffsetChecked(Context, this, SetPositionInViewport_ID, WorldPosition, Offset);
	}
	// Parent
	else
	if (PositionType == NCsUserWidget::EPosition::Parent)
	{
		// TODO:
	}

	typedef NCsUserWidget::NPayload::NText::IText TextPayloadType;

	TextPayloadType* TextPayload = PooledPayloadLibrary::GetInterfaceChecked<TextPayloadType>(Context, Payload);

	MyText->SetText(TextPayload->GetText());

	// Anim
	if (WidgetPayload->HasAnimParams())
	{
		typedef NCsWidget::NAnimation::FLibrary AnimLibrary;

		AnimLibrary::PlayChecked(Context, this, WidgetPayload->GetAnimParams());
	}
}

void UCsUserWidget_TextPooledImpl::Deallocate()
{
	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Deallocate;

	SetVisibility(ESlateVisibility::Collapsed);
	SetIsEnabled(false);

	Handle_RemoveFromViewport();

	if (SetPositionInViewport_ID != INDEX_NONE)
	{
		typedef NCsUserWidget::NManager::NSetPositionInViewports::FLibrary SetPositionInViewportsLibrary;

		 SetPositionInViewportsLibrary::DeallocateChecked(Context, this, SetPositionInViewport_ID);
	}

	SetPositionInViewport_ID = INDEX_NONE;

	PreserveChangesToDefaultMask = 0;

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void UCsUserWidget_TextPooledImpl::ConstructCache()
{
	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

void UCsUserWidget_TextPooledImpl::Handle_AddToViewport(PayloadType* Payload)
{
	using namespace NCsUserWidgetTextPooledImpl::NCached;

	const FString& Context = Str::Handle_AddToViewport;

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
				RemoveFromParent();

				ULocalPlayer* Player = CsPlayerLibrary::GetFirstLocalChecked(Context, GetWorldContext());

				CsWidgetLibrary::AddToScreenChecked(Context, GetWorldContext(), this, Player, ZOrder);
			}
		}
		else
		{
			ULocalPlayer* Player = CsPlayerLibrary::GetFirstLocalChecked(Context, GetWorldContext());

			CsWidgetLibrary::AddToScreenChecked(Context, GetWorldContext(), this, Player, ZOrder);
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
	const uint32 Mask = PreserveChangesToDefaultMask & ChangesToDefaultMask;

	// Keep in viewport
	if (CS_TEST_BITFLAG(Mask, ChangeType::AddedToViewport))
	{
		// Do Nothing
	}
	else
	{
		RemoveFromParent();
		CurrentZOrder = 0;
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::AddedToViewport);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::ZOrder);
	}
}