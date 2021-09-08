// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafe);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameInstance::FLibrary, GetSafeAsObject);
			}
		}
	}

	// Get
	#pragma region

	UGameInstance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
	{
		CS_IS_PTR_NULL_CHECKED(ContextObject)

		UWorld* World = ContextObject->GetWorld();

		if (World)
		{
			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(World, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}
		
		UGameInstance* GameInstance = const_cast<UGameInstance*>(Cast<UGameInstance>(ContextObject));

		checkf(GameInstance, TEXT("%s: ContextObject: %s does NOT contain to a World or is a reference to GameInstance."), *Context, *(ContextObject->GetName()));
		return nullptr;
	}

	UGameInstance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(ContextObject)

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
		using namespace NCsGameInstance::NLibrary::NCached;

		const FString& Context = Str::GetSafe;

		return GetSafe(Context, ContextObject, nullptr);
	}

	UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext);
	}

	UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return GetSafe(Context, WorldContext, Log);
	}

	UObject* FLibrary::GetSafeAsObject(const UObject* WorldContext)
	{
		using namespace NCsGameInstance::NLibrary::NCached;

		const FString& Context = Str::GetSafeAsObject;

		return GetSafeAsObject(Context, WorldContext, nullptr);
	}

	#pragma endregion Get

	// Editor
	#pragma region
	
	bool FLibrary::IsPIEChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject)->IsPIE();
	}

	bool FLibrary::IsMobilePIEChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject)->IsMobilePIE();
	}

	bool FLibrary::IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject)->IsStandaloneFromEditor();
	}
	
	bool FLibrary::IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject)->IsStandaloneMobileFromEditor();
	}

	bool FLibrary::IsMobilePreviewEditorChecked(const FString& Context, const UObject* ContextObject)
	{
		return GetChecked<UCsGameInstance>(Context, ContextObject)->IsMobilePreviewEditor();
	}

	bool FLibrary::SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (UCsGameInstance* GameInstance = GetSafe<UCsGameInstance>(Context, ContextObject, Log))
		{
			return GameInstance->IsMobilePreviewEditor();
		}
		return false;
	}

	#pragma endregion Editor
}