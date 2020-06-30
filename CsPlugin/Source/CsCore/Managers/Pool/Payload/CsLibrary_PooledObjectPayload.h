// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Containers/CsInterfaceMap.h"

struct CSCORE_API FCsLibrary_PooledObjectPayload
{
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPooledObjectPayload>(Context, Payload);
	}
	
	template<typename T>
	FORCEINLINE static T* StaticCastChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::StaticCastChecked<T, ICsPooledObjectPayload>(Context, Payload);
	}

	template<typename T>
	FORCEINLINE static T* GetInterfaceChecked(const FString& Context, ICsPooledObjectPayload* Payload)
	{
		return NCsInterfaceMap::GetInterfaceChecked<T, ICsPooledObjectPayload>(Context, Payload);
	}
};