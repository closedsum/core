// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

// Managers
#include "Managers/Time/CsTypes_Update.h"

#include "CsScriptLibrary_UpdateGroup.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_UpdateGroup : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (AutoCreateRefTerm = "Name"))
	static FECsUpdateGroup Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (AutoCreateRefTerm = "Index"))
	static FECsUpdateGroup GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsUpdateGroup& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup")
	static void GetAll(TArray<FECsUpdateGroup>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (AutoCreateRefTerm = "Name"))
	static FECsUpdateGroup GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UpdateGroup)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|UpdateGroup")
	static bool EqualEqual(const FECsUpdateGroup& A, const FECsUpdateGroup& B);
};