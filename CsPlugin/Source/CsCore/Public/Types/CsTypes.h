// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_View.h"
#include "Chaos/ChaosEngineInterface.h"

#include "CsTypes.generated.h"

#define CS_ACTOR_SMALLEST_SCALE 0.001f
#define CS_VECTOR_ONE FVector3f(1.0f)

#define CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID 255
#define CS_INVALID_AI_PLAYER_STATE_UNIQUE_MAPPING_ID 255

// Transform
#pragma region

	// Axes
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsAxes : uint8
{
	X	UMETA(DisplayName = "X | Pitch"),
	Y	UMETA(DisplayName = "Y | Yaw"),
	Z	UMETA(DisplayName = "Z | Roll"),
};

struct CSCORE_API EMCsAxes : public TCsEnumFlagMap<ECsAxes>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsAxes, ECsAxes)
};

namespace NCsAxes
{
	namespace Ref
	{
		typedef ECsAxes Type;

		extern CSCORE_API const Type X;
		extern CSCORE_API const Type Y;
		extern CSCORE_API const Type Z;
	}
}

#define ECS_AXES_NONE 0
					 // (1<<((uint8)ECsAxes::X)) | (1<<((uint8)ECsAxes::Y)) | (1<<((uint8)ECsAxes::Z))
					 // 1 + 2 + 4 = 7
#define ECS_AXES_3D_ALL 7

#pragma endregion Axes

	// Axes_Editor
#pragma region

UENUM(BlueprintType)
enum class ECsAxes_Editor : uint8
{
	X					UMETA(DisplayName = "X | Roll"),
	Y					UMETA(DisplayName = "Y | Pitch"),
	Z					UMETA(DisplayName = "Z | Yaw"),
	ECsAxes_Editor_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAxes_Editor : public TCsEnumMap<ECsAxes_Editor>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAxes_Editor, ECsAxes_Editor)
};

namespace NCsAxes_Editor
{
	typedef ECsAxes_Editor Type;

	namespace Ref
	{
		extern CSCORE_API const Type X;
		extern CSCORE_API const Type Y;
		extern CSCORE_API const Type Z;
		extern CSCORE_API const Type ECsAxes_Editor_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const ECsAxes& ToBaseType(const Type &EType)
	{
		if (EType == Type::X) { return NCsAxes::Ref::X; }
		if (EType == Type::Y) { return NCsAxes::Ref::Y; }
		if (EType == Type::Z) { return NCsAxes::Ref::Z; }
		return NCsAxes::Ref::X;
	}
}

#define ECS_AXES_EDITOR_MAX (uint8)ECsAxes_Editor::ECsAxes_Editor_MAX

#pragma endregion Axes_Editor

	// TransformMember
#pragma region

UENUM(BlueprintType)
enum class ECsTransformMember : uint8
{
	Location				UMETA(DisplayName = "Location"),
	Rotation				UMETA(DisplayName = "Rotation"),
	Scale					UMETA(DisplayName = "Scale"),
	ECsTransformMember_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTransformMember : public TCsEnumMap<ECsTransformMember>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTransformMember, ECsTransformMember)
};

namespace NCsTransformMember
{
	typedef ECsTransformMember Type;

	namespace Ref
	{
		extern CSCORE_API const Type Location;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type Scale;
		extern CSCORE_API const Type ECsTransformMember_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion TransformMember

#pragma endregion Transform

// Blueprint
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CsCore")
	TSoftObjectPtr<class UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, Category = "CsCore", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsBlueprint() :
		Blueprint_LoadFlags(0),
		Blueprint_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CsCore")
	TArray<TSoftObjectPtr<class UBlueprint>> Blueprints;

	UPROPERTY(EditAnywhere, Category = "CsCore", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprints_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UBlueprintGeneratedClass*> Blueprints_Internal;

public:
	FCsTArrayBlueprint() :
		Blueprints_LoadFlags(0)
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprints_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsTArrayBlueprint& operator=(const FCsTArrayBlueprint& B)
	{
		Blueprints.Reset();

		const int32 Count = B.Blueprints.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Blueprints.Add(B.Blueprints[I]);
		}
		Blueprints_LoadFlags = B.Blueprints_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArrayBlueprint& B) const
	{
		int32 Count  = Blueprints.Num();
		int32 CountB = B.Blueprints.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Blueprints[I] != B.Blueprints[I])
				return false;
		}

		Count  = Blueprints_Internal.Num();
		CountB = B.Blueprints_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Blueprints_Internal[I] != B.Blueprints_Internal[I])
				return false;
		}
		return Blueprints_LoadFlags == B.Blueprints_LoadFlags;
	}

	FORCEINLINE bool operator!=(const FCsTArrayBlueprint& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<UBlueprintGeneratedClass*>* Get()
	{
		return &Blueprints_Internal;
	}

	FORCEINLINE class UBlueprintGeneratedClass* Get(const int32 Index)
	{
		return Index < Blueprints_Internal.Num() ? Blueprints_Internal[Index] : NULL;
	}
};

#pragma endregion Blueprint

// Replication
#pragma region

#define CS_SERVER_TO_CLIENT_SEND_FREQUENCY 0.01666666667

#pragma endregion Replication

// Color
#pragma region

	// LinearColor
#pragma region

UENUM(BlueprintType)
enum class ECsLinearColor : uint8
{
	White				UMETA(DisplayName = "White"),
	Gray				UMETA(DisplayName = "Gray"),
	Black				UMETA(DisplayName = "Black"),
	Transparent			UMETA(DisplayName = "Transparent"),
	Red					UMETA(DisplayName = "Red"),
	Green				UMETA(DisplayName = "Green"),
	Blue				UMETA(DisplayName = "Blue"),
	Yellow				UMETA(DisplayName = "Yellow"),
	ECsLinearColor_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsLinearColor : public TCsEnumMap<ECsLinearColor>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsLinearColor, ECsLinearColor)
};

namespace NCsLinearColor
{
	typedef ECsLinearColor Type;

	namespace Ref
	{
		extern CSCORE_API const Type White;
		extern CSCORE_API const Type Gray;
		extern CSCORE_API const Type Black;
		extern CSCORE_API const Type Transparent;
		extern CSCORE_API const Type Red;
		extern CSCORE_API const Type Green;
		extern CSCORE_API const Type Blue;
		extern CSCORE_API const Type Yellow;
		extern CSCORE_API const Type ECsLinearColor_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE FLinearColor ToLinearColor(const Type &EType)
	{
		if (EType == Type::White) { return FLinearColor::White; }
		if (EType == Type::Gray) { return FLinearColor::Gray; }
		if (EType == Type::Black) { return FLinearColor::Black; }
		if (EType == Type::Transparent) { return FLinearColor::Transparent; }
		if (EType == Type::Red) { return FLinearColor::Red; }
		if (EType == Type::Green) { return FLinearColor::Green; }
		if (EType == Type::Blue) { return FLinearColor::Blue; }
		if (EType == Type::Yellow) { return FLinearColor::Yellow; }
		return FLinearColor::White;
	}
}

#define ECS_LINEAR_COLOR_MAX (uint8)ECsLinearColor::ECsLinearColor_MAX

#pragma endregion LinearColor

UENUM(BlueprintType)
enum class ECsColor : uint8
{
	White			UMETA(DisplayName = "White"),
	Black			UMETA(DisplayName = "Black"),
	Transparent		UMETA(DisplayName = "Transparent"),
	Red				UMETA(DisplayName = "Red"),
	Green			UMETA(DisplayName = "Green"),
	Blue			UMETA(DisplayName = "Blue"),
	Yellow			UMETA(DisplayName = "Yellow"),
	Cyan			UMETA(DisplayName = "Cyan"),
	Magenta			UMETA(DisplayName = "Magenta"),
	Orange			UMETA(DisplayName = "Orange"),
	Purple			UMETA(DisplayName = "Purple"),
	Turquoise		UMETA(DisplayName = "Turquoise"),
	Silver			UMETA(DisplayName = "Silver"),
	Emerald			UMETA(DisplayName = "Emerald"),
	ECsColor_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsColor : public TCsEnumMap<ECsColor>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsColor, ECsColor)
};

namespace NCsColor
{
	typedef ECsColor Type;

	namespace Ref
	{
		extern CSCORE_API const Type White;
		extern CSCORE_API const Type Black;
		extern CSCORE_API const Type Transparent;
		extern CSCORE_API const Type Red;
		extern CSCORE_API const Type Green;
		extern CSCORE_API const Type Blue;
		extern CSCORE_API const Type Yellow;
		extern CSCORE_API const Type Cyan;
		extern CSCORE_API const Type Magenta;
		extern CSCORE_API const Type Orange;
		extern CSCORE_API const Type Purple;
		extern CSCORE_API const Type Turquoise;
		extern CSCORE_API const Type Silver;
		extern CSCORE_API const Type Emerald;
		extern CSCORE_API const Type ECsColor_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FColor& ToColor(const Type &EType)
	{
		if (EType == Type::White) { return FColor::White; }
		if (EType == Type::Black) { return FColor::Black; }
		if (EType == Type::Transparent) { return FColor::Transparent; }
		if (EType == Type::Red) { return FColor::Red; }
		if (EType == Type::Green) { return FColor::Green; }
		if (EType == Type::Blue) { return FColor::Blue; }
		if (EType == Type::Yellow) { return FColor::Yellow; }
		if (EType == Type::Cyan) { return FColor::Cyan; }
		if (EType == Type::Magenta) { return FColor::Magenta; }
		if (EType == Type::Orange) { return FColor::Orange; }
		if (EType == Type::Purple) { return FColor::Purple; }
		if (EType == Type::Turquoise) { return FColor::Turquoise; }
		if (EType == Type::Silver) { return FColor::Silver; }
		if (EType == Type::Emerald) { return FColor::Emerald; }
		return FColor::White;
	}
}

#define ECS_COLOR_MAX (uint8)ECsColor::ECsColor_MAX

#pragma endregion Color