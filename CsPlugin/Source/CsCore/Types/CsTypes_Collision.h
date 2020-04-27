// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Collision.generated.h"
#pragma once

// FCsOnComponentBeginOverlapInfo
#pragma region

USTRUCT(Blueprintable, BlueprintType)
struct FCsOnComponentBeginOverlapInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* OverlappedComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* OtherActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* OtherComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OtherBodyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFromSweep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult SweepResult;

	FCsOnComponentBeginOverlapInfo() :
		OverlappedComponent(nullptr),
		OtherActor(nullptr),
		OtherComponent(nullptr),
		OtherBodyIndex(INDEX_NONE),
		bFromSweep(false),
		SweepResult()
	{
	}
};

#pragma endregion FCsOnComponentBeginOverlapInfo