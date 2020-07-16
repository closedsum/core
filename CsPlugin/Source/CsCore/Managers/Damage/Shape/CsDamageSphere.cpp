// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsDamageSphere.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamageSphere::Name = FName("FCsDamageSphere");

FCsDamageSphere::FCsDamageSphere() :
	InterfaceMap(),
	Type(nullptr),
	MinDamage(nullptr),
	MaxDamage(nullptr),
	MinRadius(nullptr),
	MaxRadius(nullptr),
	InterpolationMethod(nullptr),
	EasingType(nullptr),
	Curve(nullptr)
{
	InterfaceMap->SetRootName(FCsDamageSphere::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
	InterfaceMap->Add<ICsDamageShape>(static_cast<ICsDamageShape*>(this));
}

// ICsDamageShape
#pragma region

float FCsDamageSphere::CalculateDamage(const FVector& Origin, const FVector& Point) const
{
	return 0.0f;
}

bool FCsDamageSphere::IsInBounds(const FVector& Origin, const FVector& Point) const
{
	return false;
}

#pragma endregion ICsDamageSphere