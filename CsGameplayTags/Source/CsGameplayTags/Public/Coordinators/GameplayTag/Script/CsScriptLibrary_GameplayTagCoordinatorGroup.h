// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

// Managers
#include "Coordinators/GameplayTag/CsTypes_Coordinator_GameplayTag.h"

#include "CsScriptLibrary_GameplayTagCoordinatorGroup.generated.h"

UCLASS()
class CSGAMEPLAYTAGS_API UCsScriptLibrary_GameplayTagCoordinatorGroup : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameplayTagCoordinatorGroup Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Index"))
	static FECsGameplayTagCoordinatorGroup GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsGameplayTagCoordinatorGroup& Enum);

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group")
	static void GetAll(TArray<FECsGameplayTagCoordinatorGroup>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group", meta = (AutoCreateRefTerm = "Name"))
	static FECsGameplayTagCoordinatorGroup GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Group)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsGameplayTags|Library|Coordinators|GameEvent|Group")
	static bool EqualEqual(const FECsGameplayTagCoordinatorGroup& A, const FECsGameplayTagCoordinatorGroup& B);
};