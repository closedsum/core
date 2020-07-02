// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Containers/CsInterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_PooledObjectPayload
{
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPooledObjectPayload>(Context, Payload);
	}
	
	template<typename DerivedType>
	FORCEINLINE static DerivedType* StaticCastChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<DerivedType, ICsPooledObjectPayload>(Context, Payload);
	}

	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType, ICsPooledObjectPayload>(Context, Payload);
	}
};