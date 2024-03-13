// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"

#include "CsScriptLibrary_Trace_Viewport.generated.h"

UCLASS()
class CSPHYSICS_API UCsScriptLibrary_Trace_Viewport : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Perform a trace with the given Request.
	*  Request.Start is replaced by:
	*   de-projection of ScreenPosition
	*  Request.End is replaced by:
	*	The result of the Request.Start + Distance * World Direction (of the de-projectile of the current mouse position).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ScreenPosition	2D screen space to deproject.
	* @param Request
	* @param Distance		The distance to project outward from the Request->Start.
	* @param Response		(out)
	* return				Whether the trace was successful or not
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhysics|Library|Viewport", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ScreenPosition,Request,Distance"))
	static bool Trace(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse);
};