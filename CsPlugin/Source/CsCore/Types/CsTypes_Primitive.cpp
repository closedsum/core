// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

// MemberType
#pragma region

namespace NCsMemberType
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Bool);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Uint8);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Int32);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Enum);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, EnumClass);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, EnumNamespaced);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Float);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, String);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Name);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Vector);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Rotator);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Color);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Object);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Actor);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, Pawn);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, ActorComponent);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, SceneComponent);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, PrimitiveComponent);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, StaticMeshComponent);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsMemberType, SkeletalMeshComponent);
}

#pragma endregion MemberType

// StringCompare
#pragma region

namespace NCsStringCompare
{
	namespace Ref
	{
		CSCORE_API const Type Equals = EMCsStringCompare::Get().Add(Type::Equals, TEXT("Equals"));
		CSCORE_API const Type StartsWith = EMCsStringCompare::Get().Add(Type::StartsWith, TEXT("Starts With"));
		CSCORE_API const Type EndsWith = EMCsStringCompare::Get().Add(Type::EndsWith, TEXT("Ends With"));
		CSCORE_API const Type Contains = EMCsStringCompare::Get().Add(Type::Contains, TEXT("Contains"));
		CSCORE_API const Type ECsStringCompare_MAX = EMCsStringCompare::Get().Add(Type::ECsStringCompare_MAX, TEXT("ECsStringCompare_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsStringCompare_MAX;
}
#pragma endregion StringCompare