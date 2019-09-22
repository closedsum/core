// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UI/Interfaces/Button/CsButton.h"
#include "CsScriptButton.generated.h"

UINTERFACE(Blueprintable, MinimalApi)
class UCsScriptButton : public UCsButton
{
	GENERATED_UINTERFACE_BODY()
};


class ICsScriptButton : public ICsButton
{
	GENERATED_IINTERFACE_BODY()

// ICsButton
#pragma region

public:

	void Press();

	void Release();

#pragma endregion ICsButton

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptButton", meta = (DisplayName = "Press"))
	void Script_Press();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptButton", meta = (DisplayName = "Release"))
	void Script_Release();
};