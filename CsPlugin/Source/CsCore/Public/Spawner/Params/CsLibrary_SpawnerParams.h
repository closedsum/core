// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Spawner
#include "Spawner/Params/CsSpawnerParams.h"

#pragma once

namespace NCsSpawner
{
	namespace NParams
	{
	#define ParamsType NCsSpawner::NParams::IParams

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<ParamsType>
		{
		public:

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Params
			* return
			*/
			static bool IsValidChecked(const FString& Context, const ParamsType* Params);

			/**
			*
			*
			* @param Context	The calling context.
			* @param Params
			* @param Log		(optional)
			* return
			*/
			static bool IsValid(const FString& Context, const ParamsType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context	The calling context.
			* @param Params
			* return
			*/
			static float CalculateTotalTime(const FString& Context, const ParamsType* Params);
		};

	#undef ParamsType
	}
}