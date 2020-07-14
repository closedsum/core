// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsPooledObjectCache.h"
#include "Containers/CsInterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_PooledObjectCache
{
	/**
	* Get the Interface Map from an Cache with checks.
	* Cache should implement the interface: ICsPooledObjectCache.
	*
	* @param Context	The calling context
	* @param Cache		Cache that implements the interface: ICsPooledObjectCache.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPooledObjectCache>(Context, Cache);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Cache associated with ICsPooledObjectCache") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Cache		Cache that implements the interface: ICsPooledObjectCache.
	* return			Cache casted to DerivedType (static_cast<DerivedType*>(Cache))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPooledObjectCache>(Context, Cache);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Cache associated with ICsPooledObjectCache") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Cache		Cache that implements the interface: ICsPooledObjectCache.
	* return			Cache casted to DerivedType (static_cast<DerivedType*>(Cache))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsPooledObjectCache>(Context, Cache);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Cache associated with ICsPooledObjectCache") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Data		Cache that implements the interface: ICsPooledObjectCache.
	* return			Cache casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Cache))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsPooledObjectCache>(Context, Cache);
	}
};