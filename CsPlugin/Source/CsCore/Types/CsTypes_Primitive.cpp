// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

// Cached
#pragma region

namespace NCsCached
{
	namespace Str
	{
		CSCORE_API const FString Empty = TEXT("");
		CSCORE_API const FString None = TEXT("None");
		CSCORE_API const FString INVALID = TEXT("INVALID");
		CSCORE_API const FString Dot = TEXT(".");
		CSCORE_API const FString True = TEXT("True");
		CSCORE_API const FString _true = TEXT("true");
		CSCORE_API const FString False = TEXT("False");
		CSCORE_API const FString _false = TEXT("false");
		CSCORE_API const FString Index = TEXT("Index");
		CSCORE_API const FString PREVIEW = TEXT("PREVIEW");
		CSCORE_API const FString Zero = TEXT("0");
		CSCORE_API const FString One = TEXT("1");

		CSCORE_API const FString Text = TEXT("Text");
		CSCORE_API const FString Button = TEXT("Button");
		CSCORE_API const FString Image = TEXT("Image");

		// Vector to String
		CSCORE_API const FString XEquals = TEXT("X=");
		CSCORE_API const FString YEquals = TEXT("Y=");
		CSCORE_API const FString ZEquals = TEXT("Z=");
		// Rotator to String
		CSCORE_API const FString RollEquals = TEXT("R=");
		CSCORE_API const FString PitchEquals = TEXT("P=");
		CSCORE_API const FString YawEquals = TEXT("Y=");
	}

	namespace Ref
	{
		CSCORE_API const bool True = true;
		CSCORE_API const bool False = false;
		CSCORE_API const uint8 Byte = 0;
		CSCORE_API const int8 SByte = 0;
		CSCORE_API const uint16 Short = 0;
		CSCORE_API const int16 SShort = 0;
		CSCORE_API const uint32 Int = 0;
		CSCORE_API const int32 SInt = 0;
		CSCORE_API const uint64 Long = 0;
		CSCORE_API const uint64 Long_MAX = UINT64_MAX;
		CSCORE_API const int64 SLong = 0;
		CSCORE_API const float Float = 0.0f;
		CSCORE_API const FString String = TEXT("");
		CSCORE_API const FName Name = NAME_None;
	}

	namespace Name
	{
		CSCORE_API const FName None = NAME_None;
		CSCORE_API const FName Null = FName("NULL");
	}

	namespace Ext
	{
		CSCORE_API const FString json = TEXT(".json");
		CSCORE_API const FString txt = TEXT(".txt");
		CSCORE_API const FString js = TEXT(".js");
	}
}

#pragma endregion Cached

// UserDefinedEnum
#pragma region

namespace NCsUserDefinedEnum
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUserDefinedEnum, FECsDataType);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUserDefinedEnum, FECsDataCollectionType);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUserDefinedEnum, FECsInputAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUserDefinedEnum, FECsInputActionMap);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUserDefinedEnum, FECsGameEvent);
}

#pragma endregion UserDefinedEnum

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