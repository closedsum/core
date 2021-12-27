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
#pragma region

namespace NCsSenseTeam
{
	namespace Ref
	{
		typedef EMCsSenseTeam EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Friendly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Enemy);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Neutral);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSenseTeam_MAX, "MAX");
	}
}

#pragma endregion SenseTeam