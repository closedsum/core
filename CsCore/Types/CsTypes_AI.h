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

// AITypeToString
typedef const FString&(*TCsAITypeToString)(const TCsAIType&);
// StringToAIType
typedef TCsAIType(*TCsStringToAIType)(const FString&);

#define CS_DECLARE_AI_TYPE	TCsAIType AIType_MAX; \
							uint8 AI_TYPE_MAX; \
							TCsAITypeToString AITypeToString; \
							TCsStringToAIType StringToAIType;

#define CS_DEFINE_AI_TYPE	AIType_MAX = ECsAIType::ECsAIType_MAX;\
							AI_TYPE_MAX = (uint8)AIType_MAX \
							AITypeToString = &ECsAIType::ToString; \
							StringToAIType = &ECsAIType::ToType;

namespace ECsAIState
{
	enum Type : uint8;
}

typedef ECsAIState::Type TCsAIState;

// AIStateToString
typedef const FString&(*TCsAIStateToString)(const TCsAIState&);
// StringToAIState
typedef TCsAIState(*TCsStringToAIState)(const FString&);

#define CS_DECLARE_AI_STATE	TCsAIState AIState_MAX; \
							uint8 AI_STATE_MAX; \
							TCsAIStateToString AIStateToString; \
							TCsStringToAIState StringToAIState;

#define CS_DEFINE_AI_STATE	AIState_MAX = ECsAIState::ECsAIState_MAX;\
							AI_STATE_MAX = (uint8)AIState_MAX \
							AIStateToString = &ECsAIState::ToString; \
							StringToAIState = &ECsAIState::ToType;

namespace ECsAISetup
{
	enum Type : uint8;
}

typedef ECsAISetup::Type TCsAISetup;

// AISetupToString
typedef const FString&(*TCsAISetupToString)(const TCsAISetup&);
// StringToAISetup
typedef TCsAISetup(*TCsStringToAISetup)(const FString&);

#define CS_DECLARE_AI_SETUP	TCsAISetup AISetup_MAX; \
							uint8 AI_SETUP_MAX; \
							TCsAISetupToString AISetupToString; \
							TCsStringToAISetup StringToAISetup;

#define CS_DEFINE_AI_SETUP	AISetup_MAX = ECsAISetup::ECsAISetup_MAX;\
							AI_SETUP_MAX = (uint8)AISetup_MAX \
							AISetupToString = &ECsAISetup::ToString; \
							StringToAISetup = &ECsAISetup::ToType;

struct FCsAIPawnPayload
{
	bool IsAllocated;
	bool TeleportLocation;
	FVector Location;
	bool TeleportRotation;
	FRotator Rotation;

	FCsAIPawnPayload()
	{
		Reset();
	}
	~FCsAIPawnPayload() {}

	void Reset()
	{
		IsAllocated = false;
		TeleportLocation = false;
		Location = FVector::ZeroVector;
		TeleportRotation = false;
		Rotation = FRotator::ZeroRotator;
	}
};

#pragma endregion AI