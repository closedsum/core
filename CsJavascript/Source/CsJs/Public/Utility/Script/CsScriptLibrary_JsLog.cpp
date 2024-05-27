// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/Script/CsScriptLibrary_JsLog.h"
#include "CsJs.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_JsLog)

UCsScriptLibrary_JsLog::UCsScriptLibrary_JsLog(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_JsLog::Log_Warning(const FString& Message)
{
	UE_LOG(LogCsJs, Warning, TEXT("%s"), *Message);
}