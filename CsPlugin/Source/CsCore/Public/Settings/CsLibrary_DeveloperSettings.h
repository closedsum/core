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

			static UObject* LoadDataRootSetChecked(const FString& Context);
			static UObject* SafeLoadDataRootSet(const FString& Context);

			static const TArray<FString>& GetIgnoreAssetPaths();

		#pragma endregion Data
		};
	}
}