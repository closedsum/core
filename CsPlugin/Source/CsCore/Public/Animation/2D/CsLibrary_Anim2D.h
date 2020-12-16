// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Animation/2D/CsTypes_Library_Anim2D.h"
#include "Coroutine/CsTypes_Coroutine.h"

#pragma once

struct FCsRoutine;

namespace NCsAnim
{
	namespace N2D
	{
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

		private:
		#define ParamsManagerType NCsAnim::N2D::NPlay::NParams::FManager
		#define ParamsResourceType NCsAnim::N2D::NPlay::NParams::FResource
		#define ParamsType NCsAnim::N2D::NPlay::NParams::FParams

			ParamsManagerType Manager_PlayParams;
		public:
		
			FORCEINLINE ParamsResourceType* AllocatePlayParams() { return Manager_PlayParams.Allocate(); }
		
			FORCEINLINE void DeallocatePlayParams(ParamsResourceType* Resource) { Manager_PlayParams.Deallocate(Resource); }

			/**
			*/
			static const FCsRoutineHandle& Play(const ParamsType& Params);

			/**
			*/
			static const FCsRoutineHandle& Play(ParamsResourceType* Params);

		private:

			static char Play_Internal(FCsRoutine* R);

			static void Play_Internal_OnEnd(FCsRoutine* R);

		#undef ParamsManagerType
		#undef ParamsResourceType
		#undef ParamsType
		};
	}
}