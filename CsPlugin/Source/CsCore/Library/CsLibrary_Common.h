// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsLibrary_Common.generated.h"

class APlayerController;

UCLASS()
class CSCORE_API UCsLibrary_Common : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Player
#pragma region
public:

	static void GetAllLocalPlayerControllers(UWorld* World, TArray<APlayerController*>& OutControllers);

#pragma endregion Player
};