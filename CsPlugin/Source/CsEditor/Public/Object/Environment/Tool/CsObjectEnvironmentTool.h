// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Object/Environment/Tool/CsObjectEnvironmentDetails.h"

class UObject;

namespace NCsObject
{
	namespace NEnvironment
	{
		struct CSEDITOR_API FTool
		{
		public:

		#define DetailsType NCsObject::NEnvironment::FDetails

			static DetailsType GetDetails(UObject* Object);

		#undef DetailsType
		};
	}
}