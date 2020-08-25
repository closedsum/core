// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Library for interface: ICsDamageModifier
*/
struct CSCORE_API FCsLibrary_DamageModifier
{
	/**
	* Get the Interface Map from an Data with checks.
	* Modifier should implement the interface: ICsDamageModifier.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsDamageModifier.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsDamageModifier") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsDamageModifier") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsDamageModifier") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsDamageModifier") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsDamageModifier") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageModifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsDamageModifier")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsDamageModifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsDamageModifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageModifier>(Context, Modifier);
	}
};