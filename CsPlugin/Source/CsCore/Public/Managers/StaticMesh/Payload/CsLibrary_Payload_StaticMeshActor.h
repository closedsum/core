// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
	#define PayloadType NCsStaticMeshActor::NPayload::IPayload

		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<PayloadType>
		{
		public:

			/**
			*/
			static bool IsValidChecked(const FString& Context, PayloadType* Payload);
		};

	#undef PayloadType
	}
}