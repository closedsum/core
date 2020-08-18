// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Projectile.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
*/
struct CSPRJ_API FCsLibrary_Payload_Projectile
{
public:

	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsPayload_Projectile.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPayload_Projectile>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPayload_Projectile") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPayload_Projectile>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<SliceType*>("Payload associated with ICsPayload_Projectile") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to SliceType (static_cast<DerivedType*>(Payload))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* StaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		SliceInterfaceType* Interface = GetInterfaceChecked<SliceInterfaceType>(Context, Payload);

		return NCsInterfaceMap::StaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
	}

	/**
	* Safely perform the operation static_cast<DerivedType*>("Payload associated with ICsPayload_Projectile") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* SafeStaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::SafeStaticCastChecked<DerivedType, ICsPayload_Projectile>(Context, Payload);
	}

	/**
	* Safely perform the operation static_cast<SliceType*>("Payload associated with ICsPayload_Projectile") with checks.
	* SliceType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to SliceType (static_cast<SliceType*>(Payload))
	*/
	template<typename SliceType, typename SliceInterfaceType>
	FORCEINLINE static SliceType* SafeStaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		if (SliceInterfaceType* Interface = GetSafeInterfaceChecked<SliceInterfaceType>(Context, Payload))
		{
			return NCsInterfaceMap::SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, Interface);
		}
		return nullptr;
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPayload_Projectile") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsPayload_Projectile>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Payload associated with ICsPayload_Projectile") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsData_Weapon.
	* return			Payload casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Payload))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType>(Context, Payload);
	}

	/**
	* Safely perform the operation static_cast<OtherInterfaceType*>("Payload associated with ICsPayload_Projectile") 
	* with checks (for InterfaceMap).
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsData_Weapon.
	* return			Payload casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Payload))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetSafeInterfaceChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::GetSafeInterfaceChecked<OtherInterfaceType, ICsPayload_Projectile>(Context, Payload);
	}

	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  FCsPayload_PooledObjectImplSlice (ICsPayload_PooledObject)
	*  FCsPayload_ProjecitleImplSlice (ICsPayload_Projectile)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	static void CopyChecked(const FString& Context, ICsPayload_Projectile* From, ICsPayload_Projectile* To);

private:

	/**
	* Copy the slice of values from From to To with checks.
	* Currently supports To types of:
	*  FCsPayload_PooledObjectImplSlice (ICsPayload_PooledObject)
	*  FCsPayload_ProjecitleImplSlice (ICsPayload_Projectile)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	template<typename SliceType, typename SliceInterfaceType>
	static void CopySliceChecked(const FString& Context, ICsPayload_Projectile* From, ICsPayload_Projectile* To)
	{
		if (SliceType* FromSlice = SafeStaticCastChecked<SliceType, SliceInterfaceType>(Context, From))
		{
			SliceType* ToSlice = StaticCastChecked<SliceType, SliceInterfaceType>(Context, To);

			ToSlice->CopyFrom(FromSlice);
		}
	}
};