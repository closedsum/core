// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Projectile.h"

#include "CsScriptLibrary_Data_Weapon_GetProjectileType.generated.h"

UCLASS()
class CSWP_API UCsScriptLibrary_Data_Weapon_GetProjectileType : public UObject
{ 
	GENERATED_UCLASS_BODY() 


public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static const FECsProjectile& GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type);
};