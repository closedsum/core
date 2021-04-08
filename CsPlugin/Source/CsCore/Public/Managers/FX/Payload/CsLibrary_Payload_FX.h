// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)

namespace NCsFX
{
	namespace NPayload
	{
		#define PayloadType NCsFX::NPayload::IPayload

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<PayloadType>
		{
		#define PayloadImplType NCsFX::NPayload::FImpl

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Payload
			* return
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Payload
			* @param FX
			*/
			static void SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX);

		#undef PayloadImplType
		};

		#undef PayloadType
	}
}