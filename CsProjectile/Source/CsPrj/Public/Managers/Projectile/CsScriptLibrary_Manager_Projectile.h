// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsScriptLibrary_Manager_Projectile.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class ICsProjectile;

UCLASS()
class CSPRJ_API UCsScriptLibrary_Manager_Projectile : public UObject
{
	GENERATED_UCLASS_BODY()

// Spawn
#pragma region
public:

	/**
	* 
	*
	* @param WorldContextObject
	* @param Projectile
	* @param Payload
	* return					Object of type ICsProjectile
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Projectile,Payload"))
	static TScriptInterface<ICsProjectile> Spawn(const UObject* WorldContextObject, const FECsProjectile& Projectile, const FCsScriptProjectilePayload& Payload);

#pragma endregion Spawn
};