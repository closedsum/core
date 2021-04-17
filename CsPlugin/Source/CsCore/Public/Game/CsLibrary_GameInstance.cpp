// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsLibrary_GameInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsGameInstance
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafe);
			}
		}
	}

	UGameInstance* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
	{
		checkf(ContextObject, TEXT("%s: ContextObject is NULL."), *Context);

		UWorld* World = ContextObject->GetWorld();

		if (World)
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(World, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}
		
		UGameInstance* GameInstance = Cast<UGameInstance>(ContextObject);

		checkf(GameInstance, TEXT("%s: ContextObject: %s does NOT contain to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName()));
		return nullptr;
	}

	UGameInstance* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (!ContextObject)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextObject is NULL."), *Context));
			return nullptr;
		}

		UWorld* World = ContextObject->GetWorld();

		if (World)
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			if (!GameInstance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName())));
				return nullptr;
			}
		}

		UGameInstance* GameInstance = Cast<UGameInstance>(ContextObject);

		if (!GameInstance)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextObject: %s does NOT contain to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName())));
		}
		return GameInstance;
	}

	UGameInstance* FLibrary::GetSafe(UObject* ContextObject)
	{
		using namespace NCsGameInstance::NLibrary::NCached;

		const FString& Context = Str::GetSafe;

		return GetSafe(Context, ContextObject, nullptr);
	}
}