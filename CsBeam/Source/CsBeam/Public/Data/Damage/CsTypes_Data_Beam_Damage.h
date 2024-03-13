// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"

#include "CsTypes_Data_Beam_Damage.generated.h"

// FCsBeamData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FProxy)

USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Point")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Point")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Sphere")
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Sphere", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Sphere", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere",  meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere")
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min and Max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere")
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere")
	FCsCurveFloat Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Damage|Sphere")
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