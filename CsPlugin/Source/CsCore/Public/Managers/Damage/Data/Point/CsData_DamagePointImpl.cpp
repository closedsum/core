// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Point/CsData_DamagePointImpl.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"

#define PointType NCsDamage::NData::NPoint::FImpl

void FCsData_DamagePointImpl::CopyToPoint(PointType* Point)
{
	Point->SetValue(&Value);
	Point->SetType(&Type);
}

void FCsData_DamagePointImpl::CopyToPointAsValue(PointType* Point) const
{
	Point->SetValue(Value);
	Point->SetType(Type);
}

#undef PointType

bool FCsData_DamagePointImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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
				// DataType (NCsDamage::NData::IData)
				Value(),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type)
			{
				// ICsInterfaceMap

				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				typedef NCsDamage::NData::IData DataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));

				CS_CTOR_SET_MEMBER_PROXY(Type);
			}

			FImpl::~FImpl()
			{
				// ICsInterfaceMap
				delete InterfaceMap;
			}

			bool FImpl::IsValidChecked(const FString& Context) const
			{
				check(EMCsDamageType::Get().IsValidEnumChecked(Context, GetType()));
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