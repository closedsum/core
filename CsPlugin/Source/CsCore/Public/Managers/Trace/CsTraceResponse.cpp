// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTraceResponse.h"

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