// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Projectile.h"
// Container
#include "Containers/CsGetInterfaceMap.h"

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

			virtual const FECsProjectile& GetType() const = 0;

			virtual const FVector& GetDirection() const = 0;

			virtual const FVector& GetLocation() const = 0;
		};
	}
}