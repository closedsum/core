// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

//#include "CsTypes_Manager_Fade.generated.h"

namespace NCsFade
{
	struct CSUI_API FParams
	{
	public:

		FLinearColor From;

		FLinearColor To;

		float Time;

		// TODO: Add Easing / Curve

		bool bCollapseOnEnd;

		FParams() :
			From(FLinearColor::Black),
			To(FLinearColor::Black),
			Time(0.0f),
			bCollapseOnEnd(false)
		{
		}
	};
}