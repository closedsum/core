// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
#include "Event/CsStatusEffectEvent.h"

namespace NCsStatusEffect
{
	namespace NEvent
	{
		/**
		* Container for holding a reference to an object that implements the interface: NCsStatusEffect::NEvent::IEvent.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSSE_API FResource : public TCsResourceContainer<IEvent>
		{
		};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsStatusEffect::NEvent::IEvent and
		* are wrapped in the container: NCsStatusEffect::NEvent::FResource.
		*/
		struct CSSE_API FManager : public NCsResource::NManager::NPointer::TFixed<IEvent, FResource, 0>
		{
		};
	}
}