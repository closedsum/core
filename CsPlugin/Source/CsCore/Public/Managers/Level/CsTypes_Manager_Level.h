// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

	FCsManagerLevel_ChangeMapParams() :
		Map(),
		TransitionMap()
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

				FParams() : 
					Map(),
					TransitionMap()
				{
				}

				static FParams Make(const FCsManagerLevel_ChangeMapParams& Params)
				{
					FParams P;
					P.Map			= Params.Map;
					P.TransitionMap = Params.TransitionMap;
					return P;
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}