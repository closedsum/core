// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Engine/EngineTypes.h"
#include "Managers/Damage/CsTypes_Damage.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		*
		*/
		struct CSDMG_API IEvent : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			typedef NCsDamage::NValue::IValue ValueType;
			typedef NCsDamage::NRange::IRange RangeType;
			typedef NCsDamage::NData::IData DataType;

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
			virtual const ValueType* GetDamageValue() const = 0;

			/**
			*
			*
			* return 
			*/
			virtual const RangeType* GetDamageRange() const = 0;

			/**
			*
			*
			* return
			*/ 
			virtual DataType* GetData() const = 0;

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