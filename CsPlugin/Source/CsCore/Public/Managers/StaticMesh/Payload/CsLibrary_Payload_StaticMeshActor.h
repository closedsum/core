// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

#define PayloadType NCsStaticMeshActor::NPayload::IPayload

struct CSCORE_API FCsLibrary_Payload_StaticMeshActor : public TCsLibrary_InterfaceMap<PayloadType>
{
};

#undef PayloadType