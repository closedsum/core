// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Math.h"

// Library
	// Common
#include "Library/CsLibrary_Math.h"
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

	FRotator3f GetRotation(AActor* Actor, const int32& Rules)
	{
		using namespace NCached;

		const FString& Context = Str::GetRotation;

		CS_IS_PTR_NULL_CHECKED(Actor)

		typedef NCsMath::FLibrary MathLibrary;

		return GetRotation(MathLibrary::Convert(Actor->GetActorRotation()), Rules);
	}

	FRotator3f GetRotation(USceneComponent* Component, const int32& Rules)
	{
		using namespace NCached;

		const FString& Context = Str::GetRotation;

		CS_IS_PTR_NULL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return GetRotation(MathLibrary::Convert(Component->GetComponentRotation()), Rules);
	}
}

#pragma endregion RotationRules

// Transform
#pragma region

namespace NCsTransform
{
	namespace Ref
	{
		typedef EMCsTransform EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Translation);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Scale);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransform_MAX, "MAX");
	}
}

#pragma endregion Transform

// TransformSpace
#pragma region

namespace NCsTransformSpace
{
	namespace Ref
	{
		typedef EMCsTransformSpace EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Relative);
		CSCORE_API CS_ADD_TO_ENUM_MAP(World);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransformSpace_MAX, "MAX");
	}
}

#pragma endregion TransformSpace

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

		typedef NCsMath::FLibrary MathLibrary;

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

		typedef NCsMath::FLibrary MathLibrary;

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

		typedef NCsMath::FLibrary MathLibrary;

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

		typedef NCsMath::FLibrary MathLibrary;

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

		typedef NCsMath::FLibrary MathLibrary;

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
		typedef NCsMath::FLibrary MathLibrary;

		const FTransform3f T = MathLibrary::Convert(B);

		return AreTransformsEqual(A, T, Rules);
	}

	bool AreTransformsEqual(const FTransform3d& A, const FTransform3f& B, const int32& Rules)
	{
		typedef NCsMath::FLibrary MathLibrary;

		const FTransform3f T = MathLibrary::Convert(A);

		return AreTransformsEqual(T, B, Rules);
	}
}

#pragma endregion TransformRules

// TransformLocationMember
#pragma region

namespace NCsTransformLocationMember
{
	namespace Ref
	{
		typedef EMCsTransformLocationMember EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(X);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Y);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Z);
	}

	CSCORE_API const uint32 None = 0;
	CSCORE_API const uint32 All = 7; // 1 + 2 + 4
}

namespace NCsTransform
{
	namespace NLocation
	{
		namespace NMember
		{
			namespace Ref
			{
				typedef EMMember EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(X);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Y);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Z);
			}

			CSCORE_API const uint32 None = 0;
			CSCORE_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformLocationMember

// FCsTransform_Location_Multiplier
#pragma region

#define ProxyType NCsTransform::NLocation::FMultiplier

void FCsTransform_Location_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	Proxy->SetMultiplier(&Multiplier);
	Proxy->SetMembers(&Members);
}

void FCsTransform_Location_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	Proxy->SetMultiplier(Multiplier);
	Proxy->SetMembers(Members);
}

#undef ProxyType

bool FCsTransform_Location_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Location_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

namespace NCsTransform
{
	namespace NLocation
	{
		bool FMultiplier::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			return true;
		}
	}
}

#pragma endregion FCsTransform_Location_Multiplier

// TransformRotationMember
#pragma region

namespace NCsTransformRotationMember
{
	namespace Ref
	{
		typedef EMCsTransformRotationMember EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Pitch);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Yaw);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Roll);
	}

	CSCORE_API const uint32 None = 0;
	CSCORE_API const uint32 All = 7; // 1 + 2 + 4
}

namespace NCsTransform
{
	namespace NRotation
	{
		namespace NMember
		{
			namespace Ref
			{
				typedef EMMember EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Pitch);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Yaw);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Roll);
			}

			CSCORE_API const uint32 None = 0;
			CSCORE_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformRotationMember

// FCsTransform_Rotation_Multiplier
#pragma region

#define ProxyType NCsTransform::NRotation::FMultiplier

void FCsTransform_Rotation_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	Proxy->SetMultiplier(&Multiplier);
	Proxy->SetMembers(&Members);
}

void FCsTransform_Rotation_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	Proxy->SetMultiplier(Multiplier);
	Proxy->SetMembers(Members);
}

#undef ProxyType

bool FCsTransform_Rotation_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Rotation_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

namespace NCsTransform
{
	namespace NRotation
	{
		bool FMultiplier::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			return true;
		}
	}
}

#pragma endregion FCsTransform_Rotation_Multiplier

// TransformScaleMember
#pragma region

namespace NCsTransformScaleMember
{
	namespace Ref
	{
		typedef EMCsTransformScaleMember EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(X);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Y);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Z);
	}

	CSCORE_API const uint32 None = 0;
	CSCORE_API const uint32 All = 7; // 1 + 2 + 4
}

namespace NCsTransform
{
	namespace NScale
	{
		namespace NMember
		{
			namespace Ref
			{
				typedef EMMember EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(X);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Y);
				CSCORE_API CS_ADD_TO_ENUM_MASK_MAP(Z);
			}

			CSCORE_API const uint32 None = 0;
			CSCORE_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformScaleMember

// FCsTransform_Scale_Multiplier
#pragma region

#define ProxyType NCsTransform::NScale::FMultiplier

void FCsTransform_Scale_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	Proxy->SetMultiplier(&Multiplier);
	Proxy->SetMembers(&Members);
}

void FCsTransform_Scale_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	Proxy->SetMultiplier(Multiplier);
	Proxy->SetMembers(Members);
}

#undef ProxyType

bool FCsTransform_Scale_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Scale_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

namespace NCsTransform
{
	namespace NScale
	{
		bool FMultiplier::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			return true;
		}
	}
}

#pragma endregion FCsTransform_Scale_Multiplier

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

// DotDimension
#pragma region

namespace NCsDotDimension
{
	namespace Ref
	{
		typedef EMCsDotDimension EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDotDimension_MAX, "MAX");
	}
}

namespace NCsDot
{
	namespace NDimension
	{
		namespace Ref
		{
			typedef EMDimension EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDimension_MAX, "MAX");
		}
	}
}

#pragma endregion DotDimension

// Vector4Member
#pragma region

namespace NCsVector4Member
{
	namespace Ref
	{
		typedef EMCsVector4Member EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(X);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Y);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Z);
		CSCORE_API CS_ADD_TO_ENUM_MAP(W);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsVector4Member_MAX, "MAX");
	}
}

namespace NCsVector4
{
	namespace NMember
	{
		namespace Ref
		{
			typedef EMMember EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(X);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Y);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Z);
			CSCORE_API CS_ADD_TO_ENUM_MAP(W);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMember_MAX, "MAX");
		}
	}
}

#pragma endregion Vector4Member