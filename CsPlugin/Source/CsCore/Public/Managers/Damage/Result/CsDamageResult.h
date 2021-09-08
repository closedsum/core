// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "Managers/Damage/CsTypes_Damage.h"
#pragma once

namespace NCsDamage
{
	namespace NResult
	{
		/**
		*
		*/
		struct CSCORE_API IResult : public ICsGetInterfaceMap
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