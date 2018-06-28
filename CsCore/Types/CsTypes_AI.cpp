// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_AI.h"

// AIType
EMCsAIType* EMCsAIType::Instance;

EMCsAIType& EMCsAIType::Get()
{
	if (!Instance)
		Instance = new EMCsAIType();
	return *Instance;
}

// AIState
EMCsAIState* EMCsAIState::Instance;

EMCsAIState& EMCsAIState::Get()
{
	if (!Instance)
		Instance = new EMCsAIState();
	return *Instance;
}

// AISetup
EMCsAISetup* EMCsAISetup::Instance;

EMCsAISetup& EMCsAISetup::Get()
{
	if (!Instance)
		Instance = new EMCsAISetup();
	return *Instance;
}