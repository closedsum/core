// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_StatusEffect.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsData_StatusEffect;
/**
* Library for interface: ICsData_StatusEffect
*/
struct CSSE_API FCsLibrary_Data_StatusEffect
{
	/**
	* Get the Interface Map from an Data with checks.
	* Data should implement the interface: ICsData_StatusEffect.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_StatusEffect.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsData_StatusEffect* Data)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsData_StatusEffect>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_StatusEffect") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_StatusEffect.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsData_StatusEffect* Data)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsData_StatusEffect>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_StatusEffect") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_StatusEffect.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsData_StatusEffect* Data)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsData_StatusEffect>(Context, Data);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Effect associated with ICsData_StatusEffect") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_StatusEffect.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsData_StatusEffect* Data)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsData_StatusEffect>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Effect associated with ICsData_StatusEffect") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_StatusEffect.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsData_StatusEffect* Data)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsData_StatusEffect>(Context, Data);
	}
};