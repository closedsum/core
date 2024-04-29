// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsMacro_Proxy.h"
#include "Types/CsTypes_Interpolation.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

namespace NCsEasing
{
	struct CSCORELIBRARY_API FFloat
	{
	private:

		CS_DECLARE_MEMBER_WITH_PROXY(Type, ECsEasingType)
		CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
		CS_DECLARE_MEMBER_WITH_PROXY(Max, float)

	public:

		FFloat() :
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, ECsEasingType::Linear),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Min, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Max, 0.0f)
		{
			CS_CTOR_SET_MEMBER_PROXY(Type);
			CS_CTOR_SET_MEMBER_PROXY(Min);
			CS_CTOR_SET_MEMBER_PROXY(Max);
		}

		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, ECsEasingType)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)

		bool IsValidChecked(const FString& Context) const;
		bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning) const;

		float Ease(const float& Alpha) const;
	};
}