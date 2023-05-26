// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsStatusEffect
{
	namespace NModifier
	{
		/**
		* Interface to describe modifying a status effect
		*/
		struct CSSE_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier() {}
		};
	}
}