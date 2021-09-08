// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Input
#include "Managers/Input/Action/CsInputAction.h"

#include "CsScriptLibrary_InputAction.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_InputAction : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Index"))
	static FECsInputAction GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (DisplayName = "ToString (ECsInputAction)", CompactNodeTitle = "->", BlueprintAutocast, AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsInputAction& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static void GetAll(TArray<FECsInputAction>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputAction GetMAX();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (ECsInputAction)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Input")
	static bool EqualEqual(const FECsInputAction& A, const FECsInputAction& B);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static bool IsValid(const FECsInputAction& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static bool IsValidByName(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Key"))
	static FECsInputAction GetByKey(const FKey& Key);
};