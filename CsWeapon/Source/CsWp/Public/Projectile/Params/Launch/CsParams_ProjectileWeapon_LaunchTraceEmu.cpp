// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceEmu.h"

// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NProjectile::NParams::NLaunch::FTraceEmu::Name = FName("NCsWeapon::NProjectile::NParams::NLaunch::FTraceEmu");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				FTraceEmu::FTraceEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ILaunch
					LocationType(nullptr),
					DirectionType(nullptr),
					DirectionRules(nullptr),
					// ITrace
					TraceType(nullptr),
					TraceMethod(nullptr),
					TraceStartType(nullptr),
					TraceDirectionType(nullptr),
					TraceDistance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FTraceEmu::Name);

					InterfaceMap->Add<ILaunch>(static_cast<ILaunch*>(this));
					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FTraceEmu::~FTraceEmu()
				{
					delete InterfaceMap;
				}
			}
		}
	}
}