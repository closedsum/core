// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

struct CSCORE_API FCsLog final
{
public:

	static void Warning(const FString& Str);
};

#if !UE_BUILD_SHIPPING
#define CS_LOG_WARNING(Str) FCsLog::Warning(Str)
#else
#define CS_LOG_WARNING(Str)
#endif // #if !UE_BUILD_SHIPPING