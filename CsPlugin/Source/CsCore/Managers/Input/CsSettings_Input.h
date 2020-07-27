// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsSettings_Input.generated.h"
#pragma once

// FCsSettings_Input
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Input
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FECsInputActionMap, FCsInputActionSet> InputActionMappings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<FCsGameEventDefinitionSimple> GameEventDefinitionsSimple;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<FCsGameEventDefinition> GameEventDefinitions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FECsGameEvent> GameEventPriorityList;

	FCsSettings_Input() :
		InputActionMappings(),
		GameEventDefinitionsSimple(),
		GameEventDefinitions(),
		GameEventPriorityList()
	{
	}
};

#pragma endregion FCsSettings_Input