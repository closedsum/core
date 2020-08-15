// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Containers/CsInterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_Payload_PooledObject
{
	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsPooledObjectPayload.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPooledObjectPayload.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPooledObjectPayload>(Context, Payload);
	}
	
	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPooledObjectPayload") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPooledObjectPayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPooledObjectPayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsPooledObjectPayload") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPooledObjectPayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsPooledObjectPayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<OtherInterfaceType*>("Payload associated with ICsPooledObjectPayload") with checks.
	* OtherInterfaceType IS abstract.
	*
	* @param Context	The calling context
	* @param Cache		Payload that implements the interface: ICsPooledObjectPayload.
	* return			Payload casted to OtherInterfaceType (static_cast<OtherInterfaceType*>(Payload))
	*/
	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsPooledObjectPayload>(Context, Payload);
	}
};