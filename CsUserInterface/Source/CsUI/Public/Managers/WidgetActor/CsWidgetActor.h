// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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