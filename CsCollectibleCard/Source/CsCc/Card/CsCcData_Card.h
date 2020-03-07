// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsCcData_Card.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCC_API UCsCcData_Card : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UMaterialInstanceConstant;

class ICsCcData_Card
{
	GENERATED_IINTERFACE_BODY()

public:

	// GetType

	/**
	*
	*
	* return
	*/
	virtual const FString& GetDescription() = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetCost() = 0;

	/**
	*
	*
	* return
	*/
	virtual UMaterialInstanceConstant* GetFrontMaterial() = 0;

	/**
	*
	*
	* return
	*/
	virtual UMaterialInstanceConstant* GetBackMaterial() = 0;
};