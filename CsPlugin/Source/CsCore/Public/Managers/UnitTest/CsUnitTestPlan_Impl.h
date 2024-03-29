// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/UnitTest/CsUnitTestPlan.h"

class ICsUnitTest;
class UObject;
struct FCsRoutine;

class CSCORE_API FCsUnitTestPlan_Impl : public ICsUnitTestPlan
{
public:

	FCsUnitTestPlan_Impl();
	virtual ~FCsUnitTestPlan_Impl();

// ICsUnitTestPlan
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

protected:

	void Add(ICsUnitTest* Test);

public:

	FORCEINLINE const ICsUnitTest* GetCurrentTest() const
	{
		return CurrentTest;
	}

	void Start();

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

#pragma endregion ICsUnitTestPlan

protected:

	FName Name_Internal;
	FString Name;

	FName DisplayFName;
	FString DisplayName;

	UObject* MyRoot;

	TMap<FName, ICsUnitTest*> TestMap;
	TArray<ICsUnitTest*> Tests;

	ICsUnitTest* CurrentTest;

public:

	template<typename UnitTestType>
	void Add()
	{
		static_assert(std::is_base_of<ICsUnitTest, UnitTestType>(), "FCsUnitTestPlan_Impl::Add: UnitTestType does NOT implement interface: ICsUnitTest.");

		UnitTestType* Test = new UnitTestType();

		Add(Test);
	}

protected:

	FName Start_Internal_FName;
	FString Start_Internal_Name;

	char Start_Internal(FCsRoutine* R);

	bool bComplete;
};