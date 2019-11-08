// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/UnitTest/CsUnitTestSuite.h"

class ICsUnitTest;
struct FCsRoutine;

class CSCORE_API FCsUnitTestSuite_Impl : public ICsUnitTestSuite
{
public:

	FCsUnitTestSuite_Impl();
	virtual ~FCsUnitTestSuite_Impl();

// ICsUnitTestSuite
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

protected:

	void Add(ICsUnitTest* Test);

public:

	void Start();

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

#pragma endregion ICsUnitTestSuite

protected:

	FName Name;
	FString NameAsString;

	TMap<FName, ICsUnitTest*> TestMap;
	TArray<ICsUnitTest*> Tests;

public:

	template<typename UnitTestType>
	void Add()
	{
		static_assert(std::is_base_of<ICsUnitTest, UnitTestType>(), "FCsUnitTestSuite_Impl::Add: UnitTestType does NOT implement interface: ICsUnitTest.");

		UnitTestType* Test = new UnitTestType();

		Add(Test);
	}

protected:

	FName Start_Internal_Name;
	FString Start_Internal_NameAsString;

	char Start_Internal(FCsRoutine* R);

	bool bComplete;
};