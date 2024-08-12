// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Array.h"
#include "CsCoreLibrary.h"

// Library
#include "Library/CsLibrary_Array.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Array)

UCsScriptLibrary_Array::UCsScriptLibrary_Array(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
	
bool UCsScriptLibrary_Array::MakeShuffle_int32_0toN(const int32& N, TArray<int32>& OutArray)
{
	if (N <= 0)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("UCsScriptLibrary_Array::MakeShuffle_int32_0toN: N: %d is NOT > 0."), N);
		return false;
	}

	const int32 Max = N + 1;

	OutArray.Reset(FMath::Max(OutArray.Max(), Max));

	for (int32 I = 0; I < Max; ++I)
	{
		OutArray.Add(I);
	}

	CsArrayLibrary::Shuffle<int32>(OutArray);
	return true;
}