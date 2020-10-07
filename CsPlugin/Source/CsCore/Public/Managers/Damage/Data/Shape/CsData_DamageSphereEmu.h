// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
#pragma once

struct FCsInterfaceMap;

// NCsDamage::NValue::IValue
namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

// NCsDamage::NRange::IRange
namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

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
				struct CSCORE_API FEmu : public DataType,
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

					// ICsData_Damage
					ValueType* DamageValue;

					FECsDamageType* Type;

					// ICsData_DamageShape

					RangeType* DamageRange;

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

					FEmu();
					~FEmu();

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

					FORCEINLINE const ValueType* GetValue() const
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

					FORCEINLINE const RangeType* GetRange() const
					{
						return DamageRange;
					}

					float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const;

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

#undef DataType
#undef ShapeDataType
#undef CollisionDataType
			}
		}
	}
}