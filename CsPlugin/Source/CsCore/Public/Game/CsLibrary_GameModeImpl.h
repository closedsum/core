// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Game/Event/CsGameMode_Event.h"

class AGameModeBase;
class UObject;

namespace NCsGameMode
{
	namespace NImpl
	{
		class CSCORE_API FLibrary final
		{
		public:

			static FString PrintGameModeAndClass(AGameModeBase* GameMode);

		// ICsGameMode_Event
		#pragma region
		public:

		#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

			static OnPostSeamlessTravelCompleteEventType& GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext);

		#undef OnPostSeamlessTravelCompleteEventType

		#pragma endregion ICsGameMode_Event
		};
	}
}

using CsGameModeImplLibrary = NCsGameMode::NImpl::FLibrary;