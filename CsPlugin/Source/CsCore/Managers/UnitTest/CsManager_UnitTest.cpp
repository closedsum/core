// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsManager_UnitTest.h"
#include "CsCore.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

#include "Managers/UnitTest/CsGetManagerUnitTest.h"
#include "Managers/UnitTest/CsUnitTestSuite.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Time/CsGetManagerTime.h"
#endif // #if WITH_EDITOR

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

/*static*/ UCsManager_UnitTest* UCsManager_UnitTest::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerUnitTest(InRoot)->GetManager_UnitTest();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_UnitTest::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerUnitTest* GetManagerUnitTest = Get_GetManagerUnitTest(InRoot);

	UCsManager_UnitTest* Manager_UnitTest = NewObject<UCsManager_UnitTest>(InRoot, UCsManager_UnitTest::StaticClass(), TEXT("Manager_UnitTest_Singleton"), RF_Transient | RF_Public);

	GetManagerUnitTest->SetManager_UnitTest(Manager_UnitTest);

	Manager_UnitTest->SetMyRoot(InRoot);
	Manager_UnitTest->Initialize();
#else
	s_bShutdown = false;
	
	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_UnitTest>(GetTransientPackage(), UCsManager_UnitTest::StaticClass(), TEXT("Manager_UnitTest_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_UnitTest::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerUnitTest* GetManagerUnitTest = Get_GetManagerUnitTest(InRoot);
	UCsManager_UnitTest* Manager_UnitTest	  = GetManagerUnitTest->GetManager_UnitTest();
	Manager_UnitTest->CleanUp();

	GetManagerUnitTest->SetManager_UnitTest(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerUnitTest* UCsManager_UnitTest::Get_GetManagerUnitTest(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_UnitTest::Get_GetManagerUnitTest: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_UnitTest::Get_GetManagerUnitTest: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_UnitTest::Get_GetManagerUnitTest: Manager_Singleton is NULL."));

	ICsGetManagerUnitTest* GetManagerUnitTest = Cast<ICsGetManagerUnitTest>(Manager_Singleton);

	checkf(GetManagerUnitTest, TEXT("UCsManager_UnitTest::Get_GetManagerUnitTest: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerUnitTest."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerUnitTest;
}

#endif // #if WITH_EDITOR

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

	Suite->SetMyRoot(MyRoot);

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

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler					 = UCsCoroutineScheduler::Get(MyRoot);
	FCsMemoryResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(UpdateGroup);
	FCsCoroutinePayload* Payload						 = PayloadContainer->Get();

	Payload->Coroutine.BindUObject(this, &UCsManager_UnitTest::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsManagerUnitTestCached::Name::Start_Internal);
	Payload->SetNameAsString(NCsManagerUnitTestCached::Str::Start_Internal);

	UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: Starting Unit Test Suites."));
	UE_LOG(LogCs, Warning, TEXT("UCsManager_UnitTest::Start: - Processing %d Suites."), Suites.Num());

	Scheduler->Start(Payload);
}

char UCsManager_UnitTest::Start_Internal(FCsRoutine* R)
{
	int32& SuiteIndex		= R->GetValue_Indexer(CS_FIRST);
	ICsUnitTestSuite* Suite = Suites[SuiteIndex];

	const FCsTime& CurrentTime = UCsManager_Time::Get(MyRoot)->GetTime(R->Group);
	FCsTime& StartTime		   = R->GetValue_Timer(CS_FIRST);

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