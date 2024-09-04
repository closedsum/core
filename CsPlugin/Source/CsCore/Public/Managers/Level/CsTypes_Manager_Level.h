// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Manager_Level.generated.h"

USTRUCT(BlueprintType)
struct FCsManagerLevel_ChangeMapParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Managers|Level")
	FString Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Managers|Level")
	FString TransitionMap;

	/** Whether the Transition Map should be the Destination Map.
		This is used in the case when performing a Seamless Travel and "Pausing" on the Transition Map. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Managers|Level")
	bool bTransitionAsDestination;

	FCsManagerLevel_ChangeMapParams() :
		Map(),
		TransitionMap(),
		bTransitionAsDestination(false)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsLevel
{
	namespace NManager
	{
		namespace NChangeMap
		{
			struct CSCORE_API FParams
			{
				FString Map;

				FString TransitionMap;

				/** Whether the Transition Map should be the Destination Map.
					This is used in the case when performing a Seamless Travel and "Pausing" on the Transition Map. */
				bool bTransitionAsDestination;

				FParams() : 
					Map(),
					TransitionMap(),
					bTransitionAsDestination(false)
				{
				}

				FParams(FParams& B)
				{
					Copy(B);
				}

				FParams(const FParams& B)
				{
					Copy(B);
				}

				FORCEINLINE void Copy(const FParams& B)
				{
					Map					     = B.Map;
					TransitionMap			 = B.TransitionMap;
					bTransitionAsDestination = B.bTransitionAsDestination;
				}

				FORCEINLINE void Copy(FParams& B)
				{
					Map					     = B.Map;
					TransitionMap			 = B.TransitionMap;
					bTransitionAsDestination = B.bTransitionAsDestination;
				}

				FORCEINLINE static FParams Make(const FCsManagerLevel_ChangeMapParams& B)
				{
					FParams P;
					P.Map					   = B.Map;
					P.TransitionMap			   = B.TransitionMap;
					P.bTransitionAsDestination = B.bTransitionAsDestination;
					return P;
				}

				FORCEINLINE bool IsTransitionDestination() const { return bTransitionAsDestination; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}