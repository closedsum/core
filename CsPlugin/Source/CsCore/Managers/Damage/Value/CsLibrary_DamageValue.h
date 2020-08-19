// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct ICsDamageValue;

/**
* Library for interface: ICsDamageValue
*/
struct CSCORE_API FCsLibrary_DamageValue
{
	/**
	* Get the Interface Map from an Data with checks.
	* Value should implement the interface: ICsDamageValue.
	*
	* @param Context	The calling context
	* @param Value		Value that implements the interface: ICsDamageValue.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsDamageValue>(Context, Value);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Value associated with ICsDamageValue") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Value		Value that implements the interface: ICsDamageValue.
	* return			Value casted to DerivedType (static_cast<DerivedType*>(Value))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsDamageValue>(Context, Value);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Value associated with ICsDamageValue") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Value		Value that implements the interface: ICsDamageValue.
	* return			Value casted to DerivedType (static_cast<DerivedType*>(Value))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsDamageValue>(Context, Value);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsDamageValue") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Value		Value that implements the interface: ICsDamageValue.
	* return			Value casted to DerivedType (static_cast<DerivedType*>(Value))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsDamageValue>(Context, Value);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Value associated with ICsDamageValue") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Value that implements the interface: ICsDamageValue.
	* return			Value casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Value))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsDamageValue>(Context, Value);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Value associated with ICsDamageValue") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Value that implements the interface: ICsDamageValue.
	* return			Value casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Value))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsDamageValue* Value)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageValue>(Context, Value);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Value associated with ICsDamageValue")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Value that implements the interface: ICsDamageValue.
	* return			Value casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Value))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsDamageValue* Value)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageValue>(Context, Value);
	}

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsDamageValuePointImpl (ICsDamageValuePoint)
	*  FCsDamageValueRangeImpl (ICsDamageValueRange)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	static bool CopyChecked(const FString& Context, const ICsDamageValue* From, ICsDamageValue* To);
};