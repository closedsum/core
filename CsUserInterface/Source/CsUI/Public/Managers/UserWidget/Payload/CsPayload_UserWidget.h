// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#pragma once

/**
*/
struct CSUI_API ICsPayload_UserWidget : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPayload_UserWidget(){}
};