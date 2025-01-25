// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsLibrary_Cache_Projectile.h"

// Library
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"
// Projectile
#include "Cache/CsCache_ProjectileImpl.h"

namespace NCsProjectile
{
	namespace NCache
	{
		namespace NLibrary
		{
			using CacheLibrary = NCsPooledObject::NCache::NLibrary::FLibrary;
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsProjectile::NCache::ICache;
			using CacheImplType = NCsProjectile::NCache::NImpl::FImpl;
	
			void FLibrary::SetLifeTimeChecked(const FString& Context, PooledCacheType* PooledCache, const float& LifeTime)
			{
				check(CacheLibrary::ImplementsChecked<CacheType>(Context, PooledCache));

				if (CacheImplType* Impl = CacheLibrary::SafePureStaticCastChecked<CacheImplType>(Context, PooledCache))
				{
					Impl->SetLifeTimeChecked(Context, LifeTime);
					return;
				}
				checkf(0, TEXT("%s: Failed to set LifeTime for PooledCache."), *Context);
			}
		}
	}
}