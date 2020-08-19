// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsDamageSphereEmu.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"
#include "Managers/Damage/Range/CsDamageRangeEmu.h"

const FName FCsDamageSphereEmu::Name = FName("FCsDamageSphereEmu");

FCsDamageSphereEmu::FCsDamageSphereEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsDamageExpression
	DamageValue(nullptr),
	Type(nullptr),
	// ICsDamageShape
	DamageRange(nullptr),
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
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageSphereEmu::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
	InterfaceMap->Add<ICsDamageShape>(static_cast<ICsDamageShape*>(this));
	InterfaceMap->Add<ICsDamageCollision>(static_cast<ICsDamageCollision*>(this));

	// ICsDamageExpression
	DamageValue = new FCsDamageValueRangeEmu();
	// ICsDamageShape
	DamageRange = new FCsDamageRangeEmu();
}

FCsDamageSphereEmu::~FCsDamageSphereEmu()
{
	delete InterfaceMap;
}

// ICsDamageShape
#pragma region

float FCsDamageSphereEmu::CalculateDamage(const ICsDamageValue* Value, const ICsDamageRange* Range, const FVector& Origin, const FVector& Point) const
{
	return 0.0f;
}

bool FCsDamageSphereEmu::IsInBounds(const FVector& Origin, const FVector& Point) const
{
	return false;
}

#pragma endregion ICsDamageSphere

void FCsDamageSphereEmu::SetMinDamage(float* Value)
{
	FCsDamageValueRangeEmu* Emu = static_cast<FCsDamageValueRangeEmu*>(DamageValue);
	Emu->SetMinValue(Value);
}

void FCsDamageSphereEmu::SetMaxDamage(float* Value)
{
	FCsDamageValueRangeEmu* Emu = static_cast<FCsDamageValueRangeEmu*>(DamageValue);
	Emu->SetMaxValue(Value);
}

void FCsDamageSphereEmu::SetMinRadius(float* Value)
{
	FCsDamageRangeEmu* Emu = static_cast<FCsDamageRangeEmu*>(DamageRange);
	Emu->SetMinRange(Value);
}

void FCsDamageSphereEmu::SetMaxRadius(float* Value)
{
	FCsDamageRangeEmu* Emu = static_cast<FCsDamageRangeEmu*>(DamageRange);
	Emu->SetMaxValue(Value);
}