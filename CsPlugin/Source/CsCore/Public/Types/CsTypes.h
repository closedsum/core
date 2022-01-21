// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Coroutine/pt.h"
#include "Engine.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_View.h"

#include "CsTypes.generated.h"

#define CS_ACTOR_SMALLEST_SCALE 0.001f
#define CS_VECTOR_ONE FVector(1.0f)

#define CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID 255
#define CS_INVALID_AI_PLAYER_STATE_UNIQUE_MAPPING_ID 255

// Level
#pragma region

	// LevelState
#pragma region

UENUM(BlueprintType)
enum class ECsLevelState : uint8
{
	None				UMETA(DisplayName = "None"),
	Loaded				UMETA(DisplayName = "Loaded"),
	BeginTransition		UMETA(DisplayName = "Begin Transition"),
	InTransition		UMETA(DisplayName = "In Transition"),
	ECsLevelState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsLevelState : public TCsEnumMap<ECsLevelState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsLevelState, ECsLevelState)
};

namespace NCsLevelState
{
	typedef ECsLevelState Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Loaded;
		extern CSCORE_API const Type BeginTransition;
		extern CSCORE_API const Type InTransition;
		extern CSCORE_API const Type ECsLevelState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_LEVEL_STATE (uint8)ECsLevelState::ECsLevelState_MAX

#pragma endregion LevelState

#pragma endregion Level

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

// Static Mesh
#pragma region

class UStaticMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpvStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh1P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh3P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh3P_Low;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> MeshVR;

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
	FCsFpvStaticMesh() :
		Mesh1P_LoadFlags(0),
		Mesh3P_LoadFlags(0),
		Mesh3P_Low_LoadFlags(0),
		MeshVR_LoadFlags(0),
		Mesh1P_Internal(nullptr),
		Mesh3P_Internal(nullptr),
		Mesh3P_Low_Internal(nullptr),
		MeshVR_Internal(nullptr)
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

	FORCEINLINE FCsFpvStaticMesh& operator=(const FCsFpvStaticMesh& B)
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

	FORCEINLINE bool operator==(const FCsFpvStaticMesh& B) const
	{
		return Mesh1P == B.Mesh1P && Mesh1P_LoadFlags == B.Mesh1P_LoadFlags && Mesh1P_Internal == B.Mesh1P_Internal &&
			   Mesh3P == B.Mesh3P && Mesh3P_LoadFlags == B.Mesh3P_LoadFlags && Mesh3P_Internal == B.Mesh3P_Internal &&
			   Mesh3P_Low == B.Mesh3P_Low && Mesh3P_Low_LoadFlags == B.Mesh3P_Low_LoadFlags && Mesh3P_Low_Internal == B.Mesh3P_Low_Internal &&
			   MeshVR == B.MeshVR && MeshVR_LoadFlags == B.MeshVR_LoadFlags && MeshVR_Internal == B.MeshVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpvStaticMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UStaticMesh* Get(const ECsViewType& ViewType, const bool &IsLow = false) const
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
struct CSCORE_API FCsTArrayStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UStaticMesh>> Meshes;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Meshes_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UStaticMesh*> Meshes_Internal;

public:
	FCsTArrayStaticMesh() :
		Meshes_LoadFlags(0)
	{
		CS_SET_BLUEPRINT_BITFLAG(Meshes_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsTArrayStaticMesh& operator=(const FCsTArrayStaticMesh& B)
	{
		Meshes.Reset();

		const int32 Count = B.Meshes.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Meshes.Add(B.Meshes[I]);
		}
		Meshes_LoadFlags = B.Meshes_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArrayStaticMesh& B) const
	{
		int32 Count  = Meshes.Num();
		int32 CountB = B.Meshes.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Meshes[I] != B.Meshes[I])
				return false;
		}

		Count  = Meshes_Internal.Num();
		CountB = B.Meshes_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Meshes_Internal[I] != B.Meshes_Internal[I])
				return false;
		}
		return Meshes_LoadFlags == B.Meshes_LoadFlags;
	}

	FORCEINLINE bool operator!=(const FCsTArrayStaticMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<class UStaticMesh*>* Get()
	{
		return &Meshes_Internal;
	}

	FORCEINLINE class UStaticMesh* Get(const int32 Index)
	{
		return Index < Meshes_Internal.Num() ? Meshes_Internal[Index] : nullptr;
	}
};

#pragma endregion Static Mesh

// Skeletal Mesh
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh1P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh3P;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh3P_Low;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> MeshVR;

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
	FCsFpsSkeletalMesh() :
		Mesh1P_LoadFlags(0),
		Mesh3P_LoadFlags(0),
		Mesh3P_Low_LoadFlags(0),
		MeshVR_LoadFlags(0),
		Mesh1P_Internal(nullptr),
		Mesh3P_Internal(nullptr),
		Mesh3P_Low_Internal(nullptr),
		MeshVR_Internal(nullptr)
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

	FORCEINLINE FCsFpsSkeletalMesh& operator=(const FCsFpsSkeletalMesh& B)
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

	FORCEINLINE bool operator==(const FCsFpsSkeletalMesh& B) const
	{
		return Mesh1P == B.Mesh1P && Mesh1P_LoadFlags == B.Mesh1P_LoadFlags && Mesh1P_Internal == B.Mesh1P_Internal &&
			   Mesh3P == B.Mesh3P && Mesh3P_LoadFlags == B.Mesh3P_LoadFlags && Mesh3P_Internal == B.Mesh3P_Internal &&
			   Mesh3P_Low == B.Mesh3P_Low && Mesh3P_Low_LoadFlags == B.Mesh3P_Low_LoadFlags && Mesh3P_Low_Internal == B.Mesh3P_Low_Internal &&
			   MeshVR == B.MeshVR && MeshVR_LoadFlags == B.MeshVR_LoadFlags && MeshVR_Internal == B.MeshVR_Internal;
	}

	FORCEINLINE bool operator!=(const FCsFpsSkeletalMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE USkeletalMesh* Get(const ECsViewType& ViewType, const bool &IsLow = false) const
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
struct CSCORE_API FCsTArraySkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class USkeletalMesh>> Meshes;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Meshes_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class USkeletalMesh*> Meshes_Internal;

public:
	FCsTArraySkeletalMesh() :
		Meshes_LoadFlags(0)
	{
		CS_SET_BLUEPRINT_BITFLAG(Meshes_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsTArraySkeletalMesh& operator=(const FCsTArraySkeletalMesh& B)
	{
		Meshes.Reset();

		const int32 Count = B.Meshes.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Meshes.Add(B.Meshes[I]);
		}
		Meshes_LoadFlags = B.Meshes_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArraySkeletalMesh& B) const
	{
		int32 Count = Meshes.Num();
		int32 CountB = B.Meshes.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Meshes[I] != B.Meshes[I])
				return false;
		}

		Count = Meshes_Internal.Num();
		CountB = B.Meshes_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Meshes_Internal[I] != B.Meshes_Internal[I])
				return false;
		}
		return Meshes_LoadFlags == B.Meshes_LoadFlags;
	}

	FORCEINLINE bool operator!=(const FCsTArraySkeletalMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<class USkeletalMesh*>* Get()
	{
		return &Meshes_Internal;
	}

	FORCEINLINE class USkeletalMesh* Get(const int32 Index)
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
typedef const FString&(*TCsSurfaceTypeToString)(const TCsSurfaceType&);
// StringToSurfaceType
typedef TCsSurfaceType(*TCsStringToSurfaceType)(const FString&);
// PhysicalSurfaceToSurfaceType
typedef TCsSurfaceType(*TCsPhysicalSurfaceToSurfaceType)(const TEnumAsByte<EPhysicalSurface>&);

#define CS_DECLARE_SURFACE_TYPE	TCsSurfaceType SurfaceType_MAX; \
								uint8 SURFACE_TYPE_MAX; \
								TCsSurfaceTypeToString SurfaceTypeToString; \
								TCsStringToSurfaceType StringToSurfaceType; \
								TCsPhysicalSurfaceToSurfaceType PhysicalSurfaceToSurfaceType;

#define CS_DEFINE_SURFACE_TYPE	SurfaceType_MAX = ECsSurfaceType::ECsSurfaceType_MAX; \
								SURFACE_TYPE_MAX = (uint8)SurfaceType_MAX; \
								SurfaceTypeToString = &ECsSurfaceType::ToString; \
								StringToSurfaceType = (TCsSurfaceType (*)(const FString&))(&ECsSurfaceType::ToType); \
								PhysicalSurfaceToSurfaceType = (TCsSurfaceType (*)(const TEnumAsByte<EPhysicalSurface>&))(&ECsSurfaceType::ToType);

#define CS_DECLARE_SURFACE_TYPE_FUNCTIONS	TCsSurfaceTypeToString SurfaceTypeToString; \
											TCsStringToSurfaceType StringToSurfaceType; \
											TCsPhysicalSurfaceToSurfaceType PhysicalSurfaceToSurfaceType;

#define CS_DEFINE_SURFACE_TYPE_FUNCTIONS SurfaceTypeToString = &ECsSurfaceType::ToString; \
										 StringToSurfaceType = (TCsSurfaceType (*)(const FString&))(&ECsSurfaceType::ToType); \
										 PhysicalSurfaceToSurfaceType = (TCsSurfaceType (*)(const TEnumAsByte<EPhysicalSurface>&))(&ECsSurfaceType::ToType);

USTRUCT(BlueprintType)
struct CSCORE_API FECsSurfaceType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSurfaceType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSurfaceType)

struct CSCORE_API EMCsSurfaceType : public TCsEnumStructMap<FECsSurfaceType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsSurfaceType)
};

#pragma endregion Surface

// Blueprint
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Blueprint")
	TSoftObjectPtr<class UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
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

	UPROPERTY(EditAnywhere, Category = "Blueprint")
	TArray<TSoftObjectPtr<class UBlueprint>> Blueprints;

	UPROPERTY(EditAnywhere, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
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

// VR
#pragma region

	// HMDDeviceType
#pragma region

UENUM(BlueprintType)
enum class ECsHMDDeviceType : uint8
{
	DT_OculusRift			UMETA(DisplayName = "Oculus Rift"),
	DT_Morpheus				UMETA(DisplayName = "Playstaton VR"),
	DT_ES2GenericStereoMesh UMETA(DisplayName = "ES2 Generic"),
	DT_SteamVR				UMETA(DisplayName = "Vive"),
	DT_GearVR				UMETA(DisplayName = "Gear VR"),
	DT_GoogleVR				UMETA(DisplayName = "Google VR"),
	ECsHMDDeviceType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsHMDDeviceType : public TCsEnumMap<ECsHMDDeviceType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsHMDDeviceType, ECsHMDDeviceType)
};

namespace NCsHMDDeviceType
{
	typedef ECsHMDDeviceType Type;

	namespace Ref
	{
		extern CSCORE_API const Type DT_OculusRift;
		extern CSCORE_API const Type DT_Morpheus;
		extern CSCORE_API const Type DT_ES2GenericStereoMesh;
		extern CSCORE_API const Type DT_SteamVR;
		extern CSCORE_API const Type DT_GearVR;
		extern CSCORE_API const Type DT_GoogleVR;
		extern CSCORE_API const Type ECsHMDDeviceType_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	/*
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
	*/
}

#pragma endregion HMDDeviceType

#pragma endregion VR

// Replication
#pragma region

#define CS_SERVER_TO_CLIENT_SEND_FREQUENCY 0.01666666667

#pragma endregion Replication

// Motion Controller
#pragma region

#pragma endregion Motion Controller

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

// Player Data
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsPlayerData_Inventory_Slot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FCsUint8MatrixCoordinate Position; // 16 bits

	UPROPERTY()
	TArray<FGuid> Contents; // N * 64 bits

	FCsPlayerData_Inventory_Slot() {}
	~FCsPlayerData_Inventory_Slot() {}

	FORCEINLINE FCsPlayerData_Inventory_Slot& operator=(const FCsPlayerData_Inventory_Slot& B)
	{
		Position = B.Position;

		Contents.Reset();

		for (const FGuid& Guid : B.Contents)
		{
			Contents.Add(Guid);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPlayerData_Inventory_Slot& B) const
	{
		if (Position != B.Position) { return false; }

		if (Contents.Num() != B.Contents.Num())
			return false;

		const int32 Count = Contents.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Contents[I] != B.Contents[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsPlayerData_Inventory_Slot& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 16					// Position
			+ Contents.Num() * 8;	// Contents
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	FORCEINLINE bool Contains(const FGuid &Id)
	{
		for (FGuid& Guid : Contents)
		{
			if (Guid == Id)
				return true;
		}
		return false;
	}

	FORCEINLINE void Add(const FGuid &Id)
	{
		Contents.Add(Id);
	}

	FORCEINLINE void Remove(const FGuid &Id)
	{
		const int32 Count = Contents.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (Contents[I] == Id)
			{
				Contents.RemoveAt(I);
				break;
			}
		}
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsPlayerData_Inventory_Bag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FCsUint8MatrixDimension Dimension; // 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCsPlayerData_Inventory_Slot> Slots; // N * Slot[I].GetBits();

	FCsPlayerData_Inventory_Bag() {}
	~FCsPlayerData_Inventory_Bag() {}

	FORCEINLINE FCsPlayerData_Inventory_Bag& operator=(const FCsPlayerData_Inventory_Bag& B)
	{
		Dimension = B.Dimension;

		Slots.Reset();

		const int32 Count = B.Slots.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Slots.AddDefaulted();
			Slots[I] = B.Slots[I];
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPlayerData_Inventory_Bag& B) const
	{
		if (Dimension != B.Dimension)
			return false;
		if (Slots.Num() != B.Slots.Num())
			return false;

		const int32 Count = Slots.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Slots[I] != B.Slots[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsPlayerData_Inventory_Bag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE uint32 GetBits() const
	{
		uint32 Bits = Dimension.GetBits(); // Dimension

		const int32 Count = Slots.Num();  // Slot

		for (int32 I = 0; I < Count; ++I)
		{
			Bits += Slots[I].GetBits();
		}
		return Bits;
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	FORCEINLINE int32 GetSlotIndexForItem(const FGuid &Id)
	{
		const int32 Count = Slots.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Slots[I].Contains(Id))
				return I;
		}
		return INDEX_NONE;
	}

	FORCEINLINE int32 GetFirstOpenSlotIndex()
	{
		const int32 Count = Slots.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Slots[I].Contents.Num() == CS_EMPTY)
				return I;
		}
		return INDEX_NONE;
	}
};

#pragma endregion Player Data