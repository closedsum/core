// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/UnrealString.h"
#include "UObject/NameTypes.h"

namespace NCsResource
{
	namespace NManager
	{
		struct CSCONTAINER_API IManager
		{
		public:

			virtual ~IManager();

		protected :

			// With C++11, these methods would be "= default"
			IManager();
		  
			IManager(const IManager&) {}
			IManager& operator = (const IManager& ) { return *this ; }
			IManager(IManager && ) noexcept {}
			IManager& operator = (IManager && ) noexcept { return *this ; }

		public:

			virtual const FString& GetName() const = 0;

			virtual void SetName(const FString& InName) = 0;

			virtual const FName& GetFName() const = 0;

			virtual void SetFName(const FName& InName) = 0;

			virtual void Clear()= 0;

			virtual void Shutdown() = 0;

			// Pool
		#pragma region
		public:

			virtual void CreatePool(const int32& InSize) = 0;

			virtual const int32& GetPoolSize() const = 0;

			virtual bool IsExhausted() const = 0;

		#pragma endregion Pool

			// Deallocate
		#pragma region

			virtual bool DeallocateHead() = 0;

			virtual void DeallocateAll() = 0;

		#pragma endregion Deallocate
		};
	}
}