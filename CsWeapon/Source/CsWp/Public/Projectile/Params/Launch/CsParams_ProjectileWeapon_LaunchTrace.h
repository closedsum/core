// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Trace/CsTypes_Trace.h"

#include "Containers/CsGetInterfaceMap.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				*/
				struct CSWP_API ITrace : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ITrace() {}

					/**
					*
					*
					* return
					*/
					virtual const ECsTraceType& GetTraceType() const = 0;

					/**
					*
					*
					* return
					*/
					virtual const ECsTraceMethod& GetTraceMethod() const = 0;

					/**
					*
					*
					* return
					*/
					virtual const float& GetTraceDistance() const = 0;
				};
			}
		}
	}
}