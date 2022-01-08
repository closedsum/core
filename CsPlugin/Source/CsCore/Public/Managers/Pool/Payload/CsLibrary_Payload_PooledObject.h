// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Containers/CsLibrary_InterfaceMap.h"

#pragma once

namespace NCsPooledObject
{
	namespace NPayload
	{
	#define PayloadType NCsPooledObject::NPayload::IPayload

		struct CSCORE_API FLibrary : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		};

	#undef PayloadType
	}
}