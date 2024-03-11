// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Spawner.generated.h"

class UCsManager_Spawner;

UCLASS()
class CSSPAWNER_API UCsScriptLibrary_Manager_Spawner : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Spawner from a WorldContext.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				UCsManager_Spawner.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSpawner|Library|Manager|Spawner", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UCsManager_Spawner* Get(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Get
};