// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

struct CSCORE_API FCsLibrary_Payload_SkeletalMeshActor : public TCsLibrary_InterfaceMap<PayloadType>
{
};

#undef PayloadType