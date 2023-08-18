// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Log
#include "Utility/CsLog.h"

#include "CsScriptLibrary_Component.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Component : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	static bool CreateAndRegister_IsValid(const FString& Context, const UObject* Outer, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

public:

	/**
	* Create a Component of type: UCameraComponent for Outer and Register it.
	*
	* @param Context	The calling context
	* @param Outer
	* @param Name
	* return			Component
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Component", meta = (AutoCreateRefTerm = "Context,Name"))
	static UCameraComponent* CreateAndRegister_CameraComponent(const FString& Context, UObject* Outer, const FName& Name);

	/**
	* Create a Component of type: USpringArmComponent for Outer and Register it.
	*
	* @param Context	The calling context
	* @param Outer
	* @param Name
	* return			Component
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Component", meta = (AutoCreateRefTerm = "Context,Name"))
	static USpringArmComponent* CreateAndRegister_SpringArmComponent(const FString& Context, UObject* Outer, const FName& Name);
};