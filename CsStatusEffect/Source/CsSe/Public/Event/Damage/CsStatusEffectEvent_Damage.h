// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
#pragma once

// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
			/**
			*/
			struct CSSE_API IDamage : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsDamage::NEvent::IEvent DamageEventType;

			public:
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