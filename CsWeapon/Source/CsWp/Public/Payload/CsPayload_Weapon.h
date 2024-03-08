// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Weapon.h"
#include "Managers/Time/CsTypes_Update.h"

namespace NCsWeapon
{
	namespace NPayload
	{
		struct CSWP_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload() {}

			/**
			*/
			virtual const FECsWeapon& GetType() const = 0;

			/**
			*/
			virtual const FECsUpdateGroup& GetUpdateGroup() const = 0;

			/**
			*/
			virtual const FTransform3f& GetTransform() const = 0;
		};
	}
}