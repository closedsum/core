// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UI/Interfaces/Object/CsUIObject.h"
#include "CsScriptUIObject.generated.h"

UINTERFACE(Blueprintable, MinimalApi)
class UCsScriptUIObject : public UCsUIObject
{
	GENERATED_UINTERFACE_BODY()
};


class ICsScriptUIObject : public ICsUIObject
{
	GENERATED_IINTERFACE_BODY()

// ICsUIObject
#pragma region

public:

	void Show();
	
	void Hide();

	void Enable();

	void Disable();

#pragma endregion ICsUIObject

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptUIObject", meta = (DisplayName = "Show"))
	void Script_Show();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptUIObject", meta = (DisplayName = "Hide"))
	void Script_Hide();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptUIObject", meta = (DisplayName = "Enable"))
	void Script_Enable();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptUIObject", meta = (DisplayName = "Disable"))
	void Script_Disable();
};