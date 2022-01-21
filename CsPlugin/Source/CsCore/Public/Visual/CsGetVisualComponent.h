// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsGetVisualComponent.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetVisualComponent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class USceneComponent;

class CSCORE_API ICsGetVisualComponent
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	* 
	* 
	*/
	virtual USceneComponent* GetVisualComponent() = 0;
};