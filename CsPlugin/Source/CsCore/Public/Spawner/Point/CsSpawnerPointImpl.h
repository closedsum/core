// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Spawner/Point/CsTypes_SpawnerPoint.h"

#pragma once

class ICsSpawner;
class AActor;

// NCsSpawner::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, IParams)

namespace NCsSpawner
{
	namespace NPoint
	{
		/**
		* Interface that describes any spawn "points", a place where an object is spawned, for a 
		* Spawner (object that implements the interface: ICsSpawner).
		*/
		struct CSCORE_API IImpl
		{
		public:

			virtual ~IImpl() {}

		public:

		#define CountType NCsSpawner::NPoint::ECount
		#define OrderType NCsSpawner::NPoint::EOrder
		#define ParamsType NCsSpawner::NParams::IParams

			/**
			* 
			* 
			* @param Spawner
			*/
			virtual void SetSpawner(ICsSpawner* Spawner) = 0;

			/**
			* Set how to populate the number of spawn points for the spawner.
			* 
			* @param Count
			*/
			virtual void SetCountType(const CountType& Count) = 0;

			/**
			* Set the order in which spawn points are used to spawn objects.
			* 
			* @param Order
			*/
			virtual void SetOrderType(const OrderType& Order) = 0;

			/**
			* 
			* 
			* @params Params
			*/
			virtual void SetParams(ParamsType* Params) = 0;

			/**
			* Set the acting "center", this orientation is played to transform in GetTransform and
			* GetCurrentTransform, as an Actor.
			* 
			* @param Center
			*/
			virtual void SetCenter(AActor* Center) = 0;

			/**
			* Set the acting "center", this orientation is played to transform in GetTransform and
			* GetCurrentTransform, as an Transform.
			*
			* @param Center
			*/
			virtual void SetCenter(const FTransform& Center) = 0;

			/** 
			* Populate and setup any data (usually caching locations) related to the spawn params. 
			*/
			virtual void Prepare() = 0;

			/** 
			* Move onto the "next" spawn location. 
			* 
			* @param Count			The current spawn count.
			* @param Group			The current spawn group, the current "set" or collection of objects to be spawned.
			* @param CountPerGroup	The current spawn count for the current group.
			*/
			virtual void Advance(const int32& Count, const int32& Group, const int32& CountPerGroup) = 0;

			/**
			* Get the transform of the acting "center" of the spawner.
			* 
			* return Transform
			*/
			virtual FTransform GetCenterTransform() const = 0;

			/** 
			* Get the spawn transform based on Count, Group, and CountPerGroup.
			* 
			* @param Count			
			* @param Group
			* @param CountPerGroup
			* return				Spawn transform.
			*/
			virtual FTransform GetTransform(const int32& Count, const int32& Group, const int32& CountPerGroup) const = 0;

			/**
			* Get the current spawn transform. This location is usually the result after Advance is called.
			* 
			* return Current spawn transform.
			*/
			virtual FTransform GetCurrentTransform() const = 0;

		#undef CountType
		#undef OrderType
		#undef ParamsType
		};
	}
}

class ICsSpawner;
class AActor;

// NCsSpawner::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, IParams)

namespace NCsSpawner
{
	namespace NPoint
	{
	#define ImplType NCsSpawner::NPoint::IImpl

		/**
		* Basic implementation of the interface ImplType (NCsSpawner::NPoint::IImpl)
		* that describes any spawn "points", a place where an object is spawned, for a
		* Spawner (object that implements the interface: ICsSpawner).
		*/
		struct CSCORE_API FImpl : public ImplType
		{
		public:

		#define PointCountType NCsSpawner::NPoint::ECount
		#define OrderType NCsSpawner::NPoint::EOrder
		#define ParamsType NCsSpawner::NParams::IParams

			/** Reference to the object that will handle spawning objects. */
			ICsSpawner* Spawner;
			/** Reference to Spawner as an AActor. */
			AActor* SpawnerAsActor;

			/** Describes how spawning of objects is tracked (counted). */
			PointCountType CountType;
			/** Describes the order in which spawn points are chosen. */
			OrderType Order;

			ParamsType* Params;

			/** The acting "center", this orientation is played to transform in GetTransform and
				GetCurrentTransform, as an Actor. */ 
			AActor* CenterAsActor;

			/** The acting "center", this orientation is played to transform in GetTransform and
				GetCurrentTransform, as an Transform. */
			FTransform CenterAsTransform;

			int32 Index;

			int32 CurrentGroup;

			FImpl() :
				Spawner(nullptr),
				SpawnerAsActor(nullptr),
				CountType(PointCountType::TotalCount),
				Order(OrderType::Random),
				Params(nullptr),
				CenterAsActor(nullptr),
				CenterAsTransform(FTransform::Identity),
				Index(0),
				CurrentGroup(INDEX_NONE)
			{
			}

			~FImpl(){}

		// ImplType (NCsSpawner::NPoint::IImpl)
		#pragma region
		public:

			void SetSpawner(ICsSpawner* InSpawner);

			void SetCountType(const PointCountType& InCountType) { CountType = InCountType; }

			void SetOrderType(const OrderType& InOrder) { Order = InOrder; }

			void SetParams(ParamsType* InParams) { Params = InParams; }

			void SetCenter(AActor* Center) { CenterAsActor = Center; }

			void SetCenter(const FTransform& Center) { CenterAsTransform = Center; }

			void Prepare() {}

			void Advance(const int32& Count, const int32& Group, const int32& CountPerGroup);

			FTransform GetCenterTransform() const;

			FTransform GetTransform(const int32& Count, const int32& Group, const int32& CountPerGroup) const { return FTransform::Identity; }

			FTransform GetCurrentTransform() const { return FTransform::Identity; }

		#pragma endregion ImplType (NCsSpawner::NPoint::IImpl)

		public:

			static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsSpawner::NPoint::FImpl*>(Ptr);
			}

		#undef PointCountType
		#undef OrderType
		#undef ParamsType
		};

	#undef ImplType
	}
}