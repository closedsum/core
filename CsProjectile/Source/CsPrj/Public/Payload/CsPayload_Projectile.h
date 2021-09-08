// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsProjectile
{
	namespace NPayload
	{
		/**
		*/
		struct CSPRJ_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			virtual const FVector& GetDirection() const = 0;

			virtual const FVector& GetLocation() const = 0;
		};
	}
}