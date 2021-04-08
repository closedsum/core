// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/Script/CsScriptLibrary_Time.h"
#include "CsCore.h"


UCsScriptLibrary_Time::UCsScriptLibrary_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsTime UCsScriptLibrary_Time::FCsTime_Create()
{
	return FCsTime();
}

FCsTime UCsScriptLibrary_Time::FCsTime_Copy(const FCsTime& Time)
{
	return Time;
}