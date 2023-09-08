// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Time.h"
#include "CsCore.h"

#include "Engine/World.h"

namespace NCsTime
{
	uint64 FLibrary::GetWorldTimeMilliseconds(const UWorld* InWorld)
	{
		return (uint64)FMath::FloorToInt(InWorld->TimeSeconds * 1000.0f);
	}

	float FLibrary::GetCurrentDateTimeSeconds()
	{
		FDateTime DateTime = FDateTime::Now();
	
		float Seconds = (float)DateTime.GetMinute() * 60.0f;
		Seconds		 += (float)DateTime.GetSecond();
		Seconds		 += (float)DateTime.GetMillisecond() / 1000.0f;
	
		return Seconds;
	}

	uint64 FLibrary::GetCurrentFrame(const UWorld* InWorld)
	{
	#if WITH_EDITOR
		//if (IsPlayInEditorPreview(InWorld))
		//	return 0;
	#endif // #if WITH_EDITOR
		return 0ull;// InWorld->GetGameInstance<UCsGameInstance_DEPRECATED>()->CurrentGameFrame;
	}
}