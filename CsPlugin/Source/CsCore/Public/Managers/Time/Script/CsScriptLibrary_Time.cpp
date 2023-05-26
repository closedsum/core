// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

FCsDeltaTime UCsScriptLibrary_Time::FCsDeltaTime_Copy(const FCsDeltaTime& DeltaTime)
{
	return DeltaTime;
}

FCsDeltaTime UCsScriptLibrary_Time::Add_DeltaTime(const FCsDeltaTime& A, const FCsDeltaTime& B)
{
	return A + B;
}

FCsDeltaTime UCsScriptLibrary_Time::Subtract_DeltaTime(const FCsDeltaTime& A, const FCsDeltaTime& B)
{
	return A - B;
}