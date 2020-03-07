// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsCcHand.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UCsCcHand : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsCcCard;

class ICsCcHand
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return
	*/
	virtual TArray<ICsCcCard*>& GetCards()  = 0;
	
	/**
	*
	*
	* return
	*/
	virtual int32& GetSize() = 0;

	/**
	*
	*
	* @param Card
	* return
	*/
	virtual int32 GetCardPosition(ICsCcCard* Card) = 0;
};