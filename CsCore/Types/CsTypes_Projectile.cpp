// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile.h"

// ProjectileRelevance
EMCsProjectileRelevance* EMCsProjectileRelevance::Instance;

EMCsProjectileRelevance& EMCsProjectileRelevance::Get()
{
	if (!Instance)
		Instance = new EMCsProjectileRelevance();
	return *Instance;
}

namespace ECsProjectileRelevance
{
	namespace Ref
	{
		CSCORE_API const Type RealVisible = EMCsProjectileRelevance::Get().Add(Type::RealVisible, TEXT("RealVisible"), TEXT("Real Visible"));
		CSCORE_API const Type RealInvisible = EMCsProjectileRelevance::Get().Add(Type::RealInvisible, TEXT("RealInvisible"), TEXT("Real Invisible"));
		CSCORE_API const Type Fake = EMCsProjectileRelevance::Get().Add(Type::Fake, TEXT("Fake"));
		CSCORE_API const Type ECsProjectileRelevance_MAX = EMCsProjectileRelevance::Get().Add(Type::ECsProjectileRelevance_MAX, TEXT("ECsProjectileRelevance_MAX"), TEXT("MAX"));
	}
}

// ProjectileType
EMCsProjectileType* EMCsProjectileType::Instance;

EMCsProjectileType& EMCsProjectileType::Get()
{
	if (!Instance)
		Instance = new EMCsProjectileType();
	return *Instance;
}