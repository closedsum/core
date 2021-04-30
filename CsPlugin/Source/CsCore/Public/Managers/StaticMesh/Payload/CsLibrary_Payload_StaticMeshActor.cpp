// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		#define PayloadType NCsStaticMeshActor::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType

			// Check StaticMesh is Valid
			checkf(Payload->GetStaticMesh(), TEXT("%s: GetStaticMesh() is NULL."), *Context);
			return true;
		}
	}
}