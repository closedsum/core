// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/CsLibrary_Actor_Movement.h"

// Types
#include "CsMacro_Misc.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

using LogClassType = FCsLog;

namespace NCsActor
{
	namespace NMovement
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					// Interp
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, MoveByInterp_Internal);
				}

				namespace Name
				{
					// Interp
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsActor::FLibrary, MoveByInterp_Internal);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		FLibrary::FLibrary() :
			Manager_MoveByInterpParams()
		{
		}

		FLibrary::~FLibrary()
		{
			Manager_MoveByInterpParams.Shutdown();
		}
		
		using ParamsManagerType = NCsMovement::NTo::NInterp::NParams::FManager;
		using ParamsResourceType = NCsMovement::NTo::NInterp::NParams::FResource;
		using ParamsType = NCsMovement::NTo::NInterp::NParams::FParams;

		// Interp
		#pragma region

		FCsRoutineHandle FLibrary::MoveByInterpChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params)
		{
			using namespace NCsActor::NMovement::NLibrary::NCached;

			ParamsType* P = Params->Get();

			check(P->IsValidChecked(Context));
			// Get Coroutine Scheduler
			UObject* ContextRoot = CsCoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

			UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
			const FECsUpdateGroup& UpdateGroup = Params->Get()->GetGroup();
			// Allocate Payload
			typedef NCsCoroutine::NPayload::FImpl PayloadType;

			PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);
			// Setup Payload
			#define COROUTINE MoveByInterp_Internal
		
			Payload->CoroutineImpl.BindStatic(&FLibrary::COROUTINE);
			Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);

			typedef NCsMovement::EMover MoverType;

			const MoverType& Mover = P->GetMover();
			UObject* Object		   = Mover == MoverType::Actor ? Cast<UObject>(P->GetMoveActor()) : Cast<UObject>(P->GetMoveComponent());

			Payload->Owner.SetObject(Object);

			Payload->SetName(Str::COROUTINE);
			Payload->SetFName(Name::COROUTINE);

			#undef COROUTINE

			// Set End callback (to free any allocated references)
			typedef NCsCoroutine::FOnEnd OnEndType;

			OnEndType& OnEnd = Payload->OnEnds.AddDefaulted_GetRef();
			OnEnd.BindStatic(&FLibrary::MoveByInterp_Internal_OnEnd);

			static const int32 RESOURCE = 0;
			Payload->SetValue_Void(RESOURCE, Params);

			// Calculate InterpSpeed
			static const int32 INTERP_SPEED = 0;
			const FVector3f Start		= P->GetFromLocation();
			const FVector3f End		= P->GetEndLocation();
			const float Distance    = (End - Start).Size();
			const float InterpSpeed = Distance / P->GetTime();
			Payload->SetValue_Float(INTERP_SPEED, InterpSpeed);

			return Scheduler->Start(Payload);
		}

		FCsRoutineHandle FLibrary::SafeMoveByInterp(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			// Check Params are Valid.
			if (!Params)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params is NULL."), *Context));
				return FCsRoutineHandle::Invalid;
			}
			// Check Params's Resource is Valid.
			if (!Params->Get())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params's Resource is NULL."), *Context));
				return FCsRoutineHandle::Invalid;
			}

			if (!Params->Get()->IsValid(Context))
				return FCsRoutineHandle::Invalid;

			if (!Get().Manager_MoveByInterpParams.Contains(Params))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params has NOT been allocated from pool. Use the method that passes by const reference."), *Context));
				return FCsRoutineHandle::Invalid;
			}
		
			// Check to get Context Root for CoroutineScheduler
			{
				UObject* ContextRoot = CsCoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

			#if WITH_EDITOR
				if (!ContextRoot)
					return FCsRoutineHandle::Invalid;
			#endif // #if WITH_EDITOR
			}
			return MoveByInterpChecked(Context, WorldContext, Params);
		}

		char FLibrary::MoveByInterp_Internal(FCsRoutine* R)
		{
			using namespace NCsActor::NMovement::NLibrary::NCached;

			const FString& Context = Str::MoveByInterp_Internal;

			// Get Params
			static const int32 RESOURCE				  = 0;
			const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			const ParamsType* Params				  = ParamsContainer->Get();
			// Cache appropriate values from Params
			const ECsEasingType& Easing = Params->GetEasing();

			typedef NCsMovement::EMover MoverType;

			const MoverType& Mover = Params->GetMover();
			const FVector3f& Start   = Params->GetFromLocation();

			typedef NCsMovement::EDestination DestinationType;

			const DestinationType& Destination = Params->GetDestination();
			const float& Time				   = Params->GetTime();

			static const int32 CURRENT= 0;
			FVector3f& Current		  = R->GetValue_Vector3f(CURRENT);

			// Set End Location
			static const int32 END = 1;
			FVector3f& End		   = R->GetValue_Vector3f(END);
			End					   = Params->GetEndLocation();

			static const int32 INTERP_SPEED = 0;
			const float& InterpSpeed		= R->GetValue_Float(INTERP_SPEED);

			const float Percent = Time > 0.0f ? FMath::Clamp(R->GetElapsedTime().Time / Time, 0.0f, 1.0f) : 1.0f;

			CS_COROUTINE_BEGIN(R);

			// TODO: Need to do Relative Location (i.e. check MoveSpace: World or Relative)

			// Actor
			if (Mover == MoverType::Actor)
			{
				Params->GetMoveActor()->SetActorLocation(CsMathLibrary::Convert(Start));
			}
			// Component
			if (Mover == MoverType::Component)
			{
				Params->GetMoveComponent()->SetWorldLocation(CsMathLibrary::Convert(Start));
			}
			Current = Start;

			// TODO: Add CVar for logging

			do
			{
				{
					// Linear
					if (Easing == ECsEasingType::Linear)
					{
						Current = CsMathLibrary::VInterpConstantTo(Current, End, R->GetDeltaTime().Time, InterpSpeed);
					}
					else
					{					
						const float Alpha		= CsMathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);
						// TODO: Optimize, get size and normal in one function.
						const FVector3f Direction = (End - Start).GetSafeNormal();
						const float Distance	= (End - Start).Size();
						Current				    = Start + Alpha * Distance * Direction;
					}

					// Actor
					if (Mover == MoverType::Actor)
					{
						Params->GetMoveActor()->SetActorLocation(CsMathLibrary::Convert(Current));
					}
					// Component
					if (Mover == MoverType::Component)
					{
						Params->GetMoveComponent()->SetWorldLocation(CsMathLibrary::Convert(Current));
					}
				
					CS_COROUTINE_YIELD(R);
				}
			} while (R->GetElapsedTime().Time < Time);

			// Actor
			if (Mover == MoverType::Actor)
			{
				Params->GetMoveActor()->SetActorLocation(CsMathLibrary::Convert(End));
			}
			// Component
			if (Mover == MoverType::Component)
			{
				Params->GetMoveComponent()->SetWorldLocation(CsMathLibrary::Convert(End));
			}

			CS_COROUTINE_END(R);
		}

		void FLibrary::MoveByInterp_Internal_OnEnd(FCsRoutine* R)
		{
			static const int32 RESOURCE  = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			ParamsType* Params			 = Resource->Get();
			Params->Reset();

			Get().Manager_MoveByInterpParams.Deallocate(Resource);
		}

		#pragma endregion Interp

		#pragma endregion Movement
	}
}