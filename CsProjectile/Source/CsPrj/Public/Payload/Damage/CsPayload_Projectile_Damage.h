// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NDamage
		{
			/**
			*/
			struct CSPRJ_API IDamage : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IDamage(){}

				virtual const TArray<FECsDamageData>& GetDamageDataTypes() const = 0;
			};
		}
	}
}