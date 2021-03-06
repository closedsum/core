// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEnum.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum
{
	GENERATED_USTRUCT_BODY()

private:
	
	static const FName Invalid;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name_Internal;

	FECsEnum() :
		Name_Internal(Invalid)
	{
	}

	virtual ~FECsEnum(){}

	FORCEINLINE bool operator==(const FECsEnum& B) const
	{
		return Name_Internal == B.Name_Internal;
	}

	FORCEINLINE bool operator!=(const FECsEnum& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void SetFName(const FName& InName)
	{
		Name_Internal = InName;
	}

	FORCEINLINE const FName& GetFName() const 
	{
		return Name_Internal;
	}

	FORCEINLINE bool IsValid() const
	{
		return Name_Internal != Invalid;
	}
};
