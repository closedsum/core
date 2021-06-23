// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Actor/CsLibrary_Actor.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsCached.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Library/CsLibrary_Math.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Components
#include "Components/PrimitiveComponent.h"
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
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByTag);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByLabel);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, MoveByInterp_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeRootComponent);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeRootPrimitiveComponent);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetSafeMaterial);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetSafeMaterials);
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

	AActor* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_NAME_NONE_CHECKED(Tag)

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

	AActor* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_NAME_NONE_RET_NULL(Tag)

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
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString())));
		return nullptr;
	}

	void FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_ARRAY_EMPTY_CHECKED(Tags, FName)

		CS_IS_ARRAY_ANY_NONE_CHECKED(Tags)

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					continue;
				}
			}
			OutActors.Add(A);
		}

		typedef NCsName::FLibrary NameLibrary;

		checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find Actors with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
	}

	bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_ARRAY_EMPTY(Tags, FName)

		CS_IS_ARRAY_ANY_NONE(Tags)

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					continue;
				}
			}
			OutActors.Add(A);
		}

		typedef NCsName::FLibrary NameLibrary;

		if (OutActors.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actors with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
		}
		return OutActors.Num() > CS_EMPTY;
	}

	AActor* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)

		CS_IS_NAME_NONE_CHECKED(Name)

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

	AActor* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	AActor* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByName;

		return GetSafeByName(Context, WorldContext, Name, nullptr);
	}

	AActor* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
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

	AActor* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	AActor* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByLabel;

		return GetSafeByLabel(Context, WorldContext, Label, nullptr);
	}

	#pragma endregion Get

	// RootComponent
	#pragma region

	USceneComponent* FLibrary::GetRootComponentChecked(const FString& Context, AActor* Actor)
	{
		CS_IS_PTR_NULL_CHECKED(Actor)

		USceneComponent* RootComponent = Actor->GetRootComponent();

		checkf(RootComponent, TEXT("%s: Actor: %s with Class: %s does NOT have a RootComponent."), *Context, *(Actor->GetName()), *(Actor->GetClass()->GetName()));

		return RootComponent;
	}

	USceneComponent* FLibrary::GetSafeRootComponent(const FString& Context, AActor* Actor, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(Actor)

		USceneComponent* RootComponent = Actor->GetRootComponent();

		if (!RootComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Actor: %s with Class: %s does NOT have a RootComponent."), *Context, *(Actor->GetName()), *(Actor->GetClass()->GetName())));
			return nullptr;
		}
		return RootComponent;
	}

	USceneComponent* FLibrary::GetSafeRootComponent(AActor* Actor)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeRootComponent;

		return GetSafeRootComponent(Context, Actor, nullptr);
	}

	UPrimitiveComponent* FLibrary::GetRootPrimitiveComponentChecked(const FString& Context, AActor* Actor)
	{
		USceneComponent* RootComponent = GetRootComponentChecked(Context, Actor);
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(RootComponent);

		checkf(Component, TEXT("%s: RootComponent: %s with Class: %s is not of type: UPrimitiveComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));

		return Component;
	}

	UPrimitiveComponent* FLibrary::GetSafeRootPrimitiveComponent(const FString& Context, AActor* Actor, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (USceneComponent* RootComponent = GetSafeRootComponent(Context, Actor, Log))
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(RootComponent);

			if (!Component)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: RootComponent: %s with Class: %s is not of type: UPrimitiveComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName())));
				return nullptr;
			}
			return Component;
		}
		return nullptr;
	}

	UPrimitiveComponent* FLibrary::GetSafeRootPrimitiveComponent(AActor* Actor)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeRootPrimitiveComponent;

		return GetSafeRootPrimitiveComponent(Context, Actor, nullptr);
	}

	#pragma endregion RootComponent

	// Move
	#pragma region 

		// Interp
	#pragma region

	#define ParamsResourceType NCsMovement::NTo::NInterp::NParams::FResource
	#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams

	FCsRoutineHandle FLibrary::MoveByInterpChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params)
	{
		using namespace NCsActor::NLibrary::NCached;

		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		ParamsType* P = Params->Get();

		check(P->IsValidChecked(Context));
		// Get Coroutine Scheduler
		UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

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
		const FVector Start		= P->GetFromLocation();
		const FVector End		= P->GetEndLocation();
		const float Distance    = (End - Start).Size();
		const float InterpSpeed = Distance / P->GetTime();
		Payload->SetValue_Float(INTERP_SPEED, InterpSpeed);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeMoveByInterp(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
			typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

			UObject* ContextRoot = CoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}
		return MoveByInterpChecked(Context, WorldContext, Params);
	}

	char FLibrary::MoveByInterp_Internal(FCsRoutine* R)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::MoveByInterp_Internal;

		// Get Params
		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();
		// Cache appropriate values from Params
		const ECsEasingType& Easing = Params->GetEasing();

		typedef NCsMovement::EMover MoverType;

		const MoverType& Mover = Params->GetMover();
		const FVector& Start   = Params->GetFromLocation();

		typedef NCsMovement::EDestination DestinationType;

		const DestinationType& Destination = Params->GetDestination();
		const float& Time				   = Params->GetTime();

		static const int32 CURRENT= 0;
		FVector& Current		  = R->GetValue_Vector(CURRENT);

		// Set End Location
		static const int32 END = 1;
		FVector& End		   = R->GetValue_Vector(END);
		End					   = Params->GetEndLocation();

		static const int32 INTERP_SPEED = 0;
		const float& InterpSpeed		= R->GetValue_Float(INTERP_SPEED);

		const float Percent = Time > 0.0f ? FMath::Clamp(R->ElapsedTime.Time / Time, 0.0f, 1.0f) : 1.0f;

		CS_COROUTINE_BEGIN(R);

		// TODO: Need to do Relative Location (i.e. check MoveSpace: World or Relative)

		// Actor
		if (Mover == MoverType::Actor)
		{
			Params->GetMoveActor()->SetActorLocation(Start);
		}
		// Component
		if (Mover == MoverType::Component)
		{
			Params->GetMoveComponent()->SetWorldLocation(Start);
		}
		Current = Start;

		// TODO: Add CVar for logging

		do
		{
			{
				typedef NCsMath::FLibrary MathLibrary;

				// Linear
				if (Easing == ECsEasingType::Linear)
				{
					Current = FMath::VInterpConstantTo(Current, End, R->DeltaTime.Time, InterpSpeed);
				}
				else
				{					
					const float Alpha		= MathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);
					// TODO: Optimize, get size and normal in one function.
					const FVector Direction = (End - Start).GetSafeNormal();
					const float Distance	= (End - Start).Size();
					Current				    = Start + Alpha * Distance * Direction;
				}

				// Actor
				if (Mover == MoverType::Actor)
				{
					Params->GetMoveActor()->SetActorLocation(Current);
				}
				// Component
				if (Mover == MoverType::Component)
				{
					Params->GetMoveComponent()->SetWorldLocation(Current);
				}
				
				CS_COROUTINE_YIELD(R);
			}
		} while (R->ElapsedTime.Time < Time);

		// Actor
		if (Mover == MoverType::Actor)
		{
			Params->GetMoveActor()->SetActorLocation(End);
		}
		// Component
		if (Mover == MoverType::Component)
		{
			Params->GetMoveComponent()->SetWorldLocation(End);
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

	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Interp

	#pragma endregion Move

	// Material
	#pragma region

	void FLibrary::SetMaterialChecked(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index)
	{
		UPrimitiveComponent* Component = GetRootPrimitiveComponentChecked(Context, Actor);

		typedef NCsMaterial::FLibrary MaterialLibrary;

		MaterialLibrary::SetChecked(Context, Component, Material, Index);
	}

	void FLibrary::SetSafeMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (UPrimitiveComponent* Component = GetSafeRootPrimitiveComponent(Context, Actor, Log))
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetSafe(Context, Component, Material, Index, Log);
		}
	}

	void FLibrary::SetSafeMaterial(AActor* Actor, UMaterialInterface* Material, const int32& Index)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::SetSafeMaterial;

		SetSafeMaterial(Context, Actor, Material, Index, nullptr);
	}

	void FLibrary::SetMaterialsChecked(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials)
	{
		UPrimitiveComponent* Component = GetRootPrimitiveComponentChecked(Context, Actor);

		typedef NCsMaterial::FLibrary MaterialLibrary;

		MaterialLibrary::SetChecked(Context, Component, Materials);
	}

	void FLibrary::SetSafeMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (UPrimitiveComponent* Component = GetSafeRootPrimitiveComponent(Context, Actor, Log))
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetSafe(Context, Component, Materials, Log);
		}
	}

	#pragma endregion Material

	// Spawn
	#pragma region

	AActor* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return nullptr;

		typedef NCsObject::FLibrary ObjectLibrary;

		UClass* Class = ObjectLibrary::SafeLoad<UClass>(Context, Path, Log);

		if (!Class)
			return nullptr;

		AActor* Actor = World->SpawnActor<AActor>(Class);

		if (!Actor)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to Spawn Actor with Class: %s."), *Context, *(Class->GetName())));
		}
		return Actor;
	}

	AActor* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FString& Path, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FSoftObjectPath SoftPath(Path);

		if (!Path.EndsWith(NCsCached::Str::_C))
		{
			SoftPath = FSoftObjectPath(Path + NCsCached::Str::_C);
		}
		return SafeSpawn(Context, WorldContext, SoftPath, Log);
	}

	#pragma endregion Spawn
}