// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/Time/CsUpdate.h"
#include "CsScriptUpdate.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptUpdate : public UCsUpdate
{
	GENERATED_UINTERFACE_BODY()
};


class CSCORE_API ICsScriptUpdate : public ICsUpdate
{
	GENERATED_IINTERFACE_BODY()

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptUpdate", meta = (DisplayName = "Update", AutoCreateRefTerm = "DeltaTime"))
	void Script_Update(const FCsDeltaTime& DeltaTime);
};