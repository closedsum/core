// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphere.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
// Damage
#include "Value/Range/CsDamageValueRangeImpl.h"
#include "Range/CsDamageRangeImpl.h"
// Log
#include "Utility/CsDmgLog.h"

#include "CsData_DamageSphereImpl.generated.h"

// Proxy
#pragma region

struct FCsInterfaceMap;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

class UCurveFloat;

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
			#define DataType NCsData::IData
			#define DamageDataType NCsDamage::NData::IData
			// Shape
			#define ShapeDataType NCsDamage::NData::NShape::IShape
			#define SphereDataType NCsDamage::NData::NShape::NSphere::ISphere
			// Collision
			#define CollisionDataType NCsDamage::NData::NCollision::ICollision

				/**
				*
				*/
				struct CSDMG_API FProxy : public DataType,
										  public DamageDataType,
										  // Shape
										  public ShapeDataType,
										  public SphereDataType,
										  // Collision
										  public CollisionDataType
				{
				public:

					static const FName Name;

				private:

				#define ValueType NCsDamage::NValue::IValue 
				#define RangeType NCsDamage::NRange::IRange
				// Collision
				#define CollisionInfoType NCsDamage::NCollision::FInfo

					UObject* Outer;

				// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				// DamageDataType (NCsDamage::NData::IData)

					ValueType* Value;

					CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageType)

			// Shape
			
				// ShapeDataType (NCsDamage::NData::NShape::IShape)

					RangeType* Range;
					CS_DECLARE_MEMBER_WITH_PROXY(MinDamage, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MaxDamage, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MinRadius, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MaxRadius, float)
					CS_DECLARE_MEMBER_WITH_PROXY(bInterpolate, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
					CS_DECLARE_MEMBER_WITH_PROXY(EasingType, ECsEasingType)
					CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveFloat*)

			// Collision
			
				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)

					CollisionInfoType* CollisionInfo;

				public:

					FProxy();
					~FProxy();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetValue(ValueType* InValue) { Value = InValue; }

				// DamageDataType (NCsDamage::NData::IData)
				#pragma region
				public:

					FORCEINLINE const ValueType* GetValue() const { return Value; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageType)

				#pragma endregion DamageDataType (NCsDamage::NData::IData)

			// Shape

				public:

					FORCEINLINE void SetRange(RangeType* InValue) { Range = InValue; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinDamage, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxDamage, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinRadius, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxRadius, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInterpolate, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(EasingType, ECsEasingType)
					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveFloat)

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region
				public:

					FORCEINLINE const RangeType* GetRange() const { return Range; }

					float CalculateDamage(const ValueType* InValue, const RangeType* InRange, const FVector3f& Origin, const FVector3f& Point) const;

					bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const;

					FORCEINLINE bool IsFacing(const FVector3f& Direction, const FVector3f& Origin, const FVector3f& Point) const { return true; }

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

			// Collision
			
				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				#pragma region
				public:			

					FORCEINLINE const CollisionInfoType& GetCollisionInfo() const { return *CollisionInfo; }
					FORCEINLINE CollisionInfoType* GetCollisionInfoPtr() { return CollisionInfo; }
					FORCEINLINE void SetCollisionInfo(CollisionInfoType* InValue) { CollisionInfo = InValue; }

				#pragma endregion CollisionDataType (NCsDamage::NData::NCollision::ICollision)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

				#undef ValueType
				#undef RangeType
				// Collision
				#undef CollisionInfoType
				};

			#undef DataType
			#undef DamageDataType
			// Shape
			#undef ShapeDataType
			#undef SphereDataType
			// Collision
			#undef CollisionDataType
			}
		}
	}
}

#pragma endregion FCsData_DamageSphere

// Inner
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamageSphereImpl_Inner
{
	GENERATED_USTRUCT_BODY()

// ICsData_Damage

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Damage|Data")
	FECsDamageType Type;

//  ICsData_DamageSphere

	/** The minimum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Damage|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	/** The maximum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Damage|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	/** The minimum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	/** The maximum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (InlineEditConditionToggle))
	bool bInterpolate;

	/** Describes with method to use for interpolating a set of values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (editcondition = "bInterpolate"))
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min Damage and Max Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (editcondition = "bInterpolate"))
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min Damage and Max Damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Damage|Data", meta = (editcondition = "bInterpolate"))
	FCsCurveFloat Curve;

// ICsData_DamageCollision

	/** Describes any information related to Collision for Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	FCsDamage_CollisionInfo CollisionInfo;

public:

	FCsData_DamageSphereImpl_Inner() :
		// ICsData_Damage
		Type(),
		// ICsData_DamageSphere
		MinDamage(0.0f),
		MaxDamage(0.0f),
		MinRadius(0.0f),
		MaxRadius(0.0f),
		bInterpolate(false),
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		EasingType(ECsEasingType::Linear),
		Curve(),
		// ICsData_DamageCollision
		CollisionInfo()
	{
	}

// ICsData_Damage
	FORCEINLINE FECsDamageType* GetTypePtr() { return &Type; }
// ICsData_DamageSphere
	FORCEINLINE float* GetMinDamagePtr() { return &MinDamage; }
	FORCEINLINE float* GetMaxDamagePtr() { return &MaxDamage; }
	FORCEINLINE float* GetMinRadiusPtr() { return &MinRadius; }
	FORCEINLINE float* GetMaxRadiusPtr() { return &MaxRadius; }
	FORCEINLINE bool* GetbInterpolatePtr() { return &bInterpolate; }
	FORCEINLINE ECsInterpolatingMethod* GetInterpolationMethodPtr() { return &InterpolationMethod; }
	FORCEINLINE ECsEasingType* GetEasingTypePtr() { return &EasingType; }
};

#pragma endregion Inner

struct FCsInterfaceMap;

/**
* Data for a Damage Point
* 
* Implements the interfaces:
*  ICsData
*  ICsData_Damage
* Shape
*  ICsData_DamageShape
*  ICsData_DamageSphere
* Collision
*  ICsData_DamageCollision
*/
UCLASS(BlueprintType, Blueprintable)
class CSDMG_API UCsData_DamageSphereImpl : public UObject,
										   public ICsData,
										   public ICsData_Damage,
										   // Shape
										   public ICsData_DamageShape,
										   public ICsData_DamageSphere,
										   // Collision
										   public ICsData_DamageCollision
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

#define DataType NCsData::IData
#define ValueType NCsDamage::NValue::IValue
#define RangeType NCsDamage::NRange::IRange
// Collision
#define CollisionInfoType NCsDamage::NCollision::FInfo

private:

	DataType* DataProxy;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

protected:

	bool bLoaded;

private:

	void Init();
	void Reset();

	FCsInterfaceMap* InterfaceMap;

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

#pragma endregion ICsGetInterfaceMap

// ICsData
#pragma region
public:

	FORCEINLINE DataType* _getIData() const { return DataProxy; }

	bool IsValid(const int32& LoadFlags);

	void Load(const int32& LoadFlags);
	
	void Unload();

	bool IsLoaded() const;

#pragma endregion ICsData

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_DamageSphereImpl_Inner Inner;

private:

#define ValueRangeImplType NCsDamage::NValue::NRange::FImpl
	ValueRangeImplType DamageValueProxy;
#undef ValueRangeImplType

// ICsData_Damage
#pragma region
public:

	FORCEINLINE const FECsDamageType& GetType() const { return Inner.Type; }
	FORCEINLINE const ValueType* GetValue() const { return &DamageValueProxy; }

#pragma endregion ICsData_Damage

private:

#define RangeImplType NCsDamage::NRange::FImpl
	RangeImplType DamageRangeProxy;
#undef RangeImplType

// ICsData_DamageSphere
#pragma region
public:

	FORCEINLINE const RangeType* GetRange() const { return &DamageRangeProxy; }

	float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector3f& Origin, const FVector3f& Point) const;

	bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const;

	FORCEINLINE bool IsFacing(const FVector3f& Direction, const FVector3f& Origin, const FVector3f& Point) const { return true; }

#pragma endregion ICsData_DamageSphere

private:

	CollisionInfoType CollisionInfoProxy;

// ICsData_DamageCollision
#pragma region
public:

	const CollisionInfoType& GetCollisionInfo() const;

#pragma endregion ICsData_DamageCollision

#undef DataType
#undef ValueType
#undef RangeType
// Collision
#undef CollisionInfoType
};