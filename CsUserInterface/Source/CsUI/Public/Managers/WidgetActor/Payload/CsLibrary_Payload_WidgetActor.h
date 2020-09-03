// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

/**
*/
struct CSUI_API FCsLibrary_Payload_WidgetActor : public TCsLibrary_InterfaceMap<ICsPayload_WidgetActor>
{
public:

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the From copied to To successfully.
	*/
	static bool CopyChecked(const FString& Context, const ICsPayload_WidgetActor* From, ICsPayload_WidgetActor* To);

	// NOTE:

	/**
	* Copy the slice of values from From to To with checks.
	* Currently supports To types of:
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the From copied to To successfully.
	*/
	//template<typename SliceType, typename SliceInterfaceType>
	//static bool CopySliceChecked(const FString& Context, const InterfaceType* From, InterfaceType* To)
};