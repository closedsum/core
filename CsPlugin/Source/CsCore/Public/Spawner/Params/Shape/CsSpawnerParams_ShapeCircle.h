// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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