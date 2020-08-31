// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#pragma once


class CSUI_API FCsManager_WidgetActor_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActor>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActor> Super;

public:

	FCsManager_WidgetActor_ClassHandler();
};