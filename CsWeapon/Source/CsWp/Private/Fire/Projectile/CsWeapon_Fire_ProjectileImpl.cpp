// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Fire/Projectile/CsWeapon_Fire_ProjectileImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeapon_Fire_ProjectileImpl)

// UCsWeapon_Fire_ProjectileImpl
//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsWeapon_Fire_ProjectileImpl)
	// ICsWeapon_Fire_TimeBetweenShots
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_ProjectileImpl, Evaluate)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsWeapon_Fire_ProjectileImpl::UCsWeapon_Fire_ProjectileImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// ICsWeapon_Fire_Projectile
#pragma region

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchLocation(const LaunchPayloadType& Payload)
{
	return FVector::ZeroVector;
}

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchDirection(const LaunchPayloadType& LaunchPayload)
{
	return FVector::ZeroVector;
}

void UCsWeapon_Fire_ProjectileImpl::Launch(const LaunchPayloadType& LaunchPayload) 
{
}

#pragma endregion ICsWeapon_Fire_Projectile
