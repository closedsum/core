// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsSound::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, FImpl)

namespace NCsSound
{
	namespace NPayload
	{
	#define PayloadType NCsSound::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<PayloadType>
		{
		#define PayloadImplType NCsSound::NPayload::FImpl

			/**
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

			/**
			*/
			static void SetPayload(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound);

		#undef PayloadImplType
		};

	#undef PayloadType
	}
}