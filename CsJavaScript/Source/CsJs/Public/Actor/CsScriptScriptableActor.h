// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Actor/CsScriptableActor.h"

#include "CsScriptScriptableActor.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptScriptableActor : public UCsScriptableActor
{
	GENERATED_UINTERFACE_BODY()
};

class CSJS_API ICsScriptScriptableActor : public ICsScriptableActor
{
	GENERATED_IINTERFACE_BODY()

// ICsScriptableActor
#pragma region
public:

	const FCsScriptableActorInfo& GetScriptableActorInfo() const;

#pragma endregion ICsScriptableActor

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptableActor", meta = (DisplayName = "Get Scriptable Actor Info"))
	void Script_GetScriptableActorInfo(FCsScriptableActorInfo& OutInfo) const;
};