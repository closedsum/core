// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Point/CsData_DamagePointImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
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

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_DamagePointImpl)

using PointImplType = NCsDamage::NData::NPoint::NImpl::FImpl;

// FCsData_DamagePoint
#pragma region

void FCsData_DamagePoint::CopyToPoint(PointImplType* Point)
{
	CS_COPY_TO_PROXY(Point, Value);
	CS_COPY_TO_PROXY(Point, Type);
}

void FCsData_DamagePoint::CopyToPointAsValue(PointImplType* Point) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Point, Value);
	CS_COPY_TO_PROXY_AS_VALUE(Point, Type);
}

bool FCsData_DamagePoint::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageType, FECsDamageType, Type)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NData::NPoint::NImpl::FImpl);

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace NImpl
			{
				FImpl::FImpl() :
					// ICsInterfaceMap
					InterfaceMap(nullptr),
					// CsDamageDataType (NCsDamage::NData::IData)
					Value(),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type)
				{
					// ICsInterfaceMap

					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					InterfaceMap->Add<CsDataType>(static_cast<CsDataType*>(this));
					InterfaceMap->Add<CsDamageDataType>(static_cast<CsDamageDataType*>(this));

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
}

#pragma endregion FCsData_DamagePoint

CS_CLASS_DEFINE_STATIC_CONST_FNAME(UCsData_DamagePointImpl);

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

using ValueType = NCsDamage::NValue::IValue;

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
		using DataProxyType = NCsDamage::NData::NPoint::NProxy::FProxy;

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
	CsLoadLibrary::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

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

const ValueType* UCsData_DamagePointImpl::GetValue() const
{
	return DamageDataPointProxy->GetValue();
}

#pragma endregion ICsData_Damage