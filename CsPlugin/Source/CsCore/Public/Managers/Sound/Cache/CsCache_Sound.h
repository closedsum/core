// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

class UAudioComponent;

namespace NCsSound
{
	namespace NCache
	{
		/**
		* Cache associated with a Sound Pooled Object.
		*  The Manager for Sound primarily interacts with the Cache object in terms
		*  of allocation and deallocation.
		*/
		struct CSCORE_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}

			/**
			*
			*
			* return
			*/
			virtual UAudioComponent* GetAudioComponent() const = 0;
		};
	}
}