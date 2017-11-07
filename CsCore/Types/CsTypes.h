// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/pt.h"
#include "Engine.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/BlendSpace.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AnimBlueprint.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Sound/SoundCue.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "../HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"

#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_View.h"

#include "CsTypes.generated.h"
#pragma once

#define CS_CVAR_SHOW_LOG 1
#define CS_CVAR_HIDE_LOG 0
#define CS_CVAR_DRAW 1
#define CS_CVAR_DISPLAY 1

#define CS_ACTOR_SMALLEST_SCALE 0.001f
#define CS_VECTOR_ONE FVector(1.0f)

#define CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID 255

// Level
#pragma region

UENUM(BlueprintType)
namespace ECsLevelState
{
	enum Type
	{
		None				UMETA(DisplayName = "None"),
		Loaded				UMETA(DisplayName = "Loaded"),
		BeginTransition		UMETA(DisplayName = "Begin Transition"),
		InTransition		UMETA(DisplayName = "In Transition"),
		ECsLevelState_MAX	UMETA(Hidden),
	};
}

namespace ECsLevelState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString Loaded = TCsString(TEXT("Loaded"), TEXT("loaded"), TEXT("loaded"));
		const TCsString BeginTransition = TCsString(TEXT("BeginTransition"), TEXT("begintransition"), TEXT("begin transition"));
		const TCsString InTransition = TCsString(TEXT("InTransition"), TEXT("intransition"), TEXT("in transition"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::Loaded) { return Str::Loaded.Value; }
		if (EType == Type::BeginTransition) { return Str::BeginTransition.Value; }
		if (EType == Type::InTransition) { return Str::InTransition.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::Loaded) { return Type::Loaded; }
		if (String == Str::BeginTransition) { return Type::BeginTransition; }
		if (String == Str::InTransition) { return Type::InTransition; }
		return Type::ECsLevelState_MAX;
	}
}

#define ECS_LEVEL_STATE (uint8)ECsLevelState::ECsLevelState_MAX
typedef TEnumAsByte<ECsLevelState::Type> TCsLevelState;

#pragma endregion Level

UENUM(BlueprintType)
namespace ECsEasingType
{
	enum Type
	{
		Linear				UMETA(DisplayName = "Linear"),
		BounceIn			UMETA(DisplayName = "Bounce In"),
		BounceOut			UMETA(DisplayName = "Bounce Out"),
		BounceInOut			UMETA(DisplayName = "Bounce In Out"),
		CubicIn				UMETA(DisplayName = "Cubic In"),
		CubicOut			UMETA(DisplayName = "Cubic Out"),
		CubicInOut			UMETA(DisplayName = "Cubic In Out"),
		ExpoIn				UMETA(DisplayName = "Cubic In"),
		ExpoOut				UMETA(DisplayName = "Expo Out"),
		ExpoInOut			UMETA(DisplayName = "Expo In Out"),
		ECsEasingType_MAX	UMETA(Hidden),
	};
}

namespace ECsEasingType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Linear = TCsString(TEXT("Linear"), TEXT("linear"), TEXT("linear"));
		const TCsString BounceIn = TCsString(TEXT("BounceIn"), TEXT("bouncein"), TEXT("bounce in"));
		const TCsString BounceOut = TCsString(TEXT("BounceOut"), TEXT("bounceout"), TEXT("bounce out"));
		const TCsString BounceInOut = TCsString(TEXT("BounceInOut"), TEXT("bounceinout"), TEXT("bounce in out"));
		const TCsString CubicIn = TCsString(TEXT("CubicIn"), TEXT("cubicin"), TEXT("cubic in"));
		const TCsString CubicOut = TCsString(TEXT("CubicOut"), TEXT("cubicout"), TEXT("cubic out"));
		const TCsString CubicInOut = TCsString(TEXT("CubicInOut"), TEXT("cubicinout"), TEXT("cubic in out"));
		const TCsString ExpoIn = TCsString(TEXT("ExpoIn"), TEXT("expoin"), TEXT("expo in"));
		const TCsString ExpoOut = TCsString(TEXT("ExpoOut"), TEXT("expoout"), TEXT("expo out"));
		const TCsString ExpoInOut = TCsString(TEXT("ExpoInOut"), TEXT("expoinout"), TEXT("expo in out"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Linear) { return Str::Linear.Value; }
		if (EType == Type::BounceIn) { return Str::BounceIn.Value; }
		if (EType == Type::BounceOut) { return Str::BounceOut.Value; }
		if (EType == Type::BounceInOut) { return Str::BounceInOut.Value; }
		if (EType == Type::CubicIn) { return Str::CubicIn.Value; }
		if (EType == Type::CubicOut) { return Str::CubicOut.Value; }
		if (EType == Type::CubicInOut) { return Str::CubicInOut.Value; }
		if (EType == Type::ExpoIn) { return Str::ExpoIn.Value; }
		if (EType == Type::ExpoOut) { return Str::ExpoOut.Value; }
		if (EType == Type::ExpoInOut) { return Str::ExpoInOut.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Linear) { return Type::Linear; }
		if (String == Str::BounceIn) { return Type::BounceIn; }
		if (String == Str::BounceOut) { return Type::BounceOut; }
		if (String == Str::BounceInOut) { return Type::BounceInOut; }
		if (String == Str::CubicIn) { return Type::CubicIn; }
		if (String == Str::CubicOut) { return Type::CubicOut; }
		if (String == Str::CubicInOut) { return Type::CubicInOut; }
		if (String == Str::ExpoIn) { return Type::ExpoIn; }
		if (String == Str::ExpoOut) { return Type::ExpoOut; }
		if (String == Str::ExpoInOut) { return Type::ExpoInOut; }
		return Type::ECsEasingType_MAX;
	}
}

#define ECS_EASING_TYPE_MAX (uint8)ECsEasingType::ECsEasingType_MAX
typedef TEnumAsByte<ECsEasingType::Type> TCsEasingType;

// Transform
#pragma region


UENUM(BlueprintType, meta = (Bitflags))
enum class ECsAxes : uint8
{
	X	UMETA(DisplayName = "X | Pitch"),
	Y	UMETA(DisplayName = "Y | Yaw"),
	Z	UMETA(DisplayName = "Z | Roll"),
};

#define ECS_AXES_NONE 0
#define ECS_AXES_ALL (1<<((uint8)ECsAxes::X)) | (1<<((uint8)ECsAxes::Y)) | (1<<((uint8)ECsAxes::Z))

UENUM(BlueprintType)
namespace ECsAxes_Editor
{
	enum Type
	{
		X					UMETA(DisplayName = "X | Roll"),
		Y					UMETA(DisplayName = "Y | Pitch"),
		Z					UMETA(DisplayName = "Z | Yaw"),
		ECsAxes_Editor_MAX	UMETA(Hidden),
	};
}

namespace ECsAxes_Editor
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString X = TCsString(TEXT("X"), TEXT("x"), TEXT("roll"));
		const TCsString Y = TCsString(TEXT("Y"), TEXT("y"), TEXT("pitch"));
		const TCsString Z = TCsString(TEXT("Z"), TEXT("z"), TEXT("yaw"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::X) { return Str::X.Value; }
		if (EType == Type::Y) { return Str::Y.Value; }
		if (EType == Type::Z) { return Str::Z.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::X) { return Type::X; }
		if (String == Str::Y) { return Type::Y; }
		if (String == Str::Z) { return Type::Z; }
		return Type::ECsAxes_Editor_MAX;
	}

	FORCEINLINE ECsAxes ToBaseType(const Type &EType)
	{
		if (EType == Type::X) { return ECsAxes::X; }
		if (EType == Type::Y) { return ECsAxes::Y; }
		if (EType == Type::Z) { return ECsAxes::Z; }
		return ECsAxes::X;
	}

	FORCEINLINE ECsAxes ToFlag(const FString &String)
	{
		if (String == Str::X) { return ECsAxes::X; }
		if (String == Str::Y) { return ECsAxes::Y; }
		if (String == Str::Z) { return ECsAxes::Z; }
		return ECsAxes::X;;
	}
}

#define ECS_AXES_EDITOR_MAX (uint8)ECsAxes_Editor::ECsAxes_Editor_MAX
typedef TEnumAsByte<ECsAxes_Editor::Type> TCsAxes_Editor;

UENUM(BlueprintType)
namespace ECsTransformMember
{
	enum Type
	{
		Location				UMETA(DisplayName = "Location"),
		Rotation				UMETA(DisplayName = "Rotation"),
		Scale					UMETA(DisplayName = "Scale"),
		ECsTransformMember_MAX	UMETA(Hidden),
	};
}

namespace ECsTransformMember
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Location = TCsString(TEXT("Location"), TEXT("location"));
		const TCsString Rotation = TCsString(TEXT("Rotation"), TEXT("rotation"));
		const TCsString Scale = TCsString(TEXT("Scale"), TEXT("scale"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Location) { return Str::Location.Value; }
		if (EType == Type::Rotation) { return Str::Rotation.Value; }
		if (EType == Type::Scale) { return Str::Scale.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Location) { return Type::Location; }
		if (String == Str::Rotation) { return Type::Rotation; }
		if (String == Str::Scale) { return Type::Scale; }
		return Type::ECsTransformMember_MAX;
	}
}

#define ECS_TRANSFORM_MEMBER_MAX (uint8)ECsTransformMember::ECsTransformMember_MAX
typedef TEnumAsByte<ECsTransformMember::Type> TCsTransformMember;

#pragma endregion Transform

// Static Mesh
#pragma region

USTRUCT(BlueprintType)
struct FCsStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

private:
	UPROPERTY(Transient)
	class UStaticMesh* Mesh_Internal;

public:
	FCsStaticMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh_LoadFlags, ECsLoadFlags::Game);
	}

	UStaticMesh* Get() const
	{
		return Mesh_Internal;
	}

	FCsStaticMesh& operator=(const FCsStaticMesh& B)
	{
		Mesh = B.Mesh;
		Mesh_LoadFlags = B.Mesh_LoadFlags;
		Mesh_Internal = B.Mesh_Internal;
		return *this;
	}

	bool operator==(const FCsStaticMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	bool operator!=(const FCsStaticMesh& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<UStaticMesh> Mesh1P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<UStaticMesh> Mesh3P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<UStaticMesh> Mesh3P_Low;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<UStaticMesh> MeshVR;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 MeshVR_LoadFlags;

private:
	UPROPERTY(Transient)
	class UStaticMesh* Mesh1P_Internal;

	UPROPERTY(Transient)
	class UStaticMesh* Mesh3P_Internal;

	UPROPERTY(Transient)
	class UStaticMesh* Mesh3P_Low_Internal;

	UPROPERTY(Transient)
	class UStaticMesh* MeshVR_Internal;
public:
	FCsFpsStaticMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(MeshVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(MeshVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	FCsFpsStaticMesh& operator=(const FCsFpsStaticMesh& B)
	{
		Mesh1P			 = B.Mesh1P;
		Mesh1P_LoadFlags = B.Mesh1P_LoadFlags;
		Mesh1P_Internal  = B.Mesh1P_Internal;

		Mesh3P			 = B.Mesh3P;
		Mesh3P_LoadFlags = B.Mesh3P_LoadFlags;
		Mesh3P_Internal  = B.Mesh3P_Internal;

		Mesh3P_Low			 = B.Mesh3P_Low;
		Mesh3P_Low_LoadFlags = B.Mesh3P_Low_LoadFlags;
		Mesh3P_Low_Internal  = B.Mesh3P_Low_Internal;

		MeshVR			 = B.MeshVR;
		MeshVR_LoadFlags = B.MeshVR_LoadFlags;
		MeshVR_Internal  = B.MeshVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsStaticMesh& B) const
	{
		return Mesh1P == B.Mesh1P && Mesh1P_LoadFlags == B.Mesh1P_LoadFlags && Mesh1P_Internal == B.Mesh1P_Internal &&
			   Mesh3P == B.Mesh3P && Mesh3P_LoadFlags == B.Mesh3P_LoadFlags && Mesh3P_Internal == B.Mesh3P_Internal &&
			   Mesh3P_Low == B.Mesh3P_Low && Mesh3P_Low_LoadFlags == B.Mesh3P_Low_LoadFlags && Mesh3P_Low_Internal == B.Mesh3P_Low_Internal &&
			   MeshVR == B.MeshVR && MeshVR_LoadFlags == B.MeshVR_LoadFlags && MeshVR_Internal == B.MeshVR_Internal;
	}

	bool operator!=(const FCsFpsStaticMesh& B) const
	{
		return !(*this == B);
	}

	UStaticMesh* Get(const TCsViewType &ViewType, const bool &IsLow = false) const
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Mesh1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Mesh3P_Low_Internal : Mesh3P_Internal;
		if (ViewType == ECsViewType::VR)
			return MeshVR_Internal;
		return Mesh3P_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsTArrayStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UStaticMesh>> Meshes;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Meshes_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UStaticMesh*> Meshes_Internal;

public:
	FCsTArrayStaticMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Meshes_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArrayStaticMesh& operator=(const FCsTArrayStaticMesh& B)
	{
		Meshes.Reset();

		const int32 Count = B.Meshes.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Meshes.Add(B.Meshes[I]);
		}
		Meshes_LoadFlags = B.Meshes_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArrayStaticMesh& B) const
	{
		int32 Count  = Meshes.Num();
		int32 CountB = B.Meshes.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Meshes[I] != B.Meshes[I])
				return false;
		}

		Count  = Meshes_Internal.Num();
		CountB = B.Meshes_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Meshes_Internal[I] != B.Meshes_Internal[I])
				return false;
		}
		return Meshes_LoadFlags == B.Meshes_LoadFlags;
	}

	bool operator!=(const FCsTArrayStaticMesh& B) const
	{
		return !(*this == B);
	}

	TArray<class UStaticMesh*>* Get()
	{
		return &Meshes_Internal;
	}

	class UStaticMesh* Get(const int32 Index)
	{
		return Index < Meshes_Internal.Num() ? Meshes_Internal[Index] : NULL;
	}
};

#pragma endregion Static Mesh

// Skeletal Mesh
#pragma region

USTRUCT(BlueprintType)
struct FCsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

private:
	UPROPERTY(Transient)
	class USkeletalMesh* Mesh_Internal;

public:
	FCsSkeletalMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh_LoadFlags, ECsLoadFlags::Game);
	}

	FCsSkeletalMesh& operator=(const FCsSkeletalMesh& B)
	{
		Mesh = B.Mesh;
		Mesh_LoadFlags = B.Mesh_LoadFlags;
		Mesh_Internal = B.Mesh_Internal;
		return *this;
	}

	bool operator==(const FCsSkeletalMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	bool operator!=(const FCsSkeletalMesh& B) const
	{
		return !(*this == B);
	}

	USkeletalMesh* Get() const
	{
		return Mesh_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsFpsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<USkeletalMesh> Mesh1P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<USkeletalMesh> Mesh3P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<USkeletalMesh> Mesh3P_Low;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TAssetPtr<USkeletalMesh> MeshVR;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 MeshVR_LoadFlags;

private:
	UPROPERTY(Transient)
	class USkeletalMesh* Mesh1P_Internal;

	UPROPERTY(Transient)
	class USkeletalMesh* Mesh3P_Internal;

	UPROPERTY(Transient)
	class USkeletalMesh* Mesh3P_Low_Internal;

	UPROPERTY(Transient)
	class USkeletalMesh* MeshVR_Internal;
public:
	FCsFpsSkeletalMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Mesh3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(MeshVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(MeshVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	FCsFpsSkeletalMesh& operator=(const FCsFpsSkeletalMesh& B)
	{
		Mesh1P			 = B.Mesh1P;
		Mesh1P_LoadFlags = B.Mesh1P_LoadFlags;
		Mesh1P_Internal  = B.Mesh1P_Internal;

		Mesh3P			 = B.Mesh3P;
		Mesh3P_LoadFlags = B.Mesh3P_LoadFlags;
		Mesh3P_Internal  = B.Mesh3P_Internal;

		Mesh3P_Low			 = B.Mesh3P_Low;
		Mesh3P_Low_LoadFlags = B.Mesh3P_Low_LoadFlags;
		Mesh3P_Low_Internal  = B.Mesh3P_Low_Internal;

		MeshVR			 = B.MeshVR;
		MeshVR_LoadFlags = B.MeshVR_LoadFlags;
		MeshVR_Internal  = B.MeshVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsSkeletalMesh& B) const
	{
		return Mesh1P == B.Mesh1P && Mesh1P_LoadFlags == B.Mesh1P_LoadFlags && Mesh1P_Internal == B.Mesh1P_Internal &&
			   Mesh3P == B.Mesh3P && Mesh3P_LoadFlags == B.Mesh3P_LoadFlags && Mesh3P_Internal == B.Mesh3P_Internal &&
			   Mesh3P_Low == B.Mesh3P_Low && Mesh3P_Low_LoadFlags == B.Mesh3P_Low_LoadFlags && Mesh3P_Low_Internal == B.Mesh3P_Low_Internal &&
			   MeshVR == B.MeshVR && MeshVR_LoadFlags == B.MeshVR_LoadFlags && MeshVR_Internal == B.MeshVR_Internal;
	}

	bool operator!=(const FCsFpsSkeletalMesh& B) const
	{
		return !(*this == B);
	}

	USkeletalMesh* Get(const TCsViewType &ViewType, const bool &IsLow = false) const
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Mesh1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Mesh3P_Low_Internal : Mesh3P_Internal;
		if (ViewType == ECsViewType::VR)
			return MeshVR_Internal;
		return Mesh3P_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsTArraySkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class USkeletalMesh>> Meshes;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Meshes_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class USkeletalMesh*> Meshes_Internal;

public:
	FCsTArraySkeletalMesh()
	{
		CS_SET_BLUEPRINT_BITFLAG(Meshes_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArraySkeletalMesh& operator=(const FCsTArraySkeletalMesh& B)
	{
		Meshes.Reset();

		const int32 Count = B.Meshes.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Meshes.Add(B.Meshes[I]);
		}
		Meshes_LoadFlags = B.Meshes_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArraySkeletalMesh& B) const
	{
		int32 Count = Meshes.Num();
		int32 CountB = B.Meshes.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Meshes[I] != B.Meshes[I])
				return false;
		}

		Count = Meshes_Internal.Num();
		CountB = B.Meshes_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Meshes_Internal[I] != B.Meshes_Internal[I])
				return false;
		}
		return Meshes_LoadFlags == B.Meshes_LoadFlags;
	}

	bool operator!=(const FCsTArraySkeletalMesh& B) const
	{
		return !(*this == B);
	}

	TArray<class USkeletalMesh*>* Get()
	{
		return &Meshes_Internal;
	}

	class USkeletalMesh* Get(const int32 Index)
	{
		return Index < Meshes_Internal.Num() ? Meshes_Internal[Index] : NULL;
	}
};

#pragma endregion Skeletal Mesh

// Surface
#pragma region

#define CS_SURFACE_Default SurfaceType_Default

namespace ECsSurfaceType
{
	enum Type : uint8;
}

typedef ECsSurfaceType::Type TCsSurfaceType;

#pragma endregion Surface

// Materials
#pragma region

USTRUCT(BlueprintType)
struct FCsMaterialInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TAssetPtr<class UMaterialInstance> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstance* Material_Internal;

public:
	FCsMaterialInstance()
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	UMaterialInstance* Get() const
	{
		return Material_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TAssetPtr<class UMaterialInstanceConstant> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstanceConstant* Material_Internal;

public:
	FCsMaterialInstanceConstant()
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	UMaterialInstanceConstant* Get() const
	{
		return Material_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UMaterialInstanceConstant>> Materials;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> Materials_Internal;

public:
	FCsTArrayMaterialInstanceConstant()
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArrayMaterialInstanceConstant& operator=(const FCsTArrayMaterialInstanceConstant& B)
	{
		Materials.Reset();

		const int32 Count = B.Materials.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Materials.Add(B.Materials[I]);
		}
		Materials_LoadFlags = B.Materials_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArrayMaterialInstanceConstant& B) const
	{
		int32 Count  = Materials.Num();
		int32 CountB = B.Materials.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials[I] != B.Materials[I])
				return false;
		}

		Count  = Materials_Internal.Num();
		CountB = B.Materials_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials_Internal[I] != B.Materials_Internal[I])
				return false;
		}
		return Materials_LoadFlags == B.Materials_LoadFlags;
	}

	bool operator!=(const FCsTArrayMaterialInstanceConstant& B) const
	{
		return !(*this == B);
	}

	TArray<UMaterialInstanceConstant*>* Get()
	{
		return &Materials_Internal;
	}

	class UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < Materials_Internal.Num() ? Materials_Internal[Index] : NULL;
	}
};

USTRUCT(BlueprintType)
struct FCsFpsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UMaterialInstanceConstant>> Materials1P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UMaterialInstanceConstant>> Materials3P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UMaterialInstanceConstant>> Materials3P_Low;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UMaterialInstanceConstant>> MaterialsVR;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 MaterialsVR_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> Materials1P_Internal;

	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> Materials3P_Internal;

	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> Materials3P_Low_Internal;

	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> MaterialsVR_Internal;

public:
	FCsFpsTArrayMaterialInstanceConstant()
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Materials3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Materials3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(MaterialsVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(MaterialsVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	FCsFpsTArrayMaterialInstanceConstant& operator=(const FCsFpsTArrayMaterialInstanceConstant& B)
	{
		// 1P
		Materials1P.Reset();

		int32 Count = B.Materials1P.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Materials1P.Add(B.Materials1P[I]);
		}
		Materials1P_LoadFlags = B.Materials1P_LoadFlags;
		// 3P
		Materials3P.Reset();

		Count = B.Materials3P.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Materials3P.Add(B.Materials3P[I]);
		}
		Materials3P_LoadFlags = B.Materials3P_LoadFlags;
		// 3P Low
		Materials3P_Low.Reset();

		Count = B.Materials3P_Low.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Materials3P_Low.Add(B.Materials3P_Low[I]);
		}
		Materials3P_Low_LoadFlags = B.Materials3P_Low_LoadFlags;
		// VR
		MaterialsVR.Reset();

		Count = B.MaterialsVR.Num();

		for (int32 I = 0; I < Count; I++)
		{
			MaterialsVR.Add(B.MaterialsVR[I]);
		}
		MaterialsVR_LoadFlags = B.MaterialsVR_LoadFlags;
		return *this;
	}

	bool operator==(const FCsFpsTArrayMaterialInstanceConstant& B) const
	{
		// 1P
		int32 Count  = Materials1P.Num();
		int32 CountB = B.Materials1P.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials1P[I] != B.Materials1P[I])
				return false;
		}

		Count  = Materials1P_Internal.Num();
		CountB = B.Materials1P_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials1P_Internal[I] != B.Materials1P_Internal[I])
				return false;
		}

		if (Materials1P_LoadFlags != B.Materials1P_LoadFlags)
			return false;
		// 3P
		Count  = Materials3P.Num();
		CountB = B.Materials3P.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials3P[I] != B.Materials3P[I])
				return false;
		}

		Count  = Materials3P_Internal.Num();
		CountB = B.Materials3P_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials3P_Internal[I] != B.Materials3P_Internal[I])
				return false;
		}

		if (Materials3P_LoadFlags != B.Materials3P_LoadFlags)
			return false;
		// 3P Low
		Count  = Materials3P_Low.Num();
		CountB = B.Materials3P_Low.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials3P_Low[I] != B.Materials3P_Low[I])
				return false;
		}

		Count  = Materials3P_Low_Internal.Num();
		CountB = B.Materials3P_Low_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Materials3P_Low_Internal[I] != B.Materials3P_Low_Internal[I])
				return false;
		}

		if (Materials3P_Low_LoadFlags != B.Materials3P_Low_LoadFlags)
			return false;
		// VR
		Count  = MaterialsVR.Num();
		CountB = B.MaterialsVR.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (MaterialsVR[I] != B.MaterialsVR[I])
				return false;
		}

		Count  = MaterialsVR_Internal.Num();
		CountB = B.MaterialsVR_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (MaterialsVR_Internal[I] != B.MaterialsVR_Internal[I])
				return false;
		}

		if (MaterialsVR_LoadFlags != B.MaterialsVR_LoadFlags)
			return false;
		return true;
	}

	bool operator!=(const FCsFpsTArrayMaterialInstanceConstant& B) const
	{
		return !(*this == B);
	}

	TArray<UMaterialInstanceConstant*>* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return &Materials1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? &Materials3P_Low_Internal : &Materials3P_Internal;
		if (ViewType == ECsViewType::VR)
			return &MaterialsVR_Internal;
		return &Materials3P_Internal;
	}

	class UMaterialInstanceConstant* Get(const TCsViewType &ViewType, const int32 &Index, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Index < Materials1P_Internal.Num() ? Materials1P_Internal[Index] : NULL;
		if (ViewType == ECsViewType::ThirdPerson)
		{
			if (IsLow)
				return Index < Materials3P_Low_Internal.Num() ? Materials3P_Low_Internal[Index] : NULL;
			else
				return Index < Materials3P_Internal.Num() ? Materials3P_Internal[Index] : NULL;
		}
		if (ViewType == ECsViewType::VR)
			return Index < MaterialsVR_Internal.Num() ? MaterialsVR_Internal[Index] : NULL;
		return NULL;
	}
};

USTRUCT(BlueprintType)
struct FCsPhysicalMaterial
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TAssetPtr<class UPhysicalMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UPhysicalMaterial* Material_Internal;

public:
	FCsPhysicalMaterial()
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	bool operator==(const FCsPhysicalMaterial& B) const
	{
		return Material == B.Material && B.Material_LoadFlags == B.Material_LoadFlags && Material_Internal == B.Material_Internal;
	}

	bool operator!=(const FCsPhysicalMaterial& B) const
	{
		return !(*this == B);
	}

	UPhysicalMaterial* Get() const
	{
		return Material_Internal;
	}
};

#pragma endregion Materials

// Physics Asset
#pragma region

USTRUCT()
struct FCsPhysicsAsset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Physics")
	TAssetPtr<UPhysicsAsset> Physics;

	UPROPERTY(EditAnywhere, Category = "Physics", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Physics_LoadFlags;

private:
	UPROPERTY(Transient)
	class UPhysicsAsset* Physics_Internal;

public:
	FCsPhysicsAsset()
	{
		CS_SET_BLUEPRINT_BITFLAG(Physics_LoadFlags, ECsLoadFlags::Game);
	}

	FCsPhysicsAsset& operator=(const FCsPhysicsAsset& B)
	{
		Physics = B.Physics;
		Physics_LoadFlags = B.Physics_LoadFlags;
		Physics_Internal = B.Physics_Internal;
		return *this;
	}

	bool operator==(const FCsPhysicsAsset& B) const
	{
		return Physics == B.Physics && Physics_LoadFlags == B.Physics_LoadFlags && Physics_Internal == B.Physics_Internal;
	}

	bool operator!=(const FCsPhysicsAsset& B) const
	{
		return !(*this == B);
	}

	UPhysicsAsset* Get() const
	{
		return Physics_Internal;
	}
};

#pragma endregion Physics Asset

// Physics
#pragma region

#define CS_MIN_PHYSICS_LINEAR_VELOCITY_FOR_MOVEMENT 0.1f
#define CS_MIN_PHYSICS_ANGULAR_VELOCITY_FOR_MOVEMENT 0.1f

namespace NCsAttachmentTransformRules
{
	const FAttachmentTransformRules InteractivePawnKeepRelativeTransform(EAttachmentRule::KeepRelative, true);
}

USTRUCT(BlueprintType)
struct FCsPhysicsPreset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bSimulatePhysics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool OverrideMassInKg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MassInKg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float LinearDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AngularDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bEnableGravity;

	FCsPhysicsPreset()
	{
		bSimulatePhysics = false;
		OverrideMassInKg = false;
		MassInKg = 0.01f;
		LinearDamping = 0.01f;
		AngularDamping = 0.0f;
		bEnableGravity = true;
	}

	FCsPhysicsPreset& operator=(const FCsPhysicsPreset& B)
	{
		bSimulatePhysics = B.bSimulatePhysics;
		OverrideMassInKg = B.OverrideMassInKg;
		MassInKg = B.MassInKg;
		LinearDamping = B.LinearDamping;
		AngularDamping = B.AngularDamping;
		bEnableGravity = B.bEnableGravity;
		return *this;
	}

	bool operator==(const FCsPhysicsPreset& B) const
	{
		return bSimulatePhysics == B.bSimulatePhysics &&
			   OverrideMassInKg == B.OverrideMassInKg &&
			   MassInKg == B.MassInKg &&
			   LinearDamping == B.LinearDamping &&
			   AngularDamping == B.AngularDamping &&
			   bEnableGravity == B.bEnableGravity;
	}

	bool operator!=(const FCsPhysicsPreset& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Physics

// Anim
#pragma region

UENUM(BlueprintType)
namespace ECsFpsAnimMember
{
	enum Type
	{
		Anim1P					UMETA(DisplayName = "Anim1P"),
		Anim3P					UMETA(DisplayName = "Anim3P"),
		Anim3P_Low				UMETA(DisplayName = "Anim3P_Low"),
		AnimVR					UMETA(DisplayName = "AnimVR"),
		ECsFpsAnimMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimMember
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Anim1P = TCsString(TEXT("Anim1P"), TEXT("anim1p"), TEXT("anim 1p"));
		const TCsString Anim3P = TCsString(TEXT("Anim3P"), TEXT("anim3p"), TEXT("anim 3p"));
		const TCsString Anim3P_Low = TCsString(TEXT("Anim3P_Low"), TEXT("anim3p_low"), TEXT("anim 3p low"));
		const TCsString AnimVR = TCsString(TEXT("AnimVR"), TEXT("animvr"), TEXT("anim vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Anim1P) { return Str::Anim1P.Value; }
		if (EType == Type::Anim3P) { return Str::Anim3P.Value; }
		if (EType == Type::Anim3P_Low) { return Str::Anim3P_Low.Value; }
		if (EType == Type::AnimVR) { return Str::AnimVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Anim1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Anim3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Anim3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::AnimVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}
	
	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Anim1P) { return Type::Anim1P; }
		if (String == Str::Anim3P) { return Type::Anim3P; }
		if (String == Str::Anim3P_Low) { return Type::Anim3P_Low; }
		if (String == Str::AnimVR) { return Type::AnimVR; }
		return Type::ECsFpsAnimMember_MAX;
	}
}

#define ECS_FPS_ANIM_MEMBER_MAX (uint8)ECsFpsAnimMember::ECsFpsAnimMember_MAX
typedef TEnumAsByte<ECsFpsAnimMember::Type> TCsFpsAnimMember;

USTRUCT(BlueprintType)
struct FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimSequence* Anim_Internal;

public:

	FCsAnimSequence()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimSequence* Get()
	{
		return Anim_Internal;
	}

	FCsAnimSequence& operator=(const FCsAnimSequence& B)
	{
		Anim		  = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal = B.Anim_Internal;
		return *this;
	}

	bool operator==(const FCsAnimSequence& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	bool operator!=(const FCsAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimSequence> AnimVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimSequence* Anim1P_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* Anim3P_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimSequence* AnimVR_Internal;

public:

	FCsFpsAnimSequence()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UAnimSequence* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FCsFpsAnimSequence& operator=(const FCsFpsAnimSequence& B)
	{
		Anim1P = B.Anim1P;
		Anim3P = B.Anim3P;
		Anim3P_Low = B.Anim3P_Low;
		AnimVR = B.AnimVR;

		Anim1P_LoadFlags = B.Anim1P_LoadFlags;
		Anim3P_LoadFlags = B.Anim3P_LoadFlags;
		Anim3P_Low_LoadFlags = B.Anim3P_Low_LoadFlags;
		AnimVR_LoadFlags = B.AnimVR_LoadFlags;

		Anim1P_Internal = B.Anim1P_Internal;
		Anim3P_Internal = B.Anim3P_Internal;
		Anim3P_Low_Internal = B.Anim3P_Low_Internal;
		AnimVR_Internal = B.AnimVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimSequence& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			   Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			   Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	bool operator!=(const FCsFpsAnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimMontage* Anim_Internal;

public:

	FCsAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimMontage* Get()
	{
		return Anim_Internal;
	}

	FCsAnimMontage& operator=(const FCsAnimMontage& B)
	{
		Anim		   = B.Anim;
		Anim_LoadFlags = B.Anim_LoadFlags;
		Anim_Internal  = B.Anim_Internal;
		return *this;
	}

	bool operator==(const FCsAnimMontage& B) const
	{
		return Anim == B.Anim && Anim_LoadFlags == B.Anim_LoadFlags && Anim_Internal == B.Anim_Internal;
	}

	bool operator!=(const FCsAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UAnimMontage> AnimVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimMontage* Anim1P_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* Anim3P_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimMontage* AnimVR_Internal;

public:

	FCsFpsAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Anim3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(AnimVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UAnimMontage* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	FCsFpsAnimMontage& operator=(const FCsFpsAnimMontage& B)
	{
		Anim1P = B.Anim1P;
		Anim3P = B.Anim3P;
		Anim3P_Low = B.Anim3P_Low;
		AnimVR = B.AnimVR;

		Anim1P_LoadFlags = B.Anim1P_LoadFlags;
		Anim3P_LoadFlags = B.Anim3P_LoadFlags;
		Anim3P_Low_LoadFlags = B.Anim3P_Low_LoadFlags;
		AnimVR_LoadFlags = B.AnimVR_LoadFlags;

		Anim1P_Internal = B.Anim1P_Internal;
		Anim3P_Internal = B.Anim3P_Internal;
		Anim3P_Low_Internal = B.Anim3P_Low_Internal;
		AnimVR_Internal = B.AnimVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimMontage& B) const
	{
		return Anim1P == B.Anim1P && Anim3P == B.Anim3P && Anim3P_Low == B.Anim3P_Low && AnimVR == B.AnimVR &&
			   Anim1P_LoadFlags == B.Anim1P_LoadFlags && Anim3P_LoadFlags == B.Anim3P_LoadFlags && Anim3P_Low_LoadFlags == B.Anim3P_Low_LoadFlags && AnimVR_LoadFlags == B.AnimVR_LoadFlags &&
			   Anim1P_Internal == B.Anim1P_Internal && Anim3P_Internal == B.Anim3P_Internal && Anim3P_Low_Internal == B.Anim3P_Low_Internal && AnimVR_Internal == B.AnimVR_Internal;
	}

	bool operator!=(const FCsFpsAnimMontage& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsTArrayAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TAssetPtr<class UAnimMontage>> Anims;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Anims_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UAnimMontage*> Anims_Internal;

public:
	FCsTArrayAnimMontage()
	{
		CS_SET_BLUEPRINT_BITFLAG(Anims_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArrayAnimMontage& operator=(const FCsTArrayAnimMontage& B)
	{
		Anims.Reset();

		const int32 Count = B.Anims.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Anims.Add(B.Anims[I]);
		}
		Anims_LoadFlags = B.Anims_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArrayAnimMontage& B) const
	{
		int32 Count = Anims.Num();
		int32 CountB = B.Anims.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Anims[I] != B.Anims[I])
				return false;
		}

		Count = Anims_Internal.Num();
		CountB = B.Anims_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Anims_Internal[I] != B.Anims_Internal[I])
				return false;
		}
		return Anims_LoadFlags == B.Anims_LoadFlags;
	}

	bool operator!=(const FCsTArrayAnimMontage& B) const
	{
		return !(*this == B);
	}

	TArray<class UAnimMontage*>* Get()
	{
		return &Anims_Internal;
	}

	class UAnimMontage* Get(const int32 Index)
	{
		return Index < Anims_Internal.Num() ? Anims_Internal[Index] : NULL;
	}

	uint8 Find(UAnimMontage* Anim)
	{
		int index;
		if (Anims_Internal.Find(Anim, index))
			return (uint8)index;
		else
			return INDEX_NONE;
	}
};

UENUM(BlueprintType)
namespace ECsFpsAnimBlueprintMember
{
	enum Type
	{
		Blueprint1P						UMETA(DisplayName = "Blueprint1P"),
		Blueprint3P						UMETA(DisplayName = "Blueprint3P"),
		Blueprint3P_Low					UMETA(DisplayName = "Blueprint3P_Low"),
		BlueprintVR						UMETA(DisplayName = "BlueprintVR"),
		ECsFpsAnimBlueprintMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimBlueprintMember
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Blueprint1P = TCsString(TEXT("Blueprint1P"), TEXT("blueprint1p"), TEXT("blueprint 1p"));
		const TCsString Blueprint3P = TCsString(TEXT("Blueprint3P"), TEXT("blueprint3p"), TEXT("blueprint 3p"));
		const TCsString Blueprint3P_Low = TCsString(TEXT("Blueprint3P_Low"), TEXT("blueprint3p_low"), TEXT("blueprint 3p low"));
		const TCsString BlueprintVR = TCsString(TEXT("BlueprintVR"), TEXT("blueprintvr"), TEXT("blueprint vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Blueprint1P) { return Str::Blueprint1P.Value; }
		if (EType == Type::Blueprint3P) { return Str::Blueprint3P.Value; }
		if (EType == Type::Blueprint3P_Low) { return Str::Blueprint3P_Low.Value; }
		if (EType == Type::BlueprintVR) { return Str::BlueprintVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Blueprint1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Blueprint3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Blueprint3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::BlueprintVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Blueprint1P) { return Type::Blueprint1P; }
		if (String == Str::Blueprint3P) { return Type::Blueprint3P; }
		if (String == Str::Blueprint3P_Low) { return Type::Blueprint3P_Low; }
		if (String == Str::BlueprintVR) { return Type::BlueprintVR; }
		return Type::ECsFpsAnimBlueprintMember_MAX;
	}
}

#define ECS_FPS_ANIM_BLUEPRINT_MEMBER_MAX (uint8)ECsFpsAnimBlueprintMember::ECsFpsAnimBlueprintMember_MAX
typedef TEnumAsByte<ECsFpsAnimBlueprintMember::Type> TCsFpsAnimBlueprintMember;

USTRUCT(BlueprintType)
struct FCsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<class UAnimBlueprint> Blueprint;


	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

private:

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint_Internal;

public:

	FCsAnimBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
	}

	UAnimBlueprintGeneratedClass* Get()
	{
		return Blueprint_Internal;
	}

	FCsAnimBlueprint& operator=(const FCsAnimBlueprint& B)
	{
		Blueprint		   = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		return *this;
	}

	bool operator==(const FCsAnimBlueprint& B) const
	{
		return Blueprint == B.Blueprint && Blueprint_LoadFlags == B.Blueprint_LoadFlags && Blueprint_Internal == B.Blueprint_Internal;
	}

	bool operator!=(const FCsAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> Blueprint3P_Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
	TAssetPtr<class UAnimBlueprint> BlueprintVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlueprintVR_LoadFlags;

public:

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint1P_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint3P_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* Blueprint3P_Low_Internal;

	UPROPERTY(Transient)
	class UAnimBlueprintGeneratedClass* BlueprintVR_Internal;

public:

	FCsFpsAnimBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(BlueprintVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(BlueprintVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UAnimBlueprintGeneratedClass* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blueprint1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blueprint3P_Low_Internal : Blueprint3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlueprintVR_Internal;
		return Blueprint3P_Internal;
	}

	FCsFpsAnimBlueprint& operator=(const FCsFpsAnimBlueprint& B)
	{
		Blueprint1P = B.Blueprint1P;
		Blueprint3P = B.Blueprint3P;
		Blueprint3P_Low = B.Blueprint3P_Low;
		BlueprintVR = B.BlueprintVR;

		Blueprint1P_LoadFlags = B.Blueprint1P_LoadFlags;
		Blueprint3P_LoadFlags = B.Blueprint3P_LoadFlags;
		Blueprint3P_Low_LoadFlags = B.Blueprint3P_Low_LoadFlags;
		BlueprintVR_LoadFlags = B.BlueprintVR_LoadFlags;

		Blueprint1P_Internal = B.Blueprint1P_Internal;
		Blueprint3P_Internal = B.Blueprint3P_Internal;
		Blueprint3P_Low_Internal = B.Blueprint3P_Low_Internal;
		BlueprintVR_Internal = B.BlueprintVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsAnimBlueprint& B) const
	{
		return Blueprint1P == B.Blueprint1P && Blueprint3P == B.Blueprint3P && Blueprint3P_Low == B.Blueprint3P_Low && BlueprintVR == B.BlueprintVR &&
			   Blueprint1P_LoadFlags == B.Blueprint1P_LoadFlags && Blueprint3P_LoadFlags == B.Blueprint3P_LoadFlags && Blueprint3P_Low_LoadFlags == B.Blueprint3P_Low_LoadFlags && BlueprintVR_LoadFlags == B.BlueprintVR_LoadFlags &&
			   Blueprint1P_Internal == B.Blueprint1P_Internal && Blueprint3P_Internal == B.Blueprint3P_Internal && Blueprint3P_Low_Internal == B.Blueprint3P_Low_Internal && BlueprintVR_Internal == B.BlueprintVR_Internal;
	}

	bool operator!=(const FCsFpsAnimBlueprint& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsFpsAnimBlendSpaceMember
{
	enum Type
	{
		Blend1P							UMETA(DisplayName = "Blend1P"),
		Blend3P							UMETA(DisplayName = "Blend3P"),
		Blend3P_Low						UMETA(DisplayName = "Blend3P_Low"),
		BlendVR							UMETA(DisplayName = "BlendVR"),
		ECsFpsAnimBlendSpaceMember_MAX	UMETA(Hidden),
	};
}

namespace ECsFpsAnimBlendSpaceMember
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Blend1P = TCsString(TEXT("Blend1P"), TEXT("blend1p"), TEXT("blend 1p"));
		const TCsString Blend3P = TCsString(TEXT("Blend3P"), TEXT("blend3p"), TEXT("blend 3p"));
		const TCsString Blend3P_Low = TCsString(TEXT("Blend3P_Low"), TEXT("blend3p_low"), TEXT("blend 3p low"));
		const TCsString BlendVR = TCsString(TEXT("BlendVR"), TEXT("blendvr"), TEXT("blend vr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Blend1P) { return Str::Blend1P.Value; }
		if (EType == Type::Blend3P) { return Str::Blend3P.Value; }
		if (EType == Type::Blend3P_Low) { return Str::Blend3P_Low.Value; }
		if (EType == Type::BlendVR) { return Str::BlendVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToStringFromViewType(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return Str::Blend1P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return Str::Blend3P.Value; }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return Str::Blend3P_Low.Value; }
		if (ViewType == ECsViewType::VR) { return Str::BlendVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Blend1P) { return Type::Blend1P; }
		if (String == Str::Blend3P) { return Type::Blend3P; }
		if (String == Str::Blend3P_Low) { return Type::Blend3P_Low; }
		if (String == Str::BlendVR) { return Type::BlendVR; }
		return Type::ECsFpsAnimBlendSpaceMember_MAX;
	}
}

#define ECS_FPS_ANIM_BLEND_SPACE_MEMBER_MAX (uint8)ECsFpsAnimBlendSpaceMember::ECsFpsAnimBlendSpaceMember_MAX
typedef TEnumAsByte<ECsFpsAnimBlendSpaceMember::Type> TCsFpsAnimBlendSpaceMember;

USTRUCT(BlueprintType)
struct FCsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend_LoadFlags;

public:

	UPROPERTY(Transient)
	class UBlendSpace* Blend_Internal;

public:

	FCsBlendSpace()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend_LoadFlags, ECsLoadFlags::Game);
	}

	UBlendSpace* Get()
	{
		return Blend_Internal;
	}

	FCsBlendSpace& operator=(const FCsBlendSpace& B)
	{
		Blend		   = B.Blend;
		Blend_LoadFlags = B.Blend_LoadFlags;
		Blend_Internal = B.Blend_Internal;
		return *this;
	}

	bool operator==(const FCsBlendSpace& B) const
	{
		return Blend == B.Blend && Blend_LoadFlags == B.Blend_LoadFlags && Blend_Internal == B.Blend_Internal;
	}

	bool operator!=(const FCsBlendSpace& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsFpsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	TAssetPtr<UBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

public:

	UPROPERTY(Transient)
	class UBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	class UBlendSpace* BlendVR_Internal;

public:

	FCsFpsBlendSpace()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blend1P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend1P_LoadFlags, ECsLoadFlags::Game1P);

		CS_SET_BLUEPRINT_BITFLAG(Blend3P_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend3P_LoadFlags, ECsLoadFlags::Game3P);

		CS_SET_BLUEPRINT_BITFLAG(Blend3P_Low_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blend3P_Low_LoadFlags, ECsLoadFlags::Game3PLow);

		CS_SET_BLUEPRINT_BITFLAG(BlendVR_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(BlendVR_LoadFlags, ECsLoadFlags::GameVR);
	}

	UBlendSpace* Get(const TCsViewType &ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FCsFpsBlendSpace& operator=(const FCsFpsBlendSpace& B)
	{
		Blend1P = B.Blend1P;
		Blend3P = B.Blend3P;
		Blend3P_Low = B.Blend3P_Low;
		BlendVR = B.BlendVR;

		Blend1P_LoadFlags = B.Blend1P_LoadFlags;
		Blend3P_LoadFlags = B.Blend3P_LoadFlags;
		Blend3P_Low_LoadFlags = B.Blend3P_Low_LoadFlags;
		BlendVR_LoadFlags = B.BlendVR_LoadFlags;

		Blend1P_Internal = B.Blend1P_Internal;
		Blend3P_Internal = B.Blend3P_Internal;
		Blend3P_Low_Internal = B.Blend3P_Low_Internal;
		BlendVR_Internal = B.BlendVR_Internal;
		return *this;
	}

	bool operator==(const FCsFpsBlendSpace& B) const
	{
		return Blend1P == B.Blend1P && Blend3P == B.Blend3P && Blend3P_Low == B.Blend3P_Low && BlendVR == B.BlendVR &&
			   Blend1P_LoadFlags == B.Blend1P_LoadFlags && Blend3P_LoadFlags == B.Blend3P_LoadFlags && Blend3P_Low_LoadFlags == B.Blend3P_Low_LoadFlags && BlendVR_LoadFlags == B.BlendVR_LoadFlags &&
			   Blend1P_Internal == B.Blend1P_Internal && Blend3P_Internal == B.Blend3P_Internal && Blend3P_Low_Internal == B.Blend3P_Low_Internal && BlendVR_Internal == B.BlendVR_Internal;
	}

	bool operator!=(const FCsFpsBlendSpace& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsAdditiveBasePoseType
{
	enum Type
	{
		/** Will be deprecated. */
		ABPT_None		UMETA(DisplayName = "None"),
		/** Use the Skeleton's ref pose as base. */
		ABPT_RefPose	UMETA(DisplayName = "Skeleton Reference Pose"),
		/** Use a whole animation as a base pose. BasePoseSeq must be set. */
		ABPT_AnimScaled	UMETA(DisplayName = "Selected animation scaled"),
		/** Use one frame of an animation as a base pose. BasePoseSeq and RefFrameIndex must be set (RefFrameIndex will be clamped). */
		ABPT_AnimFrame	UMETA(DisplayName = "Selected animation frame"),
		ABPT_MAX		UMETA(Hidden),
	};
}

namespace ECsAdditiveBasePoseType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString ABPT_None = TCsString(TEXT("ABPT_None"), TEXT("abpt_none"), TEXT("none"));
		const TCsString ABPT_RefPose = TCsString(TEXT("ABPT_RefPose"), TEXT("abpt_refpose"), TEXT("ref pose"));
		const TCsString ABPT_AnimScaled = TCsString(TEXT("ABPT_AnimScaled"), TEXT("abpt_animscaled"), TEXT("anim scaled"));
		const TCsString ABPT_AnimFrame = TCsString(TEXT("ABPT_AnimFrame"), TEXT("abpt_animframe"), TEXT("anim frame"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::ABPT_None) { return Str::ABPT_None.Value; }
		if (EType == Type::ABPT_RefPose) { return Str::ABPT_RefPose.Value; }
		if (EType == Type::ABPT_AnimScaled) { return Str::ABPT_AnimScaled.Value; }
		if (EType == Type::ABPT_AnimFrame) { return Str::ABPT_AnimFrame.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const EAdditiveBasePoseType &EType)
	{
		if (EType == EAdditiveBasePoseType::ABPT_None) { return Str::ABPT_None.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_RefPose) { return Str::ABPT_RefPose.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_AnimScaled) { return Str::ABPT_AnimScaled.Value; }
		if (EType == EAdditiveBasePoseType::ABPT_AnimFrame) { return Str::ABPT_AnimFrame.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::ABPT_None) { return Type::ABPT_None; }
		if (String == Str::ABPT_RefPose) { return Type::ABPT_RefPose; }
		if (String == Str::ABPT_AnimScaled) { return Type::ABPT_AnimScaled; }
		if (String == Str::ABPT_AnimFrame) { return Type::ABPT_AnimFrame; }
		return Type::ABPT_MAX;
	}

	FORCEINLINE EAdditiveBasePoseType ToBaseType(const FString &String)
	{
		if (String == Str::ABPT_None) { return EAdditiveBasePoseType::ABPT_None; }
		if (String == Str::ABPT_RefPose) { return EAdditiveBasePoseType::ABPT_RefPose; }
		if (String == Str::ABPT_AnimScaled) { return EAdditiveBasePoseType::ABPT_AnimScaled; }
		if (String == Str::ABPT_AnimFrame) { return EAdditiveBasePoseType::ABPT_AnimFrame; }
		return EAdditiveBasePoseType::ABPT_MAX;
	}
}

#define ECS_ADDITIVE_BASE_POSE_TYPE_MAX (uint8)ECsAdditiveBasePoseType::ABPT_MAX
typedef TEnumAsByte<ECsAdditiveBasePoseType::Type> TCsAdditiveBasePoseType;

UENUM(BlueprintType)
namespace ECsAdditiveAnimationType
{
	enum Type
	{
		/** No additive. */
		AAT_None					UMETA(DisplayName = "None"),
		/* Create Additive from LocalSpace Base. */
		AAT_LocalSpaceBase			UMETA(DisplayName = "Local Space"),
		/* Create Additive from MeshSpace Rotation Only, Translation still will be LocalSpace. */
		AAT_RotationOffsetMeshSpace	UMETA(DisplayName = "Mesh Space"),
		AAT_MAX						UMETA(Hidden),
	};
}

namespace ECsAdditiveAnimationType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString AAT_None = TCsString(TEXT("AAT_None"), TEXT("aat_none"), TEXT("none"));
		const TCsString AAT_LocalSpaceBase = TCsString(TEXT("AAT_LocalSpaceBase"), TEXT("aat_localspacebase"), TEXT("local space base"));
		const TCsString AAT_RotationOffsetMeshSpace = TCsString(TEXT("AAT_RotationOffsetMeshSpace"), TEXT("aat_rotationoffsetmeshspace"), TEXT("rotation offset mesh space"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::AAT_None) { return Str::AAT_None.Value; }
		if (EType == Type::AAT_LocalSpaceBase) { return Str::AAT_LocalSpaceBase.Value; }
		if (EType == Type::AAT_RotationOffsetMeshSpace) { return Str::AAT_RotationOffsetMeshSpace.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const EAdditiveAnimationType &EType)
	{
		if (EType == EAdditiveAnimationType::AAT_None) { return Str::AAT_None.Value; }
		if (EType == EAdditiveAnimationType::AAT_LocalSpaceBase) { return Str::AAT_LocalSpaceBase.Value; }
		if (EType == EAdditiveAnimationType::AAT_RotationOffsetMeshSpace) { return Str::AAT_RotationOffsetMeshSpace.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::AAT_None) { return Type::AAT_None; }
		if (String == Str::AAT_LocalSpaceBase) { return Type::AAT_LocalSpaceBase; }
		if (String == Str::AAT_RotationOffsetMeshSpace) { return Type::AAT_RotationOffsetMeshSpace; }
		return Type::AAT_MAX;
	}

	FORCEINLINE EAdditiveAnimationType ToBaseType(const FString &String)
	{
		if (String == Str::AAT_None) { return EAdditiveAnimationType::AAT_None; }
		if (String == Str::AAT_LocalSpaceBase) { return EAdditiveAnimationType::AAT_LocalSpaceBase; }
		if (String == Str::AAT_RotationOffsetMeshSpace) { return EAdditiveAnimationType::AAT_RotationOffsetMeshSpace; }
		return EAdditiveAnimationType::AAT_MAX;
	}
}

#define ECS_ADDITIVE_ANIMATION_TYPE_MAX (uint8)ECsAdditiveAnimationType::AAT_MAX
typedef TEnumAsByte<ECsAdditiveAnimationType::Type> TCsAdditiveAnimationType;

#pragma endregion Anim

// Curves
#pragma region

// UCurveFloat
USTRUCT(BlueprintType)
struct FCsCurveFloat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Curves")
	TAssetPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, Category = "Curves", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

private:
	UPROPERTY(Transient)
	class UCurveFloat* Curve_Internal;

public:
	FCsCurveFloat()
	{
		CS_SET_BLUEPRINT_BITFLAG(Curve_LoadFlags, ECsLoadFlags::Game);
	}

	FCsCurveFloat& operator=(const FCsCurveFloat& B)
	{
		Curve = B.Curve;
		Curve_LoadFlags = B.Curve_LoadFlags;
		Curve_Internal = B.Curve_Internal;
		return *this;
	}

	bool operator==(const FCsCurveFloat& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	bool operator!=(const FCsCurveFloat& B) const
	{
		return !(*this == B);
	}

	UCurveFloat* Get() const
	{
		return Curve_Internal;
	}
};

// UCurveVector
USTRUCT()
struct FCsCurveVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Curves")
	TAssetPtr<UCurveVector> Curve;

	UPROPERTY(EditAnywhere, Category = "Curves", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

private:
	UPROPERTY(Transient)
	class UCurveVector* Curve_Internal;

public:
	FCsCurveVector()
	{
		CS_SET_BLUEPRINT_BITFLAG(Curve_LoadFlags, ECsLoadFlags::Game);
	}

	FCsCurveVector& operator=(const FCsCurveVector& B)
	{
		Curve = B.Curve;
		Curve_LoadFlags = B.Curve_LoadFlags;
		Curve_Internal = B.Curve_Internal;
		return *this;
	}

	bool operator==(const FCsCurveVector& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	bool operator!=(const FCsCurveVector& B) const
	{
		return !(*this == B);
	}

	UCurveVector* Get() const
	{
		return Curve_Internal;
	}
};

UENUM(BlueprintType)
namespace ECsRichCurveInterpMode
{
	enum Type
	{
		RCIM_Linear					UMETA(DisplayName = "Linear"),
		RCIM_Constant				UMETA(DisplayName = "Constant"),
		RCIM_Cubic					UMETA(DisplayName = "Cubic"),
		RCIM_None					UMETA(DisplayName = "None"),
		ECsRichCurveInterpMode_MAX	UMETA(Hidden),
	};
}

namespace ECsRichCurveInterpMode
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString RCIM_Linear = TCsString(TEXT("RCIM_Linear"), TEXT("rcim_linear"), TEXT("linear"));
		const TCsString RCIM_Constant = TCsString(TEXT("RCIM_Constant"), TEXT("rcim_constant"), TEXT("constant"));
		const TCsString RCIM_Cubic = TCsString(TEXT("RCIM_Cubic"), TEXT("rcim_cubic"), TEXT("cubic"));
		const TCsString RCIM_None = TCsString(TEXT("RCIM_None"), TEXT("rcim_none"), TEXT("none"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::RCIM_Linear) { return Str::RCIM_Linear.Value; }
		if (EType == Type::RCIM_Constant) { return Str::RCIM_Constant.Value; }
		if (EType == Type::RCIM_Cubic) { return Str::RCIM_Cubic.Value; }
		if (EType == Type::RCIM_None) { return Str::RCIM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const ERichCurveInterpMode &EType)
	{
		if (EType == ERichCurveInterpMode::RCIM_Linear) { return Str::RCIM_Linear.Value; }
		if (EType == ERichCurveInterpMode::RCIM_Constant) { return Str::RCIM_Constant.Value; }
		if (EType == ERichCurveInterpMode::RCIM_Cubic) { return Str::RCIM_Cubic.Value; }
		if (EType == ERichCurveInterpMode::RCIM_None) { return Str::RCIM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::RCIM_Linear) { return Type::RCIM_Linear; }
		if (String == Str::RCIM_Constant) { return Type::RCIM_Constant; }
		if (String == Str::RCIM_Cubic) { return Type::RCIM_Cubic; }
		if (String == Str::RCIM_None) { return Type::RCIM_None; }
		return Type::ECsRichCurveInterpMode_MAX;
	}

	FORCEINLINE ERichCurveInterpMode ToBaseType(const FString &String)
	{
		if (String == Str::RCIM_Linear) { return ERichCurveInterpMode::RCIM_Linear; }
		if (String == Str::RCIM_Constant) { return ERichCurveInterpMode::RCIM_Constant; }
		if (String == Str::RCIM_Cubic) { return ERichCurveInterpMode::RCIM_Cubic; }
		if (String == Str::RCIM_None) { return ERichCurveInterpMode::RCIM_None; }
		return ERichCurveInterpMode::RCIM_None;
	}
}

#define ECS_RICH_CURVE_INTERP_MODE_MAX (uint8)ECsRichCurveInterpMode::ABPT_MAX
typedef TEnumAsByte<ECsRichCurveInterpMode::Type> TCsRichCurveInterpMode;

UENUM(BlueprintType)
namespace ECsRichCurveTangentMode
{
	enum Type
	{
		RCTM_Auto					UMETA(DisplayName = "Auto"),
		RCTM_User					UMETA(DisplayName = "User"),
		RCTM_Break					UMETA(DisplayName = "Break"),
		RCTM_None					UMETA(DisplayName = "None"),
		ECsRichCurveTangentMode_MAX	UMETA(Hidden),
	};
}

namespace ECsRichCurveTangentMode
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString RCTM_Auto = TCsString(TEXT("RCTM_Auto"), TEXT("rctm_auto"), TEXT("auto"));
		const TCsString RCTM_User = TCsString(TEXT("RCTM_User"), TEXT("rctm_user"), TEXT("user"));
		const TCsString RCTM_Break = TCsString(TEXT("RCTM_Break"), TEXT("rctm_break"), TEXT("break"));
		const TCsString RCTM_None = TCsString(TEXT("RCTM_None"), TEXT("rctm_none"), TEXT("none"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::RCTM_Auto) { return Str::RCTM_Auto.Value; }
		if (EType == Type::RCTM_User) { return Str::RCTM_User.Value; }
		if (EType == Type::RCTM_Break) { return Str::RCTM_Break.Value; }
		if (EType == Type::RCTM_None) { return Str::RCTM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const ERichCurveTangentMode &EType)
	{
		if (EType == ERichCurveTangentMode::RCTM_Auto) { return Str::RCTM_Auto.Value; }
		if (EType == ERichCurveTangentMode::RCTM_User) { return Str::RCTM_User.Value; }
		if (EType == ERichCurveTangentMode::RCTM_Break) { return Str::RCTM_Break.Value; }
		if (EType == ERichCurveTangentMode::RCTM_None) { return Str::RCTM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::RCTM_Auto) { return Type::RCTM_Auto; }
		if (String == Str::RCTM_User) { return Type::RCTM_User; }
		if (String == Str::RCTM_Break) { return Type::RCTM_Break; }
		if (String == Str::RCTM_None) { return Type::RCTM_None; }
		return Type::ECsRichCurveTangentMode_MAX;
	}

	FORCEINLINE ERichCurveTangentMode ToBaseType(const FString &String)
	{
		if (String == Str::RCTM_Auto) { return ERichCurveTangentMode::RCTM_Auto; }
		if (String == Str::RCTM_User) { return ERichCurveTangentMode::RCTM_User; }
		if (String == Str::RCTM_Break) { return ERichCurveTangentMode::RCTM_Break; }
		if (String == Str::RCTM_None) { return ERichCurveTangentMode::RCTM_None; }
		return ERichCurveTangentMode::RCTM_None;
	}
}

#define ECS_RICH_CURVE_TANGENT_MODE_MAX (uint8)ECsRichCurveTangentMode::ABPT_MAX
typedef TEnumAsByte<ECsRichCurveTangentMode::Type> TCsRichCurveTangentMode;

#pragma endregion Curves

// Blueprint
#pragma region

USTRUCT(BlueprintType)
struct FCsBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Blueprint")
	TAssetPtr<class UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
	}

	UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

USTRUCT(BlueprintType)
struct FCsTArrayBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Blueprint")
	TArray<TAssetPtr<class UBlueprint>> Blueprints;

	UPROPERTY(EditAnywhere, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprints_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UBlueprintGeneratedClass*> Blueprints_Internal;

public:
	FCsTArrayBlueprint()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprints_LoadFlags, ECsLoadFlags::Game);
	}

	FCsTArrayBlueprint& operator=(const FCsTArrayBlueprint& B)
	{
		Blueprints.Reset();

		const int32 Count = B.Blueprints.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Blueprints.Add(B.Blueprints[I]);
		}
		Blueprints_LoadFlags = B.Blueprints_LoadFlags;
		return *this;
	}

	bool operator==(const FCsTArrayBlueprint& B) const
	{
		int32 Count  = Blueprints.Num();
		int32 CountB = B.Blueprints.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Blueprints[I] != B.Blueprints[I])
				return false;
		}

		Count  = Blueprints_Internal.Num();
		CountB = B.Blueprints_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Blueprints_Internal[I] != B.Blueprints_Internal[I])
				return false;
		}
		return Blueprints_LoadFlags == B.Blueprints_LoadFlags;
	}

	bool operator!=(const FCsTArrayBlueprint& B) const
	{
		return !(*this == B);
	}

	TArray<UBlueprintGeneratedClass*>* Get()
	{
		return &Blueprints_Internal;
	}

	class UBlueprintGeneratedClass* Get(const int32 Index)
	{
		return Index < Blueprints_Internal.Num() ? Blueprints_Internal[Index] : NULL;
	}
};

#pragma endregion Blueprint

// Coroutine
#pragma region

UENUM(BlueprintType)
namespace ECsCoroutineSchedule
{
	enum Type
	{
		Tick						UMETA(DisplayName = "Tick"),
		CalcCamera					UMETA(DisplayName = "CalcCamera"),
		LastTick					UMETA(DisplayName = "LastTick"),
		ECsCoroutineSchedule_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineSchedule
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Tick = TCsString(TEXT("Tick"), TEXT("tick"));
		const TCsString CalcCamera = TCsString(TEXT("CalcCamera"), TEXT("calccamera"));
		const TCsString LastTick = TCsString(TEXT("LastTick"), TEXT("lasttick"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Tick) { return Str::Tick.Value; }
		if (EType == Type::CalcCamera) { return Str::CalcCamera.Value; }
		if (EType == Type::LastTick) { return Str::LastTick.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Tick) { return Type::Tick; }
		if (String == Str::CalcCamera) { return Type::CalcCamera; }
		if (String == Str::LastTick) { return Type::LastTick; }
		return Type::ECsCoroutineSchedule_MAX;
	}
}

#define ECS_COROUTINE_SCHEDULE_MAX (uint8)ECsCoroutineSchedule::ECsCoroutineSchedule_MAX
typedef TEnumAsByte<ECsCoroutineSchedule::Type> TCsCoroutineSchedule;

UENUM(BlueprintType)
namespace ECsCoroutineMessage
{
	enum Type
	{
		Notify					UMETA(DisplayName = "Notify"),
		Listen					UMETA(DisplayName = "Listen"),
		Stop					UMETA(DisplayName = "Stop"),
		ECsCoroutineMessage_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineMessage
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Notify = TCsString(TEXT("Notify"), TEXT("notify"));
		const TCsString Listen = TCsString(TEXT("Listen"), TEXT("listen"));
		const TCsString Stop = TCsString(TEXT("Stop"), TEXT("stop"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Notify) { return Str::Notify.Value; }
		if (EType == Type::Listen) { return Str::Listen.Value; }
		if (EType == Type::Stop) { return Str::Stop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Notify) { return Type::Notify; }
		if (String == Str::Listen) { return Type::Listen; }
		if (String == Str::Stop) { return Type::Stop; }
		return Type::ECsCoroutineMessage_MAX;
	}
}

#define ECS_COROUTINE_MESSAGE_MAX (uint8)ECsCoroutineMessage::ECsCoroutineMessage_MAX
//typedef ECsCoroutineMessage TCsCoroutineMessage;
typedef TEnumAsByte<ECsCoroutineMessage::Type> TCsCoroutineMessage;

#define CS_ROUTINE_POOL_SIZE 256
#define CS_ROUTINE_INDEXER_SIZE 4
#define CS_ROUTINE_COUNTER_SIZE 4
#define CS_ROUTINE_FLAG_SIZE 16
#define CS_ROUTINE_TIMER_SIZE 4
#define CS_ROUTINE_INT_SIZE 4
#define CS_ROUTINE_FLOAT_SIZE 4
#define CS_ROUTINE_VECTOR_SIZE 4
#define CS_ROUTINE_COLOR_SIZE 4
#define CS_ROUTINE_STRING_SIZE 4
#define CS_ROUTINE_OBJECT_SIZE 4
#define CS_ROUTINE_VOID_POINTER_SIZE 4
#define CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE 4
#define CS_ROUTINE_MAX_TYPE 255
#define CS_ROUTINE_END -1
#define CS_ROUTINE_FREE -2

typedef char(*CsCoroutine)(struct FCsRoutine*);
typedef void(*CsCoroutineStopCondition)(struct FCsRoutine*);
typedef void(*CsAddRoutine)(class UObject*, struct FCsRoutine*, const uint8&);
typedef void(*CsRemoveRoutine)(class UObject*, struct FCsRoutine*, const uint8&);

struct FCsRoutine
{
	struct FCsRoutine* self;
	struct pt pt;
	struct FCsRoutine* parent;
	TArray<struct FCsRoutine*> children;
	class UCsCoroutineScheduler* scheduler;
	CsCoroutine coroutine;
	CsCoroutineStopCondition stopCondition;
	int32 poolIndex;
	int32 index;
	FName name;
	uint8 type;
	TWeakObjectPtr<AActor> a;
	TWeakObjectPtr<UObject> o;
	TWeakObjectPtr<UObject> owner;
	struct FCsRoutine** ownerMemberRoutine;
	CsAddRoutine addRoutine;
	CsRemoveRoutine removeRoutine;
	float startTime;
	float deltaSeconds;
	int32 tickCount;
	float delay;

	TArray<FName> stopMessages;
	TArray<FName> stopMessages_recieved;

	int32 indexers[CS_ROUTINE_INDEXER_SIZE];
	int32 counters[CS_ROUTINE_COUNTER_SIZE];
	bool flags[CS_ROUTINE_FLAG_SIZE];
	float timers[CS_ROUTINE_TIMER_SIZE];
	int32 ints[CS_ROUTINE_INT_SIZE];
	float floats[CS_ROUTINE_FLOAT_SIZE];
	FVector vectors[CS_ROUTINE_VECTOR_SIZE];
	FLinearColor colors[CS_ROUTINE_COLOR_SIZE];
	FString strings[CS_ROUTINE_STRING_SIZE];
	TWeakObjectPtr<UObject> objects[CS_ROUTINE_OBJECT_SIZE];
	void* voidPointers[CS_ROUTINE_VOID_POINTER_SIZE];
	void** voidDoublePointers[CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE];

	FCsRoutine()
	{
		self   = nullptr;
		parent = nullptr;

		children.Reset();

		scheduler = nullptr;

		Reset();
	}

	void Init(UCsCoroutineScheduler* inScheduler, const int32 &inPoolIndex)
	{
		self	  = this;
		scheduler = inScheduler;
		poolIndex = inPoolIndex;

		Reset();
	}

	bool IsValid()
	{
		if (!self)
			return false;
		if (this != self)
			return false;
		return true;
	}

	void Start(CsCoroutine inCoroutine, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, nullptr, nullptr, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, AActor* inActor, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, inActor, nullptr, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, nullptr, inObject, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, AActor* inActor, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, inActor, inObject, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, inStopCondition, inActor, inObject, inStartTime, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime, FCsRoutine** inOwnerMemberRoutine)
	{
		Start(inCoroutine, inStopCondition, inActor, inObject, inStartTime, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);

		ownerMemberRoutine  = inOwnerMemberRoutine;
		*ownerMemberRoutine = self;
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime, CsAddRoutine inAddRoutine, CsRemoveRoutine inRemoveRoutine, const uint8 &inType)
	{
		coroutine = inCoroutine;
		stopCondition = inStopCondition;
		a = inActor;
		o = inObject;
		startTime = inStartTime;
		addRoutine = inAddRoutine;
		removeRoutine = inRemoveRoutine;
		type = inType;

		if (GetActor())
		{
			owner = a;
		}
		else
		if (GetRObject())
		{
			owner = o;
		}

		if (GetOwner() && addRoutine)
			(*addRoutine)(GetOwner(), self, type);
	}

	void End()
	{
		if (ownerMemberRoutine)
			*ownerMemberRoutine = nullptr;
		else
		if (GetOwner() && removeRoutine)
			(*removeRoutine)(GetOwner(), self, type);
		EndChildren();
		index = CS_ROUTINE_END;
	}

	bool HasEnded()
	{
		return index == CS_ROUTINE_END || index == CS_ROUTINE_FREE;
	}

	void Reset()
	{
		if (parent)
		{
			parent->children.Remove(self);
		}

		parent = nullptr;

		EndChildren();

		coroutine = nullptr;
		stopCondition = nullptr;
		index = CS_ROUTINE_FREE;
		name = NAME_None;
		type = CS_ROUTINE_MAX_TYPE;
		a.Reset();
		a = nullptr;
		o.Reset();
		o = nullptr;
		owner.Reset();
		owner = nullptr;
		addRoutine = nullptr;
		removeRoutine = nullptr;
		ownerMemberRoutine = nullptr;
		startTime = 0.0f;
		tickCount = 0;
		delay = 0.0f;

		for (int32 i = 0; i < CS_ROUTINE_INDEXER_SIZE; i++)
		{
			indexers[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_COUNTER_SIZE; i++)
		{
			counters[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLAG_SIZE; i++)
		{
			flags[i] = false;
		}

		for (int32 i = 0; i < CS_ROUTINE_TIMER_SIZE; i++)
		{
			timers[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_INT_SIZE; i++)
		{
			ints[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLOAT_SIZE; i++)
		{
			floats[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_VECTOR_SIZE; i++)
		{
			vectors[i] = FVector::ZeroVector;
		}

		for (int32 i = 0; i < CS_ROUTINE_COLOR_SIZE; i++)
		{
			colors[i] = FLinearColor::White;
		}

		for (int32 i = 0; i < CS_ROUTINE_STRING_SIZE; i++)
		{
			strings[i] = TEXT("");
		}

		for (int32 i = 0; i < CS_ROUTINE_OBJECT_SIZE; i++)
		{
			objects[i].Reset();
			objects[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_POINTER_SIZE; i++)
		{
			voidPointers[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE; i++)
		{
			voidDoublePointers[i] = nullptr;
		}

		stopMessages.Reset();
		stopMessages_recieved.Reset();
	}

	void Run(const float &inDeltaSeconds)
	{
		const int32 iMax = stopMessages_recieved.Num();

		for (int32 i = 0; i < iMax; i++)
		{
			if (stopMessages.Find(stopMessages_recieved[i]) != INDEX_NONE)
			{
				stopMessages.Reset();
				End();
				break;
			}
		}
		stopMessages_recieved.Reset();

		if (stopCondition)
			(*stopCondition)(self);

		if (index == CS_ROUTINE_END)
		{
			if (GetOwner() && removeRoutine)
				(*removeRoutine)(GetOwner(), self, type);
			return;
		}
		deltaSeconds = inDeltaSeconds;
		tickCount++;
		(*coroutine)(self);
	}

	AActor* GetActor()
	{
		return a.IsValid() ? a.Get() : nullptr;
	}

	UObject* GetRObject()
	{
		return o.IsValid() ? o.Get() : nullptr;
	}

	UObject* GetOwner()
	{
		return owner.IsValid() ? owner.Get() : nullptr;
	}

	void AddChild(struct FCsRoutine* child)
	{
		child->parent = self;
		children.Add(child);
	}

	void EndChildren()
	{
		const int32 count = children.Num();

		for (int32 i = 0; i < count; i++)
		{
			children[i]->End();
		}
		children.Reset();
	}

	void EndChild(struct FCsRoutine* child)
	{
		const int32 count = children.Num();

		for (int32 i = count - 1; i >= 0; i--)
		{
			if (child == children[i])
			{
				child->End();
				children.RemoveAt(i);
				break;
			}
		}
	}

	void AddMessage(const TCsCoroutineMessage &MessageType, const FName &Message)
	{
		if (MessageType == ECsCoroutineMessage::Stop)
		{
			if (stopMessages.Find(Message) == INDEX_NONE)
				stopMessages.Add(Message);
		}
	}

	void ReceiveMessage(const TCsCoroutineMessage &MessageType, const FName &Message)
	{
		if (MessageType == ECsCoroutineMessage::Stop)
		{
			if (stopMessages_recieved.Find(Message) == INDEX_NONE)
				stopMessages_recieved.Add(Message);
		}
	}
};

#define CS_COROUTINE_DECLARE(Func)	virtual void Func(); \
									static char Func##_Internal(struct FCsRoutine* r); \
									struct FCsRoutine* Func##_Internal_Routine;
#define CS_COROUTINE(Class, Func) char Class::Func(FCsRoutine* r)

#define CS_COROUTINE_INIT(r)  PT_INIT(&((r)->pt))
#define CS_COROUTINE_BEGIN(r)   { char PT_YIELD_FLAG = 1; LC_RESUME((&((r)->pt))->lc)
#define CS_COROUTINE_END(r)	(r)->index = CS_ROUTINE_END; LC_END((&((r)->pt))->lc); PT_YIELD_FLAG = 0; \
							PT_INIT(&((r)->pt)); return PT_ENDED; }			
#define CS_COROUTINE_EXIT(r)	PT_EXIT(&((r)->pt))
#define CS_COROUTINE_YIELD(r)	PT_YIELD(&((r)->pt));
#define CS_COROUTINE_WAIT_UNTIL(r, condition) PT_WAIT_UNTIL(&((r)->pt), condition);

#pragma endregion Coroutine

// UI
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsWidgetFocus : uint8
{
	Mouse		UMETA(DisplayName = "Mouse"),
	Keyboard	UMETA(DisplayName = "Keyboard"),
	Controller	UMETA(DisplayName = "Controller"),
};

#define ECS_WIDGET_FOCUS_NONE 0
// 1 (2^0 Mouse) + 2 (2^1 Keyboard) + 4 (2^2 Controller)
#define ECS_WIDGET_FOCUS_ALL 7

namespace ECsWidgetActorType
{
	enum Type : uint8;
}

typedef ECsWidgetActorType::Type TCsWidgetActorType;

// WidgetActorTypeToString
typedef FString(*TCsWidgetActorTypeToString)(const TCsWidgetActorType&);
// StringToWidgetActorType
typedef TCsWidgetActorType(*TCsStringToWidgetActorType)(const FString&);

namespace ECsWidgetType
{
	enum Type : uint8;
}

typedef ECsWidgetType::Type TCsWidgetType;

// WidgetTypeToString
typedef FString(*TCsWidgetTypeToString)(const TCsWidgetType&);
// StringToWidgetType
typedef TCsWidgetType(*TCsStringToWidgetType)(const FString&);

USTRUCT(BlueprintType)
struct FCsWidgetActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TAssetPtr<class UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector2D DrawSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtCamera;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsWidgetActorInfo()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::UI);

		DrawSize = FVector2D(100.0f, 100.0f);
		Transform = FTransform::Identity;
	}

	FCsWidgetActorInfo& operator=(const FCsWidgetActorInfo& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		DrawSize = B.DrawSize;
		Transform = B.Transform;
		FollowCamera = B.FollowCamera;
		LookAtCamera = B.LookAtCamera;
		return *this;
	}

	bool operator==(const FCsWidgetActorInfo& B) const
	{
		return Blueprint == B.Blueprint &&
			   Blueprint_LoadFlags == B.Blueprint_LoadFlags &&
			   Blueprint_Internal == B.Blueprint_Internal &&
			   DrawSize == B.DrawSize &&
			   FollowCamera == B.FollowCamera &&
			   LookAtCamera == B.LookAtCamera;
	}

	bool operator!=(const FCsWidgetActorInfo& B) const
	{
		return !(*this == B);
	}

	UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

namespace ECsHorizTextAligment
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString EHTA_Left = TCsString(TEXT("EHTA_Left"), TEXT("ehta_left"), TEXT("left"));
		const TCsString EHTA_Center = TCsString(TEXT("EHTA_Center"), TEXT("ehta_center"), TEXT("center"));
		const TCsString EHTA_Right = TCsString(TEXT("EHTA_Right"), TEXT("ehta_right"), TEXT("right"));
	}

	FORCEINLINE FString ToString(const EHorizTextAligment &EType)
	{
		if (EType == EHorizTextAligment::EHTA_Left) { return Str::EHTA_Left.Value; }
		if (EType == EHorizTextAligment::EHTA_Center) { return Str::EHTA_Center.Value; }
		if (EType == EHorizTextAligment::EHTA_Right) { return Str::EHTA_Right.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EHorizTextAligment ToType(const FString &String)
	{
		if (String == Str::EHTA_Left) { return EHorizTextAligment::EHTA_Left; }
		if (String == Str::EHTA_Center) { return EHorizTextAligment::EHTA_Center; }
		if (String == Str::EHTA_Right) { return EHorizTextAligment::EHTA_Right; }
		return EHorizTextAligment::EHTA_Left;
	}
}

namespace ECsVerticalTextAligment
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString EVRTA_TextTop = TCsString(TEXT("EVRTA_TextTop"), TEXT("evrta_texttop"), TEXT("text top"));
		const TCsString EVRTA_TextCenter = TCsString(TEXT("EVRTA_TextCenter"), TEXT("evrta_textcenter"), TEXT("text center"));
		const TCsString EVRTA_TextBottom = TCsString(TEXT("EVRTA_TextBottom"), TEXT("evrta_textbottom"), TEXT("text bottom"));
		const TCsString EVRTA_QuadTop = TCsString(TEXT("EVRTA_QuadTop"), TEXT("evrta_quadtop"), TEXT("quad top"));
	}

	FORCEINLINE FString ToString(const EVerticalTextAligment &EType)
	{
		if (EType == EVerticalTextAligment::EVRTA_TextTop) { return Str::EVRTA_TextTop.Value; }
		if (EType == EVerticalTextAligment::EVRTA_TextCenter) { return Str::EVRTA_TextCenter.Value; }
		if (EType == EVerticalTextAligment::EVRTA_TextBottom) { return Str::EVRTA_TextBottom.Value; }
		if (EType == EVerticalTextAligment::EVRTA_QuadTop) { return Str::EVRTA_QuadTop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EVerticalTextAligment ToType(const FString &String)
	{
		if (String == Str::EVRTA_TextTop) { return EVerticalTextAligment::EVRTA_TextTop; }
		if (String == Str::EVRTA_TextCenter) { return EVerticalTextAligment::EVRTA_TextCenter; }
		if (String == Str::EVRTA_TextBottom) { return EVerticalTextAligment::EVRTA_TextBottom; }
		if (String == Str::EVRTA_QuadTop) { return EVerticalTextAligment::EVRTA_QuadTop; }
		return EVerticalTextAligment::EVRTA_TextTop;
	}
}

UENUM(BlueprintType)
namespace ECsButtonState
{
	enum Type
	{
		None				UMETA(DisplayName = "None"),
		FirstHover			UMETA(DisplayName = "FirstHover"),
		Hover				UMETA(DisplayName = "Hover"),
		FirstUnHover		UMETA(DisplayName = "FirstUnHover"),
		FirstPressed		UMETA(DisplayName = "FirstPressed"),
		Pressed				UMETA(DisplayName = "Pressed"),
		FirstReleased		UMETA(DisplayName = "FirstReleased"),
		ECsButtonState_MAX	UMETA(Hidden),
	};
}

namespace ECsButtonState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString FirstHover = TCsString(TEXT("FirstHover"), TEXT("firsthover"), TEXT("first hover"));
		const TCsString Hover = TCsString(TEXT("Hover"), TEXT("hover"), TEXT("hover"));
		const TCsString FirstUnHover = TCsString(TEXT("FirstUnHover"), TEXT("firstunhover"), TEXT("first unhover"));
		const TCsString FirstPressed = TCsString(TEXT("FirstPressed"), TEXT("firstpressed"), TEXT("first pressed"));
		const TCsString Pressed = TCsString(TEXT("Pressed"), TEXT("pressed"), TEXT("pressed"));
		const TCsString FirstReleased = TCsString(TEXT("FirstReleased"), TEXT("firstreleased"), TEXT("first released"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::FirstHover) { return Str::FirstHover.Value; }
		if (EType == Type::Hover) { return Str::Hover.Value; }
		if (EType == Type::FirstUnHover) { return Str::FirstUnHover.Value; }
		if (EType == Type::FirstPressed) { return Str::FirstPressed.Value; }
		if (EType == Type::Pressed) { return Str::Pressed.Value; }
		if (EType == Type::FirstReleased) { return Str::FirstReleased.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::FirstHover) { return Type::FirstHover; }
		if (String == Str::Hover) { return Type::Hover; }
		if (String == Str::FirstUnHover) { return Type::FirstUnHover; }
		if (String == Str::FirstPressed) { return Type::FirstPressed; }
		if (String == Str::Pressed) { return Type::Pressed; }
		if (String == Str::FirstReleased) { return Type::FirstReleased; }
		return Type::ECsButtonState_MAX;
	}
}

#define ECS_BUTTON_STATE_MAX (uint8)ECsButtonState::ECsButtonState_MAX
typedef TEnumAsByte<ECsButtonState::Type> TCsButtonState;

#pragma endregion UI

// Interactives
#pragma region

namespace ECsInteractiveType
{
	enum Type : uint8;
}

typedef ECsInteractiveType::Type TCsInteractiveType;

// InteractiveTypeToString
typedef FString(*TCsInteractiveTypeToString)(const TCsInteractiveType&);
// StringToInteractiveType
typedef TCsInteractiveType(*TCsStringToInteractiveType)(const FString&);

UENUM(BlueprintType)
namespace ECsInteractiveState
{
	enum Type
	{
		None					UMETA(DisplayName = "None"),
		FirstFreeze				UMETA(DisplayName = "Fire Freeze"),
		Freeze					UMETA(DisplayName = "Freeze"),
		FirstUnFreeze			UMETA(DisplayName = "First UnFreeze"),
		FirstHold				UMETA(DisplayName = "First Hold"),
		Hold					UMETA(DisplayName = "Hold"),
		Release					UMETA(DisplayName = "Release"),
		FirstTouch				UMETA(DisplayName = "First Touch"),
		Touch					UMETA(DisplayName = "Touch"),
		FirstHover				UMETA(DisplayName = "First Hover"),
		Hover					UMETA(DisplayName = "Hover"),
		FirstUnHover			UMETA(DisplayName = "First UnHover"),
		FirstCollide			UMETA(DisplayName = "First Collide"),
		Collide					UMETA(DisplayName = "Collide"),
		FirstUnCollide			UMETA(DisplayName = "First UnCollide"),
		Remove					UMETA(DisplayName = "Remove"),
		ECsInteractiveState_MAX	UMETA(Hidden),
	};
}

namespace ECsInteractiveState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString FirstFreeze = TCsString(TEXT("FirstFreeze"), TEXT("firstfreeze"), TEXT("first freeze"));
		const TCsString Freeze = TCsString(TEXT("Freeze"), TEXT("freeze"), TEXT("freeze"));
		const TCsString FirstUnFreeze = TCsString(TEXT("FirstUnFreeze"), TEXT("firstunfreeze"), TEXT("first unfreeze"));
		const TCsString FirstHold = TCsString(TEXT("FirstHold"), TEXT("firsthold"), TEXT("first hold"));
		const TCsString Hold = TCsString(TEXT("Hold"), TEXT("hold"), TEXT("hold"));
		const TCsString Release = TCsString(TEXT("Release"), TEXT("release"), TEXT("release"));
		const TCsString FirstTouch = TCsString(TEXT("FirstTouch"), TEXT("firsttouch"), TEXT("first touch"));
		const TCsString Touch = TCsString(TEXT("Touch"), TEXT("touch"), TEXT("touch"));
		const TCsString FirstHover = TCsString(TEXT("FirstHover"), TEXT("firsthover"), TEXT("first hover"));
		const TCsString Hover = TCsString(TEXT("Hover"), TEXT("hover"), TEXT("hover"));
		const TCsString FirstUnHover = TCsString(TEXT("FirstUnHover"), TEXT("firstunhover"), TEXT("first unhover"));
		const TCsString FirstCollide = TCsString(TEXT("FirstCollide"), TEXT("firstcollide"), TEXT("first collide"));
		const TCsString Collide = TCsString(TEXT("Collide"), TEXT("collide"), TEXT("collide"));
		const TCsString FirstUnCollide = TCsString(TEXT("FirstUnCollide"), TEXT("firstuncollide"), TEXT("first uncollide"));
		const TCsString Remove = TCsString(TEXT("Remove"), TEXT("remove"), TEXT("remove"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::FirstFreeze) { return Str::FirstFreeze.Value; }
		if (EType == Type::Freeze) { return Str::Freeze.Value; }
		if (EType == Type::FirstUnFreeze) { return Str::FirstUnFreeze.Value; }
		if (EType == Type::FirstHold) { return Str::FirstHold.Value; }
		if (EType == Type::Hold) { return Str::Hold.Value; }
		if (EType == Type::Release) { return Str::Release.Value; }
		if (EType == Type::FirstTouch) { return Str::FirstTouch.Value; }
		if (EType == Type::Touch) { return Str::Touch.Value; }
		if (EType == Type::FirstHover) { return Str::FirstHover.Value; }
		if (EType == Type::Hover) { return Str::Hover.Value; }
		if (EType == Type::FirstUnHover) { return Str::FirstUnHover.Value; }
		if (EType == Type::FirstCollide) { return Str::FirstCollide.Value; }
		if (EType == Type::Collide) { return Str::Collide.Value; }
		if (EType == Type::FirstUnCollide) { return Str::FirstUnCollide.Value; }
		if (EType == Type::Remove) { return Str::Remove.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::FirstFreeze) { return Type::FirstFreeze; }
		if (String == Str::Freeze) { return Type::Freeze; }
		if (String == Str::FirstHold) { return Type::FirstHold; }
		if (String == Str::FirstUnFreeze) { return Type::FirstUnFreeze; }
		if (String == Str::Hold) { return Type::Hold; }
		if (String == Str::Release) { return Type::Release; }
		if (String == Str::FirstTouch) { return Type::FirstTouch; }
		if (String == Str::Touch) { return Type::Touch; }
		if (String == Str::FirstHover) { return Type::FirstHover; }
		if (String == Str::Hover) { return Type::Hover; }
		if (String == Str::FirstUnHover) { return Type::FirstUnHover; }
		if (String == Str::FirstCollide) { return Type::FirstCollide; }
		if (String == Str::Collide) { return Type::Collide; }
		if (String == Str::FirstUnCollide) { return Type::FirstUnCollide; }
		if (String == Str::Remove) { return Type::Remove; }
		return Type::ECsInteractiveState_MAX;
	}
}

#define ECS_INTERACTIVE_STATE_MAX (uint8)ECsInteractiveState::ECsInteractiveState_MAX
typedef TEnumAsByte<ECsInteractiveState::Type> TCsInteractiveState;

UENUM()
namespace ECsInteractiveInstigator
{
	enum Type
	{
		Look							UMETA(DisplayName = "Look"),
		LeftHand						UMETA(DisplayName = "Left Hand"),
		RightHand						UMETA(DisplayName = "Right Hand"),
		Actor							UMETA(DisplayName = "Actor"),
		ECsInteractiveInstigator_MAX	UMETA(Hidden),
	};
}

namespace ECsInteractiveInstigator
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Look = TCsString(TEXT("Look"), TEXT("look"), TEXT("look"));
		const TCsString LeftHand = TCsString(TEXT("LeftHand"), TEXT("lefthand"), TEXT("left hand"));
		const TCsString RightHand = TCsString(TEXT("RightHand"), TEXT("righthand"), TEXT("right hand"));
		const TCsString Actor = TCsString(TEXT("Actor"), TEXT("actor"), TEXT("actor"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Look) { return Str::Look.Value; }
		if (EType == Type::LeftHand) { return Str::LeftHand.Value; }
		if (EType == Type::RightHand) { return Str::RightHand.Value; }
		if (EType == Type::Actor) { return Str::Actor.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Look) { return Type::Look; }
		if (String == Str::LeftHand) { return Type::LeftHand; }
		if (String == Str::RightHand) { return Type::RightHand; }
		if (String == Str::Actor) { return Type::Actor; }
		return Type::ECsInteractiveInstigator_MAX;
	}
}

#define ECS_INTERACTIVE_INSTIGATOR_MAX (uint8)ECsInteractiveInstigator::ECsInteractiveInstigator_MAX
typedef TEnumAsByte<ECsInteractiveInstigator::Type> TCsInteractiveInstigator;

UENUM()
namespace ECsInteractiveCollision
{
	enum Type
	{
		Box							UMETA(DisplayName = "Box"),
		Sphere						UMETA(DisplayName = "Sphere"),
		DistanceSquared				UMETA(DisplayName = "DistanceSquared"),
		Trace						UMETA(DisplayName = "Trace"),
		Mesh						UMETA(DisplayName = "Mesh"),
		ECsInteractiveCollision_MAX	UMETA(Hidden),
	};
}

namespace ECsInteractiveCollision
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Box = TCsString(TEXT("Box"), TEXT("box"), TEXT("box"));
		const TCsString Sphere = TCsString(TEXT("Sphere"), TEXT("sphere"), TEXT("sphere"));
		const TCsString DistanceSquared = TCsString(TEXT("DistanceSquared"), TEXT("distancesquared"), TEXT("distance squared"));
		const TCsString Trace = TCsString(TEXT("Trace"), TEXT("trace"), TEXT("trace"));
		const TCsString Mesh = TCsString(TEXT("Mesh"), TEXT("mesh"), TEXT("mesh"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Box) { return Str::Box.Value; }
		if (EType == Type::Sphere) { return Str::Sphere.Value; }
		if (EType == Type::DistanceSquared) { return Str::DistanceSquared.Value; }
		if (EType == Type::Trace) { return Str::Trace.Value; }
		if (EType == Type::Mesh) { return Str::Mesh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Box) { return Type::Box; }
		if (String == Str::Sphere) { return Type::Sphere; }
		if (String == Str::DistanceSquared) { return Type::DistanceSquared; }
		if (String == Str::Trace) { return Type::Trace; }
		if (String == Str::Mesh) { return Type::Mesh; }
		return Type::ECsInteractiveCollision_MAX;
	}
}

#define ECS_INTERACTIVE_COLLISION_MAX (uint8)ECsInteractiveCollision::ECsInteractiveCollision_MAX
typedef TEnumAsByte<ECsInteractiveCollision::Type> TCsInteractiveCollision;

USTRUCT()
struct FCsInteractiveMaterials
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TAssetPtr<class UMaterialInstanceConstant> Materials[ECsInteractiveState::ECsInteractiveState_MAX];

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstanceConstant* Materials_Internal[ECsInteractiveState::ECsInteractiveState_MAX];

public:
	FCsInteractiveMaterials()
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::UI);
	}

	FCsInteractiveMaterials& operator=(const FCsInteractiveMaterials& B)
	{
		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; I++)
		{
			Materials[I] = B.Materials[I];
		}
		Materials_LoadFlags = B.Materials_LoadFlags;
		return *this;
	}

	bool operator==(const FCsInteractiveMaterials& B) const
	{
		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; I++)
		{
			if (Materials[I] != B.Materials[I])
				return false;
		}

		for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; I++)
		{
			if (Materials_Internal[I] != B.Materials_Internal[I])
				return false;
		}
		return Materials_LoadFlags == B.Materials_LoadFlags;
	}

	bool operator!=(const FCsInteractiveMaterials& B) const
	{
		return !(*this == B);
	}

	UMaterialInstanceConstant** Get()
	{
		return Materials_Internal;
	}

	class UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < ECS_INTERACTIVE_STATE_MAX ? Materials_Internal[Index] : nullptr;
	}
};

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInteractivePhysicsState : uint8
{
	Grounded	UMETA(DisplayName = "Grounded"),
	Airborne	UMETA(DisplayName = "Airborne"),
	Ragdoll		UMETA(DisplayName = "Ragdoll"),
	Held		UMETA(DisplayName = "Held"),
	Custom		UMETA(DisplayName = "Custom"),
};

UENUM(BlueprintType)
namespace ECsInteractivePhysicsState_Editor
{
	enum Type
	{
		Grounded								UMETA(DisplayName = "Grounded"),
		Airborne								UMETA(DisplayName = "Airborne"),
		Ragdoll									UMETA(DisplayName = "Ragdoll"),
		Held									UMETA(DisplayName = "Held"),
		Custom									UMETA(DisplayName = "Custom"),
		ECsInteractivePhysicsState_Editor_MAX	UMETA(Hidden),
	};
}

namespace ECsInteractivePhysicsState_Editor
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Grounded = TCsString(TEXT("Grounded"), TEXT("grounded"));
		const TCsString Airborne = TCsString(TEXT("Airborne"), TEXT("airborne"));
		const TCsString Ragdoll = TCsString(TEXT("Ragdoll"), TEXT("ragdoll"));
		const TCsString Custom = TCsString(TEXT("Custom"), TEXT("custom"));
		const TCsString Held = TCsString(TEXT("Held"), TEXT("held"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Grounded) { return Str::Grounded.Value; }
		if (EType == Type::Airborne) { return Str::Airborne.Value; }
		if (EType == Type::Ragdoll) { return Str::Ragdoll.Value; }
		if (EType == Type::Held) { return Str::Held.Value; }
		if (EType == Type::Custom) { return Str::Custom.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const ECsInteractivePhysicsState &EType)
	{
		if (EType == ECsInteractivePhysicsState::Grounded) { return Str::Grounded.Value; }
		if (EType == ECsInteractivePhysicsState::Airborne) { return Str::Airborne.Value; }
		if (EType == ECsInteractivePhysicsState::Ragdoll) { return Str::Ragdoll.Value; }
		if (EType == ECsInteractivePhysicsState::Held) { return Str::Held.Value; }
		if (EType == ECsInteractivePhysicsState::Custom) { return Str::Custom.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Grounded) { return Type::Grounded; }
		if (String == Str::Airborne) { return Type::Airborne; }
		if (String == Str::Ragdoll) { return Type::Ragdoll; }
		if (String == Str::Held) { return Type::Held; }
		if (String == Str::Custom) { return Type::Custom; }
		return Type::ECsInteractivePhysicsState_Editor_MAX;
	}
}

#define ECS_INTERACTIVE_PHYSICS_STATE_EDITOR_MAX (uint8)ECsInteractivePhysicsState_Editor::ECsInteractivePhysicsState_Editor_MAX
typedef TEnumAsByte<ECsInteractivePhysicsState_Editor::Type> TCsInteractivePhysicsState_Editor;

USTRUCT(BlueprintType)
struct FCsInteractedActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class UObject> Instigator;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class AActor> Actor;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	TWeakObjectPtr<class USceneComponent> Component;

	UPROPERTY(EditAnywhere, Category = "Interactive")
	FVector Location;

public:

	FCsInteractedActorInfo& operator=(const FCsInteractedActorInfo& B)
	{
		Instigator = B.Instigator;
		Actor = B.Actor;
		Component = B.Component;
		Location = B.Location;
		return *this;
	}

	bool operator==(const FCsInteractedActorInfo& B) const
	{
		return Instigator == B.Instigator && Actor == B.Actor && Component == B.Component && Location == B.Location;
	}

	bool operator!=(const FCsInteractedActorInfo& B) const
	{
		return !(*this == B);
	}

	class AActor* GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }
	class UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	class USceneComponent* GetComponent() const { return Component.IsValid() ? Component.Get() : nullptr; }
};

#pragma endregion Interactives

// AI
#pragma region

namespace ECsAIType
{
	enum Type : uint8;
}

typedef ECsAIType::Type TCsAIType;

#pragma endregion AI

// VR
#pragma region

UENUM(BlueprintType)
namespace ECsHMDDeviceType
{
	enum Type
	{
		DT_OculusRift			UMETA(DisplayName = "Oculus Rift"),
		DT_Morpheus				UMETA(DisplayName = "Playstaton VR"),
		DT_ES2GenericStereoMesh UMETA(DisplayName = "ES2 Generic"),
		DT_SteamVR				UMETA(DisplayName = "Vive"),
		DT_GearVR				UMETA(DisplayName = "Gear VR"),
		DT_GoogleVR				UMETA(DisplayName = "Google VR"),
		ECsHMDDeviceType_MAX	UMETA(Hidden),
	};
}

namespace ECsHMDDeviceType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString DT_OculusRift = TCsString(TEXT("DT_OculusRift"), TEXT("dt_oculusrift"), TEXT("oculus rift"));
		const TCsString DT_Morpheus = TCsString(TEXT("DT_Morpheus"), TEXT("dt_morpheus"), TEXT("psvr"));
		const TCsString DT_ES2GenericStereoMesh = TCsString(TEXT("DT_ES2GenericStereoMesh"), TEXT("dt_es2genericstereomesh"), TEXT("es2 generic"));
		const TCsString DT_SteamVR = TCsString(TEXT("DT_SteamVR"), TEXT("dt_steamvr"), TEXT("vive"));
		const TCsString DT_GearVR = TCsString(TEXT("DT_GearVR"), TEXT("dt_gearvr"), TEXT("gearvr"));
		const TCsString DT_GoogleVR = TCsString(TEXT("DT_GoogleVR"), TEXT("dt_googlevr"), TEXT("goolgevr"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::DT_OculusRift) { return Str::DT_OculusRift.Value; }
		if (EType == Type::DT_Morpheus) { return Str::DT_Morpheus.Value; }
		if (EType == Type::DT_ES2GenericStereoMesh) { return Str::DT_ES2GenericStereoMesh.Value; }
		if (EType == Type::DT_SteamVR) { return Str::DT_SteamVR.Value; }
		if (EType == Type::DT_GearVR) { return Str::DT_GearVR.Value; }
		if (EType == Type::DT_GoogleVR) { return Str::DT_GoogleVR.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::DT_OculusRift) { return Type::DT_OculusRift; }
		if (String == Str::DT_Morpheus) { return Type::DT_Morpheus; }
		if (String == Str::DT_ES2GenericStereoMesh) { return Type::DT_ES2GenericStereoMesh; }
		if (String == Str::DT_SteamVR) { return Type::DT_SteamVR; }
		if (String == Str::DT_GearVR) { return Type::DT_GearVR; }
		if (String == Str::DT_GoogleVR) { return Type::DT_GoogleVR; }
		return Type::ECsHMDDeviceType_MAX;
	}

	FORCEINLINE EHMDDeviceType::Type ToBaseType(const Type &EType)
	{
		if (EType == Type::DT_OculusRift) { return EHMDDeviceType::DT_OculusRift; }
		if (EType == Type::DT_Morpheus) { return EHMDDeviceType::DT_Morpheus; }
		if (EType == Type::DT_ES2GenericStereoMesh) { return EHMDDeviceType::DT_ES2GenericStereoMesh; }
		if (EType == Type::DT_SteamVR) { return EHMDDeviceType::DT_SteamVR; }
		if (EType == Type::DT_GearVR) { return EHMDDeviceType::DT_GearVR; }
		if (EType == Type::DT_GoogleVR) { return EHMDDeviceType::DT_GoogleVR; }
		return EHMDDeviceType::DT_SteamVR;
	}

	FORCEINLINE Type FromBaseType(const EHMDDeviceType::Type &EType)
	{
		if (EType == EHMDDeviceType::DT_OculusRift) { return Type::DT_OculusRift; }
		if (EType == EHMDDeviceType::DT_Morpheus) { return Type::DT_Morpheus; }
		if (EType == EHMDDeviceType::DT_ES2GenericStereoMesh) { return Type::DT_ES2GenericStereoMesh; }
		if (EType == EHMDDeviceType::DT_SteamVR) { return Type::DT_SteamVR; }
		if (EType == EHMDDeviceType::DT_GearVR) { return Type::DT_GearVR; }
		if (EType == EHMDDeviceType::DT_GoogleVR) { return Type::DT_GoogleVR; }
		return Type::ECsHMDDeviceType_MAX;
	}
}

#define ECS_HMD_DEVICE_TYPE_MAX (uint8)ECsHMDDeviceType::ECsHMDDeviceType_MAX
typedef TEnumAsByte<ECsHMDDeviceType::Type> TCsHMDDeviceType;

#pragma  endregion VR

// Gestures
#pragma region

UENUM()
namespace ECsGestureDevice
{
	enum Type
	{
		Mouse					UMETA(DisplayName = "Mouse"),
		MotionController		UMETA(DisplayName = "MotionController"),
		ECsGestureDevice_MAX	UMETA(Hidden),
	};
}

namespace ECsGestureDevice
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Mouse = TCsString(TEXT("Mouse"), TEXT("mouse"), TEXT("mouse"));
		const TCsString MotionController = TCsString(TEXT("MotionController"), TEXT("motioncontroller"), TEXT("motion controller"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Mouse) { return Str::Mouse.Value; }
		if (EType == Type::MotionController) { return Str::MotionController.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Mouse) { return Type::Mouse; }
		if (String == Str::MotionController) { return Type::MotionController; }
		return Type::ECsGestureDevice_MAX;
	}
}

#define ECS_GESTURE_DEVICE_MAX (uint8)ECsGestureDevice::ECsGestureDevice_MAX
typedef TEnumAsByte<ECsGestureDevice::Type> TCsGestureDevice;

namespace ECsGestureType
{
	enum Type : uint8;
}

typedef ECsGestureType::Type TCsGestureType;

#pragma endregion Gestures

// Replication
#pragma region

#define CS_SERVER_TO_CLIENT_SEND_FREQUENCY 0.01666666667

#pragma endregion Replication

// Weapon
#pragma region

namespace ECsWeaponFire
{
	enum Type : uint8;
}

typedef ECsWeaponFire::Type TCsWeaponFire;

namespace ECsWeaponAnim
{
	enum Type : uint8;
}

typedef ECsWeaponAnim::Type TCsWeaponAnim;

namespace ECsWeaponBlendSpace
{
	enum Type : uint8;
}

typedef ECsWeaponBlendSpace::Type TCsWeaponBlendSpace;

namespace ECsWeaponAnimBlueprint
{
	enum Type : uint8;
}

typedef ECsWeaponAnimBlueprint::Type TCsWeaponAnimBlueprint;

namespace ECsWeaponSound
{
	enum Type : uint8;
}

typedef ECsWeaponSound::Type TCsWeaponSound;

namespace ECsWeaponOwner
{
	enum Type : uint8;
}

typedef ECsWeaponOwner::Type TCsWeaponOwner;

#pragma endregion Weapon

// Projectile
#pragma region

// ACsData_Projectile
USTRUCT()
struct FCsData_ProjectilePtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_Projectile> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

private:
	UPROPERTY(Transient)
	class ACsData_Projectile* Data_Internal;

public:
	FCsData_ProjectilePtr()
	{
		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
	{
		Data = B.Data;
		Data_LoadFlags = B.Data_LoadFlags;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsData_ProjectilePtr& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsData_ProjectilePtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_Projectile* Get() const
	{
		return Data_Internal;
	}
};

UENUM(BlueprintType)
namespace ECsProjectileRelevance
{
	enum Type
	{
		Real						UMETA(DisplayName = "Real"),
		Fake						UMETA(DisplayName = "Fake"),
		ECsProjectileRelevance_MAX	UMETA(Hidden),
	};
}

namespace ECsProjectileRelevance
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Real = TCsString(TEXT("Real"), TEXT("real"));
		const TCsString Fake = TCsString(TEXT("Fake"), TEXT("fake"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Real) { return Str::Real.Value; }
		if (EType == Type::Fake) { return Str::Fake.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Real) { return Type::Real; }
		if (String == Str::Fake) { return Type::Fake; }
		return Type::ECsProjectileRelevance_MAX;
	}
}

#define ECS_PROJECTILE_RELEVANCE_MAX (uint8)ECsProjectileRelevance::ECsProjectileRelevance_MAX
typedef TEnumAsByte<ECsProjectileRelevance::Type> TCsProjectileRelevance;

namespace ECsProjectileType
{
	enum Type : uint8;
}

typedef ECsProjectileType::Type TCsProjectileType;

UENUM(BlueprintType)
namespace ECsProjectileState
{
	enum Type
	{
		Active				   UMETA(DisplayName = "Active"),
		DeActivating		   UMETA(DisplayName = "DeActivating"),
		InActive			   UMETA(DisplayName = "InActive"),
		ECsProjectileState_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Active = TCsString(TEXT("Active"), TEXT("active"));
		const TCsString DeActivating = TCsString(TEXT("DeActivating"), TEXT("deactivating"));
		const TCsString InActive = TCsString(TEXT("InActive"), TEXT("inactive"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Active) { return Str::Active.Value; }
		if (EType == Type::DeActivating) { return Str::DeActivating.Value; }
		if (EType == Type::InActive) { return Str::InActive.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Active) { return Type::Active; }
		if (String == Str::DeActivating) { return Type::DeActivating; }
		if (String == Str::InActive) { return Type::InActive; }
		return Type::ECsProjectileState_MAX;
	}
}

#define ECS_PROJECTILE_STATE_MAX (uint8)ECsProjectileState::ECsProjectileState_MAX
typedef TEnumAsByte<ECsProjectileState::Type> TCsProjectileState;

UENUM(BlueprintType)
namespace ECsProjectileDeActivate
{
	enum Type
	{
		Collision					UMETA(DisplayName = "Collision"),
		Movement					UMETA(DisplayName = "Movement"),
		Mesh						UMETA(DisplayName = "Mesh"),
		ECsProjectileDeActivate_MAX UMETA(Hidden),
	};
}

namespace ECsProjectileDeActivate
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Collision = TCsString(TEXT("Collision"), TEXT("collision"));
		const TCsString Movement = TCsString(TEXT("Movement"), TEXT("movement"));
		const TCsString Mesh = TCsString(TEXT("Mesh"), TEXT("mesh"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Collision) { return Str::Collision.Value; }
		if (EType == Type::Movement) { return Str::Movement.Value; }
		if (EType == Type::Mesh) { return Str::Mesh.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Collision) { return Type::Collision; }
		if (String == Str::Movement) { return Type::Movement; }
		if (String == Str::Mesh) { return Type::Mesh; }
		return Type::ECsProjectileDeActivate_MAX;
	}
}

#define ECS_PROJECTILE_DEACTIVATE_MAX (uint8)ECsProjectileDeActivate::ECsProjectileDeActivate_MAX
typedef TEnumAsByte<ECsProjectileDeActivate::Type> TCsProjectileDeActivate;

USTRUCT(BlueprintType)
struct FCsProjectileFireCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;

	UPROPERTY()
	float Time;
	UPROPERTY()
	float RealTime;
	UPROPERTY()
	uint64 Frame;

	UPROPERTY()
	float ChargePercent;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float AdditionalSpeed;

	UPROPERTY()
	TWeakObjectPtr<AActor> HomingTarget;

	UPROPERTY()
	FName HomingBoneName;

	UPROPERTY()
	float HomingAccelerationMagnitude;

	FCsProjectileFireCache()
	{
		Reset();
	}

	FCsProjectileFireCache& operator=(const FCsProjectileFireCache& B)
	{
		IsAllocated = B.IsAllocated;
		Time = B.Time;
		RealTime = B.RealTime;
		Frame = B.Frame;
		ChargePercent = B.ChargePercent;
		Location = B.Location;
		Direction = B.Direction;
		AdditionalSpeed = B.AdditionalSpeed;
		HomingTarget = B.HomingTarget;
		HomingBoneName = B.HomingBoneName;
		HomingAccelerationMagnitude = B.HomingAccelerationMagnitude;
		return *this;
	}

	bool operator==(const FCsProjectileFireCache& B) const
	{
		return IsAllocated == B.IsAllocated &&
			   Time == B.Time &&
			   RealTime == B.RealTime &&
			   Frame == B.Frame &&
			   ChargePercent == B.ChargePercent &&
			   Location == B.Location &&
			   Direction == B.Direction &&
			   AdditionalSpeed == B.AdditionalSpeed &&
			   HomingTarget == B.HomingTarget &&
			   HomingBoneName == B.HomingBoneName &&
			   HomingAccelerationMagnitude == B.HomingAccelerationMagnitude;
	}

	bool operator!=(const FCsProjectileFireCache& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		IsAllocated = false;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		ChargePercent = 0.0f;
		Location = FVector::ZeroVector;
		Direction = FVector::ZeroVector;
		AdditionalSpeed = 0.0f;
		HomingTarget.Reset();
		HomingTarget = NULL;
		HomingBoneName = NAME_None;
		HomingAccelerationMagnitude = 0.0f;
	}

	AActor* GetHomingTarget() const
	{
		return HomingTarget.IsValid() ? HomingTarget.Get() : NULL;
	}
};

#pragma endregion Projectile

USTRUCT(BlueprintType)
struct FCsLocationDamageModifier
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FString Bone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float Multiplier;

	FCsLocationDamageModifier()
	{
		Multiplier = 1.0f;
	}

	FCsLocationDamageModifier& operator=(const FCsLocationDamageModifier& B)
	{
		Bone	   = B.Bone;
		Multiplier = B.Multiplier;
		return *this;
	}

	bool operator==(const FCsLocationDamageModifier& B) const
	{
		return Bone == B.Bone && Multiplier == B.Multiplier;
	}

	bool operator!=(const FCsLocationDamageModifier& B) const
	{
		return !(*this == B);
	}

	static FCsLocationDamageModifier CreateAndCopy(const FCsLocationDamageModifier& B)
	{
		FCsLocationDamageModifier A;
		A = B;
		return A;
	}
};

// Pooled Objects
#pragma region

#define CS_POOLED_OBJECT_CACHE_INVALID_TYPE 255

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPooledObjectCache_OnDeAllocate, const int32&, PoolIndex, const int32&, ActiveIndex, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsPooledObjectCache_OnDeAllocate, const uint16&, const uint16&, const uint8&);

USTRUCT(BlueprintType)
struct FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	uint16 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 Index_Script;
	
	uint16 ActiveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 ActiveIndex_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool IsAllocated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	uint8 Type;

	TWeakObjectPtr<UObject> Instigator;
	TWeakObjectPtr<UObject> Owner;
	TWeakObjectPtr<UObject> Parent;
	TWeakObjectPtr<UObject> DelegateInvoker;

	UPROPERTY(BlueprintAssignable, Category = "Cache")
	FBindableDynEvent_CsPooledObjectCache_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsPooledObjectCache_OnDeAllocate OnDeAllocate_Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float RealTime;

	uint64 Frame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	int32 Frame_Script;

	FCsPooledObjectCache()
	{
		Reset();
	}

	virtual ~FCsPooledObjectCache(){}

	virtual void Reset()
	{
		ActiveIndex = 0;
		ActiveIndex_Script = 0;

		IsAllocated = false;

		Type = CS_POOLED_OBJECT_CACHE_INVALID_TYPE;

		if (UObject* Invoker = GetDelegateInvoker())
		{
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.Clear();
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.Clear();
		}

		Instigator.Reset();
		Instigator = nullptr;
		Owner.Reset();
		Owner = nullptr;
		Parent.Reset();
		Parent = nullptr;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		Frame_Script = 0;
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	UObject* GetParent() { return Parent.IsValid() ? Parent.Get() : nullptr; }
	UObject* GetDelegateInvoker() { return DelegateInvoker.IsValid() ? DelegateInvoker.Get() : nullptr; }

	void DeAllocate()
	{
#if WITH_EDITOR
		OnDeAllocate_ScriptEvent.Broadcast(Index_Script, ActiveIndex_Script, Type);
#endif // #if WITH_EDITOR
		OnDeAllocate_Event.Broadcast(Index, ActiveIndex, Type);

		Reset();
	}
};

#pragma endregion Pooled Objects

// Motion Controller
#pragma region

UENUM(BlueprintType)
namespace ECsControllerHand
{
	enum Type
	{
		Left					UMETA(DisplayName = "Left"),
		Right					UMETA(DisplayName = "Right"),
		ECsControllerHand_MAX	UMETA(Hidden),
	};
}

namespace ECsControllerHand
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Left = TCsString(TEXT("Left"), TEXT("left"));
		const TCsString Right = TCsString(TEXT("Right"), TEXT("right"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Left) { return Str::Left.Value; }
		if (EType == Type::Right) { return Str::Right.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Left) { return Type::Left; }
		if (String == Str::Right) { return Type::Right; }
		return Type::ECsControllerHand_MAX;
	}
}

#define ECS_CONTROLLER_HAND_MAX (uint8)ECsControllerHand::ECsControllerHand_MAX
typedef TEnumAsByte<ECsControllerHand::Type> TCsControllerHand;

#pragma endregion Motion Controller

// Collision
#pragma region

namespace ECollisionEnabled
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString NoCollision = TCsString(TEXT("NoCollision"), TEXT("nocollision"), TEXT("no collision"));
		const TCsString QueryOnly = TCsString(TEXT("QueryOnly"), TEXT("queryonly"), TEXT("query only"));
		const TCsString PhysicsOnly = TCsString(TEXT("PhysicsOnly"), TEXT("physicsonly"), TEXT("physics only"));
		const TCsString QueryAndPhysics = TCsString(TEXT("QueryAndPhysics"), TEXT("queryandphysics"), TEXT("query and physics"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::NoCollision) { return Str::NoCollision.Value; }
		if (EType == Type::QueryOnly) { return Str::QueryOnly.Value; }
		if (EType == Type::PhysicsOnly) { return Str::PhysicsOnly.Value; }
		if (EType == Type::QueryAndPhysics) { return Str::QueryAndPhysics.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::NoCollision) { return Type::NoCollision; }
		if (String == Str::QueryOnly) { return Type::QueryOnly; }
		if (String == Str::PhysicsOnly) { return Type::PhysicsOnly; }
		if (String == Str::QueryAndPhysics) { return Type::QueryAndPhysics; }
		return Type::NoCollision;
	}
}

namespace ECsCollisionChannel
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString ECC_WorldStatic = TCsString(TEXT("ECC_WorldStatic"), TEXT("ecc_worldstatic"), TEXT("worldstatic"));
		const TCsString ECC_WorldDynamic = TCsString(TEXT("ECC_WorldDynamic"), TEXT("ecc_worlddynamic"), TEXT("worlddynamic"));
		const TCsString ECC_Pawn = TCsString(TEXT("ECC_Pawn"), TEXT("ecc_pawn"), TEXT("pawn"));
		const TCsString ECC_Visibility = TCsString(TEXT("ECC_Visibility"), TEXT("ecc_visibility"), TEXT("visibility"));
		const TCsString ECC_Camera = TCsString(TEXT("ECC_Camera"), TEXT("ecc_camera"), TEXT("camera"));
		const TCsString ECC_PhysicsBody = TCsString(TEXT("ECC_PhysicsBody"), TEXT("ecc_physicsbody"), TEXT("physicsbody"));
		const TCsString ECC_Vehicle = TCsString(TEXT("ECC_Vehicle"), TEXT("ecc_vehicle"), TEXT("vehicle"));
		const TCsString ECC_Destructible = TCsString(TEXT("ECC_Destructible"), TEXT("ecc_destructible"), TEXT("destructible"));

		const TCsString ECC_EngineTraceChannel1 = TCsString(TEXT("ECC_EngineTraceChannel1"), TEXT("ecc_enginetracechannel1"), TEXT("enginetracechannel 1"));
		const TCsString ECC_EngineTraceChannel2 = TCsString(TEXT("ECC_EngineTraceChannel2"), TEXT("ecc_enginetracechannel2"), TEXT("enginetracechannel 2"));
		const TCsString ECC_EngineTraceChannel3 = TCsString(TEXT("ECC_EngineTraceChannel3"), TEXT("ecc_enginetracechannel3"), TEXT("enginetracechannel 3"));
		const TCsString ECC_EngineTraceChannel4 = TCsString(TEXT("ECC_EngineTraceChannel4"), TEXT("ecc_enginetracechannel4"), TEXT("enginetracechannel 4"));
		const TCsString ECC_EngineTraceChannel5 = TCsString(TEXT("ECC_EngineTraceChannel5"), TEXT("ecc_enginetracechannel5"), TEXT("enginetracechannel 5"));
		const TCsString ECC_EngineTraceChannel6 = TCsString(TEXT("ECC_EngineTraceChannel6"), TEXT("ecc_enginetracechannel6"), TEXT("enginetracechannel 6"));

		const TCsString ECC_GameTraceChannel1 = TCsString(TEXT("ECC_GameTraceChannel1"), TEXT("ecc_gametracechannel1"), TEXT("gametracechannel 1"));
		const TCsString ECC_GameTraceChannel2 = TCsString(TEXT("ECC_GameTraceChannel2"), TEXT("ecc_gametracechannel2"), TEXT("gametracechannel 2"));
		const TCsString ECC_GameTraceChannel3 = TCsString(TEXT("ECC_GameTraceChannel3"), TEXT("ecc_gametracechannel3"), TEXT("gametracechannel 3"));
		const TCsString ECC_GameTraceChannel4 = TCsString(TEXT("ECC_GameTraceChannel4"), TEXT("ecc_gametracechannel4"), TEXT("gametracechannel 4"));
		const TCsString ECC_GameTraceChannel5 = TCsString(TEXT("ECC_GameTraceChannel5"), TEXT("ecc_gametracechannel5"), TEXT("gametracechannel 5"));
		const TCsString ECC_GameTraceChannel6 = TCsString(TEXT("ECC_GameTraceChannel6"), TEXT("ecc_gametracechannel6"), TEXT("gametracechannel 6"));
		const TCsString ECC_GameTraceChannel7 = TCsString(TEXT("ECC_GameTraceChannel7"), TEXT("ecc_gametracechannel7"), TEXT("gametracechannel 7"));
		const TCsString ECC_GameTraceChannel8 = TCsString(TEXT("ECC_GameTraceChannel8"), TEXT("ecc_gametracechannel8"), TEXT("gametracechannel 8"));
		const TCsString ECC_GameTraceChannel9 = TCsString(TEXT("ECC_GameTraceChannel9"), TEXT("ecc_gametracechannel9"), TEXT("gametracechannel 9"));
		const TCsString ECC_GameTraceChannel10 = TCsString(TEXT("ECC_GameTraceChannel10"), TEXT("ecc_gametracechannel10"), TEXT("gametracechannel 10"));
		const TCsString ECC_GameTraceChannel11 = TCsString(TEXT("ECC_GameTraceChannel11"), TEXT("ecc_gametracechannel11"), TEXT("gametracechannel 11"));
		const TCsString ECC_GameTraceChannel12 = TCsString(TEXT("ECC_GameTraceChannel12"), TEXT("ecc_gametracechannel12"), TEXT("gametracechannel 12"));
		const TCsString ECC_GameTraceChannel13 = TCsString(TEXT("ECC_GameTraceChannel13"), TEXT("ecc_gametracechannel13"), TEXT("gametracechannel 13"));
		const TCsString ECC_GameTraceChannel14 = TCsString(TEXT("ECC_GameTraceChannel14"), TEXT("ecc_gametracechannel14"), TEXT("gametracechannel 14"));
		const TCsString ECC_GameTraceChannel15 = TCsString(TEXT("ECC_GameTraceChannel15"), TEXT("ecc_gametracechannel15"), TEXT("gametracechannel 15"));
		const TCsString ECC_GameTraceChannel16 = TCsString(TEXT("ECC_GameTraceChannel16"), TEXT("ecc_gametracechannel16"), TEXT("gametracechannel 16"));
		const TCsString ECC_GameTraceChannel17 = TCsString(TEXT("ECC_GameTraceChannel17"), TEXT("ecc_gametracechannel17"), TEXT("gametracechannel 17"));
		const TCsString ECC_GameTraceChannel18 = TCsString(TEXT("ECC_GameTraceChannel18"), TEXT("ecc_gametracechannel18"), TEXT("gametracechannel 18"));
	}

	FORCEINLINE FString ToString(const ECollisionChannel &EType)
	{
		if (EType == ECollisionChannel::ECC_WorldStatic) { return Str::ECC_WorldStatic.Value; }
		if (EType == ECollisionChannel::ECC_WorldDynamic) { return Str::ECC_WorldDynamic.Value; }
		if (EType == ECollisionChannel::ECC_Pawn) { return Str::ECC_Pawn.Value; }
		if (EType == ECollisionChannel::ECC_Visibility) { return Str::ECC_Visibility.Value; }
		if (EType == ECollisionChannel::ECC_Camera) { return Str::ECC_Camera.Value; }
		if (EType == ECollisionChannel::ECC_PhysicsBody) { return Str::ECC_PhysicsBody.Value; }
		if (EType == ECollisionChannel::ECC_Vehicle) { return Str::ECC_Vehicle.Value; }
		if (EType == ECollisionChannel::ECC_Destructible) { return Str::ECC_Destructible.Value; }

		if (EType == ECollisionChannel::ECC_EngineTraceChannel1) { return Str::ECC_EngineTraceChannel1.Value; }
		if (EType == ECollisionChannel::ECC_EngineTraceChannel2) { return Str::ECC_EngineTraceChannel2.Value; }
		if (EType == ECollisionChannel::ECC_EngineTraceChannel3) { return Str::ECC_EngineTraceChannel3.Value; }
		if (EType == ECollisionChannel::ECC_EngineTraceChannel4) { return Str::ECC_EngineTraceChannel4.Value; }
		if (EType == ECollisionChannel::ECC_EngineTraceChannel5) { return Str::ECC_EngineTraceChannel5.Value; }
		if (EType == ECollisionChannel::ECC_EngineTraceChannel6) { return Str::ECC_EngineTraceChannel6.Value; }

		if (EType == ECollisionChannel::ECC_GameTraceChannel1) { return Str::ECC_GameTraceChannel1.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel2) { return Str::ECC_GameTraceChannel2.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel3) { return Str::ECC_GameTraceChannel3.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel4) { return Str::ECC_GameTraceChannel4.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel5) { return Str::ECC_GameTraceChannel5.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel6) { return Str::ECC_GameTraceChannel6.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel7) { return Str::ECC_GameTraceChannel7.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel8) { return Str::ECC_GameTraceChannel8.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel9) { return Str::ECC_GameTraceChannel9.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel10) { return Str::ECC_GameTraceChannel10.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel11) { return Str::ECC_GameTraceChannel11.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel12) { return Str::ECC_GameTraceChannel12.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel13) { return Str::ECC_GameTraceChannel13.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel14) { return Str::ECC_GameTraceChannel14.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel15) { return Str::ECC_GameTraceChannel15.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel16) { return Str::ECC_GameTraceChannel16.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel17) { return Str::ECC_GameTraceChannel17.Value; }
		if (EType == ECollisionChannel::ECC_GameTraceChannel18) { return Str::ECC_GameTraceChannel18.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE ECollisionChannel ToType(const FString &String)
	{
		if (String == Str::ECC_WorldStatic) { return ECollisionChannel::ECC_WorldStatic; }
		if (String == Str::ECC_WorldDynamic) { return ECollisionChannel::ECC_WorldDynamic; }
		if (String == Str::ECC_Pawn) { return ECollisionChannel::ECC_Pawn; }
		if (String == Str::ECC_Visibility) { return ECollisionChannel::ECC_Visibility; }
		if (String == Str::ECC_Camera) { return ECollisionChannel::ECC_Camera; }
		if (String == Str::ECC_PhysicsBody) { return ECollisionChannel::ECC_PhysicsBody; }
		if (String == Str::ECC_Vehicle) { return ECollisionChannel::ECC_Vehicle; }
		if (String == Str::ECC_Destructible) { return ECollisionChannel::ECC_Destructible; }

		if (String == Str::ECC_EngineTraceChannel1) { return ECollisionChannel::ECC_EngineTraceChannel1; }
		if (String == Str::ECC_EngineTraceChannel2) { return ECollisionChannel::ECC_EngineTraceChannel2; }
		if (String == Str::ECC_EngineTraceChannel3) { return ECollisionChannel::ECC_EngineTraceChannel3; }
		if (String == Str::ECC_EngineTraceChannel4) { return ECollisionChannel::ECC_EngineTraceChannel4; }
		if (String == Str::ECC_EngineTraceChannel5) { return ECollisionChannel::ECC_EngineTraceChannel5; }
		if (String == Str::ECC_EngineTraceChannel6) { return ECollisionChannel::ECC_EngineTraceChannel6; }

		if (String == Str::ECC_GameTraceChannel1) { return ECollisionChannel::ECC_GameTraceChannel1; }
		if (String == Str::ECC_GameTraceChannel2) { return ECollisionChannel::ECC_GameTraceChannel2; }
		if (String == Str::ECC_GameTraceChannel3) { return ECollisionChannel::ECC_GameTraceChannel3; }
		if (String == Str::ECC_GameTraceChannel4) { return ECollisionChannel::ECC_GameTraceChannel4; }
		if (String == Str::ECC_GameTraceChannel5) { return ECollisionChannel::ECC_GameTraceChannel5; }
		if (String == Str::ECC_GameTraceChannel6) { return ECollisionChannel::ECC_GameTraceChannel6; }
		if (String == Str::ECC_GameTraceChannel7) { return ECollisionChannel::ECC_GameTraceChannel7; }
		if (String == Str::ECC_GameTraceChannel8) { return ECollisionChannel::ECC_GameTraceChannel8; }
		if (String == Str::ECC_GameTraceChannel9) { return ECollisionChannel::ECC_GameTraceChannel9; }
		if (String == Str::ECC_GameTraceChannel10) { return ECollisionChannel::ECC_GameTraceChannel10; }
		if (String == Str::ECC_GameTraceChannel11) { return ECollisionChannel::ECC_GameTraceChannel11; }
		if (String == Str::ECC_GameTraceChannel12) { return ECollisionChannel::ECC_GameTraceChannel12; }
		if (String == Str::ECC_GameTraceChannel13) { return ECollisionChannel::ECC_GameTraceChannel13; }
		if (String == Str::ECC_GameTraceChannel14) { return ECollisionChannel::ECC_GameTraceChannel14; }
		if (String == Str::ECC_GameTraceChannel15) { return ECollisionChannel::ECC_GameTraceChannel15; }
		if (String == Str::ECC_GameTraceChannel16) { return ECollisionChannel::ECC_GameTraceChannel16; }
		if (String == Str::ECC_GameTraceChannel17) { return ECollisionChannel::ECC_GameTraceChannel17; }
		if (String == Str::ECC_GameTraceChannel18) { return ECollisionChannel::ECC_GameTraceChannel18; }
		return ECollisionChannel::ECC_MAX;
	}
}

namespace ECsCollisionResponse
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString ECR_Ignore = TCsString(TEXT("ECR_Ignore"), TEXT("ecr_ignore"), TEXT("ignore"));
		const TCsString ECR_Overlap = TCsString(TEXT("ECR_Overlap"), TEXT("ecr_overlap"), TEXT("overlap"));
		const TCsString ECR_Block = TCsString(TEXT("ECR_Block"), TEXT("ecr_block"), TEXT("block"));
	}

	FORCEINLINE FString ToString(const ECollisionResponse &EType)
	{
		if (EType == ECollisionResponse::ECR_Ignore) { return Str::ECR_Ignore.Value; }
		if (EType == ECollisionResponse::ECR_Overlap) { return Str::ECR_Overlap.Value; }
		if (EType == ECollisionResponse::ECR_Block) { return Str::ECR_Block.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE ECollisionResponse ToType(const FString &String)
	{
		if (String == Str::ECR_Ignore) { return ECollisionResponse::ECR_Ignore; }
		if (String == Str::ECR_Overlap) { return ECollisionResponse::ECR_Overlap; }
		if (String == Str::ECR_Block) { return ECollisionResponse::ECR_Block; }
		return ECollisionResponse::ECR_MAX;
	}
};

USTRUCT(BlueprintType)
struct FCsCollisionPreset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	bool bSimulationGeneratesHitEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FCsPhysicalMaterial PhysMaterialOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	bool bGenerateOverlapEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FCollisionResponseContainer CollisionResponses;

	FCsCollisionPreset()
	{
		bSimulationGeneratesHitEvents = false;
		bGenerateOverlapEvents = false;
		CollisionEnabled = ECollisionEnabled::NoCollision;
		ObjectType = ECollisionChannel::ECC_WorldStatic;
		CollisionResponses.SetAllChannels(ECR_Ignore);
	}

	FCsCollisionPreset& operator=(const FCsCollisionPreset& B)
	{
		bSimulationGeneratesHitEvents = B.bSimulationGeneratesHitEvents;
		bGenerateOverlapEvents = B.bGenerateOverlapEvents;
		PhysMaterialOverride = B.PhysMaterialOverride;
		CollisionEnabled = B.CollisionEnabled;
		ObjectType = B.ObjectType;
		CollisionResponses = B.CollisionResponses;
		return *this;
	}

	bool operator==(const FCsCollisionPreset& B) const
	{
		return bSimulationGeneratesHitEvents == B.bSimulationGeneratesHitEvents && 
			   bGenerateOverlapEvents == B.bGenerateOverlapEvents && 
			   PhysMaterialOverride == B.PhysMaterialOverride &&
			   CollisionEnabled == B.CollisionEnabled && 
			   ObjectType == B.ObjectType;
	}

	bool operator!=(const FCsCollisionPreset& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Collision

// Color
#pragma region

UENUM(BlueprintType)
namespace ECsLinearColor
{
	enum Type
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
}

namespace ECsLinearColor
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString White = TCsString(TEXT("White"), TEXT("white"));
		const TCsString Gray = TCsString(TEXT("Gray"), TEXT("gray"));
		const TCsString Black = TCsString(TEXT("Black"), TEXT("black"));
		const TCsString Transparent = TCsString(TEXT("Transparent"), TEXT("transparent"));
		const TCsString Red = TCsString(TEXT("Red"), TEXT("red"));
		const TCsString Green = TCsString(TEXT("Green"), TEXT("green"));
		const TCsString Blue = TCsString(TEXT("Blue"), TEXT("blue"));
		const TCsString Yellow = TCsString(TEXT("Yellow"), TEXT("yellow"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::White) { return Str::White.Value; }
		if (EType == Type::Gray) { return Str::Gray.Value; }
		if (EType == Type::Black) { return Str::Black.Value; }
		if (EType == Type::Transparent) { return Str::Transparent.Value; }
		if (EType == Type::Red) { return Str::Red.Value; }
		if (EType == Type::Green) { return Str::Green.Value; }
		if (EType == Type::Blue) { return Str::Blue.Value; }
		if (EType == Type::Yellow) { return Str::Yellow.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::White) { return Type::White; }
		if (String == Str::Gray) { return Type::Gray; }
		if (String == Str::Black) { return Type::Black; }
		if (String == Str::Transparent) { return Type::Transparent; }
		if (String == Str::Red) { return Type::Red; }
		if (String == Str::Green) { return Type::Green; }
		if (String == Str::Blue) { return Type::Blue; }
		if (String == Str::Yellow) { return Type::Yellow; }
		return Type::ECsLinearColor_MAX;
	}

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
typedef TEnumAsByte<ECsLinearColor::Type> TCsLinearColor;

UENUM(BlueprintType)
namespace ECsColor
{
	enum Type
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
}

namespace ECsColor
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString White = TCsString(TEXT("White"), TEXT("white"));
		const TCsString Black = TCsString(TEXT("Black"), TEXT("black"));
		const TCsString Transparent = TCsString(TEXT("Transparent"), TEXT("transparent"));
		const TCsString Red = TCsString(TEXT("Red"), TEXT("red"));
		const TCsString Green = TCsString(TEXT("Green"), TEXT("green"));
		const TCsString Blue = TCsString(TEXT("Blue"), TEXT("blue"));
		const TCsString Yellow = TCsString(TEXT("Yellow"), TEXT("yellow"));
		const TCsString Cyan = TCsString(TEXT("Cyan"), TEXT("cyan"));
		const TCsString Magenta = TCsString(TEXT("Magenta"), TEXT("magenta"));
		const TCsString Orange = TCsString(TEXT("Orange"), TEXT("orange"));
		const TCsString Purple = TCsString(TEXT("Purple"), TEXT("purple"));
		const TCsString Turquoise = TCsString(TEXT("Turquoise"), TEXT("turquoise"));
		const TCsString Silver = TCsString(TEXT("Silver"), TEXT("silver"));
		const TCsString Emerald = TCsString(TEXT("Emerald"), TEXT("emerald"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::White) { return Str::White.Value; }
		if (EType == Type::Black) { return Str::Black.Value; }
		if (EType == Type::Transparent) { return Str::Transparent.Value; }
		if (EType == Type::Red) { return Str::Red.Value; }
		if (EType == Type::Green) { return Str::Green.Value; }
		if (EType == Type::Blue) { return Str::Blue.Value; }
		if (EType == Type::Yellow) { return Str::Yellow.Value; }
		if (EType == Type::Cyan) { return Str::Cyan.Value; }
		if (EType == Type::Magenta) { return Str::Magenta.Value; }
		if (EType == Type::Orange) { return Str::Orange.Value; }
		if (EType == Type::Purple) { return Str::Purple.Value; }
		if (EType == Type::Turquoise) { return Str::Turquoise.Value; }
		if (EType == Type::Silver) { return Str::Silver.Value; }
		if (EType == Type::Emerald) { return Str::Emerald.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::White) { return Type::White; }
		if (String == Str::Black) { return Type::Black; }
		if (String == Str::Transparent) { return Type::Transparent; }
		if (String == Str::Red) { return Type::Red; }
		if (String == Str::Green) { return Type::Green; }
		if (String == Str::Blue) { return Type::Blue; }
		if (String == Str::Yellow) { return Type::Yellow; }
		if (String == Str::Cyan) { return Type::Cyan; }
		if (String == Str::Magenta) { return Type::Magenta; }
		if (String == Str::Orange) { return Type::Orange; }
		if (String == Str::Purple) { return Type::Purple; }
		if (String == Str::Turquoise) { return Type::Turquoise; }
		if (String == Str::Silver) { return Type::Silver; }
		if (String == Str::Emerald) { return Type::Emerald; }
		return Type::ECsColor_MAX;
	}

	FORCEINLINE FColor ToColor(const Type &EType)
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
typedef TEnumAsByte<ECsColor::Type> TCsColor;

#pragma endregion Color