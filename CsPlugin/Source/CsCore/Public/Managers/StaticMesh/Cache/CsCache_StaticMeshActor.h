// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#pragma once

namespace NCsStaticMeshActor
{
	namespace NCache
	{
		/**
		* Cache associated with a StaticMeshActor Pooled.
		*  The Manager for StaticMeshActor primarily interacts with the Cache object in terms
		*  of allocation and deallocation.
		*/
		struct CSCORE_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}
		};
	}
}