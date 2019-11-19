// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/UnitTest/CsUnitTest.h"

struct FCsRoutine;

class ICsUnitTest_Impl : public ICsUnitTest
{
public:

	virtual ~ICsUnitTest_Impl(){}

// ICsUnitTest
#pragma region
public:

	FORCEINLINE const FName& GetFName() const
	{
		return Name;
	}

	FORCEINLINE const FString& GetName() const
	{
		return NameAsString;
	}

	void Start();

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

#pragma endregion ICsUnitTest

protected:

	FName Name;
	FString NameAsString;

	bool bComplete;

	FName Start_Internal_Name;
	FString Start_Internal_NameAsString;

	virtual char Start_Internal(FCsRoutine* R) = 0;
};