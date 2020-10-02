// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage {
	namespace NEvent {
		struct IEvent; } }

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

				typedef NCsDamage::NEvent::IEvent DamageEventType;
				/**
				*
				*
				* return
				*/
				virtual DamageEventType* GetDamageEvent() const = 0;
			};
		}
	}
}