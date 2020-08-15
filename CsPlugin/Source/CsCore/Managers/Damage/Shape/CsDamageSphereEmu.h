// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Managers/Damage/Shape/CsDamageShape.h"
#include "Managers/Damage/Collision/CsDamageCollision.h"
#include "Types/CsTypes_Interpolation.h"
#pragma once

struct FCsInterfaceMap;
struct ICsDamageValue;

/**
*
*/
struct CSCORE_API FCsDamageSphereEmu : public ICsDamageExpression,
									   public ICsDamageShape,
									   public ICsDamageCollision
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageExpression
	ICsDamageValue* DamageValue;

	FECsDamageType* Type;

	// ICsDamageShape

	float* MinDamage;

	float* MaxDamage;

	float* MinRadius;

	float* MaxRadius;

	ECsInterpolatingMethod* InterpolationMethod;

	ECsEasingType* EasingType;

	FCsCurveFloat* Curve;

	// ICsDamageCollision

	bool* bIgnoreHitResultObject;

public:

	FCsDamageSphereEmu();
	~FCsDamageSphereEmu();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

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

	FORCEINLINE ICsDamageValue* GetValue() const
	{
		return DamageValue;
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

	float CalculateDamage(const ICsDamageValue* Value, const FVector& Origin, const FVector& Point) const;

	bool IsInBounds(const FVector& Origin, const FVector& Point) const;

#pragma endregion ICsDamageSphere

public:

	void SetMinDamage(float* Value);

	void SetMaxDamage(float* Value);

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

// ICsDamageCollision
#pragma region
public:

	FORCEINLINE bool IgnoreHitResultObject() const
	{
		return *bIgnoreHitResultObject;
	}

#pragma endregion ICsDamageCollision

public:

	void SetIgnoreHitResultObject(bool* Value)
	{
		bIgnoreHitResultObject = Value;
	}
};