// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/CsData_DamageSphereEmu.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"
#include "Managers/Damage/Range/CsDamageRangeEmu.h"

const FName FCsData_DamageSphereEmu::Name = FName("FCsData_DamageSphereEmu");

FCsData_DamageSphereEmu::FCsData_DamageSphereEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsData_Damage
	DamageValue(nullptr),
	Type(nullptr),
	// ICsData_DamageShape
	DamageRange(nullptr),
	MinDamage(nullptr),
	MaxDamage(nullptr),
	MinRadius(nullptr),
	MaxRadius(nullptr),
	InterpolationMethod(nullptr),
	EasingType(nullptr),
	Curve(nullptr),
	// ICsData_DamageCollision
	bIgnoreHitResultObject(nullptr)
{
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_DamageSphereEmu::Name);

	InterfaceMap->Add<ICsData_Damage>(static_cast<ICsData_Damage*>(this));
	InterfaceMap->Add<ICsData_DamageShape>(static_cast<ICsData_DamageShape*>(this));
	InterfaceMap->Add<ICsData_DamageCollision>(static_cast<ICsData_DamageCollision*>(this));

	// ICsData_Damage
	DamageValue = new NCsDamage::NValue::NRange::FEmu();
	// ICsData_DamageShape
	DamageRange = new NCsDamage::NRange::FEmu();
}

FCsData_DamageSphereEmu::~FCsData_DamageSphereEmu()
{
	delete InterfaceMap;
}

// ICsDamageShape
#pragma region

float FCsData_DamageSphereEmu::CalculateDamage(const NCsDamage::NValue::IValue* Value, const NCsDamage::NRange::IRange* Range, const FVector& Origin, const FVector& Point) const
{
	return 0.0f;
}

bool FCsData_DamageSphereEmu::IsInBounds(const FVector& Origin, const FVector& Point) const
{
	return false;
}

#pragma endregion ICsDamageSphere

void FCsData_DamageSphereEmu::SetMinDamage(float* Value)
{
	typedef NCsDamage::NValue::NRange::FEmu EmuType;

	EmuType* Emu = static_cast<EmuType*>(DamageValue);
	Emu->SetMinValue(Value);
}

void FCsData_DamageSphereEmu::SetMaxDamage(float* Value)
{
	typedef NCsDamage::NValue::NRange::FEmu EmuType;

	EmuType* Emu = static_cast<EmuType*>(DamageValue);
	Emu->SetMaxValue(Value);
}

void FCsData_DamageSphereEmu::SetMinRadius(float* Value)
{
	typedef NCsDamage::NRange::FEmu EmuType;

	EmuType* Emu = static_cast<EmuType*>(DamageRange);
	Emu->SetMinRange(Value);
}

void FCsData_DamageSphereEmu::SetMaxRadius(float* Value)
{
	typedef NCsDamage::NRange::FEmu EmuType;

	EmuType* Emu = static_cast<EmuType*>(DamageRange);
	Emu->SetMaxValue(Value);
}