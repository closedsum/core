// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Material/CsTypes_Material_Anim.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsLog.h"

class UMaterialInstanceDynamic;
struct FCsRoutine;
class UObject;

namespace NCsMaterial
{
	namespace NMID
	{
		namespace NAnim
		{
			/**
			* Library of functions related to MaterialInstanceDynamic
			*/
			struct CSCORE_API FLibrary
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

			private:

				CS_DECLARE_STATIC_LOG_LEVEL

				using ParamsManagerType = NCsMaterial::NAnim::NParams::FManager;
				using ParamsResourceType = NCsMaterial::NAnim::NParams::FResource;
				using ParamsType = NCsMaterial::NAnim::NParams::FParams;
				using AnimType = NCsMaterial::NAnim::FAnim;

				ParamsManagerType Manager_AnimParams;

			public:

				FORCEINLINE ParamsResourceType* AllocateAnimParams() { return Manager_AnimParams.Allocate(); }

				FORCEINLINE void DeallocateAnimParams(ParamsResourceType* Resource) { Manager_AnimParams.Deallocate(Resource); }

			public:

				/**
				* Animate any number of parameters on a MaterialInstanceDynamic with the given Params.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Params			Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
				* return				Handle to the animation coroutine.
				*/
				static FCsRoutineHandle PlayAnimChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params);

				/**
				* Safely animate any number of parameters on a MaterialInstanceDynamic with the given Params.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Params			Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
				* @param Log
				* return				Handle to the animation coroutine.
				*/
				static FCsRoutineHandle SafePlayAnim(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Animate any number of parameters on a MaterialInstanceDynamic with the given Anim.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Anim			Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
				* @param MIDs
				* @param Owner
				* @param Group
				* return				Handle to the animation coroutine.
				*/
				static FCsRoutineHandle PlayAnimChecked(const FString& Context, const UObject* WorldContext, const AnimType& Anim, const TArray<UMaterialInstanceDynamic*>& MIDs, UObject* Owner, const FECsUpdateGroup& Group);

			private:

				static char PlayAnim_Internal(FCsRoutine* R);

				static void PlayAnim_Internal_OnEnd(FCsRoutine* R);
			};
		}
	}
}