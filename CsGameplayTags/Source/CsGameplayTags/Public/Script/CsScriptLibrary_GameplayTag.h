// Copyright Studio Sai, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "GameplayTagContainer.h"

#include "CsScriptLibrary_GameplayTag.generated.h"

UCLASS()
class CSGAMEPLAYTAGS_API UCsScriptLibrary_GameplayTag : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Container
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (CallableWithoutWorldContext, AutoCreateRefTerm = "GameplayTag"))
	static FGameplayTagContainer MakeContainer(const FGameplayTag& GameplayTag)
	{
		return FGameplayTagContainer(GameplayTag);
	}

#pragma endregion Settings
};