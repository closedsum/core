// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsTypes_Javascript.h"

// Library
#include "Library/CsJsLibrary_Common.h"

// FCsJavascriptFileObjects
#pragma region

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
		typedef NCsJs::NCommon::FLibrary JavascriptLibrary;

		for (const FString& Name : ExposedObjectNames)
		{
			JavascriptLibrary::ClearObject(Context, Name);
		}

		Context->MarkAsGarbage();
		Context = nullptr;
	}
	ExposedObjectNames.Reset();
}

#pragma endregion FCsJavascriptFileObjects