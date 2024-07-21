// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsGameplayTagsLog.h"
#include "CsGameplayTags.h"

namespace NCsGameplayTags
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsGameplayTags, Error, TEXT("%s"), *Str);
	}
}