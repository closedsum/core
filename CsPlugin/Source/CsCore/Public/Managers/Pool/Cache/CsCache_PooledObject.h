// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Time/CsTypes_Time.h"

class UObject;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsPooledObject
{
	namespace NCache
	{
		/**
		*/
		struct CSCORE_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		#define PayloadType NCsPooledObject::NPayload::IPayload
		#define StateType NCsPooledObject::EState
		#define UpdateType NCsPooledObject::EUpdate

		public:

			virtual ~ICache(){}

			/**
			*
			*
			* @param InIndex
			*/
			virtual void Init(const int32& InIndex) = 0;

			/**
			*
			*
			* return
			*/
			virtual const int32& GetIndex() const = 0;
	
			/*
			*
			*
			* @param Payload
			* @param InTime
			*/
			virtual void Allocate(PayloadType* Payload) = 0;

			/**
			*
			*
			* return
			*/
			virtual const bool& IsAllocated() const = 0;

			/**
			*
			*/
			virtual void Deallocate() = 0;

			/**
			*
			*/
			virtual void QueueDeallocate() = 0;

			/**
			*
			*
			* return
			*/
			virtual bool ShouldDeallocate() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const StateType& GetState() const = 0;

			/**
			* Get how the pooled object should updated. Usually update for a
			* pooled object (implements the interface: ICsPooledObject) is controlled
			* by its manager.
			* Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate).
			*
			* return Update Type
			*/
			virtual const UpdateType& GetUpdateType() const = 0;

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
			virtual UObject* GetOwner() const = 0;

			/**
			*
			*
			* return
			*/
			virtual UObject* GetParent() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const float& GetWarmUpTime() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FCsTime& GetStartTime() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const FCsDeltaTime& GetElapsedTime() const = 0;

			/**
			*
			*
			* return
			*/
			virtual bool HasLifeTimeExpired() const = 0;

			/**
			*
			*/
			virtual void Reset() = 0;

		#undef PayloadType
		#undef StateType
		#undef UpdateType
		};
	}
}