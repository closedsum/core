// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsDamageExpression;

/**
* Library for interface: ICsDamageExpression
*/
struct CSCORE_API FCsLibrary_DamageExpression
{
	/**
	* Get the Interface Map from an Data with checks.
	* Expr should implement the interface: ICsDamageExpression.
	*
	* @param Context	The calling context
	* @param Expr		Expr that implements the interface: ICsDamageExpression.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsDamageExpression* Expr)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsDamageExpression>(Context, Expr);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Expr associated with ICsDamageExpression") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Expr		Expr that implements the interface: ICsDamageExpression.
	* return			Expr casted to DerivedType (static_cast<DerivedType*>(Expr))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsDamageExpression* Expr)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsDamageExpression>(Context, Expr);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Expr associated with ICsDamageExpression") with checks.
	* DerivedType is NOT abstract.
	* Expr NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Expr that implements the interface: ICsDamageExpression.
	* return			Expr casted to DerivedType (static_cast<DerivedType*>(Expr))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsDamageExpression* Expr)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsDamageExpression>(Context, Expr);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Expr associated with ICsDamageExpression") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Expr that implements the interface: ICsDamageExpression.
	* return			Expr casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Expr))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsDamageExpression* Expr)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsDamageExpression>(Context, Expr);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Expr associated with ICsDamageExpression") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Expr		Expr that implements the interface: ICsDamageExpression.
	* return			Expr casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Expr))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsDamageExpression* Expr)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsDamageExpression>(Context, Expr);
	}
};