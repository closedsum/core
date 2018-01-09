// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/CheatManager.h"
#include "CsCheatManager.generated.h"

UCLASS(Within = PlayerController)
class CSCORE_API UCsCheatManager : public UCheatManager
{
	GENERATED_UCLASS_BODY()

	void OnTick(float DeltaSeconds);

	UFUNCTION(exec)
	void RunEditorGameBatchConsoleCommands();

	FString EditorGameBatchConsoleCommandsFilePath;

	TArray<FString> EditorGameBatchConsoleCommands;

	bool Queue_EditorGameBatchConsoleCommands;

	void OnTick_Handle_EditorGameBatchConsoleCommands();

// Stream
#pragma region

	bool Stream_GetString(const TCHAR*& Str, const FString &StringName, FString &OutString, const FString &Cheat, const FString &Format);
	bool Stream_GetName(const TCHAR*& Str, const FString &StringName, FName &OutName, const FString &Cheat, const FString &Format);

#pragma endregion Stream

// Console Variables
#pragma region

	void SetCVar(const FString &CVarName, const int32 &Value);

	UFUNCTION(exec)
	void LogInputActions(const int32& Value);
	UFUNCTION(exec)
	void LogControllerRotationInput(const int32& Value);
	UFUNCTION(exec)
	void LogControllerAddYawInput(const int32& Value);

#pragma endregion Console Variables

// Javascript
#pragma region

	UFUNCTION(exec)
	void RunEditorGameJavascriptFile();

#pragma endregion Javascript

// UI
#pragma region

	UFUNCTION(exec)
	void OpenMenu(const FString &Menu);

	virtual void OpenMenu_Internal(const FString &Menu);

	UFUNCTION(exec)
	void CloseMenu(const FString &Menu);

	virtual void CloseMenu_Internal(const FString &Menu);

	UFUNCTION(exec)
	void CloseAllMenus();

	virtual void CloseAllMenus_Internal();

#pragma endregion UI
};