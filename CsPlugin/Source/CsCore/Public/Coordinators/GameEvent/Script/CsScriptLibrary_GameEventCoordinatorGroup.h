// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

// Managers
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

#include "CsScriptLibrary_GameEventCoordinatorGroup.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_GameEventCoordinatorGroup : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameEventCoordinatorGroup Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Index"))
	static FECsGameEventCoordinatorGroup GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsGameEventCoordinatorGroup& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group")
	static void GetAll(TArray<FECsGameEventCoordinatorGroup>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameEventCoordinatorGroup GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Group)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Coordinators|GameEvent|Group")
	static bool EqualEqual(const FECsGameEventCoordinatorGroup& A, const FECsGameEventCoordinatorGroup& B);
};