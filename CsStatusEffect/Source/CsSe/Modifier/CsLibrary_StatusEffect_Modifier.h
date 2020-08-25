// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsStatusEffect_Modifier.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Library for interface: ICsStatusEffect_Modifier
*/
struct CSSE_API FCsLibrary_StatusEffect_Modifier
{
	/**
	* Get the Interface Map from an Data with checks.
	* Modifier should implement the interface: ICsStatusEffect_Modifier.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsStatusEffect_Modifier") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Modifier associated with ICsStatusEffect_Modifier") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Event associated with ICsStatusEffect_Modifier") with checks (For InterfaceMap).
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Modifier		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to DerivedType (static_cast<DerivedType*>(Modifier))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafePureStaticCastChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::SafePureStaticCastChecked<DerivedType, ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffect_Modifier") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffect_Modifier") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffect_Modifier>(Context, Modifier);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Modifier associated with ICsStatusEffect_Modifier")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Modifier that implements the interface: ICsStatusEffect_Modifier.
	* return			Modifier casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Modifier))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsStatusEffect_Modifier* Modifier)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsStatusEffect_Modifier>(Context, Modifier);
	}
};