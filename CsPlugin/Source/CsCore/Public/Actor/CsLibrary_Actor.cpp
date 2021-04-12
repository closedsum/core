// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Actor/CsLibrary_Actor.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsActor
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByLabel);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, MoveByInterp_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsActor::FLibrary, MoveByInterp_Internal);
			}
		}
	}

	FLibrary::FLibrary() :
		Manager_MoveByInterpParams()
	{
	}

	FLibrary::~FLibrary()
	{
		Manager_MoveByInterpParams.Shutdown();
	}

	// Get
	#pragma region

	AActor* FLibrary::GetWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		checkf(Tag != NAME_None, TEXT("%s: Tag: None is NOT Valid."), *Context);

#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
#else
		AActor* Actor = nullptr;

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}
	
	AActor* FLibrary::GetByNameChecked(const FString& Context, UObject* WorldContext, const FName& Name)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Actor with Name: %s."), *Context, *(Name.ToString()));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByName(const FString& Context, UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (Name == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Name: %s."), *Context, *(Name.ToString())));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByName(UObject* WorldContext, const FName& Name)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByName;

		return GetSafeByName(Context, WorldContext, Name, nullptr);
	}

	AActor* FLibrary::GetByLabelChecked(const FString& Context, UObject* WorldContext, const FString& Label)
	{
	#if WITH_EDITOR
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		checkf(!Label.IsEmpty(), TEXT("%s: Label is EMPTY."), *Context);

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Actor with Label: %s."), *Context, *Label);
		return nullptr;
	#else
		checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
		return nullptr;
	#endif // #if WITH_EDITOR
	}

	AActor* FLibrary::GetSafeByLabel(const FString& Context, UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
	#if WITH_EDITOR
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (Label.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Label is EMPTY."), *Context));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Label: %s."), *Context, *Label));
		return nullptr;
#else
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
		return nullptr;
#endif // #if !WITH_EDITOR
	}

	AActor* FLibrary::GetSafeByLabel(UObject* WorldContext, const FString& Label)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByLabel;

		return GetSafeByLabel(Context, WorldContext, Label, nullptr);
	}

	#pragma endregion Get

	// Move
	#pragma region 

		// Interp
	#pragma region

	#define ParamsResourceType NCsMovement::NTo::NInterp::NParams::FResource
	#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams

	FCsRoutineHandle FLibrary::MoveByInterpChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params)
	{
		using namespace NCsActor::NLibrary::NCached;

		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		ParamsType* P = Params->Get();

		check(P->IsValidChecked(Context));

		UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

		UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
		const FECsUpdateGroup& UpdateGroup = Params->Get()->GetGroup();

		typedef NCsCoroutine::NPayload::FImpl PayloadType;

		PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

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

		Payload->OnEnds.AddDefaulted();
		OnEndType& OnEnd = Payload->OnEnds.Last();
		OnEnd.BindStatic(&FLibrary::MoveByInterp_Internal_OnEnd);

		static const int32 RESOURCE = 0;
		Payload->SetValue_Void(RESOURCE, Params);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeMoveByInterp(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return FCsRoutineHandle::Invalid;
	}

	char FLibrary::MoveByInterp_Internal(FCsRoutine* R)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::MoveByInterp_Internal;

		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();

		typedef NCsMovement::EDestination DestinationType;

		const DestinationType& Destination = Params->GetDestination();

		static const int32 START = 0;
		FVector& Start = R->GetValue_Vector(START);

		const float& Time = Params->GetTime();

		CS_COROUTINE_BEGIN(R);

		// Set Start
		{
			
		}

		do
		{
			{
				// Location
				// Actor
				// Component
				// Bone

				CS_COROUTINE_YIELD(R);
			}
		} while (R->ElapsedTime.Time < Time);

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

	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Interp

	#pragma endregion Move
}