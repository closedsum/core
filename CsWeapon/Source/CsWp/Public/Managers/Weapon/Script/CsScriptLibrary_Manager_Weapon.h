// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	static UClass* GetWeaponClassByType(const FString& Context, const UObject* WorldContextObject, const FECsWeapon& Type);

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
	static UClass* GetWeaponClassByClassType(const FString& Context, const UObject* WorldContextObject, const FECsWeaponClass& Type);

#pragma endregion Class
};