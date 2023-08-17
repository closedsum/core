// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;

namespace NCsJs
{
	namespace NCommon
	{
		struct CSJS_API FLibrary
		{
		public:

		#if WITH_EDITOR
			/**
			*/
			static void SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor);

			/**
			*/
			static void ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object);

			/**
			*/
			static void ClearObject(UObject*& JavascriptContext, const FString& Name);

			/**
			*/
			static void RunFileChecked(const FString& Context, UObject*& JavascriptContext, const FString& FileName);

			/**
			*/
			static void RunFile(UObject*& JavascriptContext, const FString& FileName);
		#else
			static void SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor){}
			static void ExposeObject(UObject*& JavascriptContext, const FString& Name, UObject* Object) {}
			static void ClearObject(UObject*& JavascriptContext, const FString& Name) {}
			static void RunFileChecked(const FString& Context, UObject*& JavascriptContext, const FString& FileName) {}
			static void RunFile(UObject*& JavascriptContext, const FString& FileName) {}
		#endif // #if WITH_EDITOR
		};
	}
}