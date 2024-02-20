// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphereImpl.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Value/CsLibrary_DamageValue.h"
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Value/Point/CsDamageValuePoint.h"

// FProxy
#pragma region

const FName NCsDamage::NData::NShape::NSphere::FProxy::Name = FName("NCsDamage::NData::NShape::NSphere::FProxy");

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
				namespace NProxy
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NData::NShape::NSphere::FImpl, CalculateDamage);
						}
					}
				}

				FProxy::FProxy() :
					Outer(nullptr),
					// ICsGetInterfaceMap
					InterfaceMap(),
					// DataType (NCsDamage::NData::IData)
					Value(nullptr),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				// Shape
					// ShapeDataType (NCsDamage::NData::NShape::IShape)
					Range(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinDamage, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxDamage, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinRadius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxRadius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bInterpolate, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod::Easing),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(EasingType, ECsEasingType::Linear),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
				// Collision
					// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
					CollisionInfo(nullptr)
				{
					// ICsGetInterfaceMap
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FProxy>(this);

					typedef NCsData::IData DataType;
					typedef NCsDamage::NData::IData DamageDataType;
					// Shape
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;
					typedef NCsDamage::NData::NShape::NSphere::ISphere SphereDataType;
					// Collision
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<DamageDataType>(static_cast<DamageDataType*>(this));
					// Shape
					InterfaceMap->Add<ShapeDataType>(static_cast<ShapeDataType*>(this));
					InterfaceMap->Add<SphereDataType>(static_cast<SphereDataType*>(this));
					// Collision
					InterfaceMap->Add<CollisionDataType>(static_cast<CollisionDataType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(MinDamage);
					CS_CTOR_SET_MEMBER_PROXY(MaxDamage);
					CS_CTOR_SET_MEMBER_PROXY(MinRadius);
					CS_CTOR_SET_MEMBER_PROXY(MaxRadius);
					CS_CTOR_SET_MEMBER_PROXY(bInterpolate);
					CS_CTOR_SET_MEMBER_PROXY(InterpolationMethod);
					CS_CTOR_SET_MEMBER_PROXY(EasingType);
					CS_CTOR_SET_MEMBER_PROXY(Curve);
				}

				FProxy::~FProxy()
				{
					delete InterfaceMap;
				}

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				#pragma region

				#define ValueType NCsDamage::NValue::IValue
				#define RangeType NCsDamage::NRange::IRange
				float FProxy::CalculateDamage(const ValueType* InValue, const RangeType* InRange, const FVector3f& Origin, const FVector3f& Point) const
				{
				#undef ValueType
				#undef RangeType

					using namespace NCsDamage::NData::NShape::NSphere::NProxy::NCached;

					const FString& Context = Str::CalculateDamage;

					CS_IS_PTR_NULL_CHECKED(InValue)
					CS_IS_PTR_NULL_CHECKED(InRange)

					// Value
					typedef NCsDamage::NValue::FLibrary ValueLibrary;
					typedef NCsDamage::NValue::NPoint::IPoint ValuePointType;
					typedef NCsDamage::NValue::NRange::IRange ValueRangeType;

					float MinValue = 0.0f;
					float MaxValue = 0.0f;

					// Point
					if (const ValuePointType* ValuePoint = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, InValue))
					{
						MinValue = ValuePoint->GetValue();
						MaxValue = MinValue;
					}
					// Range
					else
					if (const ValueRangeType* ValueRange = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, InValue))
					{
						MinValue = ValueRange->GetMinValue();
						MaxValue = ValueRange->GetMaxValue();
					}
					else
					{
						checkf(0, TEXT("%s: Failed to get Min Value or Max Value from InValue."), *Context);
					}

					// Range
					const float& MinRange = InRange->GetMinRange();
					const float& MaxRange = InRange->GetMaxRange();

					if (GetbInterpolate())
					{
						if (GetInterpolationMethod() == ECsInterpolatingMethod::Easing)
						{
							typedef NCsMath::FLibrary MathLibrary;

							const float Distance = (Point - Origin).Size();
							const float Alpha1	 = (Distance - MinRange) / (MaxRange - MinRange);
							const float Alpha2   = MathLibrary::Ease(GetEasingType(), Alpha1, 0.0f, 1.0f, 1.0f);

							return FMath::Lerp(MinValue, MaxValue, Alpha2);
						}
						checkf(0, TEXT("%s: GetInterpolationMethod(): %s currently NOT supported."), *Context, EMCsInterpolatingMethod::Get().ToChar(GetInterpolationMethod()));
					}
					return MaxValue;
				}

				bool FProxy::IsInBounds(const FVector3f& Origin, const FVector3f& Point) const
				{
					return false;
				}

				#pragma endregion ShapeDataType (NCsDamage::NData::NShape::IShape)

				bool FProxy::IsValidChecked(const FString& Context) const
				{
					CS_IS_VALID_CHECKED(GetCollisionInfo());
					return true;
				}
				
				bool FProxy::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
				{
					CS_IS_VALID(GetCollisionInfo())
					return true;
				}
			}
		}
	}
}

#pragma endregion Proxy

const FName UCsData_DamageSphereImpl::Name = FName("UCsData_DamageSphereImpl");

UCsData_DamageSphereImpl::UCsData_DamageSphereImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	DataProxy(nullptr),
	bLoaded(false),
	InterfaceMap(nullptr),
	Inner(),
	// ICsData_Damage
	DamageValueProxy(),
	// ICsData_DamageSphere
	DamageRangeProxy(),
// Collision
	// ICsData_DamageCollision
	CollisionInfoProxy()
{
}

// UObject Interface
#pragma region

void UCsData_DamageSphereImpl::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_DamageSphereImpl>())
	{
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
		// Shape
		typedef ICsData_DamageShape ShapeDataType;
		typedef ICsData_DamageSphere SphereDataType;
		// Collision
		typedef ICsData_DamageCollision CollisionDataType;

		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<DamageDataType>(Cast<DamageDataType>(this));
		// Shape
		InterfaceMap->Add<ShapeDataType>(Cast<ShapeDataType>(this));
		InterfaceMap->Add<SphereDataType>(Cast<SphereDataType>(this));
		// Collision
		InterfaceMap->Add<CollisionDataType>(Cast<CollisionDataType>(this));
	}
	if (!DataProxy)
	{
		typedef NCsDamage::NData::NShape::NSphere::FProxy DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// DataType (NCsDamage::NData::IData)
		
		// ValueRangeType (NCsDamage::NValue::NRange::IRange)
		DamageValueProxy.SetMinValue(Inner.GetMinDamagePtr());
		DamageValueProxy.SetMaxValue(Inner.GetMaxDamagePtr());
		Proxy->SetValue(&DamageValueProxy);
		Proxy->SetType(Inner.GetTypePtr());

	// Shape
		// RangeType (NCsDamage::NRange::IRange)
		DamageRangeProxy.SetMinRange(Inner.GetMinRadiusPtr());
		DamageRangeProxy.SetMaxRange(Inner.GetMaxRadiusPtr());
		Proxy->SetRange(&DamageRangeProxy);
		Proxy->SetMinDamage(Inner.GetMinDamagePtr());
		Proxy->SetMaxDamage(Inner.GetMaxDamagePtr());
		Proxy->SetMinRadius(Inner.GetMinRadiusPtr());
		Proxy->SetMaxRadius(Inner.GetMaxRadiusPtr());
		Proxy->SetbInterpolate(Inner.GetbInterpolatePtr());
		Proxy->SetInterpolationMethod(Inner.GetInterpolationMethodPtr());
		Proxy->SetEasingType(Inner.GetEasingTypePtr());
		Proxy->SetCurve(Inner.Curve.GetPtr());

	// Collision
		// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
		typedef NCsDamage::NCollision::EMethod CollisionMethodType;

		Inner.CollisionInfo.CopyToInfo(&CollisionInfoProxy);
		Proxy->SetCollisionInfo(&CollisionInfoProxy);
	}
}

void UCsData_DamageSphereImpl::Reset()
{
	CS_SAFE_DELETE_PTR(DataProxy)
	CS_SAFE_DELETE_PTR(InterfaceMap)
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

void UCsData_DamageSphereImpl::TopLoad()
{
	if (!DataProxy)
		Init();
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
float UCsData_DamageSphereImpl::CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector3f& Origin, const FVector3f& Point) const
{
#undef ValueType
#undef RangeType

	return 0.0f;
}


bool UCsData_DamageSphereImpl::IsInBounds(const FVector3f& Origin, const FVector3f& Point) const
{
	return false;
}

#pragma endregion ICsData_DamageSphere

// ICsData_DamageCollision
#pragma region

#define CollisionInfoType NCsDamage::NCollision::FInfo
const CollisionInfoType& UCsData_DamageSphereImpl::GetCollisionInfo() const
{
#undef CollisionInfoType
	typedef NCsDamage::NData::NShape::NSphere::FProxy DataProxyType;

	const DataProxyType* Proxy = (DataProxyType*)DataProxy;

	return Proxy->GetCollisionInfo();
}

#pragma endregion ICsData_DamageCollision