// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

struct ICsDamageEvent;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
			/**
			*/
			struct CSSE_API IDamage : virtual public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				/**
				*
				*
				* return
				*/
				virtual NCsDamage::NEvent::IEvent* GetDamageEvent() const = 0;
			};
		}
	}
}