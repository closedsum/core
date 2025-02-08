// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Trace/CsTypes_Trace.h"
#include "Projectile/Params/Launch/Trace/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

#include "Containers/CsGetInterfaceMap.h"

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
					/**
					*/
					struct CSWP_API ITrace : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~ITrace() {}

					private:

						// Allow clearer names without name collisions
						struct _
						{
							using TraceStartType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart;
							using TraceDirectionType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection;
						};

					public:

						/**
						*
						*
						* return Trace Type
						*/
						virtual const ECsTraceType& GetTraceType() const = 0;

						/**
						*
						*
						* return Trace Method
						*/
						virtual const ECsTraceMethod& GetTraceMethod() const = 0;

						/**
						*
						*
						* return Trace Start Type
						*/
						virtual const _::TraceStartType& GetTraceStartType() const = 0;

						/**
						*
						*
						* return Trace Direction Type
						*/
						virtual const _::TraceDirectionType& GetTraceDirectionType() const = 0;

						/**
						*
						*
						* return Distance
						*/
						virtual const float& GetTraceDistance() const = 0;
					};
				}
			}
		}
	}
}