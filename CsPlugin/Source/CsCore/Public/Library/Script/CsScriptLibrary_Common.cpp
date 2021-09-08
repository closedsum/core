// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Common.h"
#include "CsCore.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Engine/Engine.h"

UCsScriptLibrary_Common::UCsScriptLibrary_Common(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UGameInstance* UCsScriptLibrary_Common::GetGameInstanceFromContext(const FString& Context, const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: WorldContextObject is NULL."), *Context);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			return GameInstance;
		}
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get GameInstance from World: %s (WorldContextObject: %s)."), *Context, *(World->GetName()), *(WorldContextObject->GetName()));
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get Valid World from WorldContextObject: %s."), *Context, *(WorldContextObject->GetName()));
	}
	return nullptr;
}
