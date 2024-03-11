// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

namespace NCsSkeletalMeshActor
{
	namespace NCache
	{
		/**
		* Cache associated with a SkeletalMeshActor Pooled.
		*  The Manager for SkeletalMeshActor primarily interacts with the Cache object in terms
		*  of allocation and deallocation.
		*/
		struct CSSKELETALMESH_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}
		};
	}
}