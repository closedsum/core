// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsJsLibrary_Common.h"
#include "CsJs.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"

namespace NCsJs
{
	namespace NCommon
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, SetupIsolateAndContext);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, ExposeObject);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, ClearObject);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, RunFileChecked);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, RunFile);

					const FString RunError_empty = TEXT("(empty)");
					const FString RunError_undefined = TEXT("undefined");
				}
			}
		}

		void FLibrary::SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::SetupIsolateAndContext;

			CS_IS_PENDING_KILL_CHECKED(Owner)

			auto Isolate = NewObject<UJavascriptIsolate>();
			// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
			
			TMap<FString, FString> Features;
			Features = UJavascriptIsolate::DefaultIsolateFeatures();

			// Add default context feature exposures
			Features.Add(TEXT("Root"), TEXT("default"));
			Features.Add(TEXT("World"), TEXT("default"));
			Features.Add(TEXT("Engine"), TEXT("default"));
			Features.Add(TEXT("Context"), TEXT("default"));

			Isolate->Init(IsEditor, Features);
			auto ContextObject = Isolate->CreateContext();

			JavascriptIsolate = Isolate;
			JavascriptContext = ContextObject;

			ContextObject->Expose("Root", Owner);
		}

		void FLibrary::ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::ExposeObject;

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(Name)
			CS_IS_PENDING_KILL_CHECKED(Object)

			Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, Object);
		}

		void FLibrary::ClearObject(UObject*& JavascriptContext, const FString& Name)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::ClearObject;

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(Name)

			Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, nullptr);
		}

		void FLibrary::RunFileChecked(const FString& Context, UObject*& JavascriptContext, const FString& FileName)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(FileName)

			FString Output =  Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);

			checkf(Output != Str::RunError_empty, TEXT("%s: Failed to Run File: %s. Error: %s."), *Context, *FileName, *Str::RunError_empty);
			//checkf(Output != Str::RunError_undefined, TEXT("%s: Failed to Run File: %s. Error: %s."), *FileName, *Str::RunError_undefined);
		}

		void FLibrary::RunFile(UObject*& JavascriptContext, const FString& FileName)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::RunFile;

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(FileName)

			FString Output = Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);
			
			bool HasError = false;
			FString Error = TEXT("");

			if (Output == Str::RunError_empty)
			{
				HasError = true;
				Error	 = Str::RunError_empty;
			}
			/*
			else
			if (Output == Str::RunError_undefined)
			{
				HasError = true;
				Error	 = Str::RunError_undefined;
			}
			*/

			if (HasError)
			{
				UE_LOG(LogCsJs, Warning, TEXT("NCsJs::NCommon::FLibrary::RunFile: Failed to Run File: %s. Error: %s."), *FileName, *Error);
			}
		}
	}
}