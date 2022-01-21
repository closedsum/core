// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Projectile.h"

#include "CsScriptLibrary_ProjectileClass.generated.h"

UCLASS()
class CSPRJ_API UCsScriptLibrary_ProjectileClass : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Name"))
	static FECsProjectileClass Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Index"))
	static FECsProjectileClass GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsProjectileClass& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile")
	static void GetAll(TArray<FECsProjectileClass>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Name"))
	static FECsProjectileClass GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (ProjectileClass)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Projectile")
	static bool EqualEqual(const FECsProjectileClass& A, const FECsProjectileClass& B);

#pragma endregion Enum
};