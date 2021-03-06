// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsScriptLibrary_GameEvent.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_GameEvent : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameEvent Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameEvent Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Index"))
	static FECsGameEvent GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsGameEvent& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input")
	static void GetAll(TArray<FECsGameEvent>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameEvent GetMAX();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (GameEvent)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Input")
	static bool EqualEqual(const FECsGameEvent& A, const FECsGameEvent& B);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Enum"))
	static bool IsValid(const FECsGameEvent& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Name"))
	static bool IsValidByName(const FString& Name);
};