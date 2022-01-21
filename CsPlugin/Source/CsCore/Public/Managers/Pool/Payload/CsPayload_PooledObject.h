// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Time/CsTypes_Time.h"

class UObject;

namespace NCsPooledObject
{
	namespace NPayload
	{
		/**
		* Interface for delivering a "payload" or blob of data when Allocating an
		* object that implements the interface: ICsPooledObject. Usually this payload
		* is passed through a Manager handling the pooled objects.
		*/
		struct CSCORE_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:
	
			virtual ~IPayload(){}

			/**
			* Whether the payload has been marked to be used (allocated).
			*
			* return Whether or not the payload has been marked to be used.
			*/
			virtual const bool& IsAllocated() const = 0;

		#define UpdateType NCsPooledObject::EUpdate

			/**
			* Get how the pooled object should updated. Usually update for a
			* pooled object (implements the interface: ICsPooledObject) is controlled
			* by its manager.
			* Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate).
			*
			* return Update Type
			*/
			virtual const UpdateType& GetUpdateType() const = 0;

		#undef UpdateType

			/**
			* The object "instigating" or starting the process.
			*
			* return Instigator.
			*/
			virtual UObject* GetInstigator() const = 0;

			/**
			* The owner of the object.
			*
			* return Owner.
			*/
			virtual UObject* GetOwner() const = 0;

			/**
			* The parent of the object.
			*
			* return Parent.
			*/
			virtual UObject* GetParent() const = 0;

			/**
			* The current time.
			*
			* return time
			*/
			virtual const FCsTime& GetTime() const = 0;

			/**
			* Mark the payload as being used (allocated).
			*/
			virtual void Allocate() = 0;

			/**
			* Reset the contents of the payload to the default values.
			*/
			virtual void Reset() = 0;

			/**
			* Get the mask that dictates what changes should be preserved when an object
			* that implements the interface: ICsPooledObject is allocated and deallocated.
			* Usually, on deallocate the pooled object is "cleared" and put back in
			* an initial state. There are cases when references on an object should be
			* kept (and put in a "dormant" state) as an optimization.
			* 
			* Allocate: Check if any of the kept changes from a previous allocation are the SAME.
			*			If SAME, don't update.
			* Deallocate: Check if any of the changes should be KEPT and NOT cleared.
			* 
			* return Mask 
			*/
			virtual const uint32& GetPreserveChangesFromDefaultMask() const = 0;
		};
	}
}