// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsData_Projecitle;

struct CSPRJ_API FCsLibrary_Data_Projectile
{
	/**
	* Get the Interface Map from an Data with checks.
	* Data should implement the interface: ICsData_Projectile.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Projectile.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsData_Projectile>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_Projectile") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Projectile.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsData_Projectile>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_Projectile") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Data that implements the interface: ICsData_Projectile.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsData_Projectile>(Context, Data);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_Projectile") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Projectile.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsData_Projectile>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_Projectile") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Data that implements the interface: ICsData_Projectile.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsData_Projectile>(Context, Data);
	}
};