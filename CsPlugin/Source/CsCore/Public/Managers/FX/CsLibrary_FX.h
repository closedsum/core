// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_Library_FX.h"
#include "Managers/FX/Params/CsParams_FX.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsLog.h"

class ANiagaraActor;
class UNiagaraSystem;
class UNiagaraComponent;
struct FCsRoutine;

// NCsFX::NParamter::IParamter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParamter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)

struct FNiagaraVariable;

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
	#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled
	#define ParameterValueType NCsFX::NParameter::EValue

	public:

		/**
		* Check if the Niagara System has an exposed variable with name: Name.
		* 
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Name		Name of the exposed variable.
		* @param ValueType
		* return			Whether the exposed variable with name: Name exists or not.
		*/
		static bool HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType);

		/**
		* Safely check if the Niagara System has an exposed variable with name: Name.
		*
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Name		Name of the exposed variable.
		* @param ValueType
		* @param Log
		* return			Whether the exposed variable with name: Name exists or not.
		*/
		static bool SafeHasVariableName(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely check if the Niagara System has an exposed variable with name: Name.
		*
		* @param System		Niagara System.
		* @param Name		Name of the exposed variable.
		* @param ValueType
		* return			Whether the exposed variable with name: Name exists or not.
		*/
		static bool SafeHasVariableName(UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType);

		/**
		* Check if the Niagara System has an exposed variable: Parameter.
		* 
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Parameter
		* return			Whether the exposed variable: Parameter exists or not.
		*/
		static bool HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		/**
		* Safely check if the Niagara System has an exposed variable: Parameter.
		*
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Parameter
		* @param Log
		* return			Whether the exposed variable: Parameter exists or not.
		*/
		static bool SafeHasParameter(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely check if the Niagara System has an exposed variable: Parameter.
		*
		* @param System		Niagara System.
		* @param Parameter
		* return			Whether the exposed variable: Parameter exists or not.
		*/
		static bool SafeHasParameter(UNiagaraSystem* System, const ParameterType* Parameter);

		/**
		* Check if the Niagara System has an exposed variable: Parameter.
		*
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Parameter
		* return			Whether the exposed variable: Parameter exists or not.
		*/
		static bool HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ScaledParameterType* Parameter);

		/**
		* 
		* 
		* @param Context	The calling context.
		* @param Component
		* @param Parameter
		* return
		*/
		static void SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Component
		* @param Parameter
		* @param Scale
		* return
		*/
		static void SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ScaledParameterType* ScaledParameter, const float& Scale);

		static FNiagaraVariable* GetDefaultVariableChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static int32 GetDefaultVariableIntChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static float GetDefaultVariableFloatChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static FVector GetDefaultVariableVectorChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

	#undef ParameterType
	#undef ScaledParameterType
	#undef ParameterValueType

		static void SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData);

		static void SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData, TArray<int32>& Indices);

		static void SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData);

		static void SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData, TArray<int32>& Indices);

		static void SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector>& ArrayData);

		static void SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector>& ArrayData, TArray<int32>& Indices);
		
		static void SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4>& ArrayData);

		static void SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4>& ArrayData, TArray<int32>& Indices);

		static void SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat>& ArrayData);

		static void SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat>& ArrayData, TArray<int32>& Indices);

	#pragma endregion Parameter

	// Variable
	#pragma region
	public:

		static FNiagaraVariable* GetExposedVariableChecked(const FString& Context, UNiagaraSystem* System, const FName& Name);

		static FNiagaraVariable* GetSafeExposedVariable(const FString& Context, UNiagaraSystem* System, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Variable

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

	// State
	#pragma region
	public:

		/**
		* Check whether the NiagaraSystem on the RootComponent, a UNiagaraComponent, for Actor
		* is "complete".
		* Complete is:		
		*	ActualExecutionState == ENiagaraExecutionState::Complete ||
		*	ActualExecutionState == ENiagaraExecutionState::Disabled
		* 
		* @param Context	The calling context.
		* @param Actor
		*/
		static bool IsCompleteChecked(const FString& Context, ANiagaraActor* Actor);

		/**
		* Check whether the NiagaraSystem on the NiagaraComponent is "complete".
		* Complete is:
		*	ActualExecutionState == ENiagaraExecutionState::Complete ||
		*	ActualExecutionState == ENiagaraExecutionState::Disabled
		*
		* @param Context	The calling context.
		* @param Component
		*/
		static bool IsCompleteChecked(const FString& Context, UNiagaraComponent* Component);

		/**
		* Check whether the NiagaraSystem on the NiagaraComponent is "Inactive".
		* Inactive is:
		*	ActualExecutionState == ENiagaraExecutionState::Inactve
		*
		* @param Context	The calling context.
		* @param Component
		*/
		static bool IsInactiveChecked(const FString& Context, UNiagaraComponent* Component);

		/**
		* Requests the the simulation be reset on the next tick.
		* 
		* @param Context	The calling context.
		* @param Component
		*/
		static void ResetAllChecked(const FString& Context, UNiagaraComponent* Component);

	#pragma endregion State
	};
}