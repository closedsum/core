// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Trace_Viewport.h"

// Types
#include "Managers/Trace/CsTraceRequest.h"
// Library
#include "Library/CsLibrary_Viewport.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			namespace NPhysics
			{
				namespace NLibrary
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, SafeTrace);
						}
					}
				}

			#define TraceManagerLibrary NCsTrace::NManager::FLibrary
			#define ViewportLibrary NCsViewport::NLocal::NPlayer::FLibrary

			// Trace
			#pragma region

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest

			ResponseType* FLibrary::TraceChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.X, 0.0f)
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.Y, 0.0f)

				FVector3f WorldPosition;
				FVector3f WorldDirection;

				bool Success = ViewportLibrary::DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);

				check(Success);
			
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Distance, 0.0f)

				Request->Start = WorldPosition;
				Request->End   = WorldPosition + Distance * WorldDirection;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

			ResponseType* FLibrary::SafeTrace(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_RET_NULL(ScreenPosition.X, 0.0f)
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_RET_NULL(ScreenPosition.Y, 0.0f)

				FVector3f WorldPosition;
				FVector3f WorldDirection;

				if (!ViewportLibrary::SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection, Log))
					return nullptr;

				CS_IS_FLOAT_GREATER_THAN_RET_NULL(Distance, 0.0f)

				Request->Start = WorldPosition;
				Request->End   = WorldPosition + Distance * WorldDirection;

				return TraceManagerLibrary::SafeTrace(Context, WorldContext, Request, Log);
			}

			ResponseType* FLibrary::SafeTrace(const UObject* WorldContext, const FVector2f& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/)
			{
				using namespace NCsViewport::NLocal::NPlayer::NPhysics::NLibrary::NCached;

				const FString& Context = Str::SafeTrace;

				return SafeTrace(Context, WorldContext, ScreenPosition, Request, Distance, nullptr);
			}

			#undef ResponseType
			#undef RequestType

			#pragma endregion Trace

			#undef TraceManagerLibrary
			#undef ViewportLibrary
			}
		}
	}
}