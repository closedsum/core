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
};