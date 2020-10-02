// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Math.h"

#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

// ParametricFunctionType
#pragma region

namespace NCsParametricFunctionType
{
	namespace Ref
	{
		typedef EMCsParametricFunctionType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Linear);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Quadratic);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sine);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsParametricFunctionType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsParametricFunctionType_MAX;
}

#pragma endregion ParametricFunctionType

// TransformRules
#pragma region

namespace NCsTransformRules
{
	namespace Ref
	{
		typedef EMCsTransformRules EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Location);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Rotation);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Scale);
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 7; // 1 + 2 + 4

	void SetRelativeTransform(AActor* Actor, const FTransform& Transform, const int32& Rules)
	{
		// Location | Rotation | Scale
		if (Rules == All)
		{
			Actor->SetActorRelativeTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Actor->SetActorRelativeLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Actor->SetActorRelativeRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Actor->SetActorRelativeScale3D(Transform.GetScale3D());
			}
		}
	}
}

#pragma endregion TransformRules

// RotationRules
#pragma region

namespace NCsRotationRules
{
	namespace Ref
	{
		typedef EMCsRotationRules EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Pitch);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Yaw);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Roll);
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 7; // 1 + 2 + 4

	FRotator GetRotation(FRotator Rotation, const int32& Rules)
	{
		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	FRotator GetRotation(AActor* Actor, const int32& Rules)
	{
		return GetRotation(Actor->GetActorRotation(), Rules);
	}

	FRotator GetRotation(USceneComponent* Component, const int32& Rules)
	{
		return GetRotation(Component->GetComponentRotation(), Rules);
	}
}

#pragma endregion RotationRules