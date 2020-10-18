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
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner							UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the 
		Weapon, use the Bone / Socket location. */
	Bone							UMETA(DisplayName = "Bone"),
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
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
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
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner								UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone / Socket's rotation. */
	Bone								UMETA(DisplayName = "Bone"),
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
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Trace;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsTraceWeaponTraceDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponTraceDirection

// FCsTraceWeaponLineTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FLineEmu
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FLineEmu)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponLineTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceLocation Location;

	/** Describes the different methods to get the Direction from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponLineTraceParams() :
		Location(ECsTraceWeaponTraceLocation::Owner),
		Direction(ECsTraceWeaponTraceDirection::Owner),
		DirectionRules(3), // CS_ROTATION_FLAGS_PITCH_AND_YAW
		ObjectType(ECollisionChannel::ECC_MAX),
		Distance(1000.0f)
	{
	}

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FLineEmu

	void CopyParams(EmuType* Emu);

#undef EmuType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponLineTraceParams

// FCsTraceWeaponBoxTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FBoxEmu
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FBoxEmu)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponBoxTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceLocation Location;

	/** Describes the different methods to get the Direction from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionBox Shape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponBoxTraceParams() :
		Location(ECsTraceWeaponTraceLocation::Owner),
		Direction(ECsTraceWeaponTraceDirection::Owner),
		DirectionRules(3), // CS_ROTATION_FLAGS_PITCH_AND_YAW
		ObjectType(ECollisionChannel::ECC_MAX),
		Shape(),
		Distance(1000.0f)
	{
	}

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FBoxEmu

	void CopyParams(EmuType* Emu);

#undef EmuType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponBoxTraceParams

// FCsTraceWeaponSphereTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FSphereEmu
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FSphereEmu)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponSphereTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceLocation Location;

	/** Describes the different methods to get the Direction from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionSphere Shape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponSphereTraceParams() :
		Location(ECsTraceWeaponTraceLocation::Owner),
		Direction(ECsTraceWeaponTraceDirection::Owner),
		DirectionRules(3), // CS_ROTATION_FLAGS_PITCH_AND_YAW
		ObjectType(ECollisionChannel::ECC_MAX),
		Shape(),
		Distance(1000.0f)
	{
	}

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FSphereEmu

	void CopyParams(EmuType* Emu);

#undef EmuType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponSphereTraceParams

// FCsTraceWeaponCapsuleTraceParams
#pragma region

// NCsWeapon::NTrace::NParams::NTrace::FSphereEmu
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, FCapsuleEmu)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponCapsuleTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceLocation Location;

	/** Describes the different methods to get the Direction from which a trace
		will be performed from a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponTraceDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceCollisionSphere Shape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Distance;

	FCsTraceWeaponCapsuleTraceParams() :
		Location(ECsTraceWeaponTraceLocation::Owner),
		Direction(ECsTraceWeaponTraceDirection::Owner),
		DirectionRules(3), // CS_ROTATION_FLAGS_PITCH_AND_YAW
		ObjectType(ECollisionChannel::ECC_MAX),
		Shape(),
		Distance(1000.0f)
	{
	}

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FCapsuleEmu

	void CopyParams(EmuType* Emu);

#undef EmuType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponCapsuleTraceParams