// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct ICsStatusEffectEvent;
/**
* Library for interface: ICsStatusEffectEvent
*/
struct CSSE_API FCsLibrary_StatusEffectEvent
{
	/**
	* Get the Interface Map from an Event with checks.
	* Event should implement the interface: ICsStatusEffectEvent.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffectEvent") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffectEvent") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffectEvent") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static const DerivedType* PureStaticCastChecked(const FString& Context, const ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffectEvent") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Event associated with ICsStatusEffectEvent") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Event))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Event associated with ICsStatusEffectEvent") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Event))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Event associated with ICsStatusEffectEvent")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsStatusEffectEvent.
	* return			Event casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Event))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsStatusEffectEvent* Event)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffectEvent>(Context, Event);
	}

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsDamageEventImpl (ICsDamageEvent)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the copy was performed successfully.
	*/
	static bool CopyChecked(const FString& Context, const ICsStatusEffectEvent* From, ICsStatusEffectEvent* To);
};