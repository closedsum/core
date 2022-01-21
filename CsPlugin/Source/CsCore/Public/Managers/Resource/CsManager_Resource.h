// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsResource
{
	namespace NManager
	{
		struct CSCORE_API IManager
		{
		public:

			virtual ~IManager(){}

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