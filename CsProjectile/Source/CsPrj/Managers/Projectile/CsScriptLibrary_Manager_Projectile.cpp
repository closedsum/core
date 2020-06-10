// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Projectile/CsScriptLibrary_Manager_Projectile.h"
#include "CsPrj.h"

// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Projectile
#include "Managers/Projectile/CsProjectile.h"

UCsScriptLibrary_Manager_Projectile::UCsScriptLibrary_Manager_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Complete
#pragma region

TScriptInterface<ICsProjectile> UCsScriptLibrary_Manager_Projectile::Spawn(const UObject* WorldContextObject, const FECsProjectile& Projectile, const FCsScriptProjectilePayload& Payload)
{
#if WITH_EDITOR
	if (UCsManager_Projectile* Manager = UCsManager_Projectile::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Projectile* Manager = UCsManager_Projectile::Get())
#endif // #if WITH_EDITOR
	{
		const FCsProjectilePooled* ProjectileContainer = Manager->ScriptSpawn(Projectile, Payload);
		return ProjectileContainer->GetObject();
	}
	else
	{
		UE_LOG(LogCsPrj, Warning, TEXT("UCsScriptLibrary_Manager_Projectile::Spawn: No Manager Projectile of type UCsManager_Projectile was created."));
	}
	return nullptr;
}

#pragma endregion Complete