// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsStatusEffectModifier.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Library for interface: ICsStatusEffectModifier
*/
struct CSSE_API FCsLibrary_StatusEffectModifier
{
	/**
	* Get the Interface Map from an Data with checks.
	* Modifier should implement the interface: ICsStatusEffectModifier.
	*
	* @param Context	The calling context
	* @param Modifier	Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsStatusEffectModifier") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Modifier	Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsStatusEffectModifier") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier	Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffectModifier") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier	Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffectModifier") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffectModifier") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffectModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffectModifier")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffectModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsStatusEffectModifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffectModifier>(Context, Modifier);
	}
};