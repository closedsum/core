// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
#include "Types/CsTypes_Interpolation.h"
#pragma once

struct FCsInterfaceMap;
struct ICsDamageValue;
struct ICsDamageRange;

/**
*
*/
struct CSCORE_API FCsData_DamageSphereEmu : public ICsData_Damage,
											public ICsData_DamageShape,
											public ICsData_DamageCollision
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsData_Damage
	ICsDamageValue* DamageValue;

	FECsDamageType* Type;

	// ICsData_DamageShape

	ICsDamageRange* DamageRange;

	float* MinDamage;

	float* MaxDamage;

	float* MinRadius;

	float* MaxRadius;

	ECsInterpolatingMethod* InterpolationMethod;

	ECsEasingType* EasingType;

	FCsCurveFloat* Curve;

	// ICsData_DamageCollision

	bool* bIgnoreHitResultObject;

public:

	FCsData_DamageSphereEmu();
	~FCsData_DamageSphereEmu();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_Damage
#pragma region
public:

	FORCEINLINE const ICsDamageValue* GetValue() const
	{
		return DamageValue;
	}

	FORCEINLINE const FECsDamageType& GetType() const
	{
		return const_cast<FECsDamageType&>(*Type);
	}

#pragma endregion ICsData_Damage

public:

	void SetType(FECsDamageType* Value)
	{
		Type = Value;
	}

// ICsData_DamageShape
#pragma region
public:

	FORCEINLINE const ICsDamageRange* GetRange() const
	{
		return DamageRange;
	}

	float CalculateDamage(const ICsDamageValue* Value, const ICsDamageRange* Range, const FVector& Origin, const FVector& Point) const;

	bool IsInBounds(const FVector& Origin, const FVector& Point) const;

#pragma endregion ICsData_DamageShape

public:

	void SetMinDamage(float* Value);

	void SetMaxDamage(float* Value);

	void SetMinRadius(float* Value);

	void SetMaxRadius(float* Value);

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

// ICsData_DamageCollision
#pragma region
public:

	FORCEINLINE bool IgnoreHitResultObject() const
	{
		return *bIgnoreHitResultObject;
	}

#pragma endregion ICsData_DamageCollision

public:

	void SetIgnoreHitResultObject(bool* Value)
	{
		bIgnoreHitResultObject = Value;
	}
};