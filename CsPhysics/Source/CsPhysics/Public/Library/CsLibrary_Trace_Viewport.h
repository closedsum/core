// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsPhysicsLog.h"

class UObject;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)
// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			namespace NPhysics
			{
				class CSPHYSICS_API FLibrary final
				{
				public:

				// Trace
				#pragma region
				public:

				#define ResponseType NCsTrace::NResponse::FResponse
				#define RequestType NCsTrace::NRequest::FRequest

					/**
					* Perform a trace with the given Request.
					*  Request->Start is replaced by:
					*   de-projection of ScreenPosition
					*  Request->End is replaced by:
					*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
					*
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param ScreenPosition	2D screen space to deproject.
					* @param Request
					* @param Distance		(optional) The distance to project outward from the Request->Start.
					* return				Response
					*/
					static ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f);

					/**
					* Safely perform a trace with the given Request.
					*  Request->Start is replaced by:
					*   de-projection of ScreenPosition
					*  Request->End is replaced by:
					*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
					*
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param ScreenPosition	2D screen space to deproject.
					* @param Request
					* @param Distance		(optional) The distance to project outward from the Request->Start.
					* @param Log			(optional)
					* return				Response
					*/
					static ResponseType* SafeTrace(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f, void(*Log)(const FString&) = &NCsPhysics::FLog::Warning);

					/**
					* Safely perform a trace with the given Request.
					*  Request->Start is replaced by:
					*   de-projection of ScreenPosition
					*  Request->End is replaced by:
					*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
					*
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param ScreenPosition	2D screen space to deproject.
					* @param Request
					* @param Distance		(optional) The distance to project outward from the Request->Start.
					* return				Response
					*/
					static ResponseType* SafeTrace(const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f);

				#undef ResponseType
				#undef RequestType

				#pragma endregion Trace
				};
			}
		}
	}
}