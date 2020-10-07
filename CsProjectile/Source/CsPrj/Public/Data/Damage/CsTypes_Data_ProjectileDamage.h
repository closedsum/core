// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"
#include "CsTypes_Data_ProjectileDamage.generated.h"
#pragma once

// FCsPrjData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::FEmu
namespace NCsDamage {
	namespace NData {
		namespace NPoint {
			struct FEmu; } } }

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsDamageType Type;

public:

	FCsPrjData_DamagePoint() :
		Damage(0.0f),
		Type()
	{
	}

private:

	typedef NCsDamage::NData::NPoint::FEmu PointDataEmuType;

public:

	void SetData(PointDataEmuType* Data);
};

#pragma endregion FCsPrjData_DamagePoint

// FCsPrjData_DamageSphere
#pragma region

// NCsDamage::NData::NShape::NSphere::FEmu
namespace NCsDamage {
	namespace NData {
		namespace NShape {
			namespace NSphere {
				struct FEmu; } } } }

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjData_DamageSphere
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

	typedef NCsDamage::NData::NShape::NSphere::FEmu SphereDataEmuType;

public:

	void SetData(SphereDataEmuType* Data);
};

#pragma endregion FCsPrjData_DamageSphere