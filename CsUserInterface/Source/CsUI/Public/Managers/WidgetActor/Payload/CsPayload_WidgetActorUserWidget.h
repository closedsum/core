// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#pragma once

struct ICsPayload_UserWidget;

/**
*/
struct CSUI_API ICsPayload_WidgetActorUserWidget : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPayload_WidgetActorUserWidget(){}

	/**
	* Get the UserWidgetPooled Type.
	*  "Spawn" (allocate) an object that implements the interface: ICsUserWidgetPooled 
	*   and contains a reference to a UUserObject from the type GetUserWidgetType() from Manager_UserWidget.
	*
	* return UserWidgetPooled type.
	*/
	virtual const FECsUserWidgetPooled& GetUserWidgetPooledType() const = 0;

	/**
	*
	*
	* return
	*/
	virtual ICsPayload_UserWidget* GetUserWidgetPayload() const = 0;
};