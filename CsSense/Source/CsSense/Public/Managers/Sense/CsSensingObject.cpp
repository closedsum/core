// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
<<<<<<<< HEAD:CsAI/Source/CsAI/Public/Utility/CsAILog.h
#pragma once
========
#include "Managers/Sense/CsSensingObject.h"
#include "CsSense.h"
>>>>>>>> origin/master:CsSense/Source/CsSense/Public/Managers/Sense/CsSensingObject.cpp

namespace NCsAI
{
	struct CSAI_API FLog final
	{
	public:

		static void Warning(const FString& Str);
	};
}