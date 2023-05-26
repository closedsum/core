// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_AnimMontage.generated.h"

class UAnimMontage;

UCLASS()
class CSCORE_API UCsScriptLibrary_AnimMontage : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a AnimMontage at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the AnimMontage to load.
	* return			AnimMontage
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimMontage", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimMontage* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimMontage at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimMontage to load.
	* return			AnimMontage
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimMontage", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimMontage* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load
};