// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsJsLibrary_Common.h"
#include "CsJs.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Instance/CsGetJavascriptInstance.h"
#include "Isolate/CsGetJavascriptIsolate.h"
// Javascript
#include "JavascriptInstance.h"
#include "JavascriptIsolate.h"
#include "JavascriptContext.h"
//#include "V8/Private/JavascriptIsolate_Private.h"

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NCommon::FLibrary, AsyncCreateInstance);
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

		#define USING_NS_CACHED using namespace NCsJs::NCommon::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsJs::NCommon::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		void FLibrary::AsyncCreateInstance(UObject* Object)
		{
			SET_CONTEXT(AsyncCreateInstance);
	
			ICsGetJavascriptInstance* GetJavascriptInstance  = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetJavascriptInstance);
			CsJavascriptInstanceInfo& JavascriptInstanceInfo = GetJavascriptInstance->GetJavascriptInstanceInfo();

			JavascriptInstanceInfo.CreateInfo.Start();

			FJSInstanceOptions Options;
			FJavascriptFeatures& Features	   = Options.Features;
			TMap<FString, FString>& FeatureMap = Features.FeatureMap;
			FeatureMap						   = UJavascriptIsolate::DefaultIsolateFeatures();

			// Add default context feature exposures
			FeatureMap.Add(TEXT("Root"), TEXT("default"));
			FeatureMap.Add(TEXT("World"), TEXT("default"));
			FeatureMap.Add(TEXT("Engine"), TEXT("default"));
			FeatureMap.Add(TEXT("Context"), TEXT("default"));

			FJSInstanceContextSettings ContextSettings;

			TSharedPtr<FJavascriptInstance> NewInstance = MakeShareable(new FJavascriptInstance(Options, ContextSettings));

			JavascriptInstanceInfo.CreateInfo.Complete();

			JavascriptInstanceInfo.CreateInfo.bSuccess = NewInstance.IsValid();

			GetJavascriptInstance->GetJavascriptInstance() = NewInstance;

			/*
			{
				ICsGetJavascriptInstance* GetJavascriptInstance  = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetJavascriptInstance);
				CsJavascriptInstanceInfo& JavascriptInstanceInfo = GetJavascriptInstance->GetJavascriptInstanceInfo();

				JavascriptInstanceInfo.CreateInfo.Start();

			}

			// Create Instance on another Thread
			Async(EAsyncExecution::ThreadPool, [Context, NewInstance, Object]()
			{
				
				FJavascriptFeatures Features;
				Features.FeatureMap	= UJavascriptIsolate::DefaultIsolateFeatures();

				// Add default context feature exposures
				Features.FeatureMap.Add(TEXT("Root"), TEXT("default"));
				Features.FeatureMap.Add(TEXT("World"), TEXT("default"));
				Features.FeatureMap.Add(TEXT("Engine"), TEXT("default"));
				Features.FeatureMap.Add(TEXT("Context"), TEXT("default"));

				NewInstance->SetAvailableFeatures(Features);

				// Update on GameThread
				Async(EAsyncExecution::TaskGraphMainThread, [Context, NewInstance, Object]()
				{
					ICsGetJavascriptInstance* GetJavascriptInstance  = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetJavascriptInstance);
					CsJavascriptInstanceInfo& JavascriptInstanceInfo = GetJavascriptInstance->GetJavascriptInstanceInfo();

					JavascriptInstanceInfo.CreateInfo.Complete();

					JavascriptInstanceInfo.CreateInfo.bSuccess = NewInstance.IsValid();

					GetJavascriptInstance->GetJavascriptInstance() = NewInstance;
				});
			});
			*/
		}

		void FLibrary::SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor)
		{
			SET_CONTEXT(SetupIsolateAndContext);

			CS_IS_PENDING_KILL_CHECKED(Owner)

			auto Isolate = NewObject<UJavascriptIsolate>();
			
			// TODO: bIsEditor. Probably need to set to true if we want to interact with AnimInstance in Editor.

			ICsGetJavascriptIsolate* GetJavascriptIsolate = CS_INTERFACE_CAST_CHECKED(Owner, UObject, ICsGetJavascriptIsolate);

			Isolate->Init(GetJavascriptIsolate->GetSharedJavascriptIsolate());
			auto ContextObject = Isolate->CreateContext();

			JavascriptIsolate = Isolate;
			JavascriptContext = ContextObject;

			ContextObject->Expose("Root", Owner);
		}

		void FLibrary::ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object)
		{
			SET_CONTEXT(ExposeObject);

			CS_IS_PENDING_KILL_CHECKED(JavascriptContext)
			CS_IS_STRING_EMPTY_CHECKED(Name)
			CS_IS_PENDING_KILL_CHECKED(Object)

			Cast<UJavascriptContext>(JavascriptContext)->Expose(Name, Object);
		}

		void FLibrary::ClearObject(UObject*& JavascriptContext, const FString& Name)
		{
			SET_CONTEXT(ClearObject);

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
			SET_CONTEXT(RunFile);

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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}