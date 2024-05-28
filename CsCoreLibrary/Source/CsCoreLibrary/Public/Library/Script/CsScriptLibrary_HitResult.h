// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Engine/HitResult.h"

#include "CsScriptLibrary_HitResult.generated.h"

class AActor;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_HitResult : public UObject
{ 
	GENERATED_UCLASS_BODY() 

	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library", meta = (AutoCreateRefTerm = "Context"))
	static AActor* GetActor(const FString& Context, const FHitResult& Hit);

	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library", meta = (DisplayName = "Get Actor (No Log)"))
	static AActor* GetActor2(const FHitResult& Hit);

	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library", meta = (DisplayName = "Get Actor (Checked)", AutoCreateRefTerm = "Context"))
	static AActor* GetActorChecked(const FString& Context, const FHitResult& Hit, bool& OutSuccess);
};