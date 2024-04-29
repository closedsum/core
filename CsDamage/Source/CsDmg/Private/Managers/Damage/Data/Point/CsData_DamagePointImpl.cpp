// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Point/CsData_DamagePointImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Value/CsLibrary_DamageValue.h"
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Value/CsDamageValue.h"
#include "Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"

// FCsData_DamagePoint
#pragma region

#define PointType NCsDamage::NData::NPoint::FImpl

void FCsData_DamagePoint::CopyToPoint(PointType* Point)
{
	Point->SetValue(&Value);
	Point->SetType(&Type);
}

void FCsData_DamagePoint::CopyToPointAsValue(PointType* Point) const
{
	Point->SetValue(Value);
	Point->SetType(Type);
}

#undef PointType

bool FCsData_DamagePoint::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, Type)
	return true;
}

const FName NCsDamage::NData::NPoint::FImpl::Name = FName("NCsDamage::NData::NPoint::FImpl");

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			FImpl::FImpl() :
				// ICsInterfaceMap
				InterfaceMap(nullptr),
				// DamageDataType (NCsDamage::NData::IData)
				Value(),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type)
			{
				// ICsInterfaceMap

				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				typedef NCsData::IData DataType;
				typedef NCsDamage::NData::IData DamageDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<DamageDataType>(static_cast<DamageDataType*>(this));

				CS_CTOR_SET_MEMBER_PROXY(Type);
			}

			FImpl::~FImpl()
			{
				// ICsInterfaceMap
				delete InterfaceMap;
			}

			bool FImpl::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageType, GetType());
				return true;
			}

			bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, GetType())
				return true;
			}
		}
	}
}

#pragma endregion FCsData_DamagePoint


const FName UCsData_DamagePointImpl::Name = FName("UCsData_DamagePointImpl");

UCsData_DamagePointImpl::UCsData_DamagePointImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	DataProxy(nullptr),
	bLoaded(false),
	InterfaceMap(nullptr),
	// ICsData_Damage
	Value(0.0f),
	Type(),
	DamageDataPointProxy(nullptr)
{
}

// UObject Interface
#pragma region

void UCsData_DamagePointImpl::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_DamagePointImpl>())
	{
		//Init();
		bLoaded = false;
	}
}

void UCsData_DamagePointImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Reset();
}

#pragma endregion UObject Interface

void UCsData_DamagePointImpl::Init()
{
	Reset();

	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_DamagePointImpl>(this);

		typedef ICsData DataType;
		typedef ICsData_Damage DamageDataType;


		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<DamageDataType>(Cast<DamageDataType>(this));
	}
	if (!DataProxy)
	{
		typedef NCsDamage::NData::NPoint::FProxy DataProxyType;

		DamageDataPointProxy = new DataProxyType();

		DamageDataPointProxy->SetOuter(this);
		DamageDataPointProxy->SetValue(&Value);
		DamageDataPointProxy->SetType(&Type);

		DataProxy = DamageDataPointProxy;
	}
}

void UCsData_DamagePointImpl::Reset()
{
	CS_SAFE_DELETE_PTR(DataProxy)
	CS_SAFE_DELETE_PTR(InterfaceMap)
}

// ICsData
#pragma region

bool UCsData_DamagePointImpl::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_DamagePointImpl::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

	Init();

	bLoaded = true;
}

void UCsData_DamagePointImpl::TopLoad()
{
	if (!DataProxy)
		Init();
}

void UCsData_DamagePointImpl::Unload()
{

}

bool UCsData_DamagePointImpl::IsLoaded() const
{
#if WITH_EDITOR
	return false;
#else
	return bLoaded;
#endif // #if WITH_EDITOR
}

#pragma endregion ICsData

// ICsData_Damage
#pragma region

#define ValueType NCsDamage::NValue::IValue
const ValueType* UCsData_DamagePointImpl::GetValue() const
{
#undef ValueType

	return DamageDataPointProxy->GetValue();
}

#pragma endregion ICsData_Damage