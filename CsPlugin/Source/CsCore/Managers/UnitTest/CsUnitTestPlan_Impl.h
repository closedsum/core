// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
		return Name;
	}

	FORCEINLINE const FString& GetName() const
	{
		return NameAsString;
	}

	void SetMyRoot(UObject* InRoot);

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

protected:

	void Add(ICsUnitTest* Test);

public:

	void Start();

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

#pragma endregion ICsUnitTestPlan

protected:

	FName Name;
	FString NameAsString;

	UObject* MyRoot;

	TMap<FName, ICsUnitTest*> TestMap;
	TArray<ICsUnitTest*> Tests;

public:

	template<typename UnitTestType>
	void Add()
	{
		static_assert(std::is_base_of<ICsUnitTest, UnitTestType>(), "FCsUnitTestPlan_Impl::Add: UnitTestType does NOT implement interface: ICsUnitTest.");

		UnitTestType* Test = new UnitTestType();

		Add(Test);
	}

protected:

	FName Start_Internal_Name;
	FString Start_Internal_NameAsString;

	char Start_Internal(FCsRoutine* R);

	bool bComplete;
};