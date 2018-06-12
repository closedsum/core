// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interactive.h"
#include "CsCore.h"

// InteractiveType
EMCsInteractiveType* EMCsInteractiveType::Instance;

EMCsInteractiveType& EMCsInteractiveType::Get()
{
	if (!Instance)
		Instance = new EMCsInteractiveType();
	return *Instance;
}