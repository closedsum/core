// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Spawner/Params/CsTypes_SpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NShape
		{
			struct CSCORE_API ICircle : public ICsGetInterfaceMap
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