// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
// Data
#include "Managers/WidgetActor/Data/CsData_WidgetActor.h"
#include "Managers/WidgetActor/Data/CsData_WidgetActorInterfaceMap.h"
#pragma once

class CSUI_API FCsManager_WidgetActor_DataHandler : public TCsManager_PooledObject_DataHandler<ICsData_WidgetActor, FCsData_WidgetActorPtr, FCsData_WidgetActorInterfaceMap>
{
private:

	typedef TCsManager_PooledObject_DataHandler<ICsData_WidgetActor, FCsData_WidgetActorPtr, FCsData_WidgetActorInterfaceMap> Super;

public:

	FCsManager_WidgetActor_DataHandler();
};