// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Math.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Common
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Math)

// ParametricFunctionType
#pragma region

namespace NCsParametricFunctionType
{
	namespace Ref
	{
		typedef EMCsParametricFunctionType EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Linear);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Quadratic);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Sine);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsParametricFunctionType_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsParametricFunctionType_MAX;
}

#pragma endregion ParametricFunctionType

// RotationRules
#pragma region

namespace NCsRotationRules
{
	namespace Ref
	{
		typedef EMCsRotationRules EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Pitch);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Yaw);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Roll);
	}

	CSTYPES_API const int32 None = 0;
	CSTYPES_API const int32 All = 7; // 1 + 2 + 4
}

#pragma endregion RotationRules

// Transform
#pragma region

namespace NCsTransform
{
	namespace Ref
	{
		typedef EMCsTransform EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Translation);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Scale);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransform_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Relative);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(World);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransformSpace_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Location);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Rotation);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Scale);
	}

	CSTYPES_API const int32 None = 0;
	CSTYPES_API const int32 All = 7; // 1 + 2 + 4
}

#pragma endregion TransformRules

// TransformLocationMember
#pragma region

namespace NCsTransformLocationMember
{
	namespace Ref
	{
		typedef EMCsTransformLocationMember EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(X);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Y);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Z);
	}

	CSTYPES_API const uint32 None = 0;
	CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
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

				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(X);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Y);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Z);
			}

			CSTYPES_API const uint32 None = 0;
			CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformLocationMember

// FCsTransform_Location_Multiplier
#pragma region

#define ProxyType NCsTransform::NLocation::FMultiplier

void FCsTransform_Location_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	CS_COPY_TO_PROXY(Proxy, Multiplier);
	CS_COPY_TO_PROXY(Proxy, Members);
}

void FCsTransform_Location_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Multiplier);
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Members);
}

#undef ProxyType

bool FCsTransform_Location_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Location_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Pitch);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Yaw);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Roll);
	}

	CSTYPES_API const uint32 None = 0;
	CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
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

				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Pitch);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Yaw);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Roll);
			}

			CSTYPES_API const uint32 None = 0;
			CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformRotationMember

// FCsTransform_Rotation_Multiplier
#pragma region

#define ProxyType NCsTransform::NRotation::FMultiplier

void FCsTransform_Rotation_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	CS_COPY_TO_PROXY(Proxy, Multiplier);
	CS_COPY_TO_PROXY(Proxy, Members);
}

void FCsTransform_Rotation_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Multiplier);
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Members);
}

#undef ProxyType

bool FCsTransform_Rotation_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Rotation_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(X);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Y);
		CSTYPES_API CS_ADD_TO_ENUM_FLAG_MAP(Z);
	}

	CSTYPES_API const uint32 None = 0;
	CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
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

				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(X);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Y);
				CSTYPES_API CS_ADD_TO_ENUM_MASK_MAP(Z);
			}

			CSTYPES_API const uint32 None = 0;
			CSTYPES_API const uint32 All = 7; // 1 + 2 + 4
		}
	}
}

#pragma endregion TransformScaleMember

// FCsTransform_Scale_Multiplier
#pragma region

#define ProxyType NCsTransform::NScale::FMultiplier

void FCsTransform_Scale_Multiplier::CopyToProxy(ProxyType* Proxy)
{
	CS_COPY_TO_PROXY(Proxy, Multiplier);
	CS_COPY_TO_PROXY(Proxy, Members);
}

void FCsTransform_Scale_Multiplier::CopyToProxyAsValue(ProxyType* Proxy) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Multiplier);
	CS_COPY_TO_PROXY_AS_VALUE(Proxy, Members);
}

#undef ProxyType

bool FCsTransform_Scale_Multiplier::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsTransform_Scale_Multiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		bool FMultiplier::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

bool FCsRay::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDotDimension_MAX, "MAX");
	}
}

namespace NCsDot
{
	namespace NDimension
	{
		namespace Ref
		{
			typedef EMDimension EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(XY, "2D: X,Y");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(XYZ, "3D: X,Y,Z");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDimension_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(X);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Y);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Z);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(W);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsVector4Member_MAX, "MAX");
	}
}

namespace NCsVector4
{
	namespace NMember
	{
		namespace Ref
		{
			typedef EMMember EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(X);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Y);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Z);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(W);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMember_MAX, "MAX");
		}
	}
}

#pragma endregion Vector4Member