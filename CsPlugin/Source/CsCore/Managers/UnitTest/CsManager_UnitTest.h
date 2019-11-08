// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Coroutine/CsRoutine.h"
#include "CsManager_UnitTest.generated.h"

class ICsUnitTestSuite;

UCLASS(transient)
class CSCORE_API UCsManager_UnitTest : public UObject
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

#pragma endregion UObject Interface

// Singleton
#pragma region
public:

	static UCsManager_UnitTest* Get();

	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_UnitTest* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

protected:

	TMap<FName, ICsUnitTestSuite*> SuiteMap;
	TArray<ICsUnitTestSuite*> Suites;

public:

	template<typename UnitTestSuiteType>
	void Add()
	{
		static_assert(std::is_base_of<ICsUnitTestSuite, UnitTestSuiteType>(), "UCsManager_UnitTest::Add: UnitTestSuiteType does NOT implement interface: ICsUnitTestSuite.");

		UnitTestSuiteType* Suite = new UnitTestSuiteType();

		Add(Suite);
	}

protected:

	void Add(ICsUnitTestSuite* Suite);
	
public:

	void Start();
	//void Start(const FName& Name);

protected:

	char Start_Internal(FCsRoutine* R);

// Exec
#pragma region
public:

	UFUNCTION(Exec)
	void StartUnitTestSuites();

#pragma endregion Exec
};