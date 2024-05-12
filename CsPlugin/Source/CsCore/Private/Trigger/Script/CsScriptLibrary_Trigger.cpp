// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Trigger/Script/CsScriptLibrary_Trigger.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Trigger/CsLibrary_Trigger.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Trigger)

// Cached
#pragma region

namespace NCsScriptLibraryTrigger
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Trigger, GetByLabel);
		}
	}
}

#pragma endregion Cached

#define USING_NS_CACHED using namespace NCsScriptLibraryTrigger::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryTrigger::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error
#define TriggerLibrary NCsTrigger::FLibrary

UCsScriptLibrary_Trigger::UCsScriptLibrary_Trigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

bool UCsScriptLibrary_Trigger::GetAll(const FString& Context, const UObject* WorldContextObject, TArray<ATriggerBase*>& OutTriggers)
{
	CONDITIONAL_SET_CTXT(GetAll);

	return TriggerLibrary::GetSafe(Ctxt, WorldContextObject, OutTriggers);
}

ATriggerBase* UCsScriptLibrary_Trigger::GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return TriggerLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ATriggerBase* UCsScriptLibrary_Trigger::GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(GetByTags);

	return TriggerLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

bool UCsScriptLibrary_Trigger::GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return TriggerLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutTriggers);
}

ATriggerBase* UCsScriptLibrary_Trigger::GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return TriggerLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ATriggerBase* UCsScriptLibrary_Trigger::GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return TriggerLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef TriggerLibrary