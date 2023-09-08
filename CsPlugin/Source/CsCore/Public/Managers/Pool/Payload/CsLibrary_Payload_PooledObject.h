// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Containers/CsLibrary_InterfaceMap.h"

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