// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsInputSetting.generated.h"

UCLASS(Blueprintable)
class CSCORE_API UCsInputSetting : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Action Map
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Setting|Action Map")
	TMap<FECsInputActionMap, FCsInputActionSet> InputActionMappings;

#pragma endregion Action Map

// Events
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input Setting|Events")
	TSet<FCsGameEventDefinitionSimple> GameEventDefinitionsSimple;

	UPROPERTY(EditDefaultsOnly, Category = "Input Setting|Events")
	TSet<FCsGameEventDefinition> GameEventDefinitions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Setting|Events")
	TArray<FECsGameEvent> GameEventPriorityList;

#pragma endregion Events
};