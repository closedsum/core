// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsFX
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NManager::FLibrary, SafeSpawn);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR
	
		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_FX_Actor* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot			 = GetContextRootChecked(Context, ContextObject);
			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_FX)
			return Manager_FX;
		}

		UCsManager_FX_Actor* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

			if (!Manager_FX)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_FX."), *Context));
			}
			return Manager_FX;
		}

		UCsManager_FX_Actor* FLibrary::GetSafe(UObject* ContextObject)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Spawn
		#pragma region

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
			// Get Context for Manager_FX
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);
			// Allocate Payload
			typedef NCsFX::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_FX->AllocatePayload<PayloadImplType>(FX.Type);
			// Set Payload
			typedef NCsFX::NPayload::FLibrary PayloadLibrary;

			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, FX);

			// Int
			for (const FCsFXParameterInt& Param : FX.IntParameters)
			{
				typedef NCsFX::NParameter::NInt::FIntType ParameterIntType;

				ParameterIntType* IntType = Manager_FX->AllocateValue<ParameterIntType>();
				
				Param.CopyToParamsAsValue(IntType);
				Payload->Parameters.Add(IntType);
			}
			// Float
			for (const FCsFXParameterFloat& Param : FX.FloatParameters)
			{
				typedef NCsFX::NParameter::NFloat::FFloatType ParameterFloatType;

				ParameterFloatType* FloatType = Manager_FX->AllocateValue<ParameterFloatType>();

				Param.CopyToParamsAsValue(FloatType);
				Payload->Parameters.Add(FloatType);
			}
			// Vector
			for (const FCsFXParameterVector& Param : FX.VectorParameters)
			{
				typedef NCsFX::NParameter::NVector::FVectorType ParameterVectorType;

				ParameterVectorType* VectorType = Manager_FX->AllocateValue<ParameterVectorType>();

				Param.CopyToParamsAsValue(VectorType);
				Payload->Parameters.Add(VectorType);
			}
			return Manager_FX->Spawn(FX.Type, Payload);
		}

		const FCsFXActorPooled* FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			if (!PooledPayload)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PooledPayload is NULL."), *Context));
				return nullptr;
			}

			if (!FX.IsValid(Context))
				return nullptr;

			return SpawnChecked(Context, WorldContext, PooledPayload, FX);
		}
		
		const FCsFXActorPooled* FLibrary::SafeSpawn(UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, FX, nullptr);
		}

		#undef PooledPayloadType

		#pragma endregion Spawn
	}
}