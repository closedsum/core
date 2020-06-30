// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsProjectilePayload.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct CSPRJ_API FCsLibrary_ProjectilePayload
{
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsProjectilePayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsProjectilePayload>(Context, Payload);
	}

	template<typename T>
	FORCEINLINE static T* StaticCastChecked(const FString& Context, ICsProjectilePayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<T, ICsProjectilePayload>(Context, Payload);
	}
};