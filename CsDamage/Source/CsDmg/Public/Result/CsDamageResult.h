// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Engine/EngineTypes.h"
#include "Types/CsTypes_Damage.h"

namespace NCsDamage
{
	namespace NResult
	{
		/**
		*
		*/
		struct CSDMG_API IResult : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IResult() {}

			/**
			*
			*
			* return
			*/
			virtual const float& GetDamage() const = 0;

			/**
			*
			*
			* return
			*/
			virtual UObject* GetInstigator() const = 0;

			/**
			*
			*
			* return
			*/
			virtual UObject* GetCauser() const = 0;

			/**
			*
			*
			* return
			*/
			virtual UObject* GetVictim() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FECsDamageType& GetDamageType() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FECsHitType& GetHitType() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FHitResult& GetHitResult() const = 0;
		};
	}
}