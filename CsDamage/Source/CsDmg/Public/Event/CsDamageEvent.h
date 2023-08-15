// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Engine/EngineTypes.h"
#include "Types/CsTypes_Damage.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

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
			*/
			virtual const FECsDamageData& GetDataType() const = 0;

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
			virtual const FVector3f& GetDamageDirection() const = 0;

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
			* TraceStart = The origin of the event.
			* Location | ImpactPoint = Where the event is broadcasted from.
			* Normal | ImpactNormal = Direction the event is "pointing" toward.
			*
			* return
			*/
			virtual const FHitResult& GetHitResult() const = 0;

			/**
			* Get the list of Objects that should be ignored when broadcasting the Event.
			*
			* return	Objects to ignore.
			*/
			virtual const TArray<UObject*>& GetIgnoreObjects() const = 0;

			/**
			* Get a Bit Mask of Modifiers that have been applied to the Value or Range.
			*  Modifier is an object that implements the interface: DmgModifierType (NCsDamage::NModifier::IModifier).
			* 
			* return	Bit mask of Modifiers that have been applied.
			*/
			virtual const uint32& GetModifierMask() const = 0;
		};
	}
}