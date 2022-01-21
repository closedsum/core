// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
// Projectile
#include "Cache/CsCache_Projectile.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

namespace NCsProjectile
{
	namespace NCache
	{
	#define CacheType NCsProjectile::NCache::ICache

		/**
		*/
		struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<CacheType>
		{
		public:

		#define PooledCacheType NCsPooledObject::NCache::ICache

			/**
			* Set the LifeTime for PooledCache.
			* This assumes PooledCache implements the interface: CacheType (NCsProjectile::NCache::ICache).
			* 
			* @param Context		The calling context.
			* @param PooledCache
			* @param LifeTime
			*/
			static void SetLifeTimeChecked(const FString& Context, PooledCacheType* PooledCache, const float& LifeTime);

		#undef PooledCacheType
		};

	#undef CacheType
	}
}