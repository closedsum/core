// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/FX/CsTypes_FX.h"

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
			virtual UNiagaraComponent* GetFXComponent() const = 0;
		};
	}
}