// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Managers/Creep/CsTdTypes_Creep.h"

#include "CsTdLibrary_Blueprint.generated.h"
#pragma once

UCLASS()
class CSTD_API UCsTdLibrary_Blueprint : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// TSoftObjectPtr
#pragma region
public:

	// Container
#pragma region
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (Actor)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UObject* Conv_CsTdCreepRefContainerToInternal(const FCsTdCreepRefContainer& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (Class)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UClass* Conv_CsTdCreepRefContainerToClass(const FCsTdCreepRefContainer& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (SubclassOf)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static TSubclassOf<UObject> Conv_CsTdCreepRefContainerToSubclassOf(const FCsTdCreepRefContainer& Container);

#pragma endregion Container

#pragma endregion TSoftObjectPtr
};