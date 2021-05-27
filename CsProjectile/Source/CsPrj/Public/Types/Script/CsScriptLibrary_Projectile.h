// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Projectile.h"

#include "CsScriptLibrary_Projectile.generated.h"

UCLASS()
class CSPRJ_API UCsScriptLibrary_Projectile : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Name"))
	static FECsProjectile Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Index"))
	static FECsProjectile GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsProjectile& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile")
	static void GetAll(TArray<FECsProjectile>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Projectile", meta = (AutoCreateRefTerm = "Name"))
	static FECsProjectile GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Projectile)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Projectile")
	static bool EqualEqual(const FECsProjectile& A, const FECsProjectile& B);

#pragma endregion Enum
};