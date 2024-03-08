// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsLibrary_InterfaceMap.h"
#include "Trace/Data/Params/CsParams_TraceWeapon_Trace.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
			#define ParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace

				struct CSWP_API FLibrary : public NCsInterfaceMap::TLibrary<ParamsType>
				{
					/**
					*
					*
					* Context	The calling context.
					* Params	 
					*/
					static const bool IsValidChecked(const FString& Context, const ParamsType* Params);
				};

			#undef ParamsType
			}
		}
	}
}