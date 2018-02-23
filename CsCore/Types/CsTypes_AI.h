// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.

//#include "CsTypes_AI.generated.h"
#pragma once

// AI
#pragma region

namespace ECsAIType
{
	enum Type : uint8;
}

typedef ECsAIType::Type TCsAIType;

// InputActionToString
typedef FString(*TCsAITypeToString)(const TCsAIType&);
// StringToInputAction
typedef TCsAIType(*TCsStringToAIType)(const FString&);

#define CS_DECLARE_AI_TYPE	TCsAIType AIType_MAX; \
							uint8 AI_TYPE_MAX; \
							TCsAITypeToString AITypeToString; \
							TCsStringToAIType StringToAIType;

#define CS_DEFINE_AI_TYPE	AIType_MAX = ECsAIType::ECsAIType_MAX;\
							AI_TYPE_MAX = (uint8)AIType_MAX \
							AITypeToString = &ECsAIType::ToString; \
							StringToAIType = &ECsAIType::ToType;

#pragma endregion AI