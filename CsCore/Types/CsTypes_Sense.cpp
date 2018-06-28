// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Sense.h"

// SenseActorType
EMCsSenseActorType* EMCsSenseActorType::Instance;

EMCsSenseActorType& EMCsSenseActorType::Get()
{
	if (!Instance)
		Instance = new EMCsSenseActorType();
	return *Instance;
}

namespace ECsSenseActorType
{
	CSCORE_API const FECsSenseActorType Player = EMCsSenseActorType::Get().Create(TEXT("Player"));
	CSCORE_API const FECsSenseActorType AI = EMCsSenseActorType::Get().Create(TEXT("AI"));
}

// SenseTeam
EMCsSenseTeam* EMCsSenseTeam::Instance;

EMCsSenseTeam& EMCsSenseTeam::Get()
{
	if (!Instance)
		Instance = new EMCsSenseTeam();
	return *Instance;
}

namespace ECsSenseTeam
{
	namespace Ref
	{
		CSCORE_API const Type Friendly = EMCsSenseTeam::Get().Add(Type::Friendly, TEXT("Friendly"));
		CSCORE_API const Type Enemy = EMCsSenseTeam::Get().Add(Type::Friendly, TEXT("Friendly"));
		CSCORE_API const Type Neutral = EMCsSenseTeam::Get().Add(Type::Friendly, TEXT("Friendly"));
		CSCORE_API const Type ECsSenseTeam_MAX = EMCsSenseTeam::Get().Add(Type::ECsSenseTeam_MAX, TEXT("ECsSenseTeam_MAX"), TEXT("MAX"));
	}
}