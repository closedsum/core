// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsScriptLibrary_Input.generated.h"

class UGameInstance;

UCLASS()
class CSCORE_API UCsScriptLibrary_Input : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* For the First Local Player, set the InputActionMap (bit for mask)
	*
	* @param WorldContextObject
	* @param Map
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Map"))
	static void SetFirstLocalPlayerInputActionMap(const UObject* WorldContextObject, const FECsInputActionMap& Map);
};