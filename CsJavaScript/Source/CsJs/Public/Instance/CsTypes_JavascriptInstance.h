// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsJs
{
	namespace NInstance
	{
		namespace NCreate
		{
			enum class EState : uint8 
			{
				None,
				InProgress,
				Complete
			};

			struct CSJS_API FInfo
			{
			public:

				EState State;

				bool bSuccess;

				FInfo() :
					State(EState::None),
					bSuccess(false)
				{
				}

				FORCEINLINE void Start() { State = EState::InProgress; }
				FORCEINLINE void Complete() { State = EState::Complete; }
				FORCEINLINE bool IsComplete() const { return State == EState::Complete; }
				FORCEINLINE bool IsSuccessful() const { return bSuccess; }
			};
		}

		struct CSJS_API FInfo
		{
		public:

			NCreate::FInfo CreateInfo;

			FInfo() :
				CreateInfo()
			{
			}
		};
	}
}

using CsJavascriptInstanceInfo = NCsJs::NInstance::FInfo;