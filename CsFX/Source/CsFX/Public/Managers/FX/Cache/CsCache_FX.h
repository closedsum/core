// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Containers/CsGetInterfaceMap.h"

#pragma once

class UNiagaraComponent;

namespace NCsFX
{
	namespace NCache
	{
		/**
		* Cache associated with an FX Pooled Object (Actor or Component)
		*  The Manager for FX primarily interacts with the Cache object in terms
		*  of allocation and deallocation.
		*/
		struct CSFX_API ICache : public ICsGetInterfaceMap
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
			virtual UNiagaraComponent* GetFXComponent() const = 0;
		};
	}
}