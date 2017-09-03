// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "CsTypes.h"
#include "CsInputRequest.generated.h"

USTRUCT()
struct FCsInputWord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Completed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> OrInputs;

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		AndInputs.AddDefaulted();
		const int32 Index = AndInputs.Num() - 1;
		AndInputs[Index].Action = Action;
		AndInputs[Index].Event = Event;
		AndInputs[Index].Value = Value;
		AndInputs[Index].Location = Location;
		AndInputs[Index].Rotation = Rotation;
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		OrInputs.AddDefaulted();
		const int32 Index = OrInputs.Num() - 1;
		OrInputs[Index].Action = Action;
		OrInputs[Index].Event = Event;
		OrInputs[Index].Value = Value;
		OrInputs[Index].Location = Location;
		OrInputs[Index].Rotation = Rotation;
	}
};

USTRUCT()
struct FCsInputPhrase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Completed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputWord> Words;

	void AddAndInputToWord(const int32 &Index, const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; I++)
			{
				Words.AddDefaulted();
			}
		}
		Words[Index].AddAndInput(Action, Event, Value, Location, Rotation);
	}

	void AddOrInputToWord(const int32 &Index, const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; I++)
			{
				Words.AddDefaulted();
			}
		}
		Words[Index].AddOrInput(Action, Event, Value, Location, Rotation);
	}
};


UCLASS()
class CSCORE_API UCsInputRequest : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Completed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputPhrase> Phrases;

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void ProcessInput(FCsInputFrame &InputFrame);
};