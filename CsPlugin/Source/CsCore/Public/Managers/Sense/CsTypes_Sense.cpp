// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sense/CsTypes_Sense.h"

// SenseActorType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsSenseActorType)

namespace ECsSenseActorType
{
	CSCORE_API const FECsSenseActorType Player = EMCsSenseActorType::Get().Create(TEXT("Player"));
	CSCORE_API const FECsSenseActorType AI = EMCsSenseActorType::Get().Create(TEXT("AI"));
}

// SenseTeam
CS_DEFINE_ENUM_MAP_BODY(EMCsSenseTeam)

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