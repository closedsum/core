// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Collision.h"

// Components
#include "Components/SkeletalMeshComponent.h"

// CollisionEnabled
#pragma region

namespace ECollisionEnabled
{
	namespace Ref
	{
		typedef EMCollisionEnabled EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(NoCollision);
		CSCORE_API CS_ADD_TO_ENUM_MAP(QueryOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(PhysicsOnly);
		CSCORE_API CS_ADD_TO_ENUM_MAP(QueryAndPhysics);
	}
}

#pragma endregion CollisionEnabled

// CollisionChannel
#pragma region

namespace NCsCollisionChannel
{
	namespace Ref
	{
		typedef EMCsCollisionChannel EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_WorldStatic, "World Static");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_WorldDynamic, "World Dynamic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Pawn, "Pawn");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Visibility, "Visibility");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Camera, "Camera");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_PhysicsBody, "Physics Body");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Vehicle, "Vehicle");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_Destructible, "Destructible");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel1, "EngineTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel2, "EngineTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel3, "EngineTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel4, "EngineTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel5, "EngineTraceChannel 5");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_EngineTraceChannel6, "EngineTraceChannel 6");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel1, "GameTraceChannel 1");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel2, "GameTraceChannel 2");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel3, "GameTraceChannel 3");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel4, "GameTraceChannel 4");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel5, "GameTraceChannel 6");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel6, "GameTraceChannel 7");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel7, "GameTraceChannel 8");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel8, "GameTraceChannel 9");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel9, "GameTraceChannel 10");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel10, "GameTraceChannel 11");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel11, "GameTraceChannel 12");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel12, "GameTraceChannel 13");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel13, "GameTraceChannel 14");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel14, "GameTraceChannel 15");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel15, "GameTraceChannel 16");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel16, "GameTraceChannel 17");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_GameTraceChannel17, "GameTraceChannel 18");

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECC_MAX, "MAX");
	}
}

#pragma endregion CollisionChannel

// CollisionResponse
#pragma region

namespace NCsCollisionResponse
{
	namespace Ref
	{
		typedef EMCollisionResponse EnumMapType;

		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Ignore, "Ignore");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Overlap, "Overlap");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_Block, "Block");
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECR_MAX, "MAX");
	}
}

#pragma endregion CollisionResponse

// CollisionShape
#pragma region

namespace NCsCollisionShape
{
	namespace Ref
	{
		typedef EMCsCollisionShape EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Line);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Box);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sphere);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Capsule);
	}
}

#pragma endregion CollisionShape

// FCsCollisionPreset
#pragma region

void FCsCollisionPreset::Apply(USkeletalMeshComponent* Mesh) const
{
	if (CollisionEnabled != ECollisionEnabled::NoCollision)
	{
		Mesh->SetCollisionObjectType(ObjectType);
		Mesh->SetCollisionResponseToChannels(CollisionResponses);

		Mesh->SetNotifyRigidBodyCollision(bSimulationGeneratesHitEvents);
		Mesh->SetGenerateOverlapEvents(bGenerateOverlapEvents);

		Mesh->SetCollisionEnabled(CollisionEnabled);
	}
}

#pragma endregion FCsCollisionPreset