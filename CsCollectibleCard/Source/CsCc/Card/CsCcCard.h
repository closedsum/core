// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsCcCard.generated.h"

UINTERFACE(Blueprintable)
class UCsCcCard : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsCcData_Card;
class UObject;

class ICsCcCard
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return
	*/
	virtual ICsCcData_Card* GetData()  = 0;
	
	/**
	*
	*
	* @param Instigator
	*/
	virtual void Draw(UObject* Instigator) = 0;

	/**
	*
	*
	* @param Instigator
	* @param Targets
	*/
	virtual void Play(UObject* Instigator, TArray<UObject*>& Targets) = 0;

	virtual void Consume(UObject* Instigator) = 0;

	virtual void Discard(UObject* Instigator) = 0;

	virtual int32 GetCost() = 0;
};