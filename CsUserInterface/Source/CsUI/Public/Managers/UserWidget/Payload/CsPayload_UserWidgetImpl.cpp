// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// NCsUserWidget::NPayload::IPayload
			Visibility(ESlateVisibility::SelfHitTestInvisible)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsUserWidget::NPayload::IPayload>(static_cast<NCsUserWidget::NPayload::IPayload*>(this));
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
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
			// NCsUserWidget::NPayload::IPayload
			Visibility = ESlateVisibility::SelfHitTestInvisible;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}