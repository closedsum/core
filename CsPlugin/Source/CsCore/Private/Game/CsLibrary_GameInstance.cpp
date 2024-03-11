// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/CsGameInstance.h"
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
				// Get
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafe);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafeAsObject);
				// Is
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, IsSafe);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsGameInstance::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsGameInstance::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

	FString FLibrary::PrintObjectAndClass(const UGameInstance* Object)
	{
		if (!Object)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintNameAndClass(const UGameInstance* Object)
	{
		if (!Object)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("%s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	// Get
	#pragma region

	UGameInstance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
	{
		CS_IS_PENDING_KILL_CHECKED(ContextObject)

		UWorld* World = ContextObject->GetWorld();

		if (World)
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(World, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));
			return GameInstance;
		}
		
		UGameInstance* GameInstance = const_cast<UGameInstance*>(Cast<UGameInstance>(ContextObject));

		checkf(GameInstance, TEXT("%s: ContextObject: %s does NOT contain a reference to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName()));
		return GameInstance;
	}

	UGameInstance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		CS_IS_PENDING_KILL_RET_NULL(ContextObject)

		UWorld* World = ContextObject->GetWorld();

		if (World)
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			if (!GameInstance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName())));
				return nullptr;
			}
			return GameInstance;
		}

		UGameInstance* GameInstance = const_cast<UGameInstance*>(Cast<UGameInstance>(ContextObject));

		if (!GameInstance)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextObject: %s does NOT contain to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName())));
		}
		return GameInstance;
	}

	UGameInstance* FLibrary::GetSafe(const UObject* ContextObject)
	{
		SET_CONTEXT(GetSafe);

		return GetSafe(Context, ContextObject, nullptr);
	}

	UCsGameInstance* FLibrary::GetCsChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject);
	}

	UCsGameInstance* FLibrary::GetCsSafe(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		return GetSafe<UCsGameInstance>(Context, ContextObject, Log);
	}

	UCsGameInstance* FLibrary::GetCsSafe(const UObject* ContextObject)
	{
		return GetSafe<UCsGameInstance>(ContextObject);
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
	#pragma endregion
	
	UEngine* FLibrary::GetEngineChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked(Context, ContextObject)->GetEngine();
	}

	UEngine* FLibrary::GetSafeEngine(const FString& Context, const UObject* ContextObject, LogLevel)
	{
		if (UGameInstance* GameInstance = GetSafe(Context, ContextObject, Log))
		{
			UEngine* Engine = GameInstance->GetEngine();

			if (!Engine)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GameInstance does NOT have reference to Engine."), *Context));
				return nullptr;
			}
			return Engine;
		}
		return nullptr;
	}

	#pragma endregion Engine

	// Start
	#pragma region

	bool FLibrary::HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->HasStartedFromEntry();
	}

	bool FLibrary::SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (UCsGameInstance* GameInstance = GetCsSafe(Context, ContextObject, Log))
			return GameInstance->HasStartedFromEntry();
		return false;
	}

	#pragma endregion Start

	// Editor
	#pragma region
	
	bool FLibrary::IsPIEChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->IsPIE();
	}

	bool FLibrary::IsMobilePIEChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->IsMobilePIE();
	}

	bool FLibrary::IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->IsStandaloneFromEditor();
	}
	
	bool FLibrary::IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->IsStandaloneMobileFromEditor();
	}

	bool FLibrary::IsMobilePreviewEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->IsMobilePreviewEditor();
	}

	bool FLibrary::SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (UCsGameInstance* GameInstance = GetCsSafe(Context, ContextObject, Log))
		{
			return GameInstance->IsMobilePreviewEditor();
		}
		return false;
	}

	#pragma endregion Editor

	// Transition
	#pragma region
	
	bool FLibrary::HasFinishedTransitionChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->HasFinishedTransition();
	}

	#pragma endregion Transition

	// Events
	#pragma region

	#define OnQueueExitGameEventType NCsGameInstance::FOnQueueExitGame
	OnQueueExitGameEventType& FLibrary::GetOnQueueExitGame_EventChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->GetOnQueueExitGame_Event();
	}
	#undef OnQueueExitGameEventType

		// Transition
	#pragma region

	#define OnStartTransitionOutEventType NCsGameInstance::NTransition::FOut_OnStart
	#define OnFinishTransitionEventType NCsGameInstance::NTransition::FOnFinish

	OnStartTransitionOutEventType& FLibrary::GetTransitionOut_OnStart_EventChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->GetTransitionOut_OnStart_Event();
	}

	OnFinishTransitionEventType& FLibrary::GetTransition_OnFinish_EventChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetCsChecked(Context, ContextObject)->GetTransition_OnFinish_Event();
	}

	#undef OnStartTransitionOutEventType
	#undef OnFinishTransitionEventType

	#pragma endregion Transition

	#pragma endregion Events

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel
}