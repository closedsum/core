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
			// NCsPooledObject::NPayload::IPayload
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// NCsUserWidget::NPayload::IPayload
			Visibility(ESlateVisibility::SelfHitTestInvisible),
			bAddToViewport(false)
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

		// NCsPooledObject::NPayload::IPayload
		#pragma region

		void FImpl::Reset()
		{
			// NCsPooledObject::NPayload::IPayload
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;
			PreserveChangesFromDefaultMask = 0;

			Time.Reset();
			// NCsUserWidget::NPayload::IPayload
			Visibility = ESlateVisibility::SelfHitTestInvisible;
			bAddToViewport = false;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}