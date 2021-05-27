// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl::Name = FName("NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NTrace
				{
					FImpl::FImpl() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
						LocationType(ELocation::Owner),
						LocationType_Emu(nullptr),
						DirectionType(EDirection::Owner),
						DirectionType_Emu(nullptr),
						DirectionRules(0),
						DirectionRules_Emu(nullptr),
						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
						TraceType(ECsTraceType::Line),
						TraceType_Emu(nullptr),
						TraceMethod(ECsTraceMethod::Single),
						TraceMethod_Emu(nullptr),
						TraceStartType(ETraceStart::LaunchLocation),
						TraceStartType_Emu(nullptr),
						TraceDirectionType(ETraceDirection::Owner),
						TraceDirectionType_Emu(nullptr),
						TraceDistance(0.0f),
						TraceDistance_Emu(nullptr)
					{
						InterfaceMap = new FCsInterfaceMap();

						InterfaceMap->SetRootName(FImpl::Name);

						typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace LaunchTraceParamsType;

						InterfaceMap->Add<LaunchParamsType>(static_cast<LaunchParamsType*>(this));
						InterfaceMap->Add<LaunchTraceParamsType>(static_cast<LaunchTraceParamsType*>(this));
					}

					FImpl::~FImpl()
					{
						delete InterfaceMap;
					}
				}
			}
		}
	}
}