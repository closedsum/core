// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "UObject/Object.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"

#include "CsScriptLibrary_Manager_Projectile.generated.h"
#pragma once

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
	* Spawn a Projectile with the given Payload
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* @param OutIndex			(out)
	* return					Object of type ICsProjectile
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Payload"))
	static UObject* Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Projectile& Payload, int32& OutIndex);

#pragma endregion Spawn
};