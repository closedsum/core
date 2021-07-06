// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Visual/CsParams_TraceWeapon_VisualFire.h"

#include "Containers/CsInterfaceMap.h"

#define NCurrentNamespace NCsWeapon::NTrace::NData::NVisual::NFire::NParams

const FName NCurrentNamespace::IParams::Name = FName("NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams::Name");

const FName NCurrentNamespace::FEmu::Name = FName("NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FEmu::Name");

#undef NCurrentNamespace

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					namespace NParams
					{
						FEmu::FEmu() :
							// ICsGetInterfaceMap
							InterfaceMap(nullptr),
							// IParams
							FX(nullptr),
							Attach(nullptr)

						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRoot<FEmu>(this);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FEmu::~FEmu()
						{
							delete InterfaceMap;
						}
					}
				}
			}
		}
	}
}