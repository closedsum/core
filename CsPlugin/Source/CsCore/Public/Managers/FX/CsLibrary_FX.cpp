// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsLibrary_FX.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// FX
#include "Managers/FX/Params/CsParams_FX.h"
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::FLibrary, Spawn_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsFX::FLibrary, Spawn_Internal);
			}
		}
	}

	FLibrary::FLibrary() :
		Manager_SpawnParams()
	{
	}

	FLibrary::~FLibrary()
	{
		Manager_SpawnParams.Shutdown();
	}

	// Load
	#pragma region

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (!Path.IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path is NOT Valid.")));
			return nullptr;
		}

		UObject* Object = Path.TryLoad();

		if (!Object)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Object at Path: %s."), *Context, *(Path.ToString())));
			return nullptr;
		}

		UNiagaraSystem* System = Cast<UNiagaraSystem>(Object);

		if (!System)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s with Class: %s @ %s is NOT of type: UNiagaraSystem."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName())));
			return nullptr;
		}
		return System;
	}

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (Path.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path is EMPTY."), *Context));
			return nullptr;
		}

		FSoftObjectPath SoftPath(Path);

		return SafeLoad(Context, SoftPath, Log);
	}

	#pragma endregion Load

	bool FLibrary::HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name)
	{
		checkf(System, TEXT("%s: System is NULL."), *Context);

		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
				Found = true;
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	#define ParameterType NCsFX::NParameter::IParameter
	bool FLibrary::HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
	#undef ParameterType

		checkf(System, TEXT("%s: System is NULL."), *Context);

		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		check(ParameterLibrary::IsValidChecked(Context, Parameter));

		const FName& Name = Parameter->GetName();

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
				Found = true;
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	#define ParameterType NCsFX::NParameter::IParameter
	void FLibrary::SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter)
	{
	#undef ParameterType

		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		UNiagaraSystem* System = Component->GetAsset();

		checkf(System, TEXT("%s: Asset on Component: %s is NULL."), *Context, *(Component->GetName()));

		check(HasParameterChecked(Context, System, Parameter));

		typedef NCsFX::NParameter::EValue ParameterValueType;
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		const ParameterValueType& ValueType = Parameter->GetValueType();

		// Int
		if (ValueType == ParameterValueType::Int)
			Component->SetVariableInt(Parameter->GetName(), ParameterLibrary::GetIntChecked(Context, Parameter));
		// Float
		if (ValueType == ParameterValueType::Float)
			Component->SetVariableFloat(Parameter->GetName(), ParameterLibrary::GetFloatChecked(Context, Parameter));
		// Vector
		else
		if (ValueType == ParameterValueType::Vector)
			Component->SetVariableVec3(Parameter->GetName(), ParameterLibrary::GetVectorChecked(Context, Parameter));
	}

	#define ParamsResourceType NCsFX::NSpawn::NParams::FResource
	#define ParamsType NCsFX::NSpawn::NParams::FParams

	FCsRoutineHandle FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params)
	{
		using namespace NCsFX::NLibrary::NCached;

		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

		UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
		const FECsUpdateGroup& UpdateGroup = Params->Get()->Group;

		typedef NCsCoroutine::NPayload::FImpl PayloadType;

		PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

		#define COROUTINE Spawn_Internal

		Payload->CoroutineImpl.BindStatic(&NCsFX::FLibrary::COROUTINE);
		Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
		Payload->Owner.SetObject(WorldContext);
		Payload->SetName(Str::COROUTINE);
		Payload->SetFName(Name::COROUTINE);

		#undef COROUTINE

		// Set End callback (to free any allocated references)
		typedef NCsCoroutine::FOnEnd OnEndType;

		Payload->OnEnds.AddDefaulted();
		OnEndType& OnEnd = Payload->OnEnds.Last();
		OnEnd.BindStatic(&FLibrary::Spawn_Internal_OnEnd);

		static const int32 RESOURCE = 0;
		Payload->SetValue_Void(RESOURCE, Params);

		ParamsType* P = Params->Get();
		P->Update();
	
		const FCsSpawnerFrequencyParams& FrequencyParams = Params->Get()->FrequencyParams;
		const float TotalTime = FrequencyParams.CalculateTotalTime();

		static const int32 TOTAL_TIME = 0;
		Payload->SetValue_Float(TOTAL_TIME, TotalTime);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check to get Context Root for Manager_FX
		{
			typedef NCsFX::NManager::FLibrary FXManagerLibrary;

			UObject* ContextRoot = FXManagerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}

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

		if (!Get().Manager_SpawnParams.Contains(Params))
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

		return SpawnChecked(Context, WorldContext, Params);
	}

	char FLibrary::Spawn_Internal(FCsRoutine* R)
	{
		using namespace NCsFX::NLibrary::NCached;

		const FString& Context = Str::Spawn_Internal;

		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();

		const FCsSpawnerFrequencyParams& FrequencyParams = Params->FrequencyParams;
		const ECsSpawnerFrequency& FrequencyType		 = FrequencyParams.Type;

		static const int32 CAN_SPAWN = 0;
		bool& CanSpawn				 = R->GetValue_Flag(CAN_SPAWN);

		static const int32 HAS_SPAWN_INTERVAL = 1;
		bool& HasSpawnInterval				  = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

		static const int32 SPAWN_COUNT = 0;
		int32& SpawnCount			   = R->GetValue_Int(SPAWN_COUNT);

		static const int32 TOTAL_TIME = 0;
		const float& TotalTime		  = R->GetValue_Float(TOTAL_TIME);

		FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
		ElapsedTime += R->DeltaTime;

		CS_COROUTINE_BEGIN(R)

		do
		{
			{
				ElapsedTime.Reset();

				// Spawn FX
				{
					typedef NCsFX::NManager::FLibrary FXManagerLibrary;
					typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

					UObject* Owner = R->GetOwnerAsObject();

					PayloadImplType Payload;
					Payload.Instigator = Owner;
					Payload.Parent	   = Params->GetActor();

					FXManagerLibrary::SpawnChecked(Context, R->GetOwnerAsObject(), &Payload, Params->FX);
				}

				++SpawnCount;

				// Once
				if (FrequencyType == ECsSpawnerFrequency::Once)
				{
					 // Do Nothing 
				}
				// Count | TimeCount | TimeInterval
				else
				if (FrequencyType == ECsSpawnerFrequency::Count ||
					FrequencyType == ECsSpawnerFrequency::TimeCount ||
					FrequencyType == ECsSpawnerFrequency::TimeInterval)
				{
					CanSpawn		 = SpawnCount < FrequencyParams.Count;
					HasSpawnInterval = CanSpawn && FrequencyParams.Interval > 0.0f;
				}
				// Infinite
				else
				if (FrequencyType == ECsSpawnerFrequency::Infinite)
				{
					CanSpawn		 = true;
					HasSpawnInterval = true;
				}

				if (HasSpawnInterval)
				{
					CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams.Interval);
				}
			}
		} while (CanSpawn);

		CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= TotalTime);

		CS_COROUTINE_END(R)
	}

	void FLibrary::Spawn_Internal_OnEnd(FCsRoutine* R)
	{
		static const int32 RESOURCE  = 0;
		ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		ParamsType* Params			 = Resource->Get();
		Params->Reset();

		Get().Manager_SpawnParams.Deallocate(Resource);
	}

	#undef ParamsResourceType
	#undef ParamsType
}