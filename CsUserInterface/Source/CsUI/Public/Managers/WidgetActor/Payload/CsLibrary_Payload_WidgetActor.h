// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"

/**
*/
struct CSUI_API FCsLibrary_Payload_WidgetActor : public NCsInterfaceMap::TLibrary<NCsWidgetActor::NPayload::IPayload>
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
	static bool CopyChecked(const FString& Context, const NCsWidgetActor::NPayload::IPayload* From, NCsWidgetActor::NPayload::IPayload* To);

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