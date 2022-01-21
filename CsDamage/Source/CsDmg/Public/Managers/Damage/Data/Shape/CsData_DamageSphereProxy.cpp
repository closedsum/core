// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/CsData_DamageSphereProxy.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeProxy.h"
#include "Managers/Damage/Range/CsDamageRangeProxy.h"

const FName NCsDamage::NData::NShape::NSphere::FProxy::Name = FName("NCsDamage::NData::NShape::NSphere::FProxy");

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
				FProxy::FProxy() :
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

					InterfaceMap->SetRoot<FProxy>(this);

					typedef NCsDamage::NData::IData DataType;
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<ShapeDataType>(static_cast<ShapeDataType*>(this));
					InterfaceMap->Add<CollisionDataType>(static_cast<CollisionDataType*>(this));

					// NCsDamage::NValue::NRange::IRange
					typedef NCsDamage::NValue::NRange::FProxy ValueRangeProxyType;
					DamageValue = new ValueRangeProxyType();
					// NCsDamage::NRange::IRange
					typedef NCsDamage::NRange::FProxy RangeProxyType;
					DamageRange = new RangeProxyType();
				}

				FProxy::~FProxy()
				{
					delete InterfaceMap;
				}

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region

				float FProxy::CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const
				{
					return 0.0f;
				}

				bool FProxy::IsInBounds(const FVector& Origin, const FVector& Point) const
				{
					return false;
				}

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				void FProxy::SetMinDamage(float* Value)
				{
					typedef NCsDamage::NValue::NRange::FProxy ProxyType;

					ProxyType* Proxy = static_cast<ProxyType*>(DamageValue);
					Proxy->SetMinValue(Value);
				}

				void FProxy::SetMaxDamage(float* Value)
				{
					typedef NCsDamage::NValue::NRange::FProxy ProxyType;

					ProxyType* Proxy = static_cast<ProxyType*>(DamageValue);
					Proxy->SetMaxValue(Value);
				}

				void FProxy::SetMinRadius(float* Value)
				{
					typedef NCsDamage::NRange::FProxy ProxyType;

					ProxyType* Proxy = static_cast<ProxyType*>(DamageRange);
					Proxy->SetMinRange(Value);
				}

				void FProxy::SetMaxRadius(float* Value)
				{
					typedef NCsDamage::NRange::FProxy ProxyType;

					ProxyType* Proxy = static_cast<ProxyType*>(DamageRange);
					Proxy->SetMaxValue(Value);
				}
			}
		}
	}
}