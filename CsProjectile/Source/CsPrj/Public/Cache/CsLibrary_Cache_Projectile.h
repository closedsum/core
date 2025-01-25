// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
// Projectile
#include "Cache/CsCache_Projectile.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)

namespace NCsProjectile
{
	namespace NCache
	{
		namespace NLibrary
		{
			using CacheType = NCsProjectile::NCache::ICache;

			/**
			*/
			struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<CacheType>
			{
			private:
				
				using PooledCacheType = NCsPooledObject::NCache::ICache;
				
			public:

				/**
				* Set the LifeTime for PooledCache.
				* This assumes PooledCache implements the interface: CacheType (NCsProjectile::NCache::ICache).
				* 
				* @param Context		The calling context.
				* @param PooledCache
				* @param LifeTime
				*/
				static void SetLifeTimeChecked(const FString& Context, PooledCacheType* PooledCache, const float& LifeTime);
			};
		}
	}
}

using CsProjectileCacheLibrary = NCsProjectile::NCache::NLibrary::FLibrary;
using CsPrjCacheLibrary = NCsProjectile::NCache::NLibrary::FLibrary;