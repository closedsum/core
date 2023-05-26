// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Damage.h"

#include "CsScriptLibrary_DamageType.generated.h"

UCLASS()
class CSDMG_API UCsScriptLibrary_DamageType : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Name,DisplayName"))
	static FECsDamageType Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Name"))
	static FECsDamageType Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Index"))
	static FECsDamageType GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsDamageType& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage")
	static void GetAll(TArray<FECsDamageType>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Name"))
	static FECsDamageType GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (ECsDamageType)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Damage")
	static bool EqualEqual(const FECsDamageType& A, const FECsDamageType& B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (ECsDamageType)", CompactNodeTitle = "!=", ScriptMethod = "NotEquals", Keywords = "!= notequal"), Category = "CsCore|Library|Damage")
	static bool NotEqual(const FECsDamageType& A, const FECsDamageType& B);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Enum"))
	static bool IsValid(const FECsDamageType& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Damage", meta = (AutoCreateRefTerm = "Name"))
	static bool IsValidByName(const FString& Name);
};