// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
// Damage
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
// Log
#include "Utility/CsDmgLog.h"

#include "CsData_DamageSphereImpl.generated.h"

// FCsData_DamageSphere
#pragma region

// NCsDamage::NData::NShape::NSphere::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NShape, NSphere, FImpl)

/**
* Data for a Damage Sphere
* 
* Implements the interfaces:
*  ICsData
*  ICsData_Damage
*  ICsData_DamageSphere
*  ICsData_DamageCollision
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamageSphere
{
	GENERATED_USTRUCT_BODY()

// ICsData_Damage

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FECsDamageType Type;

//  ICsData_DamageSphere

	/** The minimum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	/** The maximum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	/** The minimum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	/** The maximum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	/** Describes with method to use for interpolating a set of values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min Damage and Max Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min Damage and Max Damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	FCsCurveFloat Curve;

// ICsData_DamageCollision

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	ECsDamageCollisionMethod CollisionMethod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

public:

	FCsData_DamageSphere() :
		Type(),
		MinDamage(0.0f),
		MaxDamage(0.0f),
		MinRadius(0.0f),
		MaxRadius(0.0f),
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		EasingType(ECsEasingType::Linear),
		Curve(),
		CollisionMethod(ECsDamageCollisionMethod::PhysicsOverlap),
		CollisionChannel(ECollisionChannel::ECC_WorldDynamic)
	{
	}

#define SphereType NCsDamage::NData::NShape::NSphere::FImpl
	void CopyToSphere(SphereType* Sphere);
	void CopyToSphereAsValue(SphereType* Sphere);
#undef SphereType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

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
			#define ShapeDataType NCsDamage::NData::NShape::IShape
			#define CollisionDataType NCsDamage::NData::NCollision::ICollision

				/**
				*
				*/
				struct CSDMG_API FImpl : public DataType,
										 public DamageDataType,
										 public ShapeDataType,
										 public CollisionDataType
				{
				public:

					static const FName Name;

				private:

				#define ValueType NCsDamage::NValue::IValue 
				#define RangeType NCsDamage::NRange::IRange
				#define CollisionMethodType NCsDamage::NCollision::EMethod

					UObject* Outer;

				// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				// DamageDataType (NCsDamage::NData::IData)

					CS_DECLARE_MEMBER_WITH_PROXY(Value, ValueType*)
					CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageType)

				// ShapeDataType (NCsDamage::NData::NShape::IShape)

					CS_DECLARE_MEMBER_WITH_PROXY(Range, RangeType*)
					CS_DECLARE_MEMBER_WITH_PROXY(MinDamage, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MaxDamage, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MinRadius, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MaxRadius, float)
					CS_DECLARE_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
					CS_DECLARE_MEMBER_WITH_PROXY(EasingType, ECsEasingType)
					CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveFloat*)

					// CollisionDataType (NCsDamage::NData::NCollision::ICollision)

					CS_DECLARE_MEMBER_WITH_PROXY(CollisionMethod, CollisionMethodType)
					CS_DECLARE_MEMBER_WITH_PROXY(CollisionChannel, ECollisionChannel)

				public:

					FImpl();
					~FImpl();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// DamageDataType (NCsDamage::NData::IData)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Value, ValueType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageType)

				#pragma endregion DamageDataType (NCsDamage::NData::IData)

				public:

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinDamage, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxDamage, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinRadius, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxRadius, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(EasingType, ECsEasingType)
					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveFloat)

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Range, RangeType)

					float CalculateDamage(const ValueType* InValue, const RangeType* InRange, const FVector& Origin, const FVector& Point) const;

					bool IsInBounds(const FVector& Origin, const FVector& Point) const;

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				#pragma region
				public:			

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionMethod, CollisionMethodType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionChannel, ECollisionChannel)

				#pragma endregion CollisionDataType (NCsDamage::NData::NCollision::ICollision)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

				#undef ValueType
				#undef RangeType
				#undef CollisionMethodType
				};

			#undef DataType
			#undef DamageDataType
			#undef ShapeDataType
			#undef CollisionDataType
			}
		}
	}
}

#pragma endregion FCsData_DamageSphere

struct FCsInterfaceMap;

/**
* Data for a Damage Point
* 
* Implements the interfaces:
*  ICsData
*  ICsData_Damage
*  ICsData_DamageSphere
*  ICsData_DamageCollision
*/
UCLASS(BlueprintType, Blueprintable)
class CSDMG_API UCsData_DamageSphereImpl : public UObject,
										   public ICsData,
										   public ICsData_Damage,
										   public ICsData_DamageShape,
										   public ICsData_DamageCollision
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

#define DataType NCsData::IData
#define ValueType NCsDamage::NValue::IValue
#define RangeType NCsDamage::NRange::IRange

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

private:

	ValueType* DamageValue;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsDamageType Type;

// ICsData_Damage
#pragma region
public:

	FORCEINLINE const FECsDamageType& GetType() const { return Type; }
	FORCEINLINE const ValueType* GetValue() const { return DamageValue; }

#pragma endregion ICsData_Damage

public:

	/** The minimum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinDamage;

	/** The maximum damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxDamage;

	/** The minimum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinRadius;

	/** The maximum range at which the damage is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRadius;

	/** Describes with method to use for interpolating a set of values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsInterpolatingMethod InterpolationMethod;

	/** Valid if InterpolationMethod == ECsInterpolationMethod::Easing. 
	    Easing method for interpolating values between Min Damage and Max Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsEasingType EasingType;

	/** Curve [0,1] for interpolating values between Min Damage and Max Damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCurveFloat Curve;

private:

	RangeType* DamageRange;

// ICsData_DamageSphere
#pragma region
public:

	FORCEINLINE const RangeType* GetRange() const { return DamageRange; }

	float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const;

	bool IsInBounds(const FVector& Origin, const FVector& Point) const;

#pragma endregion ICsData_DamageSphere

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDamageCollisionMethod CollisionMethod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

// ICsData_DamageCollision
#pragma region
public:

#define CollisionMethodType NCsDamage::NCollision::EMethod
	FORCEINLINE const CollisionMethodType& GetCollisionMethod() const { return *((CollisionMethodType*)(&CollisionMethod)); }
#undef CollisionMethodType

	FORCEINLINE const ECollisionChannel& GetCollisionChannel() const { return *((ECollisionChannel*)(&CollisionChannel)); }

#pragma endregion ICsData_DamageCollision

#undef DataType
#undef ValueType
#undef RangeType
};