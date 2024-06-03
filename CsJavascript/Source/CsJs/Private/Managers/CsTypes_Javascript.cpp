// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsTypes_Javascript.h"

// Library
#include "Library/CsJsLibrary_Common.h"
// Settings
#include "Managers/CsSettings_Manager_Javascript.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Javascript)

// FCsJavascriptFileObjects
#pragma region

#define JavascriptCommonLibrary NCsJs::NCommon::FLibrary

void FCsJavascriptFileObjects::Init(UObject* Owner)
{
	JavascriptCommonLibrary::SetupIsolateAndContext(Owner, Isolate, Context, false);

	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	Path = Settings.EmptyPath;

	JavascriptCommonLibrary::RunFile(Context, Path);
}

void FCsJavascriptFileObjects::Deactivate(UObject* Owner)
{
	const bool ContextExists = Context && IsValid(Context);
	const bool IsolateExists = Isolate && IsValid(Isolate);

	if (ContextExists)
	{
		for (const FString& Name : ExposedObjectNames)
		{
			JavascriptCommonLibrary::ClearObject(Context, Name);
		}
	}

	if (!(ContextExists && IsolateExists))
	{
		if (IsolateExists)
		{
			Isolate->MarkAsGarbage();
			Isolate = nullptr;
		}

		if (ContextExists)
		{
			Context->MarkAsGarbage();
			Context = nullptr;
		}

		JavascriptCommonLibrary::SetupIsolateAndContext(Owner, Isolate, Context, false);
	}

	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	Path = Settings.EmptyPath;

	JavascriptCommonLibrary::RunFile(Context, Path);
}

void FCsJavascriptFileObjects::Shutdown()
{
	if (Isolate &&
		IsValid(Isolate))
	{
		Isolate->MarkAsGarbage();
		Isolate = nullptr;
	}

	if (Context &&
	    IsValid(Context))
	{
		for (const FString& Name : ExposedObjectNames)
		{
			JavascriptCommonLibrary::ClearObject(Context, Name);
		}

		Context->MarkAsGarbage();
		Context = nullptr;
	}
	ExposedObjectNames.Reset(ExposedObjectNames.Max());
}

#undef JavascriptCommonLibrary

#pragma endregion FCsJavascriptFileObjects