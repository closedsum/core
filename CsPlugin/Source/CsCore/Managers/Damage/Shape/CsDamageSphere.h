// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Managers/Damage/Shape/CsDamageShape.h"
#include "Types/CsTypes_Interpolation.h"
#pragma once

struct FCsInterfaceMap;

/**
*
*/
struct CSCORE_API FCsDamageSphere : public ICsDamageExpression,
									public ICsDamageShape
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageExpression

	FECsDamageType* Type;

	float* MinDamage;

	float* MaxDamage;

	float* MinRadius;

	float* MaxRadius;

	ECsInterpolatingMethod* InterpolationMethod;

	ECsEasingType* EasingType;

	FCsCurveFloat* Curve;

public:

	FCsDamageSphere();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageExpression
#pragma region
public:

	FORCEINLINE float GetDamage() const
	{
		return *MaxDamage;
	}

	FORCEINLINE const FECsDamageType& GetType() const
	{
		return const_cast<FECsDamageType&>(*Type);
	}

#pragma endregion ICsDamageExpression

public:

	void SetType(FECsDamageType* Value)
	{
		Type = Value;
	}

// ICsDamageShape
#pragma region
public:

	float CalculateDamage(const FVector& Origin, const FVector& Point) const;

	bool IsInBounds(const FVector& Origin, const FVector& Point) const;

#pragma endregion ICsDamageSphere

public:

	void SetMinDamage(float* Value)
	{
		MinDamage = Value;
	}

	void SetMaxDamage(float* Value)
	{
		MaxDamage = Value;
	}

	void SetMinRadius(float* Value)
	{
		MinRadius = Value;
	}

	void SetMaxRadius(float* Value)
	{
		MaxRadius = Value;
	}

	void SetInterpoloationMethod(ECsInterpolatingMethod* Value)
	{
		InterpolationMethod = Value;
	}

	void SetEasingType(ECsEasingType* Value)
	{
		EasingType = Value;
	}

	void SetCurve(FCsCurveFloat* Value)
	{
		Curve = Value;
	}
};