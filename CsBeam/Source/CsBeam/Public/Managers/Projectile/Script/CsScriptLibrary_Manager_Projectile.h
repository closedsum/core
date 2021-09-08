// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "Types/CsTypes_Projectile.h"
#include "CsScriptLibrary_Manager_Projectile.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class ICsProjectile;

UCLASS()
class CSPRJ_API UCsScriptLibrary_Manager_Projectile : public UObject
{
	GENERATED_UCLASS_BODY()

// Settings
#pragma region
public:

	/**
	*
	*
	* @param WorldContextObject
	* @param Projectile
	* @param Key
	* @param Value
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Key,Value"))
	static void SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Key, const FECsProjectile& Value);

#pragma endregion Settings

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
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Projectile,Payload"))
	static int32 Spawn(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Projectile, const FCsPayload_Projectile& Payload);

#pragma endregion Spawn
};