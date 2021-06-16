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

const FName NCsDamage::NData::NShape::NSphere::FEmu::Name = FName("NCsDamage::NData::NShape::NSphere::FEmu");

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
				FEmu::FEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(),
					// DataType (NCsDamage::NData::IData)
					DamageValue(nullptr),
					Type(nullptr),
					// ShapeDataType (NCsDamage::NData::NShape::IShape)
					DamageRange(nullptr),
					MinDamage(nullptr),
					MaxDamage(nullptr),
					MinRadius(nullptr),
					MaxRadius(nullptr),
					InterpolationMethod(nullptr),
					EasingType(nullptr),
					Curve(nullptr),
					// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
					bIgnoreHitResultObject(nullptr)
				{
					// ICsGetInterfaceMap
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FEmu>(this);

					typedef NCsDamage::NData::IData DataType;
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<ShapeDataType>(static_cast<ShapeDataType*>(this));
					InterfaceMap->Add<CollisionDataType>(static_cast<CollisionDataType*>(this));

					// NCsDamage::NValue::NRange::IRange
					typedef NCsDamage::NValue::NRange::FEmu ValueRangeEmuType;
					DamageValue = new ValueRangeEmuType();
					// NCsDamage::NRange::IRange
					typedef NCsDamage::NRange::FEmu RangeEmuType;
					DamageRange = new RangeEmuType();
				}

				FEmu::~FEmu()
				{
					delete InterfaceMap;
				}

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region

				float FEmu::CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const
				{
					return 0.0f;
				}

				bool FEmu::IsInBounds(const FVector& Origin, const FVector& Point) const
				{
					return false;
				}

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				void FEmu::SetMinDamage(float* Value)
				{
					typedef NCsDamage::NValue::NRange::FEmu EmuType;

					EmuType* Emu = static_cast<EmuType*>(DamageValue);
					Emu->SetMinValue(Value);
				}

				void FEmu::SetMaxDamage(float* Value)
				{
					typedef NCsDamage::NValue::NRange::FEmu EmuType;

					EmuType* Emu = static_cast<EmuType*>(DamageValue);
					Emu->SetMaxValue(Value);
				}

				void FEmu::SetMinRadius(float* Value)
				{
					typedef NCsDamage::NRange::FEmu EmuType;

					EmuType* Emu = static_cast<EmuType*>(DamageRange);
					Emu->SetMinRange(Value);
				}

				void FEmu::SetMaxRadius(float* Value)
				{
					typedef NCsDamage::NRange::FEmu EmuType;

					EmuType* Emu = static_cast<EmuType*>(DamageRange);
					Emu->SetMaxValue(Value);
				}
			}
		}
	}
}