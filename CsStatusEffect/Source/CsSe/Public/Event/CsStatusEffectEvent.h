// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
#include "Managers/Time/CsTypes_Time.h"
#pragma once

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

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

		#define DataType NCsStatusEffect::NData::IData

		public:

			virtual ~IEvent(){}

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
			virtual UObject* GetReceiver() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const = 0;

		#undef DataType
		};
	}
}