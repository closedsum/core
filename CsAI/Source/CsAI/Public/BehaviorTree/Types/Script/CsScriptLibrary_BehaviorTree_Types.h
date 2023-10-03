// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "BehaviorTree/Types/CsTypes_BehaviorTree.h"

#include "CsScriptLibrary_BehaviorTree_Types.generated.h"

class UBehaviorTree;

UCLASS()
class CSAI_API UCsScriptLibrary_BehaviorTree_Types : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (UBehaviorTree)", ScriptMethod = "Get", Keywords = "get"), Category = "CsAI|Behavior Tree|Types")
	static UBehaviorTree* FCsBehaviorTree_Get(const FCsBehaviorTree& A);
};