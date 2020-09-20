// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

/**
*/
struct CSPRJ_API FCsLibrary_Payload_Projectile : public TCsLibrary_InterfaceMap<ICsPayload_Projectile>
{
public:

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsPayload_PooledObjectImplSlice (ICsPayload_PooledObject)
	*  FCsPayload_ProjecitleImplSlice (ICsPayload_Projectile)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the From copied to To successfully.
	*/
	static bool CopyChecked(const FString& Context, const ICsPayload_Projectile* From, ICsPayload_Projectile* To);

	// NOTE:

	/**
	* Copy the slice of values from From to To with checks.
	* Currently supports To types of:
	*  FCsInterface_PooledObjectImplSlice (ICsInterface_PooledObject)
	*  FCsInterface_ProjecitleImplSlice (InterfaceType)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the From copied to To successfully.
	*/
	//template<typename SliceType, typename SliceInterfaceType>
	//static bool CopySliceChecked(const FString& Context, const InterfaceType* From, InterfaceType* To)
};