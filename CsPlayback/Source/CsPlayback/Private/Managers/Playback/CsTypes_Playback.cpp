// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Playback/CsTypes_Playback.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Playback)

// NCsPlayback::EState
#pragma region

namespace NCsPlayback
{
	namespace NState
	{
		namespace Ref
		{
			typedef EMState EnumMapType;

			CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(None);
			CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(Playback);
			CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(Record);
			CSPLAYBACK_API CS_ADD_TO_ENUM_MAP_CUSTOM(EState_MAX, "MAX");
		}
	}
}

#pragma endregion NCsPlayback::EState

// PlaybackEventRepeatedState
#pragma region

namespace NCsPlaybackEventRepeatedState
{
	namespace Ref
	{
		typedef EMCsPlaybackEventRepeatedState EnumMapType;

		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(None);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(Start);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(End);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlaybackEventRepeatedState_MAX, "MAX");
	}
}

#pragma endregion PlaybackEventRepeatedState

const FCsPlaybackByEvent FCsPlaybackByEvent::Invalid;

// FCsPlaybackByEvents
#pragma region

bool FCsPlaybackByEvents::IsValidChecked(const FString& Context) const
{
	// Check Level is Valid
	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Level)
	return true;
}

bool FCsPlaybackByEvents::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/) const
{
	// Check Level is Valid
	CS_IS_SOFT_OBJECT_PATH_VALID(Level)
	return true;
}

#pragma endregion FCsPlaybackByEvents