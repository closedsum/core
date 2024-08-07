// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_Math.h"

#include "CsTypes_Physics.generated.h"

// FCsPhysicalMaterial
#pragma region

class UPhysicalMaterial;

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsPhysicalMaterial
{
	GENERATED_USTRUCT_BODY()

public:

	/** Soft reference to a Physics Material. */
	UPROPERTY(EditAnywhere, Category = "CsTypes|Physics")
	TSoftObjectPtr<UPhysicalMaterial> Material;

	/** */
	UPROPERTY(EditAnywhere, Category = "CsTypes|Physics", meta = (Bitmask, BitmaskEnum = "/Script/CsTypes.ECsLoadFlags"))
	int32 Material_LoadFlags;

	/** Hard reference to a Physics Material. */
	UPROPERTY(Transient)
	UPhysicalMaterial* Material_Internal;

public:

	FCsPhysicalMaterial() :
		Material(nullptr),
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
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

#pragma endregion FCsPhysicalMaterial

// FCsPhysicsAsset
#pragma region

class UPhysicsAsset;

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsPhysicsAsset
{
	GENERATED_USTRUCT_BODY()

public:

	/** Soft reference to a Physics Asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Physics")
	TSoftObjectPtr<UPhysicsAsset> Physics;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Physics", meta = (Bitmask, BitmaskEnum = "/Script/CsTypes.ECsLoadFlags"))
	int32 Physics_LoadFlags;

	/** Hard reference to a Physics Asset. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Physics")
	UPhysicsAsset* Physics_Internal;

public:

	FCsPhysicsAsset() :
		Physics(nullptr),
		Physics_LoadFlags(0),
		Physics_Internal(nullptr)
	{
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

#pragma endregion FCsPhysicsAsset


#define CS_MIN_PHYSICS_LINEAR_VELOCITY_FOR_MOVEMENT 0.1f
#define CS_MIN_PHYSICS_ANGULAR_VELOCITY_FOR_MOVEMENT 0.1f

// FCsPhysicsPreset
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsPhysicsPreset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	bool bSimulatePhysics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	bool OverrideMassInKg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MassInKg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float LinearDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AngularDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
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

#pragma endregion FCsPhysicsPreset

// PhysicsImpulseType
#pragma region

/**
*/
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

struct CSTYPES_API EMCsPhysicsImpulseType final : public TCsEnumMap<ECsPhysicsImpulseType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPhysicsImpulseType, ECsPhysicsImpulseType)
};

namespace NCsPhysicsImpulseType
{
	typedef ECsPhysicsImpulseType Type;

	namespace Ref
	{
		extern CSTYPES_API const Type AddForce;
		extern CSTYPES_API const Type AddForceAtPosition;
		extern CSTYPES_API const Type AddTorque;
		extern CSTYPES_API const Type AddAngularImpulse;
		extern CSTYPES_API const Type AddImpulse;
		extern CSTYPES_API const Type AddImpulseAtPosition;
		extern CSTYPES_API const Type ECsPhysicsImpulseType_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

#define ECS_PHYSICS_IMPULSE_TYPE_MAX (uint8)ECsPhysicsImpulseType::ECsPhysicsImpulseType_MAX

#pragma endregion ECsPhysicsImpulseType

// FCsPhysicsImpulse
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsPhysicsImpulse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	ECsPhysicsImpulseType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	FCsOptionalRotatorInterval ImpulseRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	float ImpulseMagnitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsTypes|Physics")
	FVector3f Impulse;

	/** Used in AddForceAtPosition and AddImpulseAtPosition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	FCsOptionalVectorInterval Position;

	/** Used in AddForce, AddForceAtPosition, and AddTorque */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	bool bAllowSubstepping;

	/** Used in AddForce and AddTorque */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	bool bAccelChange;

	/** Used in AddAngularImpulse and AddImpulse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Physics")
	bool bVelChange;

	/** Used in AddForceAtPosition */
	bool bIsLocalForce;

	FCsPhysicsImpulse() :
		Type(ECsPhysicsImpulseType::ECsPhysicsImpulseType_MAX),
		ImpulseRotation(),
		ImpulseMagnitude(0.0f),
		Impulse(0.0f),
		Position(),
		bAllowSubstepping(true),
		bAccelChange(false),
		bVelChange(false),
		bIsLocalForce(false)
	{
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
																			if (PropertyName == GET_MEMBER_NAME_CHECKED(FRotator3f, Roll) || \
																				PropertyName == GET_MEMBER_NAME_CHECKED(FRotator3f, Pitch) || \
																				PropertyName == GET_MEMBER_NAME_CHECKED(FRotator3f, Yaw)) \
																				{ \
																					MemberName.Impulse = MemberName.ImpulseMagnitude * MemberName.ImpulseRotation.Get().Vector(); \
																				} \
																		} \
																	} \
																	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPhysicsImpulse, ImpulseMagnitude)) \
																	{ \
																		MemberName.Impulse = MemberName.ImpulseMagnitude * MemberName.ImpulseRotation.Get().Vector(); \
																	}

#pragma endregion FCsPhysicsImpulse