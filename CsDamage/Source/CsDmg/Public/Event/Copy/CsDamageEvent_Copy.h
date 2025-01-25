// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

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
			struct CSDMG_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

				// Allow clearer names without name collisions
				struct _
				{
					using EventType = NCsDamage::NEvent::IEvent;
				};

			public:

				virtual ~ICopy(){}

				virtual void Copy(const _::EventType* From) = 0;
			};
		}
	}
}