// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#pragma once

namespace NCsSkeletalMeshActor
{
	namespace NCache
	{
		/**
		* Cache associated with a SkeletalMeshActor Pooled.
		*  The Manager for SkeletalMeshActor primarily interacts with the Cache object in terms
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