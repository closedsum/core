// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetSlateApplicationTool.generated.h"

namespace NCsSlate
{
	namespace NApplication
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

				void(*ApplyApplicationScaleImpl)(const float&);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetSlateApplicationTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetSlateApplicationTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define SlateApplicationToolType NCsSlate::NApplication::NTool::FImpl

	virtual SlateApplicationToolType* GetSlateApplicationTool() = 0;

#undef SlateApplicationToolType
};