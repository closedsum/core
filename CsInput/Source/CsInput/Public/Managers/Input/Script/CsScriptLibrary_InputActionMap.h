// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Input
#include "Managers/Input/Action/CsInputActionMap.h"

#include "CsScriptLibrary_InputActionMap.generated.h"

UCLASS()
class CSINPUT_API UCsScriptLibrary_InputActionMap : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputActionMap Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputActionMap Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Index"))
	static FECsInputActionMap GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsInputActionMap& Enum);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input")
	static void GetAll(TArray<FECsInputActionMap>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input")
	static FECsInputActionMap GetNONE();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (InputActionMap)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsInput|Library|Input")
	static bool EqualEqual(const FECsInputActionMap& A, const FECsInputActionMap& B);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static bool IsValid(const FECsInputActionMap& Enum);

	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static bool IsValidByName(const FString& Name);
};