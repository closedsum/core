// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsCheatManager.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Common.h"
// Game
#include "Game/CsGameState_DEPRECATED.h"
// Javascript
#include "Javascript/CsJavascriptEntryPoint.h"

UCsCheatManager::UCsCheatManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EditorGameBatchConsoleCommandsFilePath = TEXT("C:/Trees/cs1/Config/EditorGameBatchConsoleCommands.txt");
}

void UCsCheatManager::OnTick(float DeltaSeconds)
{
#if WITH_EDITOR
	OnTick_Handle_EditorGameBatchConsoleCommands();
#endif // #if WITH_EDITOR
}

void UCsCheatManager::RunEditorGameBatchConsoleCommands()
{
	FString FileAsString;

	if (FFileHelper::LoadFileToString(FileAsString, *EditorGameBatchConsoleCommandsFilePath))
	{
		const TCHAR* Stream = *FileAsString;
		FString Line;

		EditorGameBatchConsoleCommands.Reset();

		while (FParse::Line(&Stream, Line))
		{
			EditorGameBatchConsoleCommands.Add(Line);
		}
		Queue_EditorGameBatchConsoleCommands = true;
	}
}

void UCsCheatManager::OnTick_Handle_EditorGameBatchConsoleCommands()
{
	if (!Queue_EditorGameBatchConsoleCommands)
		return;

	if (EditorGameBatchConsoleCommands.Num() == 0)
	{
		Queue_EditorGameBatchConsoleCommands = false;
		return;
	}

	if (APlayerController* PlayerController = UCsLibrary_Common::GetLocalPlayerController<APlayerController>(GetWorld()))
	{
		FString Command = EditorGameBatchConsoleCommands[0];
		PlayerController->ConsoleCommand(Command);
		EditorGameBatchConsoleCommands.RemoveAt(0);
	}

	if (EditorGameBatchConsoleCommands.Num() == 0)
		Queue_EditorGameBatchConsoleCommands = false;
}

// Stream
#pragma region

bool UCsCheatManager::Stream_GetString(const TCHAR*& Str, const FString &StringName, FString &OutString, const FString &Cheat, const FString &Format)
{
	OutString = UCsLibrary_Common::Stream_GetString(Str, false);

	if (OutString == TEXT(""))
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: No %s set."), *Cheat, *StringName);
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: The correct format is %s %s"), *Cheat, *Cheat, *Format);
		return false;
	}
	return true;
}

bool UCsCheatManager::Stream_GetName(const TCHAR*& Str, const FString &StringName, FName &OutName, const FString &Cheat, const FString &Format)
{
	OutName = UCsLibrary_Common::Stream_GetName(Str);

	if (OutName == NAME_None)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: No %s set."), *Cheat, *StringName);
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: The correct format is %s %s"), *Cheat, *Cheat, *Format);
		return false;
	}
	return true;
}

#pragma endregion Stream

// Console Variables
#pragma region

void UCsCheatManager::SetCVar(const FString &CVarName, const int32 &Value)
{
	auto CVar = IConsoleManager::Get().FindConsoleVariable(*CVarName);
	CVar->Set(Value, ECVF_SetByConsole);
}

void UCsCheatManager::LogInputActions(const int32 &Value)
{
	SetCVar(TEXT("log.input.actions"), Value);
}

void UCsCheatManager::LogControllerRotationInput(const int32 &Value)
{
	SetCVar(TEXT("log.controller.rotationinput"), Value);
}

void UCsCheatManager::LogControllerAddYawInput(const int32 &Value)
{
	SetCVar(TEXT("log.controller.addyawinput"), Value);
}

#pragma endregion Console Variables

// Javascript
#pragma region

void UCsCheatManager::RunEditorGameJavascriptFile()
{
#if WITH_EDITOR
	ACsGameState_DEPRECATED* GameState = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();

	if (!GameState)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsCheatManager::RunEditorGameJavascriptFile: GameState is NOT Valid"));
		return;
	}
	GameState->JavascriptEntryPoint->Run();
#endif // #if WITH_EDTIOR
}

#pragma endregion Javascript

// UI
#pragma region

void UCsCheatManager::OpenMenu(const FString &Menu)
{
	OpenMenu_Internal(Menu);
}

void UCsCheatManager::OpenMenu_Internal(const FString &Menu)
{
}

void UCsCheatManager::CloseMenu(const FString &Menu)
{
	CloseMenu_Internal(Menu);
}

void UCsCheatManager::CloseMenu_Internal(const FString &Menu)
{
}

void UCsCheatManager::CloseAllMenus()
{
	CloseAllMenus_Internal();
}

void UCsCheatManager::CloseAllMenus_Internal()
{
}

#pragma endregion UI