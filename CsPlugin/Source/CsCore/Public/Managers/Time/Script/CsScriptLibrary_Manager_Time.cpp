// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/Script/CsScriptLibrary_Manager_Time.h"
#include "CsCore.h"

// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"

namespace NCsScriptLibraryManagerTime
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetTimeSinceStart);
		}
	}
}

UCsScriptLibrary_Manager_Time::UCsScriptLibrary_Manager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


FCsDeltaTime UCsScriptLibrary_Manager_Time::GetTimeSinceStart(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	using namespace NCsScriptLibraryManagerTime::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTimeSinceStart : Context;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	return TimeManagerLibrary::GetSafeTimeSinceStart(Ctxt, WorldContextObject, Group);
}