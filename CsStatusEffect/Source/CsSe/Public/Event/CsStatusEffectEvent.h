// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Time/CsTypes_Time.h"
#pragma once

class ICsData_StatusEffect;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		/**
		*/
		struct CSSE_API IEvent : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IEvent(){}

			/**
			*
			*
			* return
			*/
			virtual ICsData_StatusEffect* GetData() const = 0;

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
			virtual UObject* GetReceiver() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const = 0;
		};
	}
}