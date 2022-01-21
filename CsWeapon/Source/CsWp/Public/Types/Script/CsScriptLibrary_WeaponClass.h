// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Weapon.h"

#include "CsScriptLibrary_WeaponClass.generated.h"

UCLASS()
class CSWP_API UCsScriptLibrary_WeaponClass : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name,DisplayName"))
	static FECsWeaponClass Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name"))
	static FECsWeaponClass Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Index"))
	static FECsWeaponClass GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsWeaponClass& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon")
	static void GetAll(TArray<FECsWeaponClass>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name"))
	static FECsWeaponClass GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (WeaponClass)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Weapon")
	static bool EqualEqual(const FECsWeaponClass& A, const FECsWeaponClass& B);

#pragma endregion Enum
};