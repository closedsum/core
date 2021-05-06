// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Math.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Actor
#include "GameFramework/Actor.h"
// Components
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

	void SetRelativeTransform(USceneComponent* Component, const FTransform& Transform, const int32& Rules)
	{
		// Location | Rotation | Scale
		if (Rules == All)
		{
			Component->SetRelativeTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Component->SetRelativeLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Component->SetRelativeRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Component->SetRelativeScale3D(Transform.GetScale3D());
			}
		}
	}

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

	void SetTransform(USceneComponent* Component, const FTransform& Transform, const int32& Rules)
	{
		// Location | Rotation | Scale
		if (Rules == All)
		{
			Component->SetWorldTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Component->SetWorldLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Component->SetWorldRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Component->SetWorldScale3D(Transform.GetScale3D());
			}
		}
	}

	void SetTransform(AActor* Actor, const FTransform& Transform, const int32& Rules)
	{
		// Location | Rotation | Scale
		if (Rules == All)
		{
			Actor->SetActorTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Actor->SetActorLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Actor->SetActorRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Actor->SetActorScale3D(Transform.GetScale3D());
			}
		}
	}

	bool AreTransformsEqual(const FTransform& A, const FTransform& B, const int32& Rules)
	{
		bool Equal = true;

		// Location
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
		{
			Equal &= A.GetLocation() == B.GetLocation();
		}
		// Rotation
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
		{
			Equal &= A.GetRotation() == B.GetRotation();
		}
		// Scale
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
		{
			Equal &= A.GetScale3D() == B.GetScale3D();
		}
		return Equal;
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

	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsRotationRules, GetRotation);
		}
	}

	FRotator GetRotation(FRotator Rotation, const int32& Rules)
	{
		if (Rules == None)
			return FRotator::ZeroRotator;

		if (Rules == All)
			return Rotation;

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	FRotator GetRotationChecked(const FString& Context, FRotator Rotation, const int32& Rules)
	{
		checkf(Rules != None, TEXT("%s: Rules == 0. No bit flags set."), *Context);

		if (Rules == All)
			return Rotation;

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	FRotator GetRotation(AActor* Actor, const int32& Rules)
	{
		using namespace NCached;

		const FString& Context = Str::GetRotation;

		checkf(Actor, TEXT("%s: Actor is NULL"), *Context);

		return GetRotation(Actor->GetActorRotation(), Rules);
	}

	FRotator GetRotation(USceneComponent* Component, const int32& Rules)
	{
		using namespace NCached;

		const FString& Context = Str::GetRotation;

		checkf(Component, TEXT("%s: Component is NULL"), *Context);

		return GetRotation(Component->GetComponentRotation(), Rules);
	}
}

#pragma endregion RotationRules

// FCsRay
#pragma region

bool FCsRay::IsValidChecked(const FString& Context) const
{
	// Check Direction is Valid
	checkf(Direction.IsNormalized(), TEXT("%s: Direction is NOT normalized."), *Context);
	// Check Distance is Valid
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Distance, 0.0f)
	// Check End is Valid
	checkf(Origin != End, TEXT("%s: Origin == End (%s)."), *Context, *(Origin.ToCompactString()));

	checkf(End == CalculateEnd(), TEXT("%s: End != CalculateEnd() (%s != %s). End has NOT been properly calculated."), *Context, *(End.ToCompactString()), *(CalculateEnd().ToCompactString()));
	return true;
}

bool FCsRay::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Direction is Valid
	if (!Direction.IsNormalized())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Direction is NOT normalized."), *Context));
		return false;
	}
	// Check Distance is Valid
	CS_IS_FLOAT_GREATER_THAN(Distance, 0.0f)
	// Check End is Valid
	if (Origin == End)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Origin == End (%s)."), *Context, *(Origin.ToCompactString())));
		return false;
	}

	if (End != CalculateEnd())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: End != CalculateEnd() (%s != %s). End has NOT been properly calculated."), *Context, *(End.ToCompactString()), *(CalculateEnd().ToCompactString())));
		return false;
	}
	return true;
}

#pragma endregion FCsRay