// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsFXLog.h"

class UObject;
class UCsManager_FX;
struct FCsFXActorPooled;

// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParameter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)
// NCsFX::NParameter::NFloat::FFloatType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NFloat, FFloatType)
// NCsFX::NParameter::NVector::FVectorType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NVector, FVectorType)
// NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NDataInterface, NSkeletalMesh, FSkeletalMeshType)

namespace NCsFX
{
	namespace NManager
	{
		/**
		*/
		struct CSFX_API FLibrary final
		{
		// Print
		#pragma region
		public:

			static FString PrintObjectWithClass(const UCsManager_FX* Manager);

		#pragma endregion Print

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_FX from a WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsFX::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsFX::FLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_FX.
			*/
			static UCsManager_FX* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the reference to UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_FX.
			*/
			template<typename T>
			FORCEINLINE static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_FX* O = GetChecked(Context, ContextObject);
				T* Other		 = Cast<T>(O);

				checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_FX.
			*/
			static UCsManager_FX* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_FX from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_FX.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsFX::FLog::Warning)
			{
				UCsManager_FX* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_FX from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_FX.
			*/
			static UCsManager_FX* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// State
		#pragma region
		public:

			/**
			* Get whether UCsManager_FX is beginning shutdown or not (UCsManager_FX->IsBeginningShutdown()).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Whether Manager_FX is beginning shutdown or not.
			*/
			static bool IsBeginningShutdownChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion State

		// Pool
		#pragma region
		public:

			/**
			* 
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				
			*/
			static bool IsNoneAllocatedChecked(const FString& Context, const UObject* WorldContext);

			// Find
		#pragma region
		public:

			static const FCsFXActorPooled* FindSafeObject(const FString& Context, const UObject* WorldContext, const FECsFX& Type, const int32& Index, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

		#pragma endregion Find

		#pragma endregion Pool

		// Allocate / Deallocate
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define PayloadType NCsFX::NPayload::IPayload
		
			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector3f& Location);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

		#undef PayloadType

		#define PayloadImplType NCsFX::NPayload::FImpl

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector3f& Location);

			/**
			* Allocate a Payload given the FX information
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional)
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

		#undef PayloadImplType

		#undef PooledPayloadType

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static void QueueDeallocateAllChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion Allocate / Deallocate

		// Spawn
		#pragma region
		public:

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

			/**
			* Spawn an FX with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* @param Log			(optional)
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param PooledPayload
			* @param FX
			* @param Location		Location to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX, const FVector3f& Location);

		#undef PooledPayloadType

		#define PayloadType NCsFX::NPayload::IPayload

			/**
			* Spawn an FX with the given Type and Payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param PooledPayload
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsFX& Type, PayloadType* Payload);

		#undef PayloadType

			/**
			* Spawn an FX with the given payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* @param Log			(optional)
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const FString& Context, const UObject* WorldContext, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			/**
			* Safely spawn an FX with the given payload.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FX
			* @param Transform		(optional) Transform to apply the fx after allocation and before playing.
			*						FX.Transform is applied as an "offset".
			* return				Spawned FX
			*/
			static const FCsFXActorPooled* SafeSpawn(const UObject* WorldContext, const FCsFX& FX, const FTransform3f& Transform = FTransform3f::Identity);

		#pragma endregion Spawn
		};

		namespace NParameter
		{
			struct CSFX_API FLibrary final
			{
			public:

				FORCEINLINE static UCsManager_FX* GetManagerChecked(const FString& Context, const UObject* WorldContext)
				{
					typedef NCsFX::NManager::FLibrary FXManagerLibrary;

					return FXManagerLibrary::GetChecked(Context, WorldContext);
				}

				FORCEINLINE static UCsManager_FX* GetSafeManager(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsFX::FLog::Warning)
				{
					typedef NCsFX::NManager::FLibrary FXManagerLibrary;

					return FXManagerLibrary::GetSafe(Context, WorldContext, Log);
				}

			#define FloatParameterType NCsFX::NParameter::NFloat::FFloatType

				/**
				* Allocate a Float parameter
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Float parameter
				*/
				static FloatParameterType* AllocateFloatChecked(const FString& Context, const UObject* WorldContext);

			#undef FloatParameterType

			#define VectorParameterType NCsFX::NParameter::NVector::FVectorType

				/**
				* Allocate a Vector parameter
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Vector parameter
				*/
				static VectorParameterType* AllocateVectorChecked(const FString& Context, const UObject* WorldContext);

			#undef VectorParameterType

			#define SkeletalMeshParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

				/**
				* Allocate a Data Interface parameter of type: Skeletal Mesh
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Data Interface parameter of type: Skeletal Mesh
				*/
				static SkeletalMeshParameterType* AllocateSkeletalMeshChecked(const FString& Context, const UObject* WorldContext);

			#undef SkeletalMeshParameterType

			#define ParameterType NCsFX::NParameter::IParameter

				/**
				* Deallocate parameter Value, ParameterType (NCsFX::NParameter::IParameter).
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Value
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, ParameterType* Value);

				/**
				* Deallocate parameter Values, ParameterType (NCsFX::NParameter::IParameter).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Values
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<ParameterType*>& Values);

				/**
				* Safely Deallocate parameter Values, ParameterType (NCsFX::NParameter::IParameter).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Values
				* @param Log			(optional)
				*/
				static bool SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<ParameterType*>& Values, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			#undef ParameterType

			#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled

				/**
				* Deallocate parameter Value, ScaledParameterType (NCsFX::NParameter::NScaled::IScaled).
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Value
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, ScaledParameterType* Value);

				/**
				* Deallocate parameter Values, ScaledParameterType (NCsFX::NParameter::NScaled::IScaled).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Values
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<ScaledParameterType*>& Values);

				/**
				* Safely deallocate parameter Values, ScaledParameterType (NCsFX::NParameter::NScaled::IScaled).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Values
				* @param Log			(optional)
				*/
				static bool SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<ScaledParameterType*>& Values, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			#undef ScaledParameterType

			#define SkeletalMeshParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

				/**
				* Deallocate parameter Value, SkeletalmeshParameterType (NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType).
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Value
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, SkeletalMeshParameterType* Value);

				/**
				* Deallocate parameter Values, SkeletalmeshParameterType (NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Value
				*/
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, TArray<SkeletalMeshParameterType*>& Values);

				/**
				* Deallocate parameter Values, SkeletalmeshParameterType (NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType).
				*  Preserves memory space and "resets" the array.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Value
				* @param Log			(optional)
				*/
				static bool SafeDeallocate(const FString& Context, const UObject* WorldContext, TArray<SkeletalMeshParameterType*>& Values, void(*Log)(const FString&) = &NCsFX::FLog::Warning);

			#undef SkeletalMeshParameterType
			};
		}
	}
}