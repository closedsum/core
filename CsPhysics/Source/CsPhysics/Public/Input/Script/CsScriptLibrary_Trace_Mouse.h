// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"

#include "CsScriptLibrary_Trace_Mouse.generated.h"

UCLASS()
class CSPHYSICS_API UCsScriptLibrary_Trace_Mouse : public UObject
{
	GENERATED_UCLASS_BODY()

// Trace
#pragma region
public:

	/**
	* Perform a trace with the given Request.
	*  Request->Start is replaced by:
	*   de-projection of the current mouse position (viewport space)
	*  Request->End is replaced by:
	*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
	*
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Request
	* @param Distance		(optional) The distance to project outward from the Request->Start.
	* return				Response
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhysics|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Request,Distance"))
	static bool Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse);

#pragma endregion Trace
};