// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Containers/CsInterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_Payload_PooledObject
{
	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsPayload_PooledObject.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPayload_PooledObject.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPayload_PooledObject* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPayload_PooledObject>(Context, Payload);
	}
	
	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPayload_PooledObject") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPayload_PooledObject.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPayload_PooledObject* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPayload_PooledObject>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPayload_PooledObject") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPayload_PooledObject.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsPayload_PooledObject* Payload)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsPayload_PooledObject>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Payload associated with ICsPayload_PooledObject") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPayload_PooledObject.
	* return			Payload casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Payload))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsPayload_PooledObject* Payload)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsPayload_PooledObject>(Context, Payload);
	}
};