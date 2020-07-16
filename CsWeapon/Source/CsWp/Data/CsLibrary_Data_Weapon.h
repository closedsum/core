// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsData_Weapon;

struct CSPRJ_API FCsLibrary_Data_Weapon
{
	/**
	* Get the Interface Map from an Data with checks.
	* Data should implement the interface: ICsData_Weapon.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Weapon.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsData_Weapon* Data)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsData_Weapon>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_Weapon") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Weapon.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsData_Weapon* Data)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsData_Weapon>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_Weapon") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Data that implements the interface: ICsData_Weapon.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsData_Weapon* Data)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsData_Weapon>(Context, Data);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_Weapon") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Weapon.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsData_Weapon* Data)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_Weapon") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Weapon.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsData_Weapon* Data)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsData_Weapon>(Context, Data);
	}
};