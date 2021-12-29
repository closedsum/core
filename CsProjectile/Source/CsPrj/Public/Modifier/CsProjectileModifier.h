// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		struct CSPRJ_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier() {}
		};
	}
}