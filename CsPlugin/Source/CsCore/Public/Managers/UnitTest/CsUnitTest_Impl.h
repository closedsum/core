// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/UnitTest/CsUnitTest.h"

class UObject;
struct FCsRoutine;

class CSCORE_API ICsUnitTest_Impl : public ICsUnitTest
{
public:

	ICsUnitTest_Impl();
	virtual ~ICsUnitTest_Impl(){}

// ICsUnitTest
#pragma region
public:

	FORCEINLINE const FName& GetFName() const
	{
		return Name_Internal;
	}

	FORCEINLINE const FString& GetName() const
	{
		return Name;
	}

	FORCEINLINE const FName& GetDisplayFName() const
	{
		return DisplayFName;
	}

	FORCEINLINE const FString& GetDisplayName() const
	{
		return DisplayName;
	}

	void SetMyRoot(UObject* InRoot);

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

	void Start();

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

#pragma endregion ICsUnitTest

protected:

	FName Name_Internal;
	FString Name;

	FName DisplayFName;
	FString DisplayName;

	UObject* MyRoot;

	bool bComplete;

	FName Start_Internal_FName;
	FString Start_Internal_Name;

	virtual char Start_Internal(FCsRoutine* R) = 0;
};