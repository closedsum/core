// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Input/CsLibrary_Trace_Input.h"

// Library
#include "Library/CsLibrary_Trace_Viewport.h"
#include "Managers/Input/CsLibrary_Input.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsInput
{
	namespace NMouse
	{
		namespace NPhysics
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::NPhysics::FLibrary, SafeTrace);
					}
				}
			}

			#define MouseLibrary NCsInput::NMouse::FLibrary
			#define ViewportLibrary NCsViewport::NLocal::NPlayer::NPhysics::FLibrary

			// Trace
			#pragma region

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest

			ResponseType* FLibrary::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/)
			{
				FIntPoint Position;
				MouseLibrary::GetPositionChecked(Context, WorldContext, Position);

				return ViewportLibrary::TraceChecked(Context, WorldContext, FVector2f(Position.X, Position.Y), Request, Distance);
			}

			ResponseType* FLibrary::SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				FIntPoint Position;
				if (!MouseLibrary::GetSafePosition(Context, WorldContext, Position, Log))
					return nullptr;
				return ViewportLibrary::SafeTrace(Context, WorldContext, FVector2f(Position.X, Position.Y), Request, Distance, Log);
			}

			ResponseType* FLibrary::SafeTrace(const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/)
			{
				using namespace NCsInput::NMouse::NPhysics::NLibrary::NCached;

				const FString& Context = Str::SafeTrace;

				return SafeTrace(Context, WorldContext, Request, Distance, nullptr);
			}

			#undef ResponseType
			#undef RequestType

			#pragma endregion Trace

			#undef MouseLibrary
			#undef ViewportLibrary
		}
	}
}