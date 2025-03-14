// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"

// Library
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#if WITH_EDITOR
// Library
	// Common
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NManager::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NManager::FLibrary, SafeSpawn);
				}
			}
		}

		using LogClassType = NCsFX::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
		using PayloadType = NCsFX::NPayload::IPayload;
		using PayloadImplType = NCsFX::NPayload::NImpl::FImpl;
		using PayloadLibrary = NCsFX::NPayload::NLibrary::FLibrary;

		// Print
		#pragma region

		FString FLibrary::PrintObjectWithClass(const UCsManager_FX* Manager)
		{
			return FString::Printf(TEXT("%s: with Class: %s"), *(Manager->GetName()), *(Manager->GetClass()->GetName()));
		}

		#pragma endregion Print

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}
			return CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR
	
		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_FX* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot	  = GetContextRootChecked(Context, ContextObject);
			UCsManager_FX* Manager_FX = UCsManager_FX::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_FX)
			return Manager_FX;
		}

		UCsManager_FX* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_FX* Manager_FX = UCsManager_FX::GetSafe(Context, ContextRoot, Log);

			if (!Manager_FX)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_FX."), *Context));
			}
			return Manager_FX;
		}

		UCsManager_FX* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// State
		#pragma region

		bool FLibrary::IsBeginningShutdownChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->IsBeginningShutdown();
		}

		#pragma endregion State

		// Pool
		#pragma region
		
		bool FLibrary::IsNoneAllocatedChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->IsNoneAllocated();
		}

			// Find
		#pragma region
		
		const FCsFXActorPooled* FLibrary::FindSafeObject(const FString& Context, const UObject* WorldContext, const FECsFX& Type, const int32& Index, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_FX* Manager_FX = GetSafe(Context, WorldContext, Log))
			{
				return Manager_FX->FindSafeObject(Type, Index);
			}
			return nullptr;
		}

		#pragma endregion Find

		#pragma endregion Pool

		// Allocate / Deallocate
		#pragma region
		
		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			// NOTE: For now only PayloadImplType (NCsFX::NPayload::FImpl) is supported
			return AllocatePayloadImplChecked(Context, WorldContext, PooledPayload, FX, Transform);
		}

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location)
		{
			// NOTE: For now only PayloadImplType (NCsFX::NPayload::FImpl) is supported
			FTransform T = FTransform::Identity;
			T.SetTranslation(Location);
			return AllocatePayloadImplChecked(Context, WorldContext, PooledPayload, FX, T);
		}

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			// NOTE: For now only PayloadImplType (NCsFX::NPayload::FImpl) is supported
			return AllocatePayloadImplChecked(Context, WorldContext, FX, Transform);
		}

		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			UCsManager_FX* Manager_FX = GetChecked(Context, WorldContext);

			CS_IS_PTR_NULL_CHECKED(PooledPayload)
			CS_IS_VALID_CHECKED(FX);

			PayloadImplType* Payload = Manager_FX->AllocatePayload<PayloadImplType>(FX.Type);

			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, FX, Transform);

			// Int
			for (const FCsFXParameterInt& Param : FX.IntParameters)
			{
				typedef NCsFX::NParameter::NInt::FIntType IntParameterType;

				IntParameterType* IntType = Manager_FX->AllocateValue<IntParameterType>();

				Param.CopyToParamsAsValue(IntType);
				Payload->Parameters.Add(IntType);
			}
			// Float
			for (const FCsFXParameterFloat& Param : FX.FloatParameters)
			{
				typedef NCsFX::NParameter::NFloat::FFloatType FloatParameterType;

				FloatParameterType* FloatType = Manager_FX->AllocateValue<FloatParameterType>();

				Param.CopyToParamsAsValue(FloatType);
				Payload->Parameters.Add(FloatType);
			}
			// Vector
			for (const FCsFXParameterVector& Param : FX.VectorParameters)
			{
				typedef NCsFX::NParameter::NVector::FVectorType VectorParameterType;

				VectorParameterType* VectorType = Manager_FX->AllocateValue<VectorParameterType>();

				Param.CopyToParamsAsValue(VectorType);
				Payload->Parameters.Add(VectorType);
			}

			// Scaled

				// Int
			for (const FCsFX_Parameter_Scaled_Int& Param : FX.ScaledParameters.Ints)
			{
				typedef NCsFX::NParameter::NScaled::NInt::FIntType IntParameterType;

				IntParameterType* IntType = Manager_FX->AllocateValue<IntParameterType>();

				Param.CopyToParamsAsValue(IntType);
				Payload->ScaledParameters.Add(IntType);
			}
				// Float
			for (const FCsFX_Parameter_Scaled_Float& Param : FX.ScaledParameters.Floats)
			{
				typedef NCsFX::NParameter::NScaled::NFloat::FFloatType FloatParameterType;

				FloatParameterType* FloatType = Manager_FX->AllocateValue<FloatParameterType>();

				Param.CopyToParamsAsValue(FloatType);
				Payload->ScaledParameters.Add(FloatType);
			}
				// Vector
			for (const FCsFX_Parameter_Scaled_Vector& Param : FX.ScaledParameters.Vectors)
			{
				typedef NCsFX::NParameter::NScaled::NVector::FVectorType VectorParameterType;

				VectorParameterType* VectorType = Manager_FX->AllocateValue<VectorParameterType>();

				Param.CopyToParamsAsValue(VectorType);
				Payload->ScaledParameters.Add(VectorType);
			}

			// Data Interface

				// Skeletal Mesh
			for (const FCsFX_Parameters_DataInterface_SkeletalMesh& Param : FX.DataInterfaceParameters.SkeletalMeshes)
			{
				typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType SkeletalMeshParameterType;

				SkeletalMeshParameterType* SkeletalMeshType = Manager_FX->AllocateValue<SkeletalMeshParameterType>();

				Param.CopyToParamsAsValue(SkeletalMeshType);
				Payload->SkeletalMeshParameters.Add(SkeletalMeshType);
			}
			return Payload;
		}

		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location)
		{
			FTransform T = FTransform::Identity;
			T.SetTranslation(Location);
			return AllocatePayloadImplChecked(Context, WorldContext, PooledPayload, FX, T);
		}

		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			UCsManager_FX* Manager_FX = GetChecked(Context, WorldContext);

			CS_IS_VALID_CHECKED(FX);

			PayloadImplType* Payload = Manager_FX->AllocatePayload<PayloadImplType>(FX.Type);

			PayloadLibrary::SetChecked(Context, Payload, FX, Transform);

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

			// Scaled

				// Int
			for (const FCsFX_Parameter_Scaled_Int& Param : FX.ScaledParameters.Ints)
			{
				typedef NCsFX::NParameter::NScaled::NInt::FIntType ParameterIntType;

				ParameterIntType* IntType = Manager_FX->AllocateValue<ParameterIntType>();

				Param.CopyToParamsAsValue(IntType);
				Payload->ScaledParameters.Add(IntType);
			}
				// Float
			for (const FCsFX_Parameter_Scaled_Float& Param : FX.ScaledParameters.Floats)
			{
				typedef NCsFX::NParameter::NScaled::NFloat::FFloatType ParameterFloatType;

				ParameterFloatType* FloatType = Manager_FX->AllocateValue<ParameterFloatType>();

				Param.CopyToParamsAsValue(FloatType);
				Payload->ScaledParameters.Add(FloatType);
			}
				// Vector
			for (const FCsFX_Parameter_Scaled_Vector& Param : FX.ScaledParameters.Vectors)
			{
				typedef NCsFX::NParameter::NScaled::NVector::FVectorType ParameterVectorType;

				ParameterVectorType* VectorType = Manager_FX->AllocateValue<ParameterVectorType>();

				Param.CopyToParamsAsValue(VectorType);
				Payload->ScaledParameters.Add(VectorType);
			}

			// Data Interface

				// Skeletal Mesh
			for (const FCsFX_Parameters_DataInterface_SkeletalMesh& Param : FX.DataInterfaceParameters.SkeletalMeshes)
			{
				typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType SkeletalMeshParameterType;

				SkeletalMeshParameterType* SkeletalMeshType = Manager_FX->AllocateValue<SkeletalMeshParameterType>();

				Param.CopyToParamsAsValue(SkeletalMeshType);
				Payload->SkeletalMeshParameters.Add(SkeletalMeshType);
			}
			return Payload;
		}

		void FLibrary::QueueDeallocateAllChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->QueueDeallocateAll();
		}

		#pragma endregion Allocate / Deallocate

		// Spawn
		#pragma region

		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			return GetChecked(Context, WorldContext)->Spawn(FX.Type, AllocatePayloadImplChecked(Context, WorldContext, PooledPayload, FX, Transform));
		}

		const FCsFXActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

			return SpawnChecked(Context, WorldContext, PooledPayload, FX, Transform);
		}
		
		const FCsFXActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, FX, Transform, nullptr);
		}

		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector& Location)
		{
			return GetChecked(Context, WorldContext)->Spawn(FX.Type, AllocatePayloadImplChecked(Context, WorldContext, PooledPayload, FX, Location));
		}

		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsFX& Type, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			return GetChecked(Context, WorldContext)->Spawn(FX.Type, AllocatePayloadImplChecked(Context, WorldContext, FX, Transform));
		}

		const FCsFXActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			CS_IS_VALID_RET_NULL(FX)

			return SpawnChecked(Context, WorldContext, FX, Transform);
		}

		const FCsFXActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsFX::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, FX, Transform, nullptr);
		}

		#pragma endregion Spawn
	}
}

namespace NCsFX
{
	namespace NManager
	{
		namespace NParameter
		{
			using LogClassType = NCsFX::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			using ParameterType = NCsFX::NParameter::IParameter;
			using ScaledParameterType = NCsFX::NParameter::NScaled::IScaled;
			using FloatParameterType = NCsFX::NParameter::NFloat::FFloatType;
			using VectorParameterType = NCsFX::NParameter::NVector::FVectorType;
			using SkeletalMeshParameterType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType;

			FloatParameterType* FLibrary::AllocateFloatChecked(const FString& Context, const UObject* WorldContext)
			{
				return GetManagerChecked(Context, WorldContext)->AllocateValue<FloatParameterType>();
			}

			VectorParameterType* FLibrary::AllocateVectorChecked(const FString& Context, const UObject* WorldContext)
			{
				return GetManagerChecked(Context, WorldContext)->AllocateValue<VectorParameterType>();
			}

			SkeletalMeshParameterType* FLibrary::AllocateSkeletalMeshChecked(const FString& Context, const UObject* WorldContext)
			{
				return GetManagerChecked(Context, WorldContext)->AllocateValue<SkeletalMeshParameterType>();
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, ParameterType* Value)
			{
				CS_IS_PTR_NULL_CHECKED(Value);
			
				GetManagerChecked(Context, WorldContext)->DeallocateValue(Value);
			}
		
			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<ParameterType*>& Values)
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Values, ParameterType)

				UCsManager_FX* Manager_FX = GetManagerChecked(Context, WorldContext);

				const int32 Count = Values.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					Manager_FX->DeallocateValue(Values[I]);
					Values.RemoveAt(I, 1, false);
				}
			}

			bool FLibrary::SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<ParameterType*>& Values, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_TARRAY_ANY_NULL(Values, ParameterType)

				if (UCsManager_FX* Manager_FX = GetSafeManager(Context, WorldContext, Log))
				{
					const int32 Count = Values.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						Manager_FX->DeallocateValue(Values[I]);
						Values.RemoveAt(I, 1, false);
					}
					return true;
				}
				return false;
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, ScaledParameterType* Value)
			{
				CS_IS_PTR_NULL_CHECKED(Value);
			
				GetManagerChecked(Context, WorldContext)->DeallocateValue(Value);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<ScaledParameterType*>& Values)
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Values, ScaledParameterType)

				UCsManager_FX* Manager_FX = GetManagerChecked(Context, WorldContext);

				const int32 Count = Values.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					Manager_FX->DeallocateValue(Values[I]);
					Values.RemoveAt(I, 1, false);
				}
			}

			bool FLibrary::SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<ScaledParameterType*>& Values, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_TARRAY_ANY_NULL(Values, ScaledParameterType)

				if (UCsManager_FX* Manager_FX = GetSafeManager(Context, WorldContext, Log))
				{
					const int32 Count = Values.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						Manager_FX->DeallocateValue(Values[I]);
						Values.RemoveAt(I, 1, false);
					}
					return true;
				}
				return false;
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, SkeletalMeshParameterType* Value)
			{
				CS_IS_PTR_NULL_CHECKED(Value);
			
				GetManagerChecked(Context, WorldContext)->DeallocateValue(Value);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<SkeletalMeshParameterType*>& Values)
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Values, SkeletalMeshParameterType)

				UCsManager_FX* Manager_FX = GetManagerChecked(Context, WorldContext);

				const int32 Count = Values.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					Manager_FX->DeallocateValue(Values[I]);
					Values.RemoveAt(I, 1, false);
				}
			}

			bool FLibrary::SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<SkeletalMeshParameterType*>& Values, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_TARRAY_ANY_NULL(Values, SkeletalMeshParameterType)

				if (UCsManager_FX* Manager_FX = GetSafeManager(Context, WorldContext, Log))
				{
					const int32 Count = Values.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						Manager_FX->DeallocateValue(Values[I]);
						Values.RemoveAt(I, 1, false);
					}
					return true;
				}
				return false;
			}
		}
	}
}