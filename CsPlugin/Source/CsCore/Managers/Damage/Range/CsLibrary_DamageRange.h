// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRange.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct ICsDamageRange;

/**
* Library for interface: ICsDamageRange
*/
struct CSCORE_API FCsLibrary_DamageRange
{
	/**
	* Get the Interface Map from an Data with checks.
	* Range should implement the interface: ICsDamageRange.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsDamageRange>(Context, Range);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Range associated with ICsDamageRange") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Value		Range that implements the interface: ICsDamageRange.
	* return			Range casted to DerivedType (static_cast<DerivedType*>(Range))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsDamageRange>(Context, Range);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Range associated with ICsDamageRange") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Range casted to DerivedType (static_cast<DerivedType*>(Range))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsDamageRange>(Context, Range);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Range associated with ICsDamageRange") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Range casted to DerivedType (static_cast<DerivedType*>(Range))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsDamageRange>(Context, Range);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Range associated with ICsDamageRange") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Range casted to DerivedType (static_cast<DerivedType*>(Range))
	*/
	template<typename DerivedType>
	FORCEINLINE static const DerivedType* SafePureStaticCastChecked(const FString& Context, const ICsDamageRange* Range)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsDamageRange>(Context, Range);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Range associated with ICsDamageRange") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Range casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Range))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsDamageRange>(Context, Range);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Range associated with ICsDamageRange") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Range		Range that implements the interface: ICsDamageRange.
	* return			Range casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Range))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsDamageRange* Range)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageRange>(Context, Range);
	}

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsDamageRangeImpl (ICsDamageRange)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	static bool CopyChecked(const FString& Context, const ICsDamageRange* From, ICsDamageRange* To);
};