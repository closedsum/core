// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "CsLibrary_Common_DEPRECATED.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsLibrary_Common_DEPRECATED : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Javascript
#pragma region

#if WITH_EDITOR

	static void SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext, const FString &EditorJavascriptFile);
	static void SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext);

	static void Javascript_ExposeObject(UObject* &JavascriptContext, const FString &Name, UObject* InObject);
	static void Javascript_RunFile(UObject* &JavascriptContext, const FString &EditorJavascriptFile);

#endif // #if WITH_EDITOR

#pragma endregion Javascript

// Editor Message
#pragma region

#if WITH_EDITOR

	static void DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration);

#endif // #if WITH_EDITOR
	
#pragma endregion Editor Message
};