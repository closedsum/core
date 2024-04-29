// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "UObject/NameTypes.h"

#include "CsEnumStruct.generated.h"

USTRUCT(BlueprintType)
struct CSENUM_API FECsEnum
{
	GENERATED_USTRUCT_BODY()

private:
	
	static const FName Invalid;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
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
