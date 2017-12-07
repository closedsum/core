// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/pt.h"
#include "Engine.h"
#include "Materials/MaterialInstanceConstant.h"
#include "PhysicsEngine/PhysicsAsset.h"

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

// String
#pragma region

namespace ECsCachedString
{
	namespace Str
	{
		const FString Empty = TEXT("");
		const FString None = TEXT("None");
	}
}

#pragma endregion String

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

// SurfaceTypeToString
typedef FString(*TCsSurfaceTypeToString)(const TCsSurfaceType&);
// StringToSurfaceType
typedef TCsSurfaceType(*TCsStringToSurfaceType)(const FString&);
// PhysicalSurfaceToSurfaceType
typedef TCsSurfaceType(*TCsPhysicalSurfaceToSurfaceType)(const TEnumAsByte<EPhysicalSurface>&);

#define CS_DECLARE_SURFACE_TYPE_FUNCTIONS	TCsSurfaceTypeToString SurfaceTypeToString; \
											TCsStringToSurfaceType StringToSurfaceType; \
											TCsPhysicalSurfaceToSurfaceType PhysicalSurfaceToSurfaceType;

#define CS_DEFINE_SURFACE_TYPE_FUNCTIONS SurfaceTypeToString = &ECsSurfaceType::ToString; \
										 StringToSurfaceType = (TCsSurfaceType (*)(const FString&))(&ECsSurfaceType::ToType); \
										 PhysicalSurfaceToSurfaceType = (TCsSurfaceType (*)(const TEnumAsByte<EPhysicalSurface>&))(&ECsSurfaceType::ToType);

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

// Pooled Objects
#pragma region

UENUM(BlueprintType)
namespace ECsPooledObjectState
{
	enum Type
	{
		WarmUp						UMETA(DisplayName = "Warm Up"),
		Active						UMETA(DisplayName = "Active"),
		Inactive					UMETA(DisplayName = "Inactive"),
		ECsPooledObjectState_MAX	UMETA(Hidden),
	};
}

namespace ECsPooledObjectState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString WarmUp = TCsString(TEXT("WarmUp"), TEXT("warmup"), TEXT("warm up"));
		const TCsString Active = TCsString(TEXT("Active"), TEXT("active"), TEXT("active"));
		const TCsString Inactive = TCsString(TEXT("Inactive"), TEXT("inactive"), TEXT("inactive"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::WarmUp) { return Str::WarmUp.Value; }
		if (EType == Type::Active) { return Str::Active.Value; }
		if (EType == Type::Inactive) { return Str::Inactive.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::WarmUp) { return Type::WarmUp; }
		if (String == Str::Active) { return Type::Active; }
		if (String == Str::Inactive) { return Type::Inactive; }
		return Type::ECsPooledObjectState_MAX;
	}
}

#define ECS_POOLED_OBJECT_STATE_MAX (uint8)ECsPooledObjectState::ECsPooledObjectState_MAX
typedef TEnumAsByte<ECsPooledObjectState::Type> TCsPooledObjectState;

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
	TEnumAsByte<ECsPooledObjectState::Type> State;

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
	float WarmUpTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool UseLifeTime;
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
		State = ECsPooledObjectState::Inactive;

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
		WarmUpTime = 0.0f;
		UseLifeTime = false;
		LifeTime = 0.0f;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		Frame_Script = 0;
	}

	void SetLifeTime(const float &InLifeTime)
	{
		LifeTime	= InLifeTime;
		UseLifeTime = LifeTime > 0.0f;
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

// Attach / Detach
#pragma region

UENUM(BlueprintType)
namespace ECsAttachmentTransformRules
{
	enum Type
	{
		KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
		KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
		SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap To Target Not Including Scale"),
		SnapToTargetIncludingScale		UMETA(DisplayName = "Snap To Target Including Scale"),
		ECsAttachmentTransformRules_MAX	UMETA(Hidden),
	};
}

namespace ECsAttachmentTransformRules
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString KeepRelativeTransform = TCsString(TEXT("KeepRelativeTransform"), TEXT("keeprelativetransform"), TEXT("keep relative transform"));
		const TCsString KeepWorldTransform = TCsString(TEXT("KeepWorldTransform"), TEXT("keepworldtransform"), TEXT("keep world transform"));
		const TCsString SnapToTargetNotIncludingScale = TCsString(TEXT("SnapToTargetNotIncludingScale"), TEXT("snaptotargetnotincludingscale"), TEXT("snap to target not including scale"));
		const TCsString SnapToTargetIncludingScale = TCsString(TEXT("SnapToTargetIncludingScale"), TEXT("snaptotargetincludingscale"), TEXT("snap to target including scale"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::KeepRelativeTransform) { return Str::KeepRelativeTransform.Value; }
		if (EType == Type::KeepWorldTransform) { return Str::KeepWorldTransform.Value; }
		if (EType == Type::SnapToTargetNotIncludingScale) { return Str::SnapToTargetNotIncludingScale.Value; }
		if (EType == Type::SnapToTargetIncludingScale) { return Str::SnapToTargetIncludingScale.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::KeepRelativeTransform) { return Type::KeepRelativeTransform; }
		if (String == Str::KeepWorldTransform) { return Type::KeepWorldTransform; }
		if (String == Str::SnapToTargetNotIncludingScale) { return Type::SnapToTargetNotIncludingScale; }
		if (String == Str::SnapToTargetIncludingScale) { return Type::SnapToTargetIncludingScale; }
		return Type::ECsAttachmentTransformRules_MAX;
	}

	FORCEINLINE FAttachmentTransformRules ToRule(const Type &EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FAttachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FAttachmentTransformRules::KeepWorldTransform; }
		if (EType == Type::SnapToTargetNotIncludingScale) { return FAttachmentTransformRules::SnapToTargetNotIncludingScale; }
		if (EType == Type::SnapToTargetIncludingScale) { return FAttachmentTransformRules::SnapToTargetIncludingScale; }
		return FAttachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_ATTACHMENT_TRANSFORM_RULES_MAX (uint8)ECsAttachmentTransformRules::ECsAttachmentTransformRules_MAX
typedef TEnumAsByte<ECsAttachmentTransformRules::Type> TCsAttachmentTransformRules;

UENUM(BlueprintType)
namespace ECsDetachmentTransformRules
{
	enum Type
	{
		KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
		KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
		ECsDetachmentTransformRules_MAX	UMETA(Hidden),
	};
}

namespace ECsDetachmentTransformRules
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString KeepRelativeTransform = TCsString(TEXT("KeepRelativeTransform"), TEXT("keeprelativetransform"), TEXT("keep relative transform"));
		const TCsString KeepWorldTransform = TCsString(TEXT("KeepWorldTransform"), TEXT("keepworldtransform"), TEXT("keep world transform"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::KeepRelativeTransform) { return Str::KeepRelativeTransform.Value; }
		if (EType == Type::KeepWorldTransform) { return Str::KeepWorldTransform.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::KeepRelativeTransform) { return Type::KeepRelativeTransform; }
		if (String == Str::KeepWorldTransform) { return Type::KeepWorldTransform; }
		return Type::ECsDetachmentTransformRules_MAX;
	}

	FORCEINLINE FDetachmentTransformRules ToRule(const Type &EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FDetachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FDetachmentTransformRules::KeepWorldTransform; }
		return FDetachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_DETACHMENT_TRANSFORM_RULES_MAX (uint8)ECsDetachmentTransformRules::ECsDetachmentTransformRules_MAX
typedef TEnumAsByte<ECsDetachmentTransformRules::Type> TCsDetachmentTransformRules;

#pragma endregion Attach / Detach