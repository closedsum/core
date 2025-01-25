// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Value/CsDamageValue.h"
#include "Value/Point/CsDamageValuePointImpl.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NData::NPoint::NProxy::FProxy);

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace NProxy
			{
				using ValuePointImplType = NCsDamage::NValue::NPoint::FImpl;

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

					InterfaceMap->Add<CsDataType>(static_cast<CsDataType*>(this));
					InterfaceMap->Add<CsDamageDataType>(static_cast<CsDamageDataType*>(this));

					// NCsDamage::NData::IData
					Value = new ValuePointImplType();
				}

				FProxy::~FProxy()
				{
					// ICsInterfaceMap
					delete InterfaceMap;
					// CsDamageDataType (NCsDamage::NData::IData)
					delete Value;
				}

				void FProxy::SetValue(float* InValue)
				{
					ValuePointImplType* Impl = static_cast<ValuePointImplType*>(Value);
					Impl->SetValue(InValue);
				}
			}
		}
	}
}