// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Math_Library.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Common
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Actor
#include "GameFramework/Actor.h"
// Components
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

// RotationRules
#pragma region

namespace NCsRotationRules
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsRotationRules, GetRotation);
		}
	}

	#define USING_NS_CACHED using namespace NCsRotationRules::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsRotationRules::NCached; \
		const FString& Context = Str::__FunctionName
	#define MathLibrary NCsMath::FLibrary

	FRotator3f GetRotation(AActor* Actor, const int32& Rules)
	{
		SET_CONTEXT(GetRotation);

		CS_IS_PTR_NULL_CHECKED(Actor)

		return GetRotation(MathLibrary::Convert(Actor->GetActorRotation()), Rules);
	}

	FRotator3f GetRotation(USceneComponent* Component, const int32& Rules)
	{
		SET_CONTEXT(GetRotation);

		CS_IS_PTR_NULL_CHECKED(Component)

		return GetRotation(MathLibrary::Convert(Component->GetComponentRotation()), Rules);
	}

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef MathLibrary
}

#pragma endregion RotationRules

// TransformRules
#pragma region

namespace NCsTransformRules
{
	#define MathLibrary NCsMath::FLibrary

	void SetRelativeTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules)
	{
		check(Component);

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

	void SetRelativeTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules)
	{
		check(Component);

		const FTransform3d T = MathLibrary::Convert(Transform);

		// Location | Rotation | Scale
		if (Rules == All)
		{
			Component->SetRelativeTransform(T);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Component->SetRelativeLocation(T.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Component->SetRelativeRotation(T.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Component->SetRelativeScale3D(T.GetScale3D());
			}
		}
	}

	void SetRelativeTransform(AActor* Actor, const FTransform3d& Transform, const int32& Rules)
	{
		check(Actor);

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

	void SetRelativeTransform(AActor* Actor, const FTransform3f& Transform, const int32& Rules)
	{
		check(Actor);

		const FTransform3d T = MathLibrary::Convert(Transform);

		// Location | Rotation | Scale
		if (Rules == All)
		{
			Actor->SetActorRelativeTransform(T);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
			{
				Actor->SetActorRelativeLocation(T.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Actor->SetActorRelativeRotation(T.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Actor->SetActorRelativeScale3D(T.GetScale3D());
			}
		}
	}

	void SetTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules)
	{
		check(Component);

		// TODO: FIX: NOTE: SetActorTransform is producing some weird results

		// Location | Rotation | Scale
		//if (Rules == All)
		//{
		//	Component->SetWorldTransform(Transform);
		//}
		//else
		{
			// Location and Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location) &&
				CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Component->SetWorldLocationAndRotation(Transform.GetLocation(), Transform.GetRotation().Rotator());
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
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Component->SetWorldScale3D(Transform.GetScale3D());
			}
		}
	}

	void SetTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules)
	{
		check(Component);

		const FTransform3d T = MathLibrary::Convert(Transform);

		// TODO: FIX: NOTE: SetActorTransform is producing some weird results
		
		// Location | Rotation | Scale
		//if (Rules == All)
		//{
		//	Component->SetWorldTransform(Transform);
		//}
		//else
		{
			// Location and Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location) &&
				CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Component->SetWorldLocationAndRotation(T.GetLocation(), T.GetRotation().Rotator());
			}
			else
			{
				// Location
				if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
				{
					Component->SetWorldLocation(T.GetLocation());
				}
				// Rotation
				if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
				{
					Component->SetWorldRotation(T.GetRotation().Rotator());
				}
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Component->SetWorldScale3D(T.GetScale3D());
			}
		}
	}

	void SetTransform(AActor* Actor, const FTransform3d& Transform, const int32& Rules)
	{
		check(Actor);

		// TODO: FIX: NOTE: SetActorTransform is producing some weird results

		// Location | Rotation | Scale
		//if (Rules == All)
		//{
		//	Actor->SetActorTransform(Transform);
		//}
		//else
		{
			// Location and Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location) &&
				CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Actor->SetActorLocationAndRotation(Transform.GetLocation(), Transform.GetRotation().Rotator());
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
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Actor->SetActorScale3D(Transform.GetScale3D());
			}
		}
	}

	void SetTransform(AActor* Actor, const FTransform3f& Transform, const int32& Rules)
	{
		check(Actor);

		const FTransform3d T = MathLibrary::Convert(Transform);

		// TODO: FIX: NOTE: SetActorTransform is producing some weird results
		
		// Location | Rotation | Scale
		//if (Rules == All)
		//{
		//	Actor->SetActorTransform(Transform);
		//}
		//else
		{
			// Location and Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location) &&
				CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
			{
				Actor->SetActorLocationAndRotation(T.GetLocation(), T.GetRotation().Rotator());
			}
			else
			{
				// Location
				if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
				{
					Actor->SetActorLocation(T.GetLocation());
				}
				// Rotation
				if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
				{
					Actor->SetActorRotation(T.GetRotation().Rotator());
				}
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
			{
				Actor->SetActorScale3D(T.GetScale3D());
			}
		}
	}

	void SetTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules, const ECsTransformSpace(&Spaces)[(uint8)ECsTransform::ECsTransform_MAX])
	{
		check(Component);

		// Location
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
		{
			if (Spaces[(uint8)ECsTransform::Translation] == ECsTransformSpace::Relative)
				Component->SetRelativeLocation(Transform.GetLocation());
			else
				Component->SetWorldLocation(Transform.GetLocation());
		}
		// Rotation
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
		{
			if (Spaces[(uint8)ECsTransform::Rotation] == ECsTransformSpace::Relative)
				Component->SetRelativeRotation(Transform.GetRotation().Rotator());
			else
				Component->SetWorldRotation(Transform.GetRotation().Rotator());
		}
		// Scale
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
		{
			if (Spaces[(uint8)ECsTransform::Scale] == ECsTransformSpace::Relative)
				Component->SetRelativeScale3D(Transform.GetScale3D());
			else
				Component->SetWorldScale3D(Transform.GetScale3D());
		}
	}

	void SetTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules, const ECsTransformSpace(&Spaces)[(uint8)ECsTransform::ECsTransform_MAX])
	{
		check(Component);

		const FTransform3d T = MathLibrary::Convert(Transform);

		// Location
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Location))
		{
			if (Spaces[(uint8)ECsTransform::Translation] == ECsTransformSpace::Relative)
				Component->SetRelativeLocation(T.GetLocation());
			else
				Component->SetWorldLocation(T.GetLocation());
		}
		// Rotation
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Rotation))
		{
			if (Spaces[(uint8)ECsTransform::Rotation] == ECsTransformSpace::Relative)
				Component->SetRelativeRotation(T.GetRotation().Rotator());
			else
				Component->SetWorldRotation(T.GetRotation().Rotator());
		}
		// Scale
		if (CS_TEST_BLUEPRINT_BITFLAG(Rules, ECsTransformRules::Scale))
		{
			if (Spaces[(uint8)ECsTransform::Scale] == ECsTransformSpace::Relative)
				Component->SetRelativeScale3D(T.GetScale3D());
			else
				Component->SetWorldScale3D(T.GetScale3D());
		}
	}

	bool AreTransformsEqual(const FTransform3d& A, const FTransform3d& B, const int32& Rules)
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

	bool AreTransformsEqual(const FTransform3f& A, const FTransform3f& B, const int32& Rules)
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

	bool AreTransformsEqual(const FTransform3f& A, const FTransform3d& B, const int32& Rules)
	{
		const FTransform3f T = MathLibrary::Convert(B);

		return AreTransformsEqual(A, T, Rules);
	}

	bool AreTransformsEqual(const FTransform3d& A, const FTransform3f& B, const int32& Rules)
	{
		const FTransform3f T = MathLibrary::Convert(A);

		return AreTransformsEqual(T, B, Rules);
	}

	#undef MathLibrary
}

#pragma endregion TransformRules