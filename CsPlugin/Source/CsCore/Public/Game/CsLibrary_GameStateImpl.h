// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class AGameStateBase;
class UObject;

namespace NCsGameState
{
	namespace NImpl
	{
		struct CSCORE_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &FCsLog::Warning

		public:

			static FString PrintGameStateAndClass(AGameStateBase* GameState);

		#undef LogLevel
		};
	}
}

using CsGameStateImplLibrary = NCsGameState::NImpl::FLibrary;