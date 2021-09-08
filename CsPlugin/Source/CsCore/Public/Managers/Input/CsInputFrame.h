// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsInputFrame.generated.h"
#pragma once

/**
*
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTime Time;

	TArray<FCsInput*> Inputs;

	FCsInputFrame() :
		Time(),
		Inputs()
	{
	}

	FORCEINLINE FCsInputFrame& operator=(const FCsInputFrame& B)
	{
		Time = B.Time;

		Inputs.Reset(FMath::Max(Inputs.Num(), B.Inputs.Num()));

		for (FCsInput* Input : B.Inputs)
		{
			Inputs.Add(Input);
		}
		return *this;
	}

	void Init(const FCsTime& InTime)
	{
		Time = InTime;

		for (FCsInput* Input : Inputs)
		{
			Input->QueueDeallocate();
		}
		Inputs.Reset(Inputs.Max());
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action)
	{
		for (FCsInput* Input : Inputs)
		{
			if (Input->Action == Action)
				return Input;
		}
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action, const ECsInputEvent& Event)
	{
		if (FCsInput* Input = GetInput(Action))
			return Input->Event == Event ? Input : nullptr;
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events)
	{
		if (FCsInput* Input = GetInput(Action))
			return Events.Find(Input->Event) != INDEX_NONE ? Input : nullptr;
		return nullptr;
	}
};