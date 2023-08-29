// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;

namespace NCsCore
{
	namespace NSettings
	{
		/**
		*/
		class CSCORE_API FLibrary
		{
		// Data
		#pragma region
		public:
			
			static const TSoftClassPtr<UObject>& GetDataRootSetChecked(const FString& Context);
			static const TSoftClassPtr<UObject>& GetDataRootSet();

		#pragma endregion Data
		};
	}
}