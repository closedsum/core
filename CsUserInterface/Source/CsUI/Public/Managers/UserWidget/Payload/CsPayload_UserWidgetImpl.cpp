// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_UserWidgetImpl::Name = FName("FCsPayload_UserWidgetImpl");;

FCsPayload_UserWidgetImpl::FCsPayload_UserWidgetImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
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

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsPayload_UserWidget>(static_cast<ICsPayload_UserWidget*>(this));
}

FCsPayload_UserWidgetImpl::~FCsPayload_UserWidgetImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_UserWidgetImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
	// ICsPayload_UserWidget
	Visibility = ESlateVisibility::SelfHitTestInvisible;
}

#pragma endregion ICsPayload_PooledObject