// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphereImpl.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Range/CsDamageRangeImpl.h"

// FCsData_DamageSphere
#pragma region

#define SphereType NCsDamage::NData::NShape::NSphere::FImpl

void FCsData_DamageSphere::CopyToSphere(SphereType* Sphere)
{
	Sphere->SetType(&Type);
	Sphere->SetMinDamage(&MinDamage);
	Sphere->SetMaxDamage(&MaxDamage);
	Sphere->SetMinRadius(&MinRadius);
	Sphere->SetMaxRadius(&MaxRadius);
	Sphere->SetInterpolationMethod(&InterpolationMethod);
	Sphere->SetEasingType(&EasingType);
	Sphere->SetCurve(Curve.GetPtr());

	typedef NCsDamage::NCollision::EMethod CollisionMethodType;

	Sphere->SetCollisionMethod((CollisionMethodType*)(&CollisionMethod));
	Sphere->SetCollisionChannel((ECollisionChannel*)(&CollisionChannel));
}

void FCsData_DamageSphere::CopyToSphereAsValue(SphereType* Sphere)
{
	Sphere->SetType(Type);
	Sphere->SetMinDamage(MinDamage);
	Sphere->SetMaxDamage(MaxDamage);
	Sphere->SetMinRadius(MinRadius);
	Sphere->SetMaxRadius(MaxRadius);
	Sphere->SetInterpolationMethod(InterpolationMethod);
	Sphere->SetEasingType(EasingType);
	Sphere->SetCurve(Curve.Get());

	typedef NCsDamage::NCollision::EMethod CollisionMethodType;

	Sphere->SetCollisionMethod((CollisionMethodType)(CollisionMethod));
	Sphere->SetCollisionChannel((ECollisionChannel)(CollisionChannel));
}

#undef SphereType

bool FCsData_DamageSphere::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageType, Type);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(MinDamage, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MaxDamage, MinDamage)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(MinRadius, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MaxRadius, MinRadius)
	CS_IS_ENUM_VALID_CHECKED(EMCsInterpolatingMethod, InterpolationMethod);
	CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, EasingType);

	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		Curve.IsValidChecked(Context);
	}
	CS_IS_ENUM_VALID_CHECKED(EMCsDamageCollisionMethod, CollisionMethod);
	CS_IS_ENUM_VALID_CHECKED(EMCsCollisionChannel, CollisionChannel);
	return true;
}

bool FCsData_DamageSphere::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, Type);
	CS_IS_FLOAT_GREATER_THAN(MinDamage, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MaxDamage, MinDamage)
	CS_IS_FLOAT_GREATER_THAN(MinRadius, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MaxRadius, MinRadius)
	CS_IS_ENUM_VALID(EMCsInterpolatingMethod, ECsInterpolatingMethod, InterpolationMethod);
	CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, EasingType);

	if (InterpolationMethod == ECsInterpolatingMethod::Curve)
	{
		if (!Curve.IsValid(Context))
			return false;
	}
	CS_IS_ENUM_VALID(EMCsDamageCollisionMethod, ECsDamageCollisionMethod, CollisionMethod);
	CS_IS_ENUM_VALID(EMCsCollisionChannel, ECollisionChannel, CollisionChannel);
	return true;
}

const FName NCsDamage::NData::NShape::NSphere::FImpl::Name = FName("NCsDamage::NData::NShape::NSphere::FImpl");

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
				FImpl::FImpl() :
					Outer(nullptr),
					// ICsGetInterfaceMap
					InterfaceMap(),
					// DataType (NCsDamage::NData::IData)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, nullptr),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					// ShapeDataType (NCsDamage::NData::NShape::IShape)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Range, nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinDamage, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxDamage, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinRadius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxRadius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod::Easing),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(EasingType, ECsEasingType::Linear),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
					// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionMethod, NCsDamage::NCollision::EMethod::PhysicsOverlap),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionChannel, ECollisionChannel::ECC_WorldDynamic)
				{
					// ICsGetInterfaceMap
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsData::IData DataType;
					typedef NCsDamage::NData::IData DamageDataType;
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<DamageDataType>(static_cast<DamageDataType*>(this));
					InterfaceMap->Add<ShapeDataType>(static_cast<ShapeDataType*>(this));
					InterfaceMap->Add<CollisionDataType>(static_cast<CollisionDataType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(MinDamage);
					CS_CTOR_SET_MEMBER_PROXY(MaxDamage);
					CS_CTOR_SET_MEMBER_PROXY(MinRadius);
					CS_CTOR_SET_MEMBER_PROXY(MaxRadius);
					CS_CTOR_SET_MEMBER_PROXY(InterpolationMethod);
					CS_CTOR_SET_MEMBER_PROXY(EasingType);
					CS_CTOR_SET_MEMBER_PROXY(Curve);
					CS_CTOR_SET_MEMBER_PROXY(CollisionMethod);
					CS_CTOR_SET_MEMBER_PROXY(CollisionChannel);

					// NCsDamage::NValue::NRange::IRange
					{
						typedef NCsDamage::NValue::NRange::FImpl ValueImplType;
						ValueImplType* Impl = new ValueImplType();

						Impl->SetMinValue(GetMinDamagePtr());
						Impl->SetMaxValue(GetMaxDamagePtr());

						Value = Impl;
					}
					CS_CTOR_SET_MEMBER_PROXY(Value);

					// NCsDamage::NRange::IRange
					{
						typedef NCsDamage::NRange::FImpl RangeImplType;
						RangeImplType* Impl = new RangeImplType();

						Impl->SetMinRange(GetMinRadiusPtr());
						Impl->SetMaxRange(GetMaxRadiusPtr());

						Range = Impl;
					}
					CS_CTOR_SET_MEMBER_PROXY(Range);
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
					delete Value;
					delete Range;
				}

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region

				#define ValueType NCsDamage::NValue::IValue
				#define RangeType NCsDamage::NRange::IRange
				float FImpl::CalculateDamage(const ValueType* InValue, const RangeType* InRange, const FVector& Origin, const FVector& Point) const
				{
				#undef ValueType
				#undef RangeType

					return 0.0f;
				}

				bool FImpl::IsInBounds(const FVector& Origin, const FVector& Point) const
				{
					return false;
				}

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					return true;
				}
				
				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
				{
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsData_DamageSphere

const FName UCsData_DamageSphereImpl::Name = FName("UCsData_DamageSphereImpl");

UCsData_DamageSphereImpl::UCsData_DamageSphereImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	DataProxy(nullptr),
	bLoaded(false),
	InterfaceMap(nullptr),
	// ICsData_Damage
	DamageValue(nullptr),
	Type(),
	// ICsData_DamageSphere
	MinDamage(0.0f),
	MaxDamage(0.0f),
	MinRadius(0.0f),
	MaxRadius(0.0f),
	InterpolationMethod(ECsInterpolatingMethod::Easing),
	EasingType(ECsEasingType::Linear),
	Curve(),
	DamageRange(nullptr),
	// ICsData_DamageCollision
	CollisionMethod(ECsDamageCollisionMethod::PhysicsOverlap),
	CollisionChannel(ECollisionChannel::ECC_WorldDynamic)
{
}

// UObject Interface
#pragma region

void UCsData_DamageSphereImpl::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_DamageSphereImpl>())
	{
		//Init();
		bLoaded = false;
	}
}

void UCsData_DamageSphereImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Reset();
}

#pragma endregion UObject Interface

void UCsData_DamageSphereImpl::Init()
{
	Reset();

	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_DamageSphereImpl>(this);

		typedef ICsData DataType;
		typedef ICsData_Damage DamageDataType;
		typedef ICsData_DamageShape DamageShapeDataType;
		typedef ICsData_DamageCollision DamageCollisionDataType;

		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<DamageDataType>(Cast<DamageDataType>(this));
		InterfaceMap->Add<DamageShapeDataType>(Cast<DamageShapeDataType>(this));
		InterfaceMap->Add<DamageCollisionDataType>(Cast<DamageCollisionDataType>(this));
	}
	if (!DataProxy)
	{
		typedef NCsDamage::NData::NShape::NSphere::FImpl DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// DataType (NCsDamage::NData::IData)
		
		// ValueRangeType (NCsDamage::NValue::NRange::IRange)
		{
			typedef NCsDamage::NValue::NRange::FImpl ValueImplType;
			ValueImplType* Impl = new ValueImplType();

			Impl->SetMinValue(&MinDamage);
			Impl->SetMaxValue(&MaxDamage);

			DamageValue = Impl;
		}
		Proxy->SetValue(&DamageValue);
		Proxy->SetType(&Type);

		// RangeType (NCsDamage::NRange::IRange)
		{
			typedef NCsDamage::NRange::FImpl RangeImplType;
			RangeImplType* Impl = new RangeImplType();

			Impl->SetMinRange(&MinRadius);
			Impl->SetMaxRange(&MaxRadius);

			DamageRange = Impl;
		}
		Proxy->SetRange(&DamageRange);
		Proxy->SetMinDamage(&MinDamage);
		Proxy->SetMaxDamage(&MaxDamage);
		Proxy->SetMinRadius(&MinRadius);
		Proxy->SetMaxRadius(&MaxRadius);
		Proxy->SetInterpolationMethod(&InterpolationMethod);
		Proxy->SetEasingType(&EasingType);
		Proxy->SetCurve(Curve.GetPtr());

		typedef NCsDamage::NCollision::EMethod CollisionMethodType;

		Proxy->SetCollisionMethod((CollisionMethodType*)(&CollisionMethod));
		Proxy->SetCollisionChannel((ECollisionChannel*)(&CollisionChannel));
	}
}

void UCsData_DamageSphereImpl::Reset()
{
	CS_SAFE_DELETE_PTR(DataProxy)
	CS_SAFE_DELETE_PTR(InterfaceMap)
	CS_SAFE_DELETE_PTR(DamageValue)
	CS_SAFE_DELETE_PTR(DamageRange)
}

// ICsData
#pragma region

bool UCsData_DamageSphereImpl::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_DamageSphereImpl::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

	Init();

	bLoaded = true;
}

void UCsData_DamageSphereImpl::Unload()
{

}

bool UCsData_DamageSphereImpl::IsLoaded() const
{
#if WITH_EDITOR
	return false;
#else
	return bLoaded;
#endif // #if WITH_EDITOR
}

#pragma endregion ICsData

// ICsData_DamageSphere
#pragma region

#define ValueType NCsDamage::NValue::IValue
#define RangeType NCsDamage::NRange::IRange
float UCsData_DamageSphereImpl::CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const
{
#undef ValueType
#undef RangeType

	return 0.0f;
}


bool UCsData_DamageSphereImpl::IsInBounds(const FVector& Origin, const FVector& Point) const
{
	return false;
}

#pragma endregion ICsData_DamageSphere