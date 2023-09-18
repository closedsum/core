// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_AI.h"

#include "CsScriptLibrary_AI_Controller.generated.h"

class AAIController;

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Controller : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** 
	* Makes AI go toward specified destination
	* 
	* @param MoveRequest	details about move
	* @param OutPath		optional output param, filled in with assigned path
	* @return				struct holding MoveId and enum code
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Controller|Library", meta = (AutoCreateRefTerm = "Context,MoveRequest"))
	static FCsPathFollowingRequestResult MoveTo(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest);

	/**
	* Call Controller->GetDefaultNavigationFilterClass()
	*
	* @param Context	The calling context.
	* @param Controller
	* return			Default Navigation Filter Class
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Controller|Library")
	static TSubclassOf<UNavigationQueryFilter> GetDefaultNavigationFilterClass(const FString& Context, AAIController* Controller);
};