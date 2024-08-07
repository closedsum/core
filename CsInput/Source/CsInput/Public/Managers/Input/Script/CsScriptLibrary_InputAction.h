// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Input
#include "Managers/Input/Action/CsInputAction.h"

#include "CsScriptLibrary_InputAction.generated.h"

UCLASS()
class CSINPUT_API UCsScriptLibrary_InputAction : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Index"))
	static FECsInputAction GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (DisplayName = "ToString (ECsInputAction)", CompactNodeTitle = "->", BlueprintAutocast, AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsInputAction& Enum);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input")
	static void GetAll(TArray<FECsInputAction>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction GetMAX();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (ECsInputAction)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsInput|Library|Input")
	static bool EqualEqual(const FECsInputAction& A, const FECsInputAction& B);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static bool IsValid(const FECsInputAction& Enum);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static bool IsValidByName(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Key"))
	static FECsInputAction GetByKey(const FKey& Key);
};