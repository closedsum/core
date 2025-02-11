// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"

#include "CsTypes_Data_ProjectileDamage.generated.h"

// FCsPrjData_DamagePoint
#pragma region

// PointDataProxyType (NCsDamage::NData::NPoint::NProxy::FProxy)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NPoint, NProxy, FProxy)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Projectile|Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Projectile|Data")
	FECsDamageType Type;

public:

	FCsPrjData_DamagePoint() :
		Damage(0.0f),
		Type()
	{
	}

private:

	using PointDataProxyType = NCsDamage::NData::NPoint::NProxy::FProxy;

public:

	void SetData(PointDataProxyType* Data);
};

#pragma endregion FCsPrjData_DamagePoint

// FCsPrjData_DamageSphere
#pragma region

// NCsDamage::NData::NShape::NSphere::NProxy::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsDamage, NData, NShape, NSphere, NProxy, FProxy)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjData_DamageSphere
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Projectile|Data")
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Projectile|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Projectile|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data",  meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min and Max. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min and Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	FCsCurveFloat Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	bool bIgnoreHitResultObject;

public:

	FCsPrjData_DamageSphere() :
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

	using SphereDataProxyType = NCsDamage::NData::NShape::NSphere::NProxy::FProxy;

public:

	void SetData(SphereDataProxyType* Data);
};

#pragma endregion FCsPrjData_DamageSphere