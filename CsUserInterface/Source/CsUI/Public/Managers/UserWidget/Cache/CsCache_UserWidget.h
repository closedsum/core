// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#pragma once

/**
* Cache associated with an UserWidget
*  The Manager for UserWidget primarily interacts with the Cache object in terms
*  of allocation and deallocation.
*/
struct CSUI_API ICsCache_UserWidget : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsCache_UserWidget() {}
};