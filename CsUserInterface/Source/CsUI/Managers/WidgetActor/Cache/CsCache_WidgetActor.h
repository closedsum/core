// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

class UCsWidgetComponent;

/**
* Cache associated with an object that implements the interface: ICsWidgetActor
*  The Manager for Widget Actor primarily interacts with the Cache object in terms
*  of allocation and deallocation.
*/
struct CSUI_API ICsCache_WidgetActor : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsCache_WidgetActor() {}

	/**
	*
	*
	* return
	*/
	virtual UCsWidgetComponent* GetWidgetComponent() const = 0;
};