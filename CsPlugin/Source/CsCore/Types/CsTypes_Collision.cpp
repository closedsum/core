// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Collision.h"

// CollisionEnabled
#pragma region

namespace ECollisionEnabled
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCollisionEnabled, NoCollision);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCollisionEnabled, QueryOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCollisionEnabled, PhysicsOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCollisionEnabled, QueryAndPhysics);
	}
}

#pragma endregion CollisionEnabled

// CollisionChannel
#pragma region

namespace NCsCollisionChannel
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_WorldStatic, "World Static");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_WorldDynamic, "World Dynamic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_Pawn, "Pawn");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_Visibility, "Visibility");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_Camera, "Camera");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_PhysicsBody, "Physics Body");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_Vehicle, "Vehicle");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_Destructible, "Destructible");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel1, "EngineTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel2, "EngineTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel3, "EngineTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel4, "EngineTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel5, "EngineTraceChannel 5");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_EngineTraceChannel6, "EngineTraceChannel 6");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel1, "GameTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel2, "GameTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel3, "GameTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel4, "GameTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel5, "GameTraceChannel 6");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel6, "GameTraceChannel 7");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel7, "GameTraceChannel 8");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel8, "GameTraceChannel 9");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel9, "GameTraceChannel 10");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel10, "GameTraceChannel 11");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel11, "GameTraceChannel 12");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel12, "GameTraceChannel 13");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel13, "GameTraceChannel 14");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel14, "GameTraceChannel 15");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel15, "GameTraceChannel 16");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel16, "GameTraceChannel 17");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_GameTraceChannel17, "GameTraceChannel 18");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCollisionChannel, ECC_MAX, "MAX");
	}
}

#pragma endregion CollisionChannel

// CollisionResponse
#pragma region

namespace NCsCollisionResponse
{
	namespace Ref
	{
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCollisionResponse, ECR_Ignore, "Ignore");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCollisionResponse, ECR_Overlap, "Overlap");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCollisionResponse, ECR_Block, "Block");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCollisionResponse, ECR_MAX, "MAX");
	}
}

#pragma endregion CollisionResponse