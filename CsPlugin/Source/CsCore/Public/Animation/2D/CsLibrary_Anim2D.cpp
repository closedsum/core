// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsLibrary_Anim2D.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

namespace NCsAnim
{
	namespace N2D
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsAnim::N2D::FLibrary, Play_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsAnim::N2D::FLibrary, Play_Internal);
			}
		}

		#define ParamsType NCsAnim::N2D::NPlay::NStaticMesh::FParams
		const FCsRoutineHandle& FLibrary::Play(const ParamsType& Params)
		{
		#undef ParamsType

			using namespace NCached;

			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Params.Context);
			const FECsUpdateGroup UpdateGroup = Params.UpdateGroup;

			typedef NCsCoroutine::NPayload::FImpl PayloadType;

			PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

			Payload->CoroutineImpl.BindStatic(&FLibrary::Play_Internal);
			Payload->StartTime = UCsManager_Time::Get(Params.Context)->GetTime(UpdateGroup);
			Payload->Owner.SetObject(Params.Owner);
			Payload->SetName(Str::Play_Internal);
			Payload->SetFName(Name::Play_Internal);

			return Scheduler->Start(Payload);
		}

		char FLibrary::Play_Internal(FCsRoutine* R)
		{
			CS_COROUTINE_BEGIN(R);

			CS_COROUTINE_END(R);
		}
	}
}