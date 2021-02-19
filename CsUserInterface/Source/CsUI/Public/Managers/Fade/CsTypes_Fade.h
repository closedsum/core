// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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