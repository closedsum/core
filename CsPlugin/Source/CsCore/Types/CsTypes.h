// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
struct CSCORE_API FCsStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient)
	UStaticMesh* Mesh_Internal;

public:
	FCsStaticMesh() :
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UStaticMesh* Get() const
	{
		return Mesh_Internal;
	}

	FORCEINLINE FCsStaticMesh& operator=(const FCsStaticMesh& B)
	{
		Mesh = B.Mesh;
		Mesh_LoadFlags = B.Mesh_LoadFlags;
		Mesh_Internal = B.Mesh_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsStaticMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	FORCEINLINE bool operator!=(const FCsStaticMesh& B) const
	{
		return !(*this == B);
	}
};

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

class USkeletalMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient)
	USkeletalMesh* Mesh_Internal;

public:
	FCsSkeletalMesh() :
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Mesh_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE bool operator==(const FCsSkeletalMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	FORCEINLINE bool operator!=(const FCsSkeletalMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE USkeletalMesh* Get() const
	{
		return Mesh_Internal;
	}
};

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

// Materials
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TSoftObjectPtr<class UMaterialInstance> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstance* Material_Internal;

public:
	FCsMaterialInstance() :
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UMaterialInstance* Get() const
	{
		return Material_Internal;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TSoftObjectPtr<class UMaterialInstanceConstant> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UMaterialInstanceConstant* Material_Internal;

public:
	FCsMaterialInstanceConstant() :
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE UMaterialInstanceConstant* Get() const
	{
		return Material_Internal;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UMaterialInstanceConstant>> Materials;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

private:
	UPROPERTY(Transient)
	TArray<class UMaterialInstanceConstant*> Materials_Internal;

public:
	FCsTArrayMaterialInstanceConstant() :
		Materials_LoadFlags(0)
	{
		CS_SET_BLUEPRINT_BITFLAG(Materials_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsTArrayMaterialInstanceConstant& operator=(const FCsTArrayMaterialInstanceConstant& B)
	{
		Materials.Reset();

		const int32 Count = B.Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Materials.Add(B.Materials[I]);
		}
		Materials_LoadFlags = B.Materials_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArrayMaterialInstanceConstant& B) const
	{
		int32 Count  = Materials.Num();
		int32 CountB = B.Materials.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Materials[I] != B.Materials[I])
				return false;
		}

		Count  = Materials_Internal.Num();
		CountB = B.Materials_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Materials_Internal[I] != B.Materials_Internal[I])
				return false;
		}
		return Materials_LoadFlags == B.Materials_LoadFlags;
	}

	FORCEINLINE bool operator!=(const FCsTArrayMaterialInstanceConstant& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<UMaterialInstanceConstant*>* Get()
	{
		return &Materials_Internal;
	}

	FORCEINLINE class UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < Materials_Internal.Num() ? Materials_Internal[Index] : NULL;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UMaterialInstanceConstant>> Materials1P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UMaterialInstanceConstant>> Materials3P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UMaterialInstanceConstant>> Materials3P_Low;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<class UMaterialInstanceConstant>> MaterialsVR;

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
	FCsFpsTArrayMaterialInstanceConstant() :
		Materials1P_LoadFlags(0),
		Materials3P_LoadFlags(0),
		Materials3P_Low_LoadFlags(0),
		MaterialsVR_LoadFlags(0)
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

	FORCEINLINE FCsFpsTArrayMaterialInstanceConstant& operator=(const FCsFpsTArrayMaterialInstanceConstant& B)
	{
		// 1P
		Materials1P.Reset();

		int32 Count = B.Materials1P.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Materials1P.Add(B.Materials1P[I]);
		}
		Materials1P_LoadFlags = B.Materials1P_LoadFlags;
		// 3P
		Materials3P.Reset();

		Count = B.Materials3P.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Materials3P.Add(B.Materials3P[I]);
		}
		Materials3P_LoadFlags = B.Materials3P_LoadFlags;
		// 3P Low
		Materials3P_Low.Reset();

		Count = B.Materials3P_Low.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Materials3P_Low.Add(B.Materials3P_Low[I]);
		}
		Materials3P_Low_LoadFlags = B.Materials3P_Low_LoadFlags;
		// VR
		MaterialsVR.Reset();

		Count = B.MaterialsVR.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			MaterialsVR.Add(B.MaterialsVR[I]);
		}
		MaterialsVR_LoadFlags = B.MaterialsVR_LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsFpsTArrayMaterialInstanceConstant& B) const
	{
		// 1P
		int32 Count  = Materials1P.Num();
		int32 CountB = B.Materials1P.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (Materials1P[I] != B.Materials1P[I])
				return false;
		}

		Count  = Materials1P_Internal.Num();
		CountB = B.Materials1P_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
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

		for (int32 I = 0; I < Count; ++I)
		{
			if (Materials3P[I] != B.Materials3P[I])
				return false;
		}

		Count  = Materials3P_Internal.Num();
		CountB = B.Materials3P_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
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

		for (int32 I = 0; I < Count; ++I)
		{
			if (Materials3P_Low[I] != B.Materials3P_Low[I])
				return false;
		}

		Count  = Materials3P_Low_Internal.Num();
		CountB = B.Materials3P_Low_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
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

		for (int32 I = 0; I < Count; ++I)
		{
			if (MaterialsVR[I] != B.MaterialsVR[I])
				return false;
		}

		Count  = MaterialsVR_Internal.Num();
		CountB = B.MaterialsVR_Internal.Num();

		if (Count != CountB)
			return false;

		for (int32 I = 0; I < Count; ++I)
		{
			if (MaterialsVR_Internal[I] != B.MaterialsVR_Internal[I])
				return false;
		}

		if (MaterialsVR_LoadFlags != B.MaterialsVR_LoadFlags)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsFpsTArrayMaterialInstanceConstant& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE TArray<UMaterialInstanceConstant*>* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return &Materials1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? &Materials3P_Low_Internal : &Materials3P_Internal;
		if (ViewType == ECsViewType::VR)
			return &MaterialsVR_Internal;
		return &Materials3P_Internal;
	}

	FORCEINLINE class UMaterialInstanceConstant* Get(const ECsViewType& ViewType, const int32 &Index, const bool &IsLow = false)
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
struct CSCORE_API FCsPhysicalMaterial
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TSoftObjectPtr<class UPhysicalMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

private:
	UPROPERTY(Transient)
	class UPhysicalMaterial* Material_Internal;

public:
	FCsPhysicalMaterial() :
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Material_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE bool operator==(const FCsPhysicalMaterial& B) const
	{
		return Material == B.Material && B.Material_LoadFlags == B.Material_LoadFlags && Material_Internal == B.Material_Internal;
	}

	FORCEINLINE bool operator!=(const FCsPhysicalMaterial& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UPhysicalMaterial* Get() const
	{
		return Material_Internal;
	}
};

#pragma endregion Materials

// Physics Asset
#pragma region

USTRUCT()
struct CSCORE_API FCsPhysicsAsset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Physics")
	TSoftObjectPtr<UPhysicsAsset> Physics;

	UPROPERTY(EditAnywhere, Category = "Physics", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Physics_LoadFlags;

private:
	UPROPERTY(Transient)
	class UPhysicsAsset* Physics_Internal;

public:
	FCsPhysicsAsset() :
		Physics_LoadFlags(0),
		Physics_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Physics_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE FCsPhysicsAsset& operator=(const FCsPhysicsAsset& B)
	{
		Physics = B.Physics;
		Physics_LoadFlags = B.Physics_LoadFlags;
		Physics_Internal = B.Physics_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPhysicsAsset& B) const
	{
		return Physics == B.Physics && Physics_LoadFlags == B.Physics_LoadFlags && Physics_Internal == B.Physics_Internal;
	}

	FORCEINLINE bool operator!=(const FCsPhysicsAsset& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UPhysicsAsset* Get() const
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
struct CSCORE_API FCsPhysicsPreset
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

	FORCEINLINE FCsPhysicsPreset& operator=(const FCsPhysicsPreset& B)
	{
		bSimulatePhysics = B.bSimulatePhysics;
		OverrideMassInKg = B.OverrideMassInKg;
		MassInKg = B.MassInKg;
		LinearDamping = B.LinearDamping;
		AngularDamping = B.AngularDamping;
		bEnableGravity = B.bEnableGravity;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPhysicsPreset& B) const
	{
		return bSimulatePhysics == B.bSimulatePhysics &&
			   OverrideMassInKg == B.OverrideMassInKg &&
			   MassInKg == B.MassInKg &&
			   LinearDamping == B.LinearDamping &&
			   AngularDamping == B.AngularDamping &&
			   bEnableGravity == B.bEnableGravity;
	}

	FORCEINLINE bool operator!=(const FCsPhysicsPreset& B) const
	{
		return !(*this == B);
	}
};

	// PhysicsImpulseType
#pragma region

UENUM(BlueprintType)
enum class ECsPhysicsImpulseType : uint8
{
	AddForce					UMETA(DisplayName = "Add Force"),
	AddForceAtPosition			UMETA(DisplayName = "Add Force At Position"),
	AddTorque					UMETA(DisplayName = "Add Torque"),
	AddAngularImpulse			UMETA(DisplayName = "Add Angular Impulse"),
	AddImpulse					UMETA(DisplayName = "Add Impulse"),
	AddImpulseAtPosition		UMETA(DisplayName = "Add Impulse At Position"),
	ECsPhysicsImpulseType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPhysicsImpulseType : public TCsEnumMap<ECsPhysicsImpulseType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPhysicsImpulseType, ECsPhysicsImpulseType)
};

namespace NCsPhysicsImpulseType
{
	typedef ECsPhysicsImpulseType Type;

	namespace Ref
	{
		extern CSCORE_API const Type AddForce;
		extern CSCORE_API const Type AddForceAtPosition;
		extern CSCORE_API const Type AddTorque;
		extern CSCORE_API const Type AddAngularImpulse;
		extern CSCORE_API const Type AddImpulse;
		extern CSCORE_API const Type AddImpulseAtPosition;
		extern CSCORE_API const Type ECsPhysicsImpulseType_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_PHYSICS_IMPULSE_TYPE_MAX (uint8)ECsPhysicsImpulseType::ECsPhysicsImpulseType_MAX

#pragma endregion ECsPhysicsImpulseType

USTRUCT(BlueprintType)
struct CSCORE_API FCsPhysicsImpulse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	ECsPhysicsImpulseType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	FCsOptionalRotatorInterval ImpulseRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float ImpulseMagnitude;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	FVector Impulse;

	/** Used in AddForceAtPosition and AddImpulseAtPosition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	FCsOptionalVectorInterval Position;
	/** Used in AddForce, AddForceAtPosition, and AddTorque */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bAllowSubstepping;
	/** Used in AddForce and AddTorque */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bAccelChange;
	/** Used in AddAngularImpulse and AddImpulse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bVelChange;
	/** Used in AddForceAtPosition */
	bool bIsLocalForce;

	FCsPhysicsImpulse() :
		Type(ECsPhysicsImpulseType::ECsPhysicsImpulseType_MAX)
	{
		ImpulseRotation.Reset();
		ImpulseMagnitude = 0.0f;
		Impulse = FVector::ZeroVector;
		Position.Reset();
		bAllowSubstepping = true;
		bAccelChange = false;
		bVelChange = false;
		bIsLocalForce = false;
	}
	~FCsPhysicsImpulse(){}

	FORCEINLINE FCsPhysicsImpulse& operator=(const FCsPhysicsImpulse& B)
	{
		Type = B.Type;
		ImpulseRotation = B.ImpulseRotation;
		ImpulseMagnitude = B.ImpulseMagnitude;
		Impulse = Impulse;
		Position = B.Position;
		bAllowSubstepping = B.bAllowSubstepping;
		bAccelChange = B.bAccelChange;
		bVelChange = B.bVelChange;
		bIsLocalForce = B.bIsLocalForce;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPhysicsImpulse& B) const
	{
		return	Type == B.Type &&
				ImpulseRotation == B.ImpulseRotation &&
				ImpulseMagnitude == B.ImpulseMagnitude &&
				Impulse == B.Impulse &&
				Position == B.Position &&
				bAllowSubstepping == B.bAllowSubstepping &&
				bAccelChange == B.bAccelChange &&
				bVelChange == B.bVelChange &&
				bIsLocalForce == B.bIsLocalForce;
	}

	FORCEINLINE bool operator!=(const FCsPhysicsImpulse& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Seed()
	{
		ImpulseRotation.Seed();
		Impulse = ImpulseMagnitude * ImpulseRotation.Get().Vector();
		Position.Seed();
	}
};

// PostEditChangeProperty FCsPhysicsImpulse
#define CS_PECP_FCS_PHYSICS_IMPULSE(e, PropertyName, MemberName)	if (UStructProperty* StructProperty = Cast<UStructProperty>(e.MemberProperty)) \
																	{ \
																		if (StructProperty->Struct == FCsPhysicsImpulse::StaticStruct()) \
																		{ \
																			if (PropertyName == GET_MEMBER_NAME_CHECKED(FRotator, Roll) || \
																				PropertyName == GET_MEMBER_NAME_CHECKED(FRotator, Pitch) || \
																				PropertyName == GET_MEMBER_NAME_CHECKED(FRotator, Yaw)) \
																				{ \
																					MemberName.Impulse = MemberName.ImpulseMagnitude * MemberName.ImpulseRotation.Get().Vector(); \
																				} \
																		} \
																	} \
																	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPhysicsImpulse, ImpulseMagnitude)) \
																	{ \
																		MemberName.Impulse = MemberName.ImpulseMagnitude * MemberName.ImpulseRotation.Get().Vector(); \
																	}

#pragma endregion Physics

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

// Gestures
#pragma region

	// GestureDevice
#pragma region

UENUM(BlueprintType)
enum class ECsGestureDevice : uint8
{
	Mouse					UMETA(DisplayName = "Mouse"),
	MotionController		UMETA(DisplayName = "MotionController"),
	ECsGestureDevice_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsGestureDevice : public TCsEnumMap<ECsGestureDevice>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGestureDevice, ECsGestureDevice)
};

namespace NCsGestureDevice
{
	typedef ECsGestureDevice Type;

	namespace Ref
	{
		extern CSCORE_API const Type Mouse;
		extern CSCORE_API const Type MotionController;
		extern CSCORE_API const Type ECsGestureDevice_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion GestureDevice

	// GestureType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGestureType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGestureType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGestureType)

struct CSCORE_API EMCsGestureType : public TCsEnumStructMap<FECsGestureType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsGestureType)
};

#pragma endregion GestureType

#pragma endregion Gestures

// Replication
#pragma region

#define CS_SERVER_TO_CLIENT_SEND_FREQUENCY 0.01666666667

#pragma endregion Replication

// Motion Controller
#pragma region

#pragma endregion Motion Controller

// Collision
#pragma region

	// CollisionEnabled
#pragma region

struct CSCORE_API EMCollisionEnabled : public TCsEnumMap<ECollisionEnabled::Type>
{
	CS_ENUM_MAP_BODY(EMCollisionEnabled, ECollisionEnabled::Type)
};

namespace ECollisionEnabled
{
	namespace Ref
	{
		extern CSCORE_API const Type NoCollision;
		extern CSCORE_API const Type QueryOnly;
		extern CSCORE_API const Type PhysicsOnly;
		extern CSCORE_API const Type QueryAndPhysics;
	}
}

#pragma endregion CollisionEnabled

	// CollisionChannel
#pragma region

struct CSCORE_API EMCsCollisionChannel : public TCsEnumMap<ECollisionChannel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsCollisionChannel, ECollisionChannel)
};

namespace NCsCollisionChannel
{
	typedef ECollisionChannel Type;

	namespace Ref
	{
		extern CSCORE_API const Type ECC_WorldStatic;
		extern CSCORE_API const Type ECC_WorldDynamic;
		extern CSCORE_API const Type ECC_Pawn;
		extern CSCORE_API const Type ECC_Visibility;
		extern CSCORE_API const Type ECC_Camera;
		extern CSCORE_API const Type ECC_PhysicsBody;
		extern CSCORE_API const Type ECC_Vehicle;
		extern CSCORE_API const Type ECC_Destructible;

		extern CSCORE_API const Type ECC_EngineTraceChannel1;
		extern CSCORE_API const Type ECC_EngineTraceChannel2;
		extern CSCORE_API const Type ECC_EngineTraceChannel3;
		extern CSCORE_API const Type ECC_EngineTraceChannel4;
		extern CSCORE_API const Type ECC_EngineTraceChannel5;
		extern CSCORE_API const Type ECC_EngineTraceChannel6;

		extern CSCORE_API const Type ECC_GameTraceChannel1;
		extern CSCORE_API const Type ECC_GameTraceChannel2;
		extern CSCORE_API const Type ECC_GameTraceChannel3;
		extern CSCORE_API const Type ECC_GameTraceChannel4;
		extern CSCORE_API const Type ECC_GameTraceChannel5;
		extern CSCORE_API const Type ECC_GameTraceChannel6;
		extern CSCORE_API const Type ECC_GameTraceChannel7;
		extern CSCORE_API const Type ECC_GameTraceChannel8;
		extern CSCORE_API const Type ECC_GameTraceChannel9;
		extern CSCORE_API const Type ECC_GameTraceChannel10;
		extern CSCORE_API const Type ECC_GameTraceChannel11;
		extern CSCORE_API const Type ECC_GameTraceChannel12;
		extern CSCORE_API const Type ECC_GameTraceChannel13;
		extern CSCORE_API const Type ECC_GameTraceChannel14;
		extern CSCORE_API const Type ECC_GameTraceChannel15;
		extern CSCORE_API const Type ECC_GameTraceChannel16;
		extern CSCORE_API const Type ECC_GameTraceChannel17;
		extern CSCORE_API const Type ECC_GameTraceChannel18;

		extern CSCORE_API const Type ECC_MAX;
	}
}

#pragma endregion CollisionChannel

	// CollisionResponse
#pragma region

struct CSCORE_API EMCollisionResponse : public TCsEnumMap<ECollisionResponse>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCollisionResponse, ECollisionResponse)
};

namespace NCsCollisionResponse
{
	typedef ECollisionResponse Type;

	namespace Ref
	{
		extern CSCORE_API const Type ECR_Ignore;
		extern CSCORE_API const Type ECR_Overlap;
		extern CSCORE_API const Type ECR_Block;
		extern CSCORE_API const Type ECR_MAX;
	}
};

#pragma endregion CollisionResponse

USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionPreset
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

	FORCEINLINE FCsCollisionPreset& operator=(const FCsCollisionPreset& B)
	{
		bSimulationGeneratesHitEvents = B.bSimulationGeneratesHitEvents;
		bGenerateOverlapEvents = B.bGenerateOverlapEvents;
		PhysMaterialOverride = B.PhysMaterialOverride;
		CollisionEnabled = B.CollisionEnabled;
		ObjectType = B.ObjectType;
		CollisionResponses = B.CollisionResponses;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsCollisionPreset& B) const
	{
		return bSimulationGeneratesHitEvents == B.bSimulationGeneratesHitEvents && 
			   bGenerateOverlapEvents == B.bGenerateOverlapEvents && 
			   PhysMaterialOverride == B.PhysMaterialOverride &&
			   CollisionEnabled == B.CollisionEnabled && 
			   ObjectType == B.ObjectType;
	}

	FORCEINLINE bool operator!=(const FCsCollisionPreset& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Collision

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

// Attach / Detach
#pragma region

	// AttachmentTransformRules
#pragma region

UENUM(BlueprintType)
enum class ECsAttachmentTransformRules : uint8
{
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
	SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap To Target Not Including Scale"),
	SnapToTargetIncludingScale		UMETA(DisplayName = "Snap To Target Including Scale"),
	ECsAttachmentTransformRules_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAttachmentTransformRules : public TCsEnumMap<ECsAttachmentTransformRules>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAttachmentTransformRules, ECsAttachmentTransformRules)
};

namespace NCsAttachmentTransformRules
{
	typedef ECsAttachmentTransformRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type KeepRelativeTransform;
		extern CSCORE_API const Type KeepWorldTransform;
		extern CSCORE_API const Type SnapToTargetNotIncludingScale;
		extern CSCORE_API const Type SnapToTargetIncludingScale;
		extern CSCORE_API const Type ECsAttachmentTransformRules_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FAttachmentTransformRules& ToRule(const Type& EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FAttachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FAttachmentTransformRules::KeepWorldTransform; }
		if (EType == Type::SnapToTargetNotIncludingScale) { return FAttachmentTransformRules::SnapToTargetNotIncludingScale; }
		if (EType == Type::SnapToTargetIncludingScale) { return FAttachmentTransformRules::SnapToTargetIncludingScale; }
		return FAttachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_ATTACHMENT_TRANSFORM_RULES_MAX NCsAttachmentTransformRules::MAX

#pragma endregion AttachmentTransformRules

	// DetachmentTransformRules
#pragma region

UENUM(BlueprintType)
enum class ECsDetachmentTransformRules : uint8
{
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
	ECsDetachmentTransformRules_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDetachmentTransformRules : public TCsEnumMap<ECsDetachmentTransformRules>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDetachmentTransformRules, ECsDetachmentTransformRules)
};

namespace NCsDetachmentTransformRules
{
	typedef ECsDetachmentTransformRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type KeepRelativeTransform;
		extern CSCORE_API const Type KeepWorldTransform;
		extern CSCORE_API const Type ECsDetachmentTransformRules_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FDetachmentTransformRules& ToRule(const Type& EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FDetachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FDetachmentTransformRules::KeepWorldTransform; }
		return FDetachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_DETACHMENT_TRANSFORM_RULES_MAX NCsDetachmentTransformRules::MAX

#pragma endregion DetachmentTransformRules

#pragma endregion Attach / Detach

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