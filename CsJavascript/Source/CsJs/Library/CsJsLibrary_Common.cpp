// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsJsLibrary_Common.h"
#include "CsJs.h"

// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"

void FCsJsLibrary_Common::SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor)
{
	checkf(Owner, TEXT("FCsJsLibrary_Common::SetupIsloateAndContext: Owner is NULL."));

	auto Isolate = NewObject<UJavascriptIsolate>();
	// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
	Isolate->Init(IsEditor);
	auto Context = Isolate->CreateContext();

	JavascriptIsolate = Isolate;
	JavascriptContext = Context;

	Context->Expose("Root", Owner);
}

void FCsJsLibrary_Common::ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object)
{
	checkf(JavascriptContext, TEXT("FCsJsLibrary_Common::ExposeObject: JavascriptContext is NULL."));

	checkf(!Name.IsEmpty(), TEXT("FCsJsLibrary_Common::ExposeObject: Name is Empty."));

	checkf(Object, TEXT("FCsJsLibrary_Common::ExposeObject: Object is NULL."));

	Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, Object);
}

void FCsJsLibrary_Common::RunFile(UObject*& JavascriptContext, const FString& FileName)
{
	checkf(JavascriptContext, TEXT("FCsJsLibrary_Common::RunFile: JavascriptContext is NULL."));

	checkf(!FileName.IsEmpty(), TEXT("FCsJsLibrary_Common::ExposeObject: FileName is Empty."));

	Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);
}
