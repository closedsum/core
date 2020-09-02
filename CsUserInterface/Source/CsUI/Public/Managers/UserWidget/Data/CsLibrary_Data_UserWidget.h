// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
*/
struct CSUI_API FCsLibrary_Data_UserWidget
{
public:

	/**
	* Get the Interface Map from an Data with checks.
	* Data should implement the interface: ICsData_UserWidget.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsData_UserWidget>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_UserWidget") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsData_UserWidget>(Context, Data);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_UserWidget") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static const DerivedType* StaticCastChecked(const FString& Context, const ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsData_UserWidget>(Context, Data);
	}

	/**
	* Perform the operation static_cast<SliceType*>("Data associated with ICsData_UserWidget") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to SliceType (static_cast<DerivedType*>(Data))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* StaticCastChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		SliceInterfaceType* Interface = GetInterfaceChecked<SliceInterfaceType>(Context, Data);

		return NCsInterfaceMap::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<SliceType*>("Data associated with ICsData_UserWidget") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to SliceType (static_cast<DerivedType*>(Data))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static const SliceType* StaticCastChecked(const FString& Context, const ICsData_UserWidget* Data)
	{
		const SliceInterfaceType* Interface = GetInterfaceChecked<SliceInterfaceType>(Context, Data);

		return NCsInterfaceMap::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Data associated with ICsData_UserWidget") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafeStaticCastChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::SafeStaticCastChecked<DerivedType, ICsData_UserWidget>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<SliceType*>("Data associated with ICsData_UserWidget") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to SliceType (static_cast<SliceType*>(Data))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* SafeStaticCastChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		if (SliceInterfaceType* Interface = GetSafeInterfaceChecked<SliceInterfaceType>(Context, Data))
		{
			return NCsInterfaceMap::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
		}
		return nullptr;
	}

	/**
	* Safely perform the operation static_cast<SliceType*>("Data associated with ICsData_UserWidget") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to SliceType (static_cast<SliceType*>(Data))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static const SliceType* SafeStaticCastChecked(const FString& Context, const ICsData_UserWidget* Data)
	{
		if (const SliceInterfaceType* Interface = GetSafeInterfaceChecked<SliceInterfaceType>(Context, Data))
		{
			return NCsInterfaceMap::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
		}
		return nullptr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Data associated with ICsData_UserWidget") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_UserWidget.
	* return			Data casted to DerivedType (static_cast<DerivedType*>(Data))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsData_UserWidget>(Context, Data);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_UserWidget") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_Weapon.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_UserWidget") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_Weapon.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsData_UserWidget>(Context, Data);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Data associated with ICsData_UserWidget")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data	Data that implements the interface: ICsData_Weapon.
	* return			Data casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Data))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const ICsData_UserWidget* Data)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsData_UserWidget>(Context, Data);
	}
};