// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UI.h"

// WidgetActorType
EMCsWidgetActorType* EMCsWidgetActorType::Instance;

EMCsWidgetActorType& EMCsWidgetActorType::Get()
{
	if (!Instance)
		Instance = new EMCsWidgetActorType();
	return *Instance;
}

// WidgetType
EMCsWidgetType* EMCsWidgetType::Instance;

EMCsWidgetType& EMCsWidgetType::Get()
{
	if (!Instance)
		Instance = new EMCsWidgetType();
	return *Instance;
}