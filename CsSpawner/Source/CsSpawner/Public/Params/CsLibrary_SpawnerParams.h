// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Spawner
#include "Params/CsSpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
	#define ParamsType NCsSpawner::NParams::IParams

		struct CSSPAWNER_API FLibrary : public NCsInterfaceMap::TLibrary<ParamsType>
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
			static bool IsValid(const FString& Context, const ParamsType* Params, void(*Log)(const FString&) = &NCsSpawner::FLog::Warning);

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

using CsSpawnerParamsLibrary = NCsSpawner::NParams::FLibrary;