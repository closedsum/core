// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
		#else
			static void SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor){}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			*/
			static void ExposeObject(UObject*& Context, const FString& Name, UObject* Object);
		#else
			static void ExposeObject(UObject*& Context, const FString& Name, UObject* Object){}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			*/
			static void ClearObject(UObject*& Context, const FString& Name);
		#else
			static void ClearObject(UObject*& Context, const FString& Name){}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			*/
			static void RunFile(UObject*& Context, const FString& FileName);
		#else
			static void RunFile(UObject*& Context, const FString& FileName){}
		#endif // #if WITH_EDITOR
		};
	}
}