// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_UserWidgetImpl::Name = FName("FCsPayload_UserWidgetImpl");;

FCsPayload_UserWidgetImpl::FCsPayload_UserWidgetImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// NCsPooledObject::NPayload::IPayload
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	// ICsPayload_UserWidget
	Visibility(ESlateVisibility::SelfHitTestInvisible)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_UserWidgetImpl::Name);

	InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
	InterfaceMap->Add<ICsPayload_UserWidget>(static_cast<ICsPayload_UserWidget*>(this));
}

FCsPayload_UserWidgetImpl::~FCsPayload_UserWidgetImpl()
{
	delete InterfaceMap;
}

// NCsPooledObject::NPayload::IPayload
#pragma region

void FCsPayload_UserWidgetImpl::Reset()
{
	// NCsPooledObject::NPayload::IPayload
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
	// ICsPayload_UserWidget
	Visibility = ESlateVisibility::SelfHitTestInvisible;
}

#pragma endregion NCsPooledObject::NPayload::IPayload