// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsStatusEffect::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, IEvent)

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NCopy
		{
			/**
			* Interface for a Status Effect Event performing various Copy commands.
			*/
			struct CSSE_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define EventType NCsStatusEffect::NEvent::IEvent

			public:

				virtual ~ICopy(){}

				virtual void Copy(const EventType* From) = 0;

			#undef EventType
			};
		}
	}
}