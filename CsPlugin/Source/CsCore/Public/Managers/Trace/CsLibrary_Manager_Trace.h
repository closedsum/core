// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Engine/EngineTypes.h"
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsManager_Trace;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)
// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsTrace
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Trace from the WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
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
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Trace.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
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
			static UCsManager_Trace* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Trace from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Trace.
			*/
			static UCsManager_Trace* GetSafe(UObject* WorldContext);

		#pragma endregion Get

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
			* @param Log
			* return				Response
			*/
			static ResponseType* SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely perform a trace with the given Request.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* return				Response
			*/
			static ResponseType* SafeTrace(const UObject* WorldContext, RequestType* Request);

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
			static ResponseType* TraceScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const float& Distance, const ECollisionChannel& Channel);

		#undef ResponseType
		#undef RequestType
		};
	}
}