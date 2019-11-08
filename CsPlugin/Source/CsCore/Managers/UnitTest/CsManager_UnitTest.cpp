// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/RsManager_UnitTest.h"
#include "RsCore.h"
#include "RsCVars.h"

// Coroutine
#include "Coroutine/RsCoroutineScheduler.h"
// Managers
#include "Managers/Time/RsManager_Time.h"

#include "Managers/UnitTest/RsUnitTestSuite.h"

// static initializations
UCsManager_UnitTest* UCsManager_UnitTest::s_Instance;
bool UCsManager_UnitTest::s_bShutdown = false;

namespace NCsManagerUnitTestCached
{
	namespace Str
	{
		const FString Start_Internal = TEXT("UCsManager_UnitTest::Start_Internal");
	}

	namespace Name
	{
		const FName Start_Internal = FName("UCsManager_UnitTest::Start_Internal");
	}
}

UCsManager_UnitTest::UCsManager_UnitTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

bool UCsManager_UnitTest::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	return Super::ProcessConsoleExec(Cmd, Ar, Executor);
}

#pragma endregion UObject Interface

// Singleton
#pragma region

/*static*/ UCsManager_UnitTest* UCsManager_UnitTest::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_UnitTest>(GetTransientPackage(), UCsManager_UnitTest::StaticClass(), TEXT("Manager_UnitTest_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ void UCsManager_UnitTest::Init()
{
	s_bShutdown = false;
	UCsManager_UnitTest::Get();
}

/*static*/ void UCsManager_UnitTest::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_UnitTest::Initialize()
{
}

void UCsManager_UnitTest::CleanUp()
{
	for (TPair<FName, ICsUnitTestSuite*>& Pair : SuiteMap)
	{
		Pair.Value = nullptr;
	}
	SuiteMap.Reset();

	const int32 Count = Suites.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ICsUnitTestSuite* Suite = Suites[I];
		delete Suite;
		Suites[I] = nullptr;
	}
	Suites.Reset();
	
}

#pragma endregion Singleton

void UCsManager_UnitTest::Add(ICsUnitTestSuite* Suite)
{
	checkf(Suite, TEXT("UCsManager_UnitTest::Add: Suite is NULL."));

	const FName& Name = Suite->GetFName();

	ICsUnitTestSuite** SuitePtr = SuiteMap.Find(Name);

	checkf(!SuitePtr, TEXT("UCsManager_UnitTest::Add: Suite: %s has already been added."), *(Suite->GetName()));

	SuiteMap.Add(Name, Suite);
	Suites.Add(Suite);
}

void UCsManager_UnitTest::Start()
{
	/*
	ICsUnitTestSuite** SuitePtr = SuiteMap.Find(Name);

	if (!SuitePtr)
	{
		return;
	}
	*/

	const FECsTimeGroup& TimeGroup = NCsTimeGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler					 = UCsCoroutineScheduler::Get();
	FCsMemoryResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(TimeGroup);
	FCsCoroutinePayload* Payload						 = PayloadContainer->Get();

	Payload->Coroutine.BindUObject(this, &UCsManager_UnitTest::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get()->GetTime(TimeGroup);
	Payload->Owner.SetObject(this);
	Payload->bPerformFirstRun = true;
	Payload->Name			  = NCsManagerUnitTestCached::Name::Start_Internal;
	Payload->NameAsString	  = NCsManagerUnitTestCached::Str::Start_Internal;

	UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: Starting Unit Test Suites."));
	UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: - Processing %d Suites."), Suites.Num());

	Scheduler->Start(Payload);
}

char UCsManager_UnitTest::Start_Internal(FCsRoutine* R)
{
	int32& SuiteIndex		= R->GetValue_Indexer(RS_FIRST);
	ICsUnitTestSuite* Suite = Suites[SuiteIndex];

	const FCsTime& CurrentTime = UCsManager_Time::Get()->GetTime(R->Group);
	FCsTime& StartTime		   = R->GetValue_Timer(RS_FIRST);

	FCsDeltaTime ElapsedTime = FCsDeltaTime::GetDeltaTime(CurrentTime, StartTime);

	CS_COROUTINE_BEGIN(R);

	StartTime = CurrentTime;

	do
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: Starting Suite[%d/%d]: %s."), SuiteIndex + 1, Suites.Num(), *(Suite->GetName()));

		Suite->Start();

		CS_COROUTINE_WAIT_UNTIL(R, Suite->IsComplete());

		UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: Completed Suite[%d/%d]: %s in %f seconds."), SuiteIndex + 1, Suites.Num(), *(Suite->GetName()), (float)ElapsedTime.Timespan.GetTotalSeconds());

		++SuiteIndex;
	} while (SuiteIndex < Suites.Num());

	CS_COROUTINE_END(R);
}

// Exec
#pragma region

void UCsManager_UnitTest::StartUnitTestSuites()
{
	Start();
}

#pragma endregion Exec