// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

class CSJS_API FCsJsLibrary_Common
{
public:

	/**
	*/
	static void SetupIsolateAndContext(UObject* Owner, UObject*& JavascriptIsolate, UObject*& JavascriptContext, const bool& IsEditor);

	/**
	*/
	static void ExposeObject(UObject*& Context, const FString& Name, UObject* Object);

	/**
	*/
	static void RunFile(UObject*& Context, const FString& FileName);
};