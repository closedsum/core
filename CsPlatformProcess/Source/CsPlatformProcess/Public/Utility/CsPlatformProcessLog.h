// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsPlatform
{
	namespace NProcess
	{
		struct CSPLATFORMPROCESS_API FLog final
		{
		public:

			static void Warning(const FString& Str);

			static void Error(const FString& Str);
		};
	}
}