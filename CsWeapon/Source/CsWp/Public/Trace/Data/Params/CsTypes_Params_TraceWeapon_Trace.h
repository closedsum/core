// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"

#include "CsTypes_Params_TraceWeapon_Trace.generated.h"
#pragma once

// TraceWeaponLaunchLocation
#pragma region

/**
* Describes the different methods to get the Location from which a trace
* will be performed from a weapon of type: ICsTraceWeapon.
*/
UENUM(BlueprintType)
enum class ECsTraceWeaponTraceLocation : uint8
{
	/** Root object's Location (usually a SceneComponent). */
	Self							UMETA(DisplayName = "Self"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner							UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the 
		Weapon, use the Bone's location. */
	Bone							UMETA(DisplayName = "Bone"),
	/** If there is a SkeletalMesh that acts as the root object for the
		Weapon, use the Socket's location. */
	Socket							UMETA(DisplayName = "Socket"),
	/** SceneComponent's Location. The Component is marked as the Trace Component Transform. */
	Component						UMETA(DisplayName = "Component"),
	/** Owner's Camera's Location. */
	Camera							UMETA(DisplayName = "Camera"),
	Custom							UMETA(DisplayName = "Custom"),
	ECsTraceWeaponTraceLocation_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsTraceWeaponTraceLocation : public TCsEnumMap<ECsTraceWeaponTraceLocation>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceWeaponTraceLocation, ECsTraceWeaponTraceLocation)
};

namespace NCsTraceWeaponTraceLocation
{
	typedef ECsTraceWeaponTraceLocation Type;

	namespace Ref
	{
		extern CSWP_API const Type Self;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Socket;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsTraceWeaponTraceLocation_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponLaunchLocation

// TraceWeaponTraceDirection
#pragma region

/**
* Describes the different methods to get the Direction from which a trace
* will be performed from a weapon of type: ICsTraceWeapon.
*/
UENUM(BlueprintType)
enum class ECsTraceWeaponTraceDirection : uint8
{
	/** Root object's direction (usually a SceneComponent). */
	Self								UMETA(DisplayName = "Self"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner								UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone's rotation. */
	Bone								UMETA(DisplayName = "Bone"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Socket's rotation. */
	Socket								UMETA(DisplayName = "Socket"),
	/** SceneComponent's Rotation. The Component is marked as the Trace Component Transform. */
	Component							UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation. */
	Camera								UMETA(DisplayName = "Camera"),
	/** A trace is used to determine the direction. The start and end points of the
		trace are determined by other parameters. */
	Trace								UMETA(DisplayName = "Trace"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsTraceWeaponTraceDirection_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsTraceWeaponTraceDirection : public TCsEnumMap<ECsTraceWeaponTraceDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceWeaponTraceDirection, ECsTraceWeaponTraceDirection)
};

namespace NCsTraceWeaponTraceDirection
{
	typedef ECsTraceWeaponTraceDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Self;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Socket;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Trace;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsTraceWeaponTraceDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponTraceDirection

// TraceWeaponTraceShape
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsTraceWeaponTraceShape : uint8
{
	Line							UMETA(DisplayName = "Line"),
	Box								UMETA(DisplayName = "Box"),
	Sphere							UMETA(DisplayName = "Sphere"),
	Capsule							UMETA(DisplayName = "Capsule"),
	ECsTraceWeaponTraceShape_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsTraceWeaponTraceShape : public TCsEnumMap<ECsTraceWeaponTraceShape>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceWeaponTraceShape, ECsTraceWeaponTraceShape)
};

namespace NCsTraceWeaponTraceShape
{
	typedef ECsTraceWeaponTraceShape Type;

	namespace Ref
	{
		extern CSWP_API const Type Line;
		extern CSWP_API const Type Box;
		extern CSWP_API const Type Sphere;
		extern CSWP_API const Type Capsule;
		extern CSWP_API const Type ECsTraceWeaponTraceShape_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponTraceShape

// FCsTraceWeaponTraceParamsLocationInfo
#pragma region

/**
* Describes Location related information for performing a trace from a
* weapon of type: ICsTraceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponTraceParamsLocationInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceLocation Type;

	/** Get the Bone from which Location information is used.
		Only valid if:
		 Type == ECsTraceWeaponTraceLocation::Bone ||
		 Type == ECsTraceWeaponTraceLocation::Socket */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneOrSocket;

	FCsTraceWeaponTraceParamsLocationInfo() :
		Type(ECsTraceWeaponTraceLocation::Owner),
		BoneOrSocket(NAME_None)
	{
	}
};

#pragma endregion FCsTraceWeaponTraceParamsLocationInfo

// FCsTraceWeaponTraceParamsDirectionInfo
#pragma region

/**
* Describes Direction related information for performing a trace from a
* weapon of type: ICsTraceWeapon
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponTraceParamsDirectionInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceDirection Type;

	/** Get the Bone from which Direction information is used.
		Only valid if:
		 Type == ECsTraceWeaponTraceDirection::Bone ||
		 Type == ECsTraceWeaponTraceDirection::Socket */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneOrSocket;

	/** The Rules, components (Pitch, Yaw, Roll), to use from a given rotation
		when calculating the Direction.
		See ECsRotationRules */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 Rules;

	FCsTraceWeaponTraceParamsDirectionInfo() :
		Type(ECsTraceWeaponTraceDirection::Owner),
		BoneOrSocket(NAME_None),
		Rules(3) // CS_ROTATION_FLAGS_PITCH_AND_YAW
	{
	}
};

#pragma endregion FCsTraceWeaponTraceParamsDirectionInfo

// FCsTraceWeaponLineTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FLineImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FLineImpl)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponLineTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsTraceWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsDirectionInfo DirectionInfo;

	/** The ObjectTypes to perform the trace again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	/** The length of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponLineTraceParams() :
		LocationInfo(),
		DirectionInfo(),
		ObjectTypes(),
		Distance(1000.0f)
	{
	}

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FLineImpl

	void CopyParams(ImplType* Impl);

#undef ImplType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponLineTraceParams

// FCsTraceWeaponBoxTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FBoxImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FBoxImpl)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponBoxTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsTraceWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsDirectionInfo DirectionInfo;

	/** The ObjectTypes to perform the trace again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionBox Shape;

	/** The length of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponBoxTraceParams() :
		LocationInfo(),
		DirectionInfo(),
		ObjectTypes(),
		Shape(),
		Distance(1000.0f)
	{
	}

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FBoxImpl

	void CopyParams(ImplType* Impl);

#undef ImplType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponBoxTraceParams

// FCsTraceWeaponSphereTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FSphereImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FSphereImpl)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponSphereTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsTraceWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsDirectionInfo DirectionInfo;

	/** The ObjectTypes to perform the trace again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionSphere Shape;

	/** The length of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponSphereTraceParams() :
		LocationInfo(),
		DirectionInfo(),
		ObjectTypes(),
		Shape(),
		Distance(1000.0f)
	{
	}

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FSphereImpl

	void CopyParams(ImplType* Impl);

#undef ImplType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponSphereTraceParams

// FCsTraceWeaponCapsuleTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FCapsuleImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FCapsuleImpl)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponCapsuleTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsTraceWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsDirectionInfo DirectionInfo;

	/** The ObjectTypes to perform the trace again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionSphere Shape;

	/** The length of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponCapsuleTraceParams() :
		LocationInfo(),
		DirectionInfo(),
		ObjectTypes(),
		Shape(),
		Distance(1000.0f)
	{
	}

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FCapsuleImpl

	void CopyParams(ImplType* Impl);

#undef ImplType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponCapsuleTraceParams

// FCsTraceWeaponTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::ITrace
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, ITrace)

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsTraceWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponTraceParamsDirectionInfo DirectionInfo;

	/** The ObjectTypes to perform the trace again. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ECollisionChannel>> ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceShape Shape;

	/** The length of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionBox BoxShape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionSphere SphereShape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionCapsule CapsuleShape;

	FCsTraceWeaponTraceParams() :
		LocationInfo(),
		DirectionInfo(),
		ObjectTypes(),
		Shape(ECsTraceWeaponTraceShape::Line),
		Distance(1000.0f),
		BoxShape(),
		SphereShape(),
		CapsuleShape()
	{
	}

#define ParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace

	ParamsType* ConstructAndCopyParams();

#undef ParamsType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponTraceParams