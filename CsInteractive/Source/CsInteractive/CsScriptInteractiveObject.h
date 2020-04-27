// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsInteractiveObject.h"
#include "CsScriptInteractiveObject.generated.h"

UINTERFACE(Blueprintable)
class CSINTERACTIVE_API UCsScriptInteractiveObject : public UCsInteractiveObject
{
	GENERATED_UINTERFACE_BODY()
};


class CSINTERACTIVE_API ICsScriptInteractiveObject : public ICsInteractiveObject
{
	GENERATED_IINTERFACE_BODY()

// ICsInteractiveObject
#pragma region
public:

	void Freeze();
	void UnFreeze();
	void Hold();
	void Release();
	void Touch();
	void Hover();
	void UnHover();
	void Collide();
	void UnCollide();
	void Remove();

#pragma endregion ICsInteractiveObject

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Freeze"))
	void Script_Freeze();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "UnFreeze"))
	void Script_UnFreeze();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Hold"))
	void Script_Hold();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Release"))
	void Script_Release();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Touch"))
	void Script_Touch();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Hover"))
	void Script_Hover();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "UnHover"))
	void Script_UnHover();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Collide"))
	void Script_Collide();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "UnCollide"))
	void Script_UnCollide();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsInteractiveObject", meta = (DisplayName = "Remove"))
	void Script_Remove();
};