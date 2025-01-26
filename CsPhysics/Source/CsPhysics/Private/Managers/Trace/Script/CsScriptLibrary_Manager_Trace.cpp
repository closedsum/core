// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/Script/CsScriptLibrary_Manager_Trace.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
	// Common
#include "Library/CsLibrary_Math.h"
// Actor
#include "GameFramework/Actor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Trace)

// Cached
#pragma region

namespace NCsScriptLibraryManagerTrace
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, Trace);
			// Line
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, LineTraceSingleByChannel);
			// Sphere
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SphereTraceSingleByChannel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SphereTraceSingleByChannelAtBone);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SphereTraceSingleByObjectType);
			// Capsule
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SweepByCapsuleComponent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SweepByCapsuleComponentAgainstObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Trace, SweepByCapsuleComponentAgainstObjectOnly);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Trace::UCsScriptLibrary_Manager_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerTrace::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerTrace::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
using RequestType = NCsTrace::NRequest::FRequest;
using ResponseType = NCsTrace::NResponse::FResponse;

void UCsScriptLibrary_Manager_Trace::Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, FCsTraceResponse& OutResponse)
{
	CONDITIONAL_SET_CTXT(Trace);

	if (!Request.IsValid(Ctxt))
		return;

	if (RequestType* RequestPtr = CsTraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject))
	{
		Request.CopyToRequestAsValue(RequestPtr);

		ResponseType* ResponsePtr = CsTraceManagerLibrary::SafeTrace(Ctxt, WorldContextObject, RequestPtr);

		if (ResponsePtr)
		{
			OutResponse.CopyFromResponse(ResponsePtr);
		}
	}
}

// Line
#pragma region

bool UCsScriptLibrary_Manager_Trace::LineTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
	CONDITIONAL_SET_CTXT(LineTraceSingleByChannel);
	
	if (RequestType* Request = CsTraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject))
	{
		// Fill out Request
		Request->Start				  = CsMathLibrary::Convert(Start);
		Request->End				  = CsMathLibrary::Convert(End);
		Request->Channel			  = Channel;
		Request->Params.bTraceComplex = bTraceComplex;

		if (bIgnoreSelf)
		{
			if (AActor* Actor = Cast<AActor>(WorldContextObject))
				Request->Params.AddIgnoredActor(Actor);
		}

		Request->Params.AddIgnoredActors(ActorsToIgnore);

		// Check Response
		if (ResponseType* Response = CsTraceManagerLibrary::SafeTrace(Ctxt, WorldContextObject, Request))
		{
			if (Response->bResult)
			{
				OutHit = Response->OutHits[CS_FIRST];
			}
			return Response->bResult;
		}
		return false;
	}
	return false;
}

#pragma endregion Line

// Sphere
#pragma region

bool UCsScriptLibrary_Manager_Trace::SphereTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
	CONDITIONAL_SET_CTXT(SphereTraceSingleByChannel);
	
	if (RequestType* Request = CsTraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject))
	{
		// Fill out Request
		Request->Start				  = CsMathLibrary::Convert(Start);
		Request->End				  = CsMathLibrary::Convert(End);
		Request->Channel			  = Channel;
		Request->Params.bTraceComplex = bTraceComplex;
		Request->Shape.SetSphere(Radius);

		if (bIgnoreSelf)
		{
			if (AActor* Actor = Cast<AActor>(WorldContextObject))
				Request->Params.AddIgnoredActor(Actor);
		}

		Request->Params.AddIgnoredActors(ActorsToIgnore);

		// Check Response
		if (ResponseType* Response = CsTraceManagerLibrary::SafeTrace(Ctxt, WorldContextObject, Request))
		{
			if (Response->bResult)
			{
				OutHit = Response->OutHits[CS_FIRST];
			}
			return Response->bResult;
		}
		return false;
	}
	return false;
}

bool UCsScriptLibrary_Manager_Trace::SphereTraceSingleByChannelAtBone(const FString& Context, UObject* WorldContextObject, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
	CONDITIONAL_SET_CTXT(SphereTraceSingleByChannelAtBone);

	return CsTraceManagerLibrary::SafeSphereTrace(Ctxt, WorldContextObject, Component, BoneOrSocket, Radius, Channel, bTraceComplex, bIgnoreSelf, ActorsToIgnore, OutHit);
}

bool UCsScriptLibrary_Manager_Trace::SphereTraceSingleByObjectType(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const float& Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
	CONDITIONAL_SET_CTXT(SphereTraceSingleByObjectType);
	
	if (RequestType* Request = CsTraceManagerLibrary::SafeAllocateRequest(Ctxt, WorldContextObject))
	{
		// Fill out Request
		Request->Start	= CsMathLibrary::Convert(Start);
		Request->End	= CsMathLibrary::Convert(End);
		
		NCsCollisionObjectQueryParams::Populate(Request->ObjectParams, ObjectTypes);

		Request->Params.bTraceComplex = bTraceComplex;
		Request->Shape.SetSphere(Radius);

		if (bIgnoreSelf)
		{
			if (AActor* Actor = Cast<AActor>(WorldContextObject))
				Request->Params.AddIgnoredActor(Actor);
		}

		Request->Params.AddIgnoredActors(ActorsToIgnore);

		// Check Response
		if (ResponseType* Response = CsTraceManagerLibrary::SafeTrace(Ctxt, WorldContextObject, Request))
		{
			if (Response->bResult)
			{
				OutHit = Response->OutHits[CS_FIRST];
			}
			return Response->bResult;
		}
		return false;
	}
	return false;
}

#pragma endregion Sphere

// Capsule
#pragma region

bool UCsScriptLibrary_Manager_Trace::SweepByCapsuleComponent(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, FCsTraceResponse& OutResponse)
{
	CONDITIONAL_SET_CTXT(SweepByCapsuleComponent);

	if (!Params.IsValid(Ctxt))
		return false;

	static FCollisionQueryParams QueryParams;
	Params.CopyToParams(QueryParams);

	ResponseType* ResponsePtr = CsTraceManagerLibrary::SafeSweep(Ctxt, WorldContextObject, CapsuleComponent, QueryParams);

	if (ResponsePtr)
	{
		OutResponse.CopyFromResponse(ResponsePtr);
		return OutResponse.OutHits.Num() > CS_EMPTY;
	}
	return false;
}

bool UCsScriptLibrary_Manager_Trace::SweepByCapsuleComponentAgainstObject(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, UObject* Object, FCsTraceResponse& OutResponse)
{
	CONDITIONAL_SET_CTXT(SweepByCapsuleComponentAgainstObject);

	if (!Params.IsValid(Ctxt))
		return false;

	static FCollisionQueryParams QueryParams;
	Params.CopyToParams(QueryParams);

	ResponseType* ResponsePtr = CsTraceManagerLibrary::SafeSweepAgainstObject(Ctxt, WorldContextObject, CapsuleComponent, QueryParams, Object);

	if (ResponsePtr)
	{
		OutResponse.CopyFromResponse(ResponsePtr);
		return true;
	}
	return false;
}

bool UCsScriptLibrary_Manager_Trace::SweepByCapsuleComponentAgainstObjectOnly(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, UObject* Object, FCsTraceResponse& OutResponse)
{
	CONDITIONAL_SET_CTXT(SweepByCapsuleComponentAgainstObjectOnly);

	if (!Params.IsValid(Ctxt))
		return false;

	static FCollisionQueryParams QueryParams;
	Params.CopyToParams(QueryParams);

	ResponseType* ResponsePtr = CsTraceManagerLibrary::SafeSweepAgainstObjectOnly(Ctxt, WorldContextObject, CapsuleComponent, QueryParams, Object);

	if (ResponsePtr)
	{
		OutResponse.CopyFromResponse(ResponsePtr);
		return true;
	}
	return false;
}

#pragma endregion Capsule

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT