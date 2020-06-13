// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEnum.generated.h"
#pragma once

#define CS_ENUM_MAX_NAME_LENGTH 1024
#define CS_ENUM_MAX_DISPLAY_NAME_LENGTH 1024

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name_Internal;

	FECsEnum() :
		Name(),
		DisplayName(),
		Name_Internal(NAME_None)
	{
	}

	virtual ~FECsEnum(){}

	FORCEINLINE operator FString() const
	{
		return Name;
	}

	FORCEINLINE friend bool operator==(const FString& Lhs, const FECsEnum& Rhs)
	{
		return Lhs == Rhs.Name;
	}

	FORCEINLINE friend bool operator==(const FECsEnum& Lhs, const FString& Rhs)
	{
		return Lhs.Name == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const FECsEnum& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE virtual FString ToString() const
	{
		return TEXT("Name: ") + Name;
	}

	FORCEINLINE const FString& GetName() const 
	{
		return Name;
	}

	FORCEINLINE const FName& GetFName() const 
	{
		return Name_Internal;
	}

	FORCEINLINE const FString& GetDisplayName() const 
	{
		return DisplayName;
	}

	FORCEINLINE const TCHAR* ToChar() const
	{
		return *Name;
	}

	FORCEINLINE const TCHAR* DisplayNameToChar() const
	{
		return *DisplayName;
	}
};
