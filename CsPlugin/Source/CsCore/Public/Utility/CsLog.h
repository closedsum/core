// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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