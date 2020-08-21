// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#pragma once

#include "Components/WidgetComponent.h"
#include "CsWidgetComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = "UserInterface", hidecategories = (Object, Activation, "Components|Activation", Sockets, Base, Lighting, LOD, Mesh), editinlinenew, meta = (BlueprintSpawnableComponent))
class CSUI_API UCsWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = UserInterface)
	UUserWidget* GetWidget();

	template<typename T>
	T* GetWidget()
	{
		return Cast<T>(GetWidget());
	}

	void Show();
	void Hide();

	void Enable();
	void Disable();
};