// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsSeqLog.h"
#include "CsSeq.h"

namespace NCsSequencer
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsSeq, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsSeq, Error, TEXT("%s"), *Str);
	}
}