// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

#define PayloadType NCsSound::NPayload::IPayload

struct CSCORE_API FCsLibrary_Payload_Sound : public TCsLibrary_InterfaceMap<PayloadType>
{
};

#undef PayloadType