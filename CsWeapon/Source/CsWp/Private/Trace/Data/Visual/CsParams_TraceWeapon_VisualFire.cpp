// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Visual/CsParams_TraceWeapon_VisualFire.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams::Name = FName("NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams::Name");

const FName NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FProxy::Name = FName("NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FProxy::Name");

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
						FProxy::FProxy() :
							// ICsGetInterfaceMap
							InterfaceMap(nullptr),
							// IParams
							FX(nullptr),
							Attach(nullptr)

						{
							InterfaceMap = new FCsInterfaceMap();

							InterfaceMap->SetRoot<FProxy>(this);

							InterfaceMap->Add<IParams>(static_cast<IParams*>(this));
						}

						FProxy::~FProxy()
						{
							delete InterfaceMap;
						}
					}
				}
			}
		}
	}
}