// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Projectile.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
*/
struct CSPRJ_API FCsLibrary_Payload_Projectile
{
	/**
	* Get the Interface Map from an Payload with checks.
	* Payload should implement the interface: ICsPayload_Projectile.
	*
	* @param Context	The calling context
	* @param Payload		Payload that implements the interface: ICsPayload_Projectile.
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
	* @param Payload		Payload that implements the interface: ICsPayload_Projectile.
	* return			Payload casted to DerivedType (static_cast<DerivedType*>(Payload))
	*/
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPayload_Projectile* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPayload_Projectile>(Context, Payload);
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
};