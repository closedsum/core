// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/LevelScriptActor.h"
// Types
#include "Types/CsTypes_Load.h"
#include "CsLevelScriptActor.generated.h"

UCLASS()
class ACsLevelScriptActor : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Payload")
	FCsPayload Payload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Payload")
	FCsPayload Payload_Level;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Payload")
	FCsPayload Payload_Test;
#endif // #if WITH_EDITORONLY_DATA

// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor
};