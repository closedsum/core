// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

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
		struct CSSOUND_API ICache : public ICsGetInterfaceMap
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