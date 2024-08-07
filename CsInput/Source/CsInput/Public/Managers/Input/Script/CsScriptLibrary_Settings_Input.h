// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Input
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/Action/CsInputAction.h"

#include "CsScriptLibrary_Settings_Input.generated.h"

UCLASS()
class CSINPUT_API UCsScriptLibrary_Settings_Input : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsInput|Settings|Input", meta = (AutoCreateRefTerm = "Context,Map"))
	static bool DoesMappingExist(const FString& Context, const FECsInputActionMap& Map);

	UFUNCTION(BlueprintPure, Category = "CsInput|Settings|Input", meta = (AutoCreateRefTerm = "Context,Map,Action"))
	static bool DoesActionByMapExist(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "CsInput|Settings|Input", meta = (AutoCreateRefTerm = "Context,Map,Action"))
	static void AddActionToMap(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "CsInput|Settings|Input", meta = (AutoCreateRefTerm = "Context,Map,Action"))
	static void RemoveActionFromMap(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "CsInput|Settings|Input", meta = (AutoCreateRefTerm = "Context,Map"))
	static void ClearMapping(const FString& Context, const FECsInputActionMap& Map);
};