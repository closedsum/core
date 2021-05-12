// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsScriptLibrary_InputActionMap.generated.h"

class UNiagaraSystem;

UCLASS()
class CSCORE_API UCsScriptLibrary_InputActionMap : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputActionMap Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Index"))
	static FECsInputActionMap GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsInputActionMap& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static void GetAll(TArray<FECsInputActionMap>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsInputActionMap GetNONE();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (InputActionMap)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Input")
	static bool EqualEqual(const FECsInputActionMap& A, const FECsInputActionMap& B);

};