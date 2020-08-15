// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct ICsDamageEvent;
/**
* Library for interface: ICsDamageEvent
*/
struct CSCORE_API FCsLibrary_DamageEvent
{
	/**
	* Get the Interface Map from an Event with checks.
	* Event should implement the interface: ICsDamageEvent.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsDamageEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Event associated with ICsDamageEvent") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsDamageEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Event associated with ICsDamageEvent") with checks.
	* DerivedType is NOT abstract.
	* Event NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsDamageEvent>(Context, Event);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsDamageEvent") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Event does NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Event casted to DerivedType (static_cast<DerivedType*>(Event))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsDamageEvent>(Context, Event);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Event associated with ICsDamageEvent") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Event casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Event))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsDamageEvent>(Context, Event);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Event associated with ICsDamageEvent") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Event		Event that implements the interface: ICsDamageEvent.
	* return			Event casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Event))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsDamageEvent* Event)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageEvent>(Context, Event);
	}

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsDamageEventImpl (ICsDamageEvent)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	static void CopyChecked(const FString& Context, ICsDamageEvent* From, ICsDamageEvent* To);

	/**
	* Set the damage on the Event with checks.
	*
	* @param Context	The calling context.
	* @param Event
	*/
	static void SetDamageChecked(const FString&, ICsDamageEvent* Event);
};