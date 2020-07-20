// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsDamageSphereEmu.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamageSphereEmu::Name = FName("FCsDamageSphereEmu");

FCsDamageSphereEmu::FCsDamageSphereEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsDamageExpression
	Type(nullptr),
	// ICsDamageShape
	MinDamage(nullptr),
	MaxDamage(nullptr),
	MinRadius(nullptr),
	MaxRadius(nullptr),
	InterpolationMethod(nullptr),
	EasingType(nullptr),
	Curve(nullptr),
	// ICsDamageCollision
	bIgnoreHitResultObject(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageSphereEmu::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
	InterfaceMap->Add<ICsDamageShape>(static_cast<ICsDamageShape*>(this));
	InterfaceMap->Add<ICsDamageCollision>(static_cast<ICsDamageCollision*>(this));
}

FCsDamageSphereEmu::~FCsDamageSphereEmu()
{
	delete InterfaceMap;
}

// ICsDamageShape
#pragma region

float FCsDamageSphereEmu::CalculateDamage(const FVector& Origin, const FVector& Point) const
{
	return 0.0f;
}

bool FCsDamageSphereEmu::IsInBounds(const FVector& Origin, const FVector& Point) const
{
	return false;
}

#pragma endregion ICsDamageSphere