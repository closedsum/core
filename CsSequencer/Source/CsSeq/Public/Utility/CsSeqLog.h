// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsSequencer
{
	struct CSSEQ_API FLog final
	{
	public:

		static void Warning(const FString& Str);

		static void Error(const FString& Str);
	};
}