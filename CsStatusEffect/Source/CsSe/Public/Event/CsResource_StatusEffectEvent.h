// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
#include "Event/CsStatusEffectEvent.h"
#pragma once

struct CSSE_API FCsResource_StatusEffectEvent : public TCsResourceContainer<ICsStatusEffectEvent>
{
};

struct CSSE_API FCsManager_StatusEffectEvent : public TCsManager_ResourcePointerType_Fixed<ICsStatusEffectEvent, FCsResource_StatusEffectEvent, 0>
{
};