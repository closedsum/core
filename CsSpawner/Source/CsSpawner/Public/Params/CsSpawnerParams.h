// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/CsTypes_SpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
		/** 
		* Interface for describing any information regarding the act of spawning an object.
		* i.e. Count, Frequency, Time, ... etc. 
		*/
		struct CSSPAWNER_API IParams : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IParams(){}
	
		#define CountParamsType NCsSpawner::NParams::FCount
		#define FrequencyParamsType NCsSpawner::NParams::FFrequency

			/**
			* Get the parameters describing the number of objects "created" when
			* Spawn is called.
			*
			* return Count Params
			*/
			virtual const CountParamsType& GetCountParams() const = 0;

			/**
			* Get the parameters describing how often objects are "created" when
			* Spawn is called.
			*
			* return Frequency Params
			*/
			virtual const FrequencyParamsType& GetFrequencyParams() const = 0;

			/**
			* Get the total time the objects are being spawned for.
			*
			* return Total Time
			*/
			virtual const float& GetTotalTime() const = 0;

		#undef CountParamsType
		#undef FrequencyParamsType
		};
	}
}