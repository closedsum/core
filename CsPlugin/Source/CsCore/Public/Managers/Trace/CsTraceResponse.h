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

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Index;

	/** Whether the response should be queued for deallocation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDeallocate;

	/** Whether the trace successful hit something. */
	UPROPERTY(BlueprintReadOnly)
	bool bResult;

	/** */
	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime;

	/** All hit results as a result of the trace. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FHitResult> OutHits;

	/** All overlap results as a result of the trace. */
	UPROPERTY()
	TArray<FOverlapResult> OutOverlaps;

	FCsTraceResponse() :
		Index(INDEX_NONE),
		bDeallocate(false),
		bResult(false),
		ElapsedTime(0.0f),
		OutHits(),
		OutOverlaps()
	{
	}

	void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex()
	{
		return Index;
	}

	FORCEINLINE void QueueDeallocate()
	{
		bDeallocate = true;
	}

	FORCEINLINE bool ShouldDeallocate() const
	{
		return bDeallocate;
	}

	FORCEINLINE void Reset()
	{
		bDeallocate = false;
		bResult = false;
		ElapsedTime = 0.0f;

		OutHits.Reset(OutHits.Max());
		OutOverlaps.Reset(OutOverlaps.Max());
	}
};

namespace NCsTrace
{
	namespace NResponse
	{
		struct CSCORE_API FResponse
		{
		public:

			/** */
			int32 Index;

			/** Whether the response should be queued for deallocation. */
			bool bDeallocate;

			/** Whether the trace successful hit something. */
			bool bResult;

			/** */
			float ElapsedTime;

			/** All hit results as a result of the trace. */
			TArray<FHitResult> OutHits;

			/** All overlap results as a result of the trace. */
			TArray<FOverlapResult> OutOverlaps;

			FResponse() :
				Index(INDEX_NONE),
				bDeallocate(false),
				bResult(false),
				ElapsedTime(0.0f),
				OutHits(),
				OutOverlaps()
			{
			}

			void SetIndex(const int32& InIndex) { Index = InIndex; }

			FORCEINLINE const int32& GetIndex() { return Index; }

			FORCEINLINE void QueueDeallocate() { bDeallocate = true; }
			FORCEINLINE bool ShouldDeallocate() const { return bDeallocate; }

			FORCEINLINE void Reset()
			{
				bDeallocate = false;
				bResult = false;
				ElapsedTime = 0.0f;

				OutHits.Reset(OutHits.Max());
				OutOverlaps.Reset(OutOverlaps.Max());
			}
		};
	}
}