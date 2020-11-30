// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Time/CsTypes_Update.h"
#pragma once

class UObject;

namespace NCsTime
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* 
			* 
			* @param ContextRoot
			* @param Group
			*/
			static void UpdateTimeAndCoroutineScheduler(UObject* ContextRoot, const FECsUpdateGroup& Group, const float& DeltaTime);
		};
	}
}