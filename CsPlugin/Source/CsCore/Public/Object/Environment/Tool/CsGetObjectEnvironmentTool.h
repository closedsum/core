// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Object/Environment/Tool/CsObjectEnvironmentDetails.h"

#include "CsGetObjectEnvironmentTool.generated.h"

namespace NCsObject
{
	namespace NEnvironment
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

			#define DetailsType NCsObject::NEnvironment::FDetails

				DetailsType(*GetDetailsImpl)(UObject* /*Object*/);

			#undef DetailsType
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetObjectEnvironmentTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetObjectEnvironmentTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define ObjectEnvironmentToolType NCsObject::NEnvironment::NTool::FImpl

	virtual ObjectEnvironmentToolType* GetObjectEnvironmentTool() = 0;

#undef ObjectEnvironmentToolType
};