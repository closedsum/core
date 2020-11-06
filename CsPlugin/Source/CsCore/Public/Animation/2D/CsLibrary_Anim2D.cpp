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

		FLibrary::FLibrary() :
			Manager_StaticMeshParams()
		{
		}

		FLibrary::~FLibrary()
		{
			Manager_StaticMeshParams.Shutdown();
		}

		#define ParamsType NCsAnim::N2D::NPlay::NStaticMesh::NParams::FParams
		const FCsRoutineHandle& FLibrary::Play(const ParamsType& Params)
		{
		#undef ParamsType

			using namespace NCached;

			
			checkf(Params.Component, TEXT("%s: Params.Component is NULL."));



			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Params.Context);
			const FECsUpdateGroup UpdateGroup = Params.UpdateGroup;

			typedef NCsCoroutine::NPayload::FImpl PayloadType;

			PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

			Payload->CoroutineImpl.BindStatic(&FLibrary::Play_Internal);
			Payload->StartTime = UCsManager_Time::Get(Params.Context)->GetTime(UpdateGroup);
			Payload->Owner.SetObject(Params.Owner);
			Payload->SetName(Str::Play_Internal);
			Payload->SetFName(Name::Play_Internal);

			typedef NCsCoroutine::FOnEnd FOnEnd;

			Payload->OnEnds.AddDefaulted();
			FOnEnd& OnEnd = Payload->OnEnds.Last();
			OnEnd.BindStatic(&FLibrary::Play_Internal_OnEnd);

			typedef NCsAnim::N2D::NPlay::NStaticMesh::NParams::FResource ParamsResourceType;

			ParamsResourceType* R = Get().Manager_StaticMeshParams.Allocate();

			static const int32 RESOURCE = 0;
			Payload->SetValue_Void(RESOURCE, R);

			return Scheduler->Start(Payload);
		}

		char FLibrary::Play_Internal(FCsRoutine* R)
		{
			typedef NCsAnim::N2D::NPlay::NStaticMesh::NParams::FResource ParamsResourceType;

			static const int32 RESOURCE = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);

			CS_COROUTINE_BEGIN(R);

			CS_COROUTINE_END(R);
		}

		void FLibrary::Play_Internal_OnEnd(FCsRoutine* R)
		{
			typedef NCsAnim::N2D::NPlay::NStaticMesh::NParams::FResource ParamsResourceType;

			static const int32 RESOURCE = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);

			Get().Manager_StaticMeshParams.Deallocate(Resource);
		}
	}
}