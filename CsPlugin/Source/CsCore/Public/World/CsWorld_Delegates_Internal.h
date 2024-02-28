// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Engine
#include "Engine/World.h"

namespace NCsWorld
{
	namespace NDelegates
	{
		struct CSCORE_API FInternal
		{
		private:

			FDelegateHandle OnPostWorldInitializationHandle;

			FInternal() :
				OnPostWorldInitializationHandle()
			{
			}

			FInternal(const FInternal&) = delete;
			FInternal(FInternal&&) = delete;
		public:
			~FInternal() {}

			FORCEINLINE static FInternal& Get()
			{
				static FInternal Instance;
				return Instance;
			}

		public:

			void Init();

			static void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
		};
	}
}