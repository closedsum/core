// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Templates/SubclassOf.h"
#include "CsMacro_Cached.h"
// Weapon
#include "Payload/CsPayload_WeaponImpl.h"

#include "CsScriptLibrary_Manager_Weapon.generated.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_Weapon)

UCLASS()
class CSWP_API UCsScriptLibrary_Manager_Weapon : public UObject
{ 
	GENERATED_UCLASS_BODY() 

private:

	CS_USING_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_Weapon);

// Class
#pragma region
public:

	/**
	* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type			Type of the weapon.
	* return				Weapon class as a UClass.
	*/
	UFUNCTION(BlueprintPure, Category = "CsWp|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static UClass* GetClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type);

	/**
	* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type			Class type of the weapon.
	* return				Weapon class as a UClass.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static UClass* GetClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type);

	/**
	* Add the Class for Type to Manager_Weapon's ClassHandler.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Class
	* @param Log				(optional)
	* return					Whether the Class was successfully added for Type.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsWp|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static bool AddClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type, TSubclassOf<UObject> Class);

	/**
	* Add the Class for Class Type to Manager_Weapon's ClassHandler.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Class
	* @param Log				(optional)
	* return					Whether the Class was successfully added for Class Type.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsWp|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static bool AddClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type, TSubclassOf<UObject> Class);

#pragma endregion Class

// Spawn
#pragma region
public:

	/**
	* Spawn a Weapon with the given Payload
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* @param OutIndex			(out)
	* return					Object of type ICsWeapon
	*/
	UFUNCTION(BlueprintCallable, Category = "CsWp|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Payload"))
	static UObject* Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Weapon& Payload, int32& OutIndex);

#pragma endregion Spawn
};