// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "Managers/Damage/CsTypes_Damage.h"
#pragma once

class ICsData_Damage;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		*
		*/
		struct CSCORE_API IEvent : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IEvent() {}

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
			virtual const NCsDamage::NValue::IValue* GetDamageValue() const = 0;

			/**
			*
			*
			* return 
			*/
			virtual const NCsDamage::NRange::IRange* GetDamageRange() const = 0;

			/**
			*
			*
			* return
			*/ 
			virtual ICsData_Damage* GetData() const = 0;

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
			virtual const FECsHitType& GetHitType() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FHitResult& GetOrigin() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FHitResult& GetHitResult() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const TArray<UObject*>& GetIgnoreObjects() const = 0;
		};
	}
}