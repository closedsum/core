// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/CsTypes_SpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NShape
		{
			struct CSSPAWNER_API ICircle : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ICircle(){}
	
				virtual const float& GetMinRadius() const = 0;

				virtual const float& GetMaxRadius() const = 0;
			};
		}
	}
}