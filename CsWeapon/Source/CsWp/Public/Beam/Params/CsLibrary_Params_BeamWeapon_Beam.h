// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsLibrary_InterfaceMap.h"
#include "Beam/Params/CsParams_BeamWeapon_Beam.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
			#define ParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam

				struct CSWP_API FLibrary : public TCsLibrary_InterfaceMap<ParamsType>
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