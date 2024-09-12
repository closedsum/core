// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"

#include "CsWidgetActor.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsWidgetActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UCsWidgetComponent;

/**
*/
class CSUI_API ICsWidgetActor
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	* 
	*
	* return
	*/
	virtual UCsWidgetComponent* GetWidgetComponent() const = 0;
};