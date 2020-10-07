// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"

const FName NCsDamage::NData::NPoint::FEmu::Name = FName("NCsDamage::NData::NPoint::FEmu");

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			FEmu::FEmu() :
				// ICsInterfaceMap
				InterfaceMap(nullptr),
				// NCsDamage::NData::IData
				Value(nullptr),
				Type(nullptr)
			{
				// ICsInterfaceMap

				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRootName(FEmu::Name);

				typedef NCsDamage::NData::IData DataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));

				// NCsDamage::NData::IData
				typedef NCsDamage::NValue::NPoint::FEmu ValuePointEmuType;

				Value = new ValuePointEmuType();
			}

			FEmu::~FEmu()
			{
				// ICsInterfaceMap
				if (InterfaceMap)
				{
					delete InterfaceMap;
					InterfaceMap = nullptr;
				}
				// NCsDamage::NData::IData
				if (Value)
				{
					delete Value;
					Value = nullptr;
				}
			}

			void FEmu::SetValue(float* InValue)
			{
				typedef NCsDamage::NValue::NPoint::FEmu EnumType;

				EnumType* Emu = static_cast<EnumType*>(Value);
				Emu->SetValue(InValue);
			}
		}
	}
}