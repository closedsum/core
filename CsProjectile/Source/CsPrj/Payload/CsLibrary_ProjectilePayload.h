// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsProjectilePayload.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct CSPRJ_API FCsLibrary_ProjectilePayload
{
	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsProjectilePayload.
	*
	* @param Context	The calling context
	* @param Payload		Payload that implements the interface: ICsProjectilePayload.
	* return			Interface Map
	*/
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsProjectilePayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsProjectilePayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsProjectilePayload") with checks.
	* DerivedType is NOT abstract.
	*
	* @param Context	The calling context
	* @param Payload		Payload that implements the interface: ICsProjectilePayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsProjectilePayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsProjectilePayload>(Context, Payload);
	}

	/**
	* Perform the operation static_cast<DerivedType*>("Payload associated with ICsProjectilePayload") with checks.
	* DerivedType is NOT abstract.
	* Does NOT check if the InterfaceMap has "unique based" interfaces.
	*
	* @param Context	The calling context
	* @param Payload	Payload that implements the interface: ICsProjectilePayload.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* PureStaticCastChecked(const FString& Context, ICsProjectilePayload* Payload)
	{
		return NCsInterfaceMap::PureStaticCastChecked<DerivedType, ICsProjectilePayload>(Context, Payload);
	}
};