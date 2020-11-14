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
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsAnim::N2D::FLibrary, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsAnim::N2D::FLibrary, Play_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsAnim::N2D::FLibrary, Play_Internal);
			}
		}

		FLibrary::FLibrary() :
			Manager_PlayParams()
		{
		}

		FLibrary::~FLibrary()
		{
			Manager_PlayParams.Shutdown();
		}

		#define ParamsType NCsAnim::N2D::NPlay::NParams::FParams
		const FCsRoutineHandle& FLibrary::Play(const ParamsType& Params)
		{
			using namespace NCached;

			const FString& Context = Str::Play;

			check(Params.IsValidChecked(Context));

			typedef NCsAnim::N2D::EPlayback PlaybackType;

			const PlaybackType& Playback = Params.Anim.GetPlayback();

			checkf(Playback != PlaybackType::Custom, TEXT("%s: Playback: EPlayback::Custom is NOT Supported."), *Context)

			UCsCoroutineScheduler* Scheduler  = UCsCoroutineScheduler::Get(Params.Context);
			const FECsUpdateGroup UpdateGroup = Params.UpdateGroup;

			typedef NCsCoroutine::NPayload::FImpl PayloadType;

			PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

			Payload->CoroutineImpl.BindStatic(&FLibrary::Play_Internal);
			Payload->StartTime = UCsManager_Time::Get(Params.Context)->GetTime(UpdateGroup);
			Payload->Owner.SetObject(Params.Owner);
			Payload->SetName(Str::Play_Internal);
			Payload->SetFName(Name::Play_Internal);

			// Allocate and set params
			typedef NCsAnim::N2D::NPlay::NParams::FResource ParamsResourceType;

			ParamsResourceType* R = Get().Manager_PlayParams.Allocate();
			ParamsType* P		  = R->Get();
			*P					  = Params;

			// Set Abort callback
			typedef NCsCoroutine::FOnAbort OnAbortType;

			if (Params.OnAbort.IsBound())
			{
				Payload->OnAborts.AddDefaulted();
				OnAbortType& OnAbort = Payload->OnAborts.Last();
				OnAbort				 = Params.OnAbort;
			}

			// Set End callback (to free any allocated references)
			typedef NCsCoroutine::FOnEnd OnEndType;

			if (Params.OnEnd.IsBound())
			{
				Payload->OnEnds.AddDefaulted();
				OnEndType& OnEnd = Payload->OnEnds.Last();
				OnEnd			 = Params.OnEnd;
			}

			Payload->OnEnds.AddDefaulted();
			OnEndType& OnEnd = Payload->OnEnds.Last();
			OnEnd.BindStatic(&FLibrary::Play_Internal_OnEnd);
			
			static const int32 RESOURCE = 0;
			Payload->SetValue_Void(RESOURCE, R);

			return Scheduler->Start(Payload);
		}
		#undef ParamsType

		char FLibrary::Play_Internal(FCsRoutine* R)
		{
			// Cache appropriate references
			typedef NCsAnim::N2D::NPlay::NParams::FResource ParamsResourceType;
			typedef NCsAnim::N2D::NPlay::NParams::FParams ParamsType;

			static const int32 RESOURCE = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			ParamsType* Params			 = Resource->Get();

			UMaterialInstanceDynamic* MID = Params->MID.IsValid() ? Params->MID.Get() : nullptr;

			checkf(MID, TEXT("%s: MID is NULL."), **(R->GetName()));

			// Anim
			typedef NCsAnim::N2D::NFlipbook::NTexture::FFlipbook AnimType;

			const AnimType& Anim = Params->Anim;

			typedef NCsAnim::N2D::EPlayback PlaybackType;

			const PlaybackType& Playback = Params->Anim.GetPlayback();
			const bool LoopingForever	 = Params->Anim.IsLoopingForever();
			const float& DeltaTime		 = Anim.GetDeltaTime();
			const float& TotalTime		 = Anim.GetTotalTime();
			const int32 FrameCount		 = Anim.Frames.Num();
			const int32& TotalCount		 = Anim.GetTotalCount();

			static const int32 COUNT = 0;
			int32& Count = R->GetValue_Int(COUNT);

			static const int32 FRAME_INDEX = 1;
			int32& FrameIndex = R->GetValue_Int(FRAME_INDEX);

			// Frames
			typedef NCsAnim::N2D::NFlipbook::NTexture::FFrame FrameType;

			const FrameType& Frame = Anim.Frames[FrameIndex];

			FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
			ElapsedTime += R->DeltaTime;

			static const int32 DIRECTION = 2;
			int32& Direction = R->GetValue_Int(DIRECTION);

			// Play Animation
			CS_COROUTINE_BEGIN(R);

			FrameIndex = Anim.ShouldStartReverse() ? FrameCount - 1 : 0;
			Direction  = Anim.ShouldStartReverse() ? -1 : 1;

			ElapsedTime.Reset();

			do
			{
				{
					MID->SetTextureParameterValue(Frame.GetParameterName(), Frame.GetTexture());

					CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= DeltaTime);

					ElapsedTime.Reset();

					// Forward
					if (Playback == PlaybackType::Forward)
						++FrameIndex;
					// Reverse
					else
					if (Playback == PlaybackType::Reverse)
						--FrameIndex;
					// PingPong
					else
					if (Playback == PlaybackType::PingPong)
					{
						if (FrameIndex == FrameCount - 1)
						{
							Direction = -1;
						}
	
						FrameIndex += Direction;
					}
					// Loop
					else
					if (Playback == PlaybackType::Loop)
					{
						FrameIndex = (FrameIndex + 1) % FrameCount;
					}
					// Loop Reverse
					else
					if (Playback == PlaybackType::LoopReverse)
					{
						FrameIndex = FrameIndex == 0 ? FrameCount - 1 : FrameIndex - 1;
					}
					// TODO: LoopPingPong
					++Count;
				}
			} while (LoopingForever || Count < TotalCount);

			CS_COROUTINE_END(R);
		}

		void FLibrary::Play_Internal_OnEnd(FCsRoutine* R)
		{
			typedef NCsAnim::N2D::NPlay::NParams::FResource ParamsResourceType;
			typedef NCsAnim::N2D::NPlay::NParams::FParams ParamsType;

			static const int32 RESOURCE = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			ParamsType* Params			 = Resource->Get();
			Params->Reset();

			Get().Manager_PlayParams.Deallocate(Resource);
		}
	}
}