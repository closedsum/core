// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/FX/CsTypes_Library_FX.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsLog.h"
#pragma once

class UNiagaraSystem;
class UNiagaraComponent;
struct FCsRoutine;

// NCsFX::NParamter::IParamter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)

namespace NCsFX
{
	/**
	* Library of functions related to FX
	*/
	struct CSCORE_API FLibrary final
	{
	private:
		FLibrary();

		FLibrary(const FLibrary&) = delete;
		FLibrary(FLibrary&&) = delete;
	public:
		~FLibrary();

		FORCEINLINE static FLibrary& Get()
		{
			static FLibrary Instance;
			return Instance;
		}

	// Load
	#pragma region
	public:

		/**
		* Load a NiagaraSystem at the given Path.
		* 
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the NiagaraSystem to load.
		* @param Log
		* return			NiagaraSystem.
		*/
		static UNiagaraSystem* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a NiagaraSystem at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the NiagaraSystem to load.
		* @param Log
		* return			NiagaraSystem.
		*/
		static UNiagaraSystem* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Parameter
	#pragma region

	#define ParameterType NCsFX::NParameter::IParameter

	public:

		/**
		* 
		* 
		* @param Context	The calling context.
		* @param System
		* @param Name
		* return
		*/
		static bool HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name);

		/**
		* 
		* 
		* @param Context	The calling context.
		* @param System
		* @param Parameter
		* return
		*/
		static bool HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		/**
		* 
		* 
		* @param Context	The calling context.
		* @param Component
		* @param Parameter
		* return
		*/
		static void SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter);

	#undef ParameterType

	#pragma endregion Parameter

	// Spawn
	#pragma region
	private:

	#define ParamsManagerType NCsFX::NSpawn::NParams::FManager
	#define ParamsResourceType NCsFX::NSpawn::NParams::FResource
	#define ParamsType NCsFX::NSpawn::NParams::FParams

		ParamsManagerType Manager_SpawnParams;

	public:

		FORCEINLINE ParamsResourceType* AllocateSpawnParams() { return Manager_SpawnParams.Allocate(); }

		FORCEINLINE void DeallocateSpawnParams(ParamsResourceType* Resource) { Manager_SpawnParams.Deallocate(Resource); }

	public:


		/**
		* Spawn an FX with the given params.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param ParamsType
		* return
		*/
		static FCsRoutineHandle SpawnChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params);

		/**
		* Safely spawn an FX with the given params.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param ParamsType
		* @param Log
		* return				Handle to the coroutine if the system is spawned via a coroutine.
		*/
		static FCsRoutineHandle SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

		static char Spawn_Internal(FCsRoutine* R);

		static void Spawn_Internal_OnEnd(FCsRoutine* R);

	#undef ParamsManagerType
	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Spawn
	};
}