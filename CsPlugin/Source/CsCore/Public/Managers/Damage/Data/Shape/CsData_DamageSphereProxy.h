// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
#pragma once

struct FCsInterfaceMap;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
			#define DataType NCsDamage::NData::IData
			#define ShapeDataType NCsDamage::NData::NShape::IShape
			#define CollisionDataType NCsDamage::NData::NCollision::ICollision

				/**
				*
				*/
				struct CSCORE_API FProxy : public DataType,
										   public ShapeDataType,
										   public CollisionDataType
				{
				public:

					static const FName Name;

				private:

					typedef NCsDamage::NValue::IValue ValueType;
					typedef NCsDamage::NRange::IRange RangeType;

					FCsInterfaceMap* InterfaceMap;

				public:

					// DataType (NCsDamage::NData::IData)
					ValueType* DamageValue;

					FECsDamageType* Type;

					// ShapeDataType (NCsDamage::NData::NShape::IShape)

					RangeType* DamageRange;

					float* MinDamage;

					float* MaxDamage;

					float* MinRadius;

					float* MaxRadius;

					ECsInterpolatingMethod* InterpolationMethod;

					ECsEasingType* EasingType;

					FCsCurveFloat* Curve;

					// CollisionDataType (NCsDamage::NData::NCollision::ICollision)

					bool* bIgnoreHitResultObject;

				public:

					FProxy();
					~FProxy();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetType(FECsDamageType* Value) { Type = Value; }

				// DataType (NCsDamage::NData::IData)
				#pragma region
				public:

					FORCEINLINE const ValueType* GetValue() const { return DamageValue; }
					FORCEINLINE const FECsDamageType& GetType() const { return const_cast<FECsDamageType&>(*Type); }

				#pragma endregion DataType (NCsDamage::NData::IData)

				public:

					void SetMinDamage(float* Value);
					void SetMaxDamage(float* Value);
					void SetMinRadius(float* Value);
					void SetMaxRadius(float* Value);
					FORCEINLINE void SetInterpoloationMethod(ECsInterpolatingMethod* Value) { InterpolationMethod = Value; }
					FORCEINLINE void SetEasingType(ECsEasingType* Value) { EasingType = Value; }
					FORCEINLINE void SetCurve(FCsCurveFloat* Value) { Curve = Value; }

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region
				public:

					FORCEINLINE const RangeType* GetRange() const { return DamageRange; }

					float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const;

					bool IsInBounds(const FVector& Origin, const FVector& Point) const;

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				public:

					FORCEINLINE void SetIgnoreHitResultObject(bool* Value) { bIgnoreHitResultObject = Value; }

				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				#pragma region
				public:

					FORCEINLINE bool IgnoreHitResultObject() const { return *bIgnoreHitResultObject; }

				#pragma endregion CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				};

			#undef DataType
			#undef ShapeDataType
			#undef CollisionDataType
			}
		}
	}
}