// Copyright 2017-2022 Closed Sum Games, Inc. All rights reserved.
#pragma once
#include "Components/WidgetComponent.h"

#include "CsWidgetComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = "UserInterface", hidecategories = (Object, Activation, "Components|Activation", Sockets, Base, Lighting, LOD, Mesh), editinlinenew, meta = (BlueprintSpawnableComponent))
class CSUI_API UCsWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

public:

	void Show();
	void Hide();

	void Enable();
	void Disable();

	void ConditionalSetWidgetChecked(const FString& Context, UClass* InWidgetClass);
};