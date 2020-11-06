// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Library_Anim2D.h"
#include "Coroutine/CsTypes_Coroutine.h"

#pragma once

struct FCsRoutine;

namespace NCsAnim
{
	namespace N2D
	{
		struct CSCORE_API FLibrary
		{
			#define ParamsType NCsAnim::N2D::NPlay::NStaticMesh::FParams
			/**
			*/
			static const FCsRoutineHandle& Play(const ParamsType& Params);
			#undef ParamsType

			static char Play_Internal(FCsRoutine* R);
		};
	}
}