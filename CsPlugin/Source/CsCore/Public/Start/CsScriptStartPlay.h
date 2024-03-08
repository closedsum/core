// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Start/CsStartPlay.h"

#include "CsScriptStartPlay.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptStartPlay : public UCsStartPlay
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsScriptStartPlay : public ICsStartPlay
{
	GENERATED_IINTERFACE_BODY()

// ICsStartPlay
#pragma region
public:

	void StartPlay();
	bool HasStartedPlay() const;

#pragma endregion ICsStartPlay

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptStartPlay", meta = (DisplayName = "Start Play"))
	void Script_StartPlay();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptStartPlay", meta = (DisplayName = "Has Started Play"))
	bool Script_HasStartedPlay() const;
};