// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Engine/EngineTypes.h"

#pragma once

class UObject;
struct FCsTraceResponse;

namespace NCsTrace
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get the Context (Root) for UCsManager_Trace from the WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Trace
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ScreenPosition	Screen position.
			* @param Distance		How far the the trace should go outward.
			* @param Channel	
			* return				Trace response for the given trace. NULL if result was found.
			*/
			static FCsTraceResponse* TraceScreenToWorldChecked(const FString& Context, UObject* WorldContext, const FVector2D& ScreenPosition, const float& Distance, const TEnumAsByte<ECollisionChannel>& Channel);
		};
	}
}