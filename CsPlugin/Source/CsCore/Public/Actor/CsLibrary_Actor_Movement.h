// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coroutine/CsRoutineHandle.h"
#include "Types/CsTypes_Movement_Interp.h"
// Log
#include "Utility/CsLog.h"

class AActor;
class UObject;
struct FCsRoutine;

namespace NCsActor
{
	namespace NMovement
	{
		/**
		* Library of functions related to Actor
		*/
		struct CSCORE_API FLibrary final
		{
		private:
			FLibrary();

			FLibrary(const FLibrary&) = delete;
			FLibrary(FLibrary&&) = delete;
		public:
			~FLibrary();

			FORCEINLINE static FLibrary& Get()
			{
				static FLibrary Instance;
				return Instance;
			}

		// Interp
		#pragma region
		private:

		#define ParamsManagerType NCsMovement::NTo::NInterp::NParams::FManager
		#define ParamsResourceType NCsMovement::NTo::NInterp::NParams::FResource
		#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams

			ParamsManagerType Manager_MoveByInterpParams;

		public:

			FORCEINLINE ParamsResourceType* AllocateMoveByInterpParams() { return Manager_MoveByInterpParams.Allocate(); }

			FORCEINLINE void DeallocateMoveByInterpParams(ParamsResourceType* Resource) { Manager_MoveByInterpParams.Deallocate(Resource); }

		public:

			/**
			* Move an Object via interpolation (i.e. an simple easing function) with the given Params.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Params			Information describing how to interpolate the Object.
			* return				Handle to the movement coroutine.
			*/
			static FCsRoutineHandle MoveByInterpChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params);

			/**
			* Safely move an Object via interpolation (i.e. an simple easing function) with the given Params.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Params			Information describing how to interpolate the Object.
			* @param Log
			* return				Handle to the movement coroutine.
			*/
			static FCsRoutineHandle SafeMoveByInterp(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

			static char MoveByInterp_Internal(FCsRoutine* R);

			static void MoveByInterp_Internal_OnEnd(FCsRoutine* R);

		#undef ParamsManagerType
		#undef ParamsResourceType
		#undef ParamsType

		#pragma endregion Interp
		};
	}
}