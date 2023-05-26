// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsProjectile;

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