// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Sense.h"

// SenseActorType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsSenseActorType)

namespace ECsSenseActorType
{
	CSSENSE_API const FECsSenseActorType Player = EMCsSenseActorType::Get().Create(TEXT("Player"));
	CSSENSE_API const FECsSenseActorType AI = EMCsSenseActorType::Get().Create(TEXT("AI"));
}

// SenseTeam
#pragma region

namespace NCsSenseTeam
{
	namespace Ref
	{
		typedef EMCsSenseTeam EnumMapType;

		CSSENSE_API CS_ADD_TO_ENUM_MAP(Friendly);
		CSSENSE_API CS_ADD_TO_ENUM_MAP(Enemy);
		CSSENSE_API CS_ADD_TO_ENUM_MAP(Neutral);
		CSSENSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSenseTeam_MAX, "MAX");
	}
}

#pragma endregion SenseTeam