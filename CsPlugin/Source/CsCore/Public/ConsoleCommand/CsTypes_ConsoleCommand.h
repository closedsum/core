// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once

namespace NCsConsoleCommand
{
	struct CSCORE_API FInfo
	{
	public:

		TArray<FString> Commands;
		TArray<FString> Definitions;
		FString Description;

		FInfo() :
			Commands(),
			Definitions(),
			Description()
		{
		}
	};
}

namespace NCsConsoleCommand
{
	namespace NManager
	{
		struct CSCORE_API FHandle
		{
		public:

			//static const FHandle Invalid;

		public:

			FGuid Handle;

			FHandle() :
				Handle()
			{
			}

			FORCEINLINE bool operator==(const FHandle& B) const
			{
				return Handle == B.Handle;
			}

			FORCEINLINE bool operator!=(const FHandle& B) const
			{
				return !(*this == B);
			}

			friend uint32 GetTypeHash(const FHandle& InHandle)
			{
				return GetTypeHash(InHandle.Handle);
			}

			FORCEINLINE bool IsValid() const { return Handle.IsValid(); }

			FORCEINLINE void New() { Handle = FGuid::NewGuid(); }

			FORCEINLINE void Reset() { Handle.Invalidate(); }
		};
	}
}