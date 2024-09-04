// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameInstance.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
// Engine
#include "Engine/Engine.h"

namespace NCsGameInstance
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				// Get
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafe);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafeAsObject);
				// Is
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, IsSafe);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsGameInstance::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsGameInstance::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

	FString FLibrary::PrintObjectAndClass(const UGameInstance* Object)
	{
		if (!IsValid(Object))
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintNameAndClass(const UGameInstance* Object)
	{
		if (!IsValid(Object))
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("%s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	// Get
	#pragma region

	UGameInstance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
	{
		CS_IS_PENDING_KILL_CHECKED(ContextObject)

		UWorld* World = ContextObject->GetWorld();

		if (IsValid(World))
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(IsValid(GameInstance), TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));
			return GameInstance;
		}
		
		UGameInstance* GameInstance = const_cast<UGameInstance*>(Cast<UGameInstance>(ContextObject));

		checkf(IsValid(GameInstance), TEXT("%s: ContextObject: %s does NOT contain a reference to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName()));
		return GameInstance;
	}

	UGameInstance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		CS_IS_PENDING_KILL_RET_NULL(ContextObject)

		UWorld* World = ContextObject->GetWorld();

		if (IsValid(World))
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			if (!IsValid(GameInstance))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName())));
				return nullptr;
			}
			return GameInstance;
		}

		UGameInstance* GameInstance = const_cast<UGameInstance*>(Cast<UGameInstance>(ContextObject));

		if (!IsValid(GameInstance))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextObject: %s does NOT contain to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName())));
			return nullptr;
		}
		return GameInstance;
	}

	UGameInstance* FLibrary::GetSafe(const UObject* ContextObject)
	{
		SET_CONTEXT(GetSafe);

		return GetSafe(Context, ContextObject, nullptr);
	}

	UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext);
	}

	UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, LogLevel)
	{
		return GetSafe(Context, WorldContext, Log);
	}

	UObject* FLibrary::GetSafeAsObject(const UObject* WorldContext)
	{
		SET_CONTEXT(GetSafeAsObject);

		return GetSafeAsObject(Context, WorldContext, nullptr);
	}

	#pragma endregion Get

	// Is
	#pragma region
	
	bool FLibrary::IsChecked(const FString& Context, const UObject* ContextObject)
	{
		return CS_CONST_CAST_CHECKED(ContextObject, UObject, UGameInstance) != nullptr;
	}

	bool FLibrary::IsSafe(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		return CS_CONST_CAST(ContextObject, UObject, UGameInstance) != nullptr;
	}

	bool FLibrary::IsSafe(const UObject* ContextObject)
	{
		SET_CONTEXT(IsSafe);

		return IsSafe(Context, ContextObject, nullptr);
	}

	#pragma endregion Is

	// Engine
	#pragma region
	
	UEngine* FLibrary::GetEngineChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked(Context, ContextObject)->GetEngine();
	}

	UEngine* FLibrary::GetSafeEngine(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		if (UGameInstance* GameInstance = GetSafe(Context, ContextObject, Log))
		{
			UEngine* Engine = GameInstance->GetEngine();

			if (!IsValid(Engine))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GameInstance does NOT have reference to Engine."), *Context));
				return nullptr;
			}
			return Engine;
		}
		return nullptr;
	}

	#pragma endregion Engine

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel
}