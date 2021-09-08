// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsJsLibrary_Common.h"
#include "CsJs.h"

#if WITH_EDITOR
// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"
#endif // #if WITH_EDITOR

namespace NCsJs
{
	namespace NCommon
	{
	#if WITH_EDITOR

		void FLibrary::SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor)
		{
			checkf(Owner, TEXT("FCsJs::NCommon::FLibrary::SetupIsloateAndContext: Owner is NULL."));

			auto Isolate = NewObject<UJavascriptIsolate>();
			// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
			Isolate->Init(IsEditor);
			auto Context = Isolate->CreateContext();

			JavascriptIsolate = Isolate;
			JavascriptContext = Context;

			Context->Expose("Root", Owner);
		}

		void FLibrary::ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object)
		{
			checkf(JavascriptContext, TEXT("FCsJs::NCommon::FLibrary::ExposeObject: JavascriptContext is NULL."));

			checkf(!Name.IsEmpty(), TEXT("FCsJs::NCommon::FLibrary::ExposeObject: Name is Empty."));

			checkf(Object, TEXT("FCsJs::NCommon::FLibrary::ExposeObject: Object is NULL."));

			Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, Object);
		}

		void FLibrary::ClearObject(UObject*& JavascriptContext, const FString& Name)
		{
			checkf(JavascriptContext, TEXT("FCsJs::NCommon::FLibrary::ClearObject: JavascriptContext is NULL."));

			checkf(!Name.IsEmpty(), TEXT("FCsJs::NCommon::FLibrary::ClearObject: Name is Empty."));

			Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, nullptr);
		}

		void FLibrary::RunFile(UObject*& JavascriptContext, const FString& FileName)
		{
			checkf(JavascriptContext, TEXT("FCsJs::NCommon::FLibrary::RunFile: JavascriptContext is NULL."));

			checkf(!FileName.IsEmpty(), TEXT("FCsJs::NCommon::FLibrary::ExposeObject: FileName is Empty."));

			Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);
		}

	#endif // #if WITH_EDITOR
	}
}