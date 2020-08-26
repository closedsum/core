// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsData_Damage;
struct ICsDamageValue;
struct ICsDamageRange;

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

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the copy was performed successfully.
	*/
	static bool CopyChecked(const FString& Context, const ICsDamageModifier* From, ICsDamageModifier* To);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Modifier
	* @param Data
	* @param Value
	* return			Whether the Modify was "attempted" (a Modify method was called) successfully.
	*/
	static bool ModifyChecked(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageValue* Value);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Modifier
	* @param Data
	* @param Range
	* return			Whether the Modify was "attempted" (a Modify method was called) successfully.
	*/
	static bool ModifyChecked(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageRange* Range);
};