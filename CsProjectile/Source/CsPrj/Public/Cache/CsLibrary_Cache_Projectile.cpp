// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsLibrary_Cache_Projectile.h"

// Library
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"
// Projectile
#include "Cache/CsCache_ProjectileImpl.h"

namespace NCsProjectile
{
	namespace NCache
	{
		#define CacheType NCsProjectile::NCache::ICache

		#define PooledCacheType NCsPooledObject::NCache::ICache
		void FLibrary::SetLifeTimeChecked(const FString& Context, PooledCacheType* PooledCache, const float& LifeTime)
		{
		#undef PooledCacheType

			typedef NCsPooledObject::NCache::FLibrary CacheLibrary;

			check(CacheLibrary::ImplementsChecked<CacheType>(Context, PooledCache));

			typedef NCsProjectile::NCache::FImpl CacheImplType;

			if (CacheImplType* Impl = CacheLibrary::SafePureStaticCastChecked<CacheImplType>(Context, PooledCache))
			{
				Impl->SetLifeTimeChecked(Context, LifeTime);
				return;
			}
			checkf(0, TEXT("%s: Failed to set LifeTime for PooledCache."), *Context);
		}

		#undef CacheType
	}
}