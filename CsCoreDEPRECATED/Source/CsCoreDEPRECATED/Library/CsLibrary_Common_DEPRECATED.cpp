// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Common_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"

#if WITH_EDITOR

// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"

// Slate
#include "Runtime/Slate/Public/Framework/Notifications/NotificationManager.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h"
#include "../Source/Editor/EditorStyle/Public/EditorStyleSet.h"

#include "Runtime/Core/Public/Internationalization/Internationalization.h"

#endif // #if WITH_EDITOR

UCsLibrary_Common_DEPRECATED::UCsLibrary_Common_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Javascript
#pragma region

#if WITH_EDITOR

void UCsLibrary_Common_DEPRECATED::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	auto Isolate = NewObject<UJavascriptIsolate>();
	// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
	Isolate->Init(false);
	auto Context = Isolate->CreateContext();

	JavascriptIsolate = Isolate;
	JavascriptContext = Context;

	Context->Expose("Root", InOwner);
	Context->Expose("GWorld", InWorld);
	Context->Expose("GEngine", GEngine);

	if (EditorJavascriptFile != TEXT(""))
		Context->RunFile(*EditorJavascriptFile);
}

void UCsLibrary_Common_DEPRECATED::SetupJavascript(UObject* InOwner, UWorld* InWorld, UObject* &JavascriptIsolate, UObject* &JavascriptContext)
{
	SetupJavascript(InOwner, InWorld, JavascriptIsolate, JavascriptContext, TEXT(""));
}

void UCsLibrary_Common_DEPRECATED::Javascript_ExposeObject(UObject* &JavascriptContext, const FString &Name, UObject* InObject)
{
	Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, InObject);
}

void UCsLibrary_Common_DEPRECATED::Javascript_RunFile(UObject* &JavascriptContext, const FString &EditorJavascriptFile)
{
	Cast<UJavascriptContext>(JavascriptContext)->RunFile(*EditorJavascriptFile);
}

#endif // #if WITH_EDITOR

#pragma endregion Javascript

// Editor Message
#pragma region

#if WITH_EDITOR

void UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration)
{
	FText Text = FInternationalization::Get().ForUseOnlyByLocMacroAndGraphNodeTextLiterals_CreateText(*InTextLiteral, *InNamespace, *InKey);
	//FText Text = FTextCache::Get().FindOrCache(*InTextLiteral, *InNamespace, *InKey);

	FNotificationInfo Info(Text);

	Info.Image = FEditorStyle::GetBrush(TEXT("LevelEditor.RecompileGameCode"));
	Info.FadeInDuration = 0.1f;
	Info.FadeOutDuration = 0.5f;
	Info.ExpireDuration = Duration;
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = true;
	Info.bUseLargeFont = true;
	Info.bFireAndForget = false;
	Info.bAllowThrottleWhenFrameRateIsLow = false;

	auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);

	NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
	NotificationItem->ExpireAndFadeout();
}

#endif // #if WITH_EDITOR

#pragma endregion Editor Message