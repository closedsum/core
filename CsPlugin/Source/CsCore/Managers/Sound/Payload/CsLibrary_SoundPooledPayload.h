// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsSoundPooledPayload.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct CSPRJ_API FCsLibrary_SoundPooledPayload
{
	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsSoundPooledPayload.
	*
	* @param Context	The calling context
	* @param Payload		Payload that implements the interface: ICsSoundPooledPayload.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsSoundPooledPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsSoundPooledPayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsSoundPooledPayload") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsSoundPooledPayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsSoundPooledPayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsSoundPooledPayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsSoundPooledPayload") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap "emulates" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsSoundPooledPayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsSoundPooledPayload* Payload)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsSoundPooledPayload>(Context, Payload);
	}
};