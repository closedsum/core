// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Weapon.h"

#include "CsScriptLibrary_Weapon.generated.h"

UCLASS()
class CSWP_API UCsScriptLibrary_Weapon : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name,DisplayName"))
	static FECsWeapon Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name"))
	static FECsWeapon Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Index"))
	static FECsWeapon GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsWeapon& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon")
	static void GetAll(TArray<FECsWeapon>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Weapon", meta = (AutoCreateRefTerm = "Name"))
	static FECsWeapon GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Weapon)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Weapon")
	static bool EqualEqual(const FECsWeapon& A, const FECsWeapon& B);

#pragma endregion Enum
};