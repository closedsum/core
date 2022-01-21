// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Weapon.h"

#include "CsScriptLibrary_Manager_Weapon.generated.h"

UCLASS()
class CSWP_API UCsScriptLibrary_Manager_Weapon : public UObject
{ 
	GENERATED_UCLASS_BODY() 

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
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
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
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Manager|Block", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
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
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Manager|Block", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static bool AddClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type, TSubclassOf<UObject> Class);

#pragma endregion Class
};