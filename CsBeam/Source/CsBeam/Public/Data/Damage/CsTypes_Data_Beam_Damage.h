// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"

#include "CsTypes_Data_Beam_Damage.generated.h"
#pragma once

// FCsBeamData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FProxy)

USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsDamageType Type;

public:

	FCsBeamData_DamagePoint() :
		Damage(0.0f),
		Type()
	{
	}

private:

	typedef NCsDamage::NData::NPoint::FProxy PointDataProxyType;

public:

	void SetData(PointDataProxyType* Data);
};

#pragma endregion FCsBeamData_DamagePoint

// FCsBeamData_DamageSphere
#pragma region

// NCsDamage::NData::NShape::NSphere::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NShape, NSphere, FProxy)

USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamData_DamageSphere
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min and Max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCurveFloat Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIgnoreHitResultObject;

public:

	FCsBeamData_DamageSphere() :
		Type(),
		MinDamage(0.0f),
		MaxDamage(0.0f),
		MinRadius(0.0f),
		MaxRadius(0.0f),
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		EasingType(ECsEasingType::Linear),
		Curve(),
		bIgnoreHitResultObject(true)
	{
	}

private:

	typedef NCsDamage::NData::NShape::NSphere::FProxy SphereDataProxyType;

public:

	void SetData(SphereDataProxyType* Data);
};

#pragma endregion FCsBeamData_DamageSphere