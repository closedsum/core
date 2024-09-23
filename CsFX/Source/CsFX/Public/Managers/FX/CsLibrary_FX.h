// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/FX/CsTypes_Library_FX.h"
#include "Managers/FX/Params/CsParams_FX.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsFXLog.h"

class ANiagaraActor;
class UNiagaraSystem;
class UNiagaraComponent;
struct FCsRoutine;

// NCsFX::NParameter::IParamter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParameter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)
// NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NDataInterface, NSkeletalMesh, FSkeletalMeshType)

class UNiagaraParameterCollectionInstance;
class UNiagaraParameterCollection;
class UNiagaraDataInterfaceSkeletalMesh;
class UNiagaraDataInterfaceArrayInt32;
class UNiagaraDataInterfaceArrayFloat;
class UNiagaraDataInterfaceArrayFloat3;
class UNiagaraDataInterfaceArrayFloat4;
class UNiagaraDataInterfaceArrayQuat;
struct FNiagaraVariable;

//class UCsNiagaraDataInterfaceArrayFloatRW;

class FNiagaraSystemInstance;
class FNiagaraSystemSimulation;

namespace NCsFX
{
	/**
	* Library of functions related to FX
	*/
	struct CSFX_API FLibrary final
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
		static UNiagaraSystem* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		/**
		* Load a NiagaraSystem at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the NiagaraSystem to load.
		* @param Log
		* return			NiagaraSystem.
		*/
		static UNiagaraSystem* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

	#pragma endregion Load

	public:

		static UNiagaraParameterCollectionInstance* GetInstancedChecked(const FString& Context, const UObject* WorldContext, UNiagaraParameterCollection* Collection);

	// Parameter
	#pragma region

	#define ParameterType NCsFX::NParameter::IParameter
	#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled
	#define ParameterValueType NCsFX::NParameter::EValue

	public:

		/**
		* Check if the Name of a User Parameter is valid or not.
		*
		* @param Context	The calling context.
		* @param Name		Name of the user parameter.
		* return			Whether or note the Name is a valid User Parameter.
		*/
		static bool IsValidUserVariableNameChecked(const FString& Context, const FName& Name);

		/**
		* Safely check if the Name of a User Parameter is valid or not.
		*
		* @param Context	The calling context.
		* @param Name		Name of the user parameter.
		* @param Log		(optional)
		* return			Whether or note the Name is a valid User Parameter.
		*/
		static bool IsValidUserVariableName(const FString& Context, const FName& Name, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

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
		static bool SafeHasVariableName(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

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
		static bool SafeHasParameter(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

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

		static void SetIntParameterChecked(const FString& Context, ANiagaraActor* Actor, const FName& ParameterName, const int32& Value);

		static void SetIntParameterChecked(const FString& Context, UNiagaraComponent* Component, const FName& ParameterName, const int32& Value);

		static FNiagaraVariable* GetDefaultVariableChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static int32 GetDefaultVariableIntChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static float GetDefaultVariableFloatChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		static FVector3f GetDefaultVariableVectorChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

	#undef ParameterType
	#undef ScaledParameterType
	#undef ParameterValueType

	#define SkeletalMeshParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

		/**
		* Get the Niagara Data Interface of type: Skeletal Mesh.
		*
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Parameter
		* return			Data Interface.
		*/
		static UNiagaraDataInterfaceSkeletalMesh* GetDataInterfaceChecked(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter);

		/**
		* Safely get the Niagara Data Interface of type: Skeletal Mesh.
		*
		* @param Context	The calling context.
		* @param System		Niagara System.
		* @param Parameter
		* @param Log		(optional)
		* return			Data Interface.
		*/
		static UNiagaraDataInterfaceSkeletalMesh* GetSafeDataInterface(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		/**
		* Set the Niagara Data Interface of type: Skeletal Mesh associated with Parameter.
		*
		* @param Context	The calling context.
		* @param Component
		* @param Parameter
		* return
		*/
		static void SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter);

		/**
		* Safely set the Niagara Data Interface of type: Skeletal Mesh associated with Parameter.
		*
		* @param Context	The calling context.
		* @param Component
		* @param Parameter
		* @param Log		(optional)
		* return
		*/
		static void SetSafeParameter(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

	#undef SkeletalMeshParameterType

		FORCEINLINE static bool HasArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
		{
			return GetArrayInt32Checked(Context, System, OverrideName) != nullptr;
		}

		static UNiagaraDataInterfaceArrayInt32* GetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName);
		
		static UNiagaraDataInterfaceArrayInt32* GetArrayInt32Checked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName);

		static void SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData);

		static void SetArrayInt32Checked(const FString& Context, UNiagaraDataInterfaceArrayInt32* ArrayDI, const TArray<int32>& ArrayData, TArray<int32>& Indices);

		static void SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData, TArray<int32>& Indices);

		static UNiagaraDataInterfaceArrayFloat* GetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName);

		static UNiagaraDataInterfaceArrayFloat* GetArrayFloatChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const int32& Index);

		//static UCsNiagaraDataInterfaceArrayFloatRW* GetArrayFloatRWChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const int32& Index);

		static void InitArrayFloatChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, const TArray<float>& ArrayData);

		//static void InitArrayFloatChecked(const FString& Context, UCsNiagaraDataInterfaceArrayFloatRW* ArrayDI, const TArray<float>& ArrayData);

		static void SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData);

		static void SetArrayFloatChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, const TArray<float>& ArrayData, TArray<int32>& Indices);

		static void SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData, TArray<int32>& Indices);

	#define PayloadType NCsFX::NLibrary::NSetArrayFloatChecked::FPayload

		static void SetArrayFloatChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, PayloadType& Payload);

		//static void SetArrayFloatChecked(const FString& Context, UCsNiagaraDataInterfaceArrayFloatRW* ArrayDI, PayloadType& Payload);

	#undef PayloadType

		static UNiagaraDataInterfaceArrayFloat3* GetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName);

		static UNiagaraDataInterfaceArrayFloat3* GetArrayVectorChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName);

		static void SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector3f>& ArrayData);

		static void SetArrayVectorChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat3* ArrayDI, const TArray<FVector3f>& ArrayData, TArray<int32>& Indices);

		static void SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector3f>& ArrayData, TArray<int32>& Indices);
		
		static UNiagaraDataInterfaceArrayFloat4* GetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName);

		static UNiagaraDataInterfaceArrayFloat4* GetArrayVector4Checked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName);

		static void SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4f>& ArrayData);

		static void SetArrayVector4Checked(const FString& Context, UNiagaraDataInterfaceArrayFloat4* ArrayDI, const TArray<FVector4f>& ArrayData, TArray<int32>& Indices);

		static void SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4f>& ArrayData, TArray<int32>& Indices);

		static UNiagaraDataInterfaceArrayQuat* GetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName);

		static UNiagaraDataInterfaceArrayQuat* GetArrayQuatChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName);

		static void SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat4f>& ArrayData);

		static void SetArrayQuatChecked(const FString& Context, UNiagaraDataInterfaceArrayQuat* ArrayDI, const TArray<FQuat4f>& ArrayData, TArray<int32>& Indices);

		static void SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat4f>& ArrayData, TArray<int32>& Indices);

	#pragma endregion Parameter

	// Variable
	#pragma region
	public:

		static FNiagaraVariable* GetExposedVariableChecked(const FString& Context, UNiagaraSystem* System, const FName& Name);

		static FNiagaraVariable* GetSafeExposedVariable(const FString& Context, UNiagaraSystem* System, const FName& Name, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		static bool SafeIsExposedVariableInt(const FString& Context, UNiagaraSystem* System, const FName& Name, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		static bool SetSafeExposedVariableInt(const FString& Context, UNiagaraSystem* System, const FName& Name, const int32& Value, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

	#if WITH_EDITOR
		static bool SafeExposedParameters_PostGenericEditChange(const FString& Context, UNiagaraSystem* System, void(*Log)(const FString&) = &NCsFX::FLog::Warning);
	#endif // #if WITH_EDITOR

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
		static FCsRoutineHandle SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		/**
		* Spawn an FX ONCE with a DELAY on the UpdateGroup: GameState.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param FX
		* @param Delay
		* return
		*/
		static FCsRoutineHandle Spawn_GameState_OnceWithDelayChecked(const FString& Context, UObject* WorldContext, const FCsFX& FX, const float& Delay);

		/**
		* Safely spawn an FX ONCE with a DELAY on the UpdateGroup: GameState.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param FX
		* @param Delay
		* return
		*/
		static FCsRoutineHandle SafeSpawn_GameState_OnceWithDelay(const FString& Context, UObject* WorldContext, const FCsFX& FX, const float& Delay, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

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
		* Check whether the NiagaraSystem on the NiagaraComponent is "Ready to Run".
		*  This implies there are no pending compilation, setup, etc for the System.
		* 
		* @param Context	The calling context.
		* @param Component
		*/
		static bool IsReadyToRunChecked(const FString& Context, const UNiagaraComponent* Component);

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

	// System
	#pragma region
	public:

		static const FNiagaraSystemInstance* GetSystemInstanceChecked(const FString& Context, const UNiagaraComponent* Component);
		static FNiagaraSystemInstance* GetSystemInstanceChecked(const FString& Context, UNiagaraComponent* Component);

		static FNiagaraSystemInstance* GetSafeSystemInstance(const FString& Context, UNiagaraComponent* Component, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		static bool SafeHasSystemInstance(const FString& Context, const UNiagaraComponent* Component, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		static TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> GetSystemSimulationChecked(const FString& Context, UNiagaraComponent* Component);

		static TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> GetSafeSystemSimulation(const FString& Context, UNiagaraComponent* Component, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

	#pragma endregion System
	};
}

using CsFXLibrary = NCsFX::FLibrary;