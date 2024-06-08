// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/CsLibrary_Material_Anim.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Common
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"

namespace NCsMaterial
{
	namespace NMID
	{
		namespace NAnim
		{
			namespace NLibrary
			{
				namespace NCached 
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::NAnim::FLibrary, PlayAnim_Internal);
					}

					namespace Name
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsMaterial::NMID::NAnim::FLibrary, PlayAnim_Internal);
					}
				}
			}

			FLibrary::FLibrary() :
				Manager_AnimParams()
			{
			}

			FLibrary::~FLibrary()
			{
				Manager_AnimParams.Shutdown();
			}

			#define LogWarning void(*Log)(const FString&) /*=&FCsLog::Warning*/
			#define CoroutineSchedulerLibrary NCsCoroutine::NScheduler::FLibrary
			#define MathLibrary NCsMath::FLibrary
			#define MIDLibrary NCsMaterial::NMID::FLibrary

			#define ParamsResourceType NCsMaterial::NAnim::NParams::FResource
			#define ParamsType NCsMaterial::NAnim::NParams::FParams

			FCsRoutineHandle FLibrary::PlayAnimChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params)
			{
				using namespace NCsMaterial::NMID::NAnim::NLibrary::NCached;

				ParamsType* P = Params->Get();

				check(P->IsValidChecked(Context));

				// Get Coroutine Scheduler
				UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

				UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(ContextRoot);
				const FECsUpdateGroup& UpdateGroup = Params->Get()->GetGroup();
				// Allocate Payload
				typedef NCsCoroutine::NPayload::FImpl PayloadType;

				PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);
				// Setup Payload
				#define COROUTINE PlayAnim_Internal

				Payload->CoroutineImpl.BindStatic(&FLibrary::COROUTINE);
				Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
				Payload->Owner.SetObject(P->GetOwner());
				Payload->SetName(Str::COROUTINE);
				Payload->SetFName(Name::COROUTINE);

	#			undef COROUTINE

				// Set End callback (to free any allocated references)
				typedef NCsCoroutine::FOnEnd OnEndType;

				OnEndType& OnEnd = Payload->OnEnds.AddDefaulted_GetRef();
				OnEnd.BindStatic(&FLibrary::PlayAnim_Internal_OnEnd);

				static const int32 RESOURCE = 0;
				Payload->SetValue_Void(RESOURCE, Params);

				return Scheduler->Start(Payload);
			}

			FCsRoutineHandle FLibrary::SafePlayAnim(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, LogWarning)
			{
				// Check Params are Valid.
				CS_IS_PTR_NULL_RET_VALUE(Params, FCsRoutineHandle::Invalid)
				// Check Params's Resource is Valid.
				if (!Params->Get())
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params's Resource is NULL."), *Context));
					return FCsRoutineHandle::Invalid;
				}

				if (!Params->Get()->IsValid(Context))
					return FCsRoutineHandle::Invalid;

				if (!Get().Manager_AnimParams.Contains(Params))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params has NOT been allocated from pool. Use the method that passes by const reference."), *Context));
					return FCsRoutineHandle::Invalid;
				}

				// Check to get Context Root for CoroutineScheduler
				{
					UObject* ContextRoot = CoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

			#if WITH_EDITOR
					if (!ContextRoot)
						return FCsRoutineHandle::Invalid;
			#endif // #if WITH_EDITOR
				}
				return PlayAnimChecked(Context, WorldContext, Params);
			}

			#define AnimType NCsMaterial::NAnim::FAnim

			FCsRoutineHandle FLibrary::PlayAnimChecked(const FString& Context, const UObject* WorldContext, const AnimType& Anim, const TArray<UMaterialInstanceDynamic*>& MIDs, UObject* Owner, const FECsUpdateGroup& Group)
			{
				ParamsResourceType* Resource = Get().AllocateAnimParams();
				ParamsType* Params			 = Resource->Get();

				Params->Anim = Anim;
				Params->SetMIDs(MIDs);
				Params->SetOwner(Owner);
				Params->SetGroup(Group);

				return PlayAnimChecked(Context, WorldContext, Resource);
			}

			#undef AnimType

			char FLibrary::PlayAnim_Internal(FCsRoutine* R)
			{
				using namespace NCsMaterial::NMID::NAnim::NLibrary::NCached;

				const FString& Context = Str::PlayAnim_Internal;

				static const int32 RESOURCE = 0;
				ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
				ParamsType* Params			 = Resource->Get();

				const TArray<UMaterialInstanceDynamic*>& MIDs = Params->ResolveAndGetMIDsChecked(Context);

				// Anim
				typedef NCsMaterial::NAnim::FAnim AnimType;

				const AnimType& Anim = Params->Anim;

				typedef NCsAnim::EPlayback PlaybackType;

				const PlaybackType& Playback = Params->Anim.GetPlayback();
				const bool LoopingForever	 = Params->Anim.IsLoopingForever();
				const int32 FrameCount		 = Anim.FrameCount;
				const int32& TotalCount		 = Anim.GetTotalCount();

				static const int32 COUNT = 0;
				int32& Count = R->GetValue_Int(COUNT);

				static const int32 FRAME_INDEX = 1;
				int32& FrameIndex = R->GetValue_Int(FRAME_INDEX);

				// Frames
				typedef NCsMaterial::NAnim::FFrame FrameType;

				const FrameType& Frame = Anim.Frames[FrameIndex];

				FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
				ElapsedTime += R->GetDeltaTime();

				const float& Duration = Frame.GetDuration();
				float Percent		   = FMath::Clamp(ElapsedTime.Time / Duration, 0.0f, 1.0f);

				static const int32 DIRECTION = 2;
				int32& Direction = R->GetValue_Int(DIRECTION);

				// Play Animation
				CS_COROUTINE_BEGIN(R);

				FrameIndex = Anim.ShouldStartReverse() ? FrameCount - 1 : 0;
				Direction  = Anim.ShouldStartReverse() ? -1 : 1;

				ElapsedTime.Reset();

				Percent = 0.0f;

				do
				{
					{
						typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;
						typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

						// Vector
						for (const VectorType& Param : Frame.VectorParameters)
						{
							// TODO: HSV
							//FLinearColor::LerpUsingHSV()

							const FLinearColor& Start = Param.GetFrom();
							const FLinearColor& End	  = Param.GetTo();

							// If SAME, set END ONCE
							if (Start == End)
							{
								if (Percent == 0.0f)
								{
									MIDLibrary::SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), End);
								}
							}
							else
							{
								const FLinearColor StartToEnd = End - Start;

								float DistanceSq;
								float Distance;
								const FLinearColor Normal = MathLibrary::GetSafeNormal(StartToEnd, DistanceSq, Distance);
						
								const ECsEasingType& Easing = Param.GetEasing();
								const float Alpha			= MathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);

								FLinearColor Current = Start + Alpha * Distance * Normal;

								MIDLibrary::SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), Current);
							};
						}
						// Scalar
						for (const ScalarType& Param : Frame.ScalarParameters)
						{
							const float& Start = Param.GetFrom();
							const float& End   = Param.GetTo();

							// If SAME, set END ONCE
							if (Start == End)
							{
								if (Percent == 0.0f)
								{
									MIDLibrary::SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), End);
								}
							}
							else
							{
								const ECsEasingType& Easing = Param.GetEasing();
								const float Alpha			= MathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);

								const float Delta = End - Start;
								float Final		  = Start + Alpha * Delta;

								MIDLibrary::SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), Final);
							};
						}

						if (ElapsedTime.Time < Duration)
						{
							CS_COROUTINE_YIELD(R);	
						}
						else
						{
							// Vector
							for (const VectorType& Param : Frame.VectorParameters)
							{
								MIDLibrary::SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), Param.GetTo());
							}
							// Float
							for (const ScalarType& Param : Frame.ScalarParameters)
							{
								MIDLibrary::SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), Param.GetTo());
							}

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
						//CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= Duration);
					}
				} while (LoopingForever || Count < TotalCount);

				CS_COROUTINE_END(R);
			}

			void FLibrary::PlayAnim_Internal_OnEnd(FCsRoutine* R)
			{
				static const int32 RESOURCE  = 0;
				ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
				ParamsType* Params			 = Resource->Get();
				Params->Reset();

				Get().Manager_AnimParams.Deallocate(Resource);
			}

			#undef ParamsResourceType
			#undef ParamsType

			#undef LogWarning
			#undef CoroutineSchedulerLibrary
			#undef MathLibrary
			#undef MIDLibrary
		}
	}
}