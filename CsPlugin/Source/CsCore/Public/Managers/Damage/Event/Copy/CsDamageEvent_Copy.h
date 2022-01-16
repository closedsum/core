// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NCopy
		{
			/**
			* Interface for a Damage Event, object that implements the interface: NCsDamage::NEvent::IEvent,
			* performing various Copy commands.
			*/
			struct CSCORE_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define EventType NCsDamage::NEvent::IEvent

			public:

				virtual ~ICopy(){}

				virtual void Copy(const EventType* From) = 0;

			#undef EventType
			};
		}
	}
}