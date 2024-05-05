// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Collision/CsTypes_Collision.h"
// Log
#include "Utility/CsPhysicsLog.h"

class UObject;
class UCsManager_Trace;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)
// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

class AActor;
class UCapsuleComponent;
class USkeletalMeshComponent;

namespace NCsTrace
{
	namespace NManager
	{
		struct CSPHYSICS_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsPhysics::FLog::Warning

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Trace from the WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Trace
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
			* Safely get the Context (Root) for UCsManager_Trace from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Trace.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Trace from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Trace.
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
			* Get the reference to UCsManager_Trace from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Trace.
			*/
			static UCsManager_Trace* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Trace from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_Trace.
			*/
			static UCsManager_Trace* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Safely get the reference to UCsManager_Trace from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Trace.
			*/
			static UCsManager_Trace* GetSafe(UObject* WorldContext);

		#pragma endregion Get

		// Request
		#pragma region
		public:

		#define RequestType NCsTrace::NRequest::FRequest

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static RequestType* AllocateRequestChecked(const FString& Context, const UObject* WorldContext);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static RequestType* SafeAllocateRequest(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static RequestType* SafeAllocateRequest(const UObject* WorldContext);

			/**
			* Safely deallocate Request.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* @param Log			(optional)
			* return				Whether the Request was successful deallocated.
			*/
			static bool SafeDeallocateRequest(const FString& Context, const UObject* WorldContext, RequestType* Request, LogLevel);

		#undef RequestType

		#pragma endregion Request

		// Response
		#pragma region

		#define ResponseType NCsTrace::NResponse::FResponse
		#define RequestType NCsTrace::NRequest::FRequest

		public:

			/**
			* Perform a trace with the given Request.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* return				Response
			*/
			static ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request);

			/**
			* Safely perform a trace with the given Request.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* @param Log			(optional)
			* return				Response
			*/
			static ResponseType* SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, LogLevel);

			/**
			* Safely perform a trace with the given Request.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* return				Response
			*/
			static ResponseType* SafeTrace(const UObject* WorldContext, RequestType* Request);

			// Sphere
		#pragma region
		public:

			/**
			* Safely sweeps a sphere at the given Bone location for Component and returns the first blocking hit encountered.
			* This trace finds the objects that RESPONDS to the given Collision Channel
			* 
			* @param Context			The calling context
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Component
			* @param BoneOrSocket		Bone or Socket on SkeletalMesh for Component (Component->GetSkeletalMeshAsset())
			* @param Radius				Radius of the sphere to sweep
			* @param Channel
			* @param bTraceComplex		True to test against complex collision, false to test against simplified collision.
			* @param bIgnoreSelf
			* @param OutHit				Properties of the trace hit.
			* @return					True if there was a hit, false otherwise.
			*/
			static bool SafeSphereTrace(const FString& Context, UObject* WorldContext, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, LogLevel);

		#pragma endregion Sphere

			// Sweep
		#pragma region
		public:

			/**
			* Safely perform a sweep using the collision information from the CapsuleComponent.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Component
			* @param Params
			* @param Log			(optional)
			* @param 
			*/
			static ResponseType* SafeSweep(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, LogLevel);

			/**
			* Safely perform a sweep using the collision information from the CapsuleComponent.
			* NOTE: OutResponse may include other objects (not Object) that have been hit or overlapped from the sweep.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Component
			* @param Params
			* @param Object
			* @param Log			(optional)
			* @param
			*/
			static ResponseType* SafeSweepAgainstObject(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, UObject* Object, LogLevel);

			/**
			* Safely perform a sweep using the collision information from the CapsuleComponent.
			* NOTE: OutResponse ONLY includes a hit or overlaps from the sweep with Object.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Component
			* @param Params
			* @param Object
			* @param Log			(optional)
			* @param
			*/
			static ResponseType* SafeSweepAgainstObjectOnly(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, UObject* Object, LogLevel);

		#pragma endregion Sweep

			// Screen
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ScreenPosition	Screen position.
			* @param Distance		How far the the trace should go outward.
			* @param Channel	
			* return				Trace response for the given trace. NULL if result was found.
			*/
			static ResponseType* TraceScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const float& Distance, const ECollisionChannel& Channel);

		#pragma endregion Screen

		#undef ResponseType
		#undef RequestType

		#pragma endregion Response

		#undef LogLevel
		};
	}
}