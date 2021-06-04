// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsTypes_Javascript.h"

// Library
#include "Library/CsJsLibrary_Common.h"

// FCsJavascriptFileObjects
#pragma region

void FCsJavascriptFileObjects::Shutdown()
{
	if (Isolate &&
		!Isolate->IsPendingKill())
	{
		Isolate->MarkPendingKill();
		Isolate = nullptr;
	}

	if (Context &&
	    !Context->IsPendingKill())
	{
		typedef NCsJs::NCommon::FLibrary JavascriptLibrary;

		for (const FString& Name : ExposedObjectNames)
		{
			JavascriptLibrary::ClearObject(Context, Name);
		}

		Context->MarkPendingKill();
		Context = nullptr;
	}
	ExposedObjectNames.Reset();
}

#pragma endregion FCsJavascriptFileObjects