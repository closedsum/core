// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsStatusEffect.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsStatusEffect;
/**
* Library for interface: ICsStatusEffect
*/
struct CSSE_API FCsLibrary_StatusEffect
{
	/**
	* Get the Interface Map from an Effect with checks.
	* Effect should implement the interface: ICsStatusEffect.
	*
	* @param Context	The calling context
	* @param Effect		Effect that implements the interface: ICsStatusEffect.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsStatusEffect* Effect)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsStatusEffect>(Context, Effect);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Effect associated with ICsStatusEffect") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Effect		Effect that implements the interface: ICsStatusEffect.
	* return			Effect casted to DerivedType (static_cast<DerivedType*>(Effect))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsStatusEffect* Effect)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsStatusEffect>(Context, Effect);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Effect associated with ICsStatusEffect") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Effect		Effect that implements the interface: ICsStatusEffect.
	* return			Effect casted to DerivedType (static_cast<DerivedType*>(Effect))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsStatusEffect* Effect)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsStatusEffect>(Context, Effect);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Effect associated with ICsStatusEffect") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Effect		Effect that implements the interface: ICsStatusEffect.
	* return			Effect casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Effect))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsStatusEffect* Effect)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsStatusEffect>(Context, Effect);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Effect associated with ICsStatusEffect") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Effect		Effect that implements the interface: ICsStatusEffect.
	* return			Effect casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Effect))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsStatusEffect* Effect)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffect>(Context, Effect);
	}
};