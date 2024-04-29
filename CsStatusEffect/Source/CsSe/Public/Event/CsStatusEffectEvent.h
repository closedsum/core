// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Time/CsTypes_Time.h"

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsStatusEffect::IStatusEffect
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, IStatusEffect)

namespace NCsStatusEffect
{
	namespace NEvent
	{
		/**
		* Interface describing the broadcast of a Status Effect.
		*/
		struct CSSE_API IEvent : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		#define StatusEffectType NCsStatusEffect::IStatusEffect
		#define DataType NCsStatusEffect::NData::IData

		public:

			virtual ~IEvent(){}

			/**
			*/
			virtual StatusEffectType* GetStatusEffect() const = 0;

			/**
			* Get the Data (object that implements the interface: DataType (NCsStatusEffect::NData::IData))
			* associated with the Status Effect.
			*
			* return
			*/
			virtual DataType* GetData() const = 0;

			/**
			* Get the object that initiates the broadcasting of the event.
			*  i.e. In the case of a Weapon Owner using a Weapon and Weapon is the 
			*	    origin of the event. 
			*		The "Instigator" is usually Weapon Owner.
			*		The "Causer" is usually the Weapon
			* 
			* return
			*/
			virtual UObject* GetInstigator() const = 0;

			/**
			* Get the object that broadcasting the event.
			*  i.e. In the case of a Weapon Owner using a Weapon and Weapon is the
			*	    origin of the event.
			*		The "Instigator" is usually Weapon Owner.
			*		The "Causer" is usually the Weapon
			*
			* return
			*/
			virtual UObject* GetCauser() const = 0;

			/**
			* The primary object receiving the event.
			* The object usually implements the interface: ICsReceiveStatusEffect.
			*
			* return
			*/
			virtual UObject* GetReceiver() const = 0;

			/**
			* Objects to ignore if the event should be passed along to other objects.
			*
			* return
			*/
			virtual const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const = 0;

		#undef StatusEffectType
		#undef DataType
		};
	}
}