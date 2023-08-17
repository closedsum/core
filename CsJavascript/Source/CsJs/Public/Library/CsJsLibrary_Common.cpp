// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsJsLibrary_Common.h"
#include "CsJs.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Javascript
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"
#endif // #if WITH_EDITOR

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
				}
			}
		}

	#if WITH_EDITOR

		void FLibrary::SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::SetupIsolateAndContext;

			CS_IS_PENDING_KILL_CHECKED(Owner)

			auto Isolate = NewObject<UJavascriptIsolate>();
			// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.
			Isolate->Init(IsEditor);
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

			// TODO: Check return value of RunFile
			Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);
		}

		void FLibrary::RunFile(UObject*& JavascriptContext, const FString& FileName)
		{
			using namespace NCsJs::NCommon::NLibrary::NCached;

			const FString& Context = Str::RunFile;

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(FileName)

			Cast<UJavascriptContext>(JavascriptContext)->RunFile(*FileName);
		}

	#endif // #if WITH_EDITOR
	}
}