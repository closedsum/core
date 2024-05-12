// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsTraceResponse.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTraceResponse)

#define ResponseType NCsTrace::NResponse::FResponse
void FCsTraceResponse::CopyFromResponse(ResponseType* Response)
{
#undef ResponseType

	bResult = Response->bResult;
	ElapsedTime = Response->ElapsedTime;

	OutHits.Reset(FMath::Max(OutHits.Max(), Response->OutHits.Num()));

	for (const FHitResult& Hit : Response->OutHits)
	{
		OutHits.Add(Hit);
	}

	OutOverlaps.Reset(FMath::Max(OutOverlaps.Max(), Response->OutOverlaps.Num()));

	for (const FOverlapResult& Overlap : Response->OutOverlaps)
	{
		OutOverlaps.Add(Overlap);
	}
}