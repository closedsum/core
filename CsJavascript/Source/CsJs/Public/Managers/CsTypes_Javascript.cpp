// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsTypes_Javascript.h"

// Types
#include "Types/CsTypes_Macro.h"

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
		Context->MarkPendingKill();
		Context = nullptr;
	}
}

#pragma endregion FCsJavascriptFileObjects