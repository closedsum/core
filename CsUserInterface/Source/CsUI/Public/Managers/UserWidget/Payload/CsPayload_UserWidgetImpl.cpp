// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsUserWidget::NPayload::FImpl::Name = FName("NCsUserWidget::NPayload::FImpl");;

namespace NCsUserWidget
{
	namespace NPayload
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// WidgetPayloadType (NCsUserWidget::NPayload::IPayload)
			Visibility(ESlateVisibility::SelfHitTestInvisible),
			bAddToViewport(false),
			RenderScale(1.0f),
			LifeTime(0.0f),
			Position(FVector2D::ZeroVector),
			ZOrder(0)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsUserWidget::NPayload::IPayload WidgetPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<WidgetPayloadType>(static_cast<WidgetPayloadType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImpl::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;
			PreserveChangesFromDefaultMask = 0;

			Time.Reset();
			// WidgetPayloadType (NCsUserWidget::NPayload::IPayload)
			Visibility = ESlateVisibility::SelfHitTestInvisible;
			bAddToViewport = false;
			RenderScale = 1.0f;
			LifeTime = 0.0f;
			Position = FVector2D::ZeroVector;
			ZOrder = 0;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}