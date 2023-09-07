// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"

// Library
#include "Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Value/CsDamageValue.h"
#include "Value/Point/CsDamageValuePointImpl.h"

const FName NCsDamage::NData::NPoint::FProxy::Name = FName("NCsDamage::NData::NPoint::FProxy");

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			FProxy::FProxy() :
				Outer(nullptr),
				// ICsInterfaceMap
				InterfaceMap(nullptr),
				// DataType (NCsDamage::NData::IData)
				Value(nullptr),
				Type(nullptr)
			{
				// ICsInterfaceMap

				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FProxy>(this);

				typedef NCsData::IData DataType;
				typedef NCsDamage::NData::IData DamageDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<DamageDataType>(static_cast<DamageDataType*>(this));

				// NCsDamage::NData::IData
				typedef NCsDamage::NValue::NPoint::FImpl ValuePointImplType;

				Value = new ValuePointImplType();
			}

			FProxy::~FProxy()
			{
				// ICsInterfaceMap
				delete InterfaceMap;
				// DamageDataType (NCsDamage::NData::IData)
				delete Value;
			}

			void FProxy::SetValue(float* InValue)
			{
				typedef NCsDamage::NValue::NPoint::FImpl ValuePointImplType;

				ValuePointImplType* Impl = static_cast<ValuePointImplType*>(Value);
				Impl->SetValue(InValue);
			}
		}
	}
}