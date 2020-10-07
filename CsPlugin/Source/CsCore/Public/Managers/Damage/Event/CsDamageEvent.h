// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "Managers/Damage/CsTypes_Damage.h"
#pragma once

// NCsDamage::NValue::IValue
namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

// NCsDamage::NRange::IRange
namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

// NCsDamage::NData::IData
namespace NCsDamage {
	namespace NData {
		struct IData; } }

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