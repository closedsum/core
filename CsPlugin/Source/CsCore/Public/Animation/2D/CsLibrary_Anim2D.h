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
		#define StaticMeshParamsType NCsAnim::N2D::NPlay::NStaticMesh::NParams::FManager
			StaticMeshParamsType Manager_StaticMeshParams;
		#undef StaticMeshParamsType

		public:

			#define ParamsType NCsAnim::N2D::NPlay::NStaticMesh::NParams::FParams
			/**
			*/
			static const FCsRoutineHandle& Play(const ParamsType& Params);
			#undef ParamsType

			static char Play_Internal(FCsRoutine* R);

			static void Play_Internal_OnEnd(FCsRoutine* R);
		};
	}
}