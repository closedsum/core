// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
*/
template<typename InterfaceType>
struct TCsLibrary_InterfaceMap
{
public:

	/**
	* Get the Interface Map from an Interface with checks.
	* Interface should implement the interface: InterfaceType.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<InterfaceType>(Context, Interface);
	}

	/**
	* Get the Interface Map from an Interface with checks.
	* Interface should implement the interface: InterfaceType.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface Map
	*/
	FORCEINLINE static const FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, const InterfaceType* Interface)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType>
	FORCEINLINE static const DerivedType* StaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<SliceType*>("Interface associated with InterfaceType") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to SliceType (static_cast<DerivedType*>(Interface))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* StaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		SliceInterfaceType* SliceInterface = GetInterfaceChecked<SliceInterfaceType>(Context, Interface);

		return NCsInterfaceMap::StaticCastChecked<SliceType, SliceInterfaceType>(Context, SliceInterface);
	}

	/**
	* Perform the operation static_cast<SliceType*>("Interface associated with InterfaceType") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to SliceType (static_cast<DerivedType*>(Interface))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static const SliceType* StaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		const SliceInterfaceType* SliceInterface = GetInterfaceChecked<SliceInterfaceType>(Context, Interface);

		return NCsInterfaceMap::StaticCastChecked<SliceType, SliceInterfaceType>(Context, SliceInterface);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafeStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::SafeStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<SliceType*>("Interface associated with InterfaceType") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to SliceType (static_cast<SliceType*>(Interface))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* SafeStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		if (SliceInterfaceType* SliceInterface = GetSafeInterfaceChecked<SliceInterfaceType>(Context, Interface))
		{
			return NCsInterfaceMap::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, SliceInterface);
		}
		return nullptr;
	}

	/**
	* Safely perform the operation static_cast<SliceType*>("Interface associated with InterfaceType") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to SliceType (static_cast<SliceType*>(Interface))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static const SliceType* SafeStaticCastChecked(const FString& Context, const InterfaceType* Interface)
	{
		if (const SliceInterfaceType* SliceInterface = GetSafeInterfaceChecked<SliceInterfaceType>(Context, Interface))
		{
			return NCsInterfaceMap::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, SliceInterface);
		}
		return nullptr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Interface associated with InterfaceType") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: InterfaceType.
	* return			Interface casted to DerivedType (static_cast<DerivedType*>(Interface))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, InterfaceType>(Context, Interface);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Interface associated with InterfaceType") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsData_Weapon.
	* return			Interface casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Interface))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Interface associated with InterfaceType") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsData_Weapon.
	* return			Interface casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Interface))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, InterfaceType* Interface)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, InterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Interface associated with InterfaceType")
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Interface	Interface that implements the interface: ICsData_Weapon.
	* return			Interface casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Interface))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static const OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, const InterfaceType* Interface)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, InterfaceType>(Context, Interface);
	}

	/**
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static bool Implements(const FString& Context, const InterfaceType* Interface)
	{
		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked(Context, Interface);

		return InterfaceMap->Implements<OtherInterfaceType>();
	}

	/**
	*/
	FORCEINLINE static bool HasUniqueBasedSlices(const FString& Context, const InterfaceType* Interface)
	{
		const FCsInterfaceMap* InterfaceMap = GetInterfaceMapChecked(Context, Interface);

		return InterfaceMap->HasUniqueBasedSlices();
	}

	/**
	* Copy the slice of values from From to To with checks.
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the From copied to To successfully.
	*/
	template<typename SliceType, typename SliceInterfaceType>
	static bool CopySliceChecked(const FString& Context, const InterfaceType* From, InterfaceType* To)
	{
		if (const SliceType* FromSlice = SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, From))
		{
			SliceType* ToSlice = StaticCastChecked<SliceType, SliceInterfaceType>(Context, To);

			return ToSlice->CopyFrom(FromSlice);
		}
		return false;
	}
};