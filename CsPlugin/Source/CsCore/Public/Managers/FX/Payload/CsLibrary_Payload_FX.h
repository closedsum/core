// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsFX
{
	namespace NPayload
	{
		#define PayloadType NCsFX::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<PayloadType>
		{
		};

		#undef PayloadType
	}
}