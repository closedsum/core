// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Engine/EngineTypes.h"

#include "CsTraceResponse.generated.h"
#pragma once

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTraceResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllocated;

	UPROPERTY(BlueprintReadOnly)
	bool bResult;

	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHitResult> OutHits;

	UPROPERTY()
	TArray<FOverlapResult> OutOverlaps;

	FCsTraceResponse() :
		bAllocated(false),
		bResult(false),
		ElapsedTime(0.0f),
		OutHits(),
		OutOverlaps()
	{
	}

	FORCEINLINE FCsTraceResponse& operator=(const FCsTraceResponse& B)
	{
		bAllocated = B.bAllocated;
		bResult	   = B.bResult;

		OutHits.Reset(FMath::Max(OutHits.Max(), B.OutHits.Max()));

		for (const FHitResult& Hit : B.OutHits)
		{
			OutHits.Add(Hit);
		}

		OutOverlaps.Reset(FMath::Max(OutOverlaps.Max(), B.OutOverlaps.Max()));

		for (const FOverlapResult& Overlap : B.OutOverlaps)
		{
			OutOverlaps.Add(Overlap);
		}
		ElapsedTime = B.ElapsedTime;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTraceResponse& B) const
	{
		if (bAllocated != B.bAllocated)
			return false;
		if (bResult != B.bResult)
			return false;
		if (ElapsedTime != B.ElapsedTime)
			return false;
		if (OutHits.Num() != B.OutHits.Num())
			return false;
		if (OutOverlaps.Num() != B.OutOverlaps.Num())
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsTraceResponse& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		bAllocated = false;
		bResult = false;
		ElapsedTime = 0.0f;

		OutHits.Reset(OutHits.Max());
		OutOverlaps.Reset(OutOverlaps.Max());
	}
};