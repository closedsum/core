// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsManager_UnitTest.h"
#include "CsCore.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

#include "Managers/UnitTest/CsGetManagerUnitTest.h"
#include "Managers/UnitTest/CsUnitTestPlan.h"

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
	MyRoot = nullptr;

	PlanMap.Reset();
	Plans.Reset();

	CurrentPlan = nullptr;
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

/*static*/ void UCsManager_UnitTest::Init(UObject* InRoot, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerUnitTest* GetManagerUnitTest = Get_GetManagerUnitTest(InRoot);

	UCsManager_UnitTest* Manager_UnitTest = NewObject<UCsManager_UnitTest>(InOuter ? InOuter : InRoot, UCsManager_UnitTest::StaticClass(), TEXT("Manager_UnitTest_Singleton"), RF_Transient | RF_Public);

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
	for (TPair<FName, ICsUnitTestPlan*>& Pair : PlanMap)
	{
		Pair.Value = nullptr;
	}
	PlanMap.Reset();

	const int32 Count = Plans.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ICsUnitTestPlan* Plan = Plans[I];
		delete Plan;
		Plans[I] = nullptr;
	}
	Plans.Reset();
	
	CurrentPlan = nullptr;
}

#pragma endregion Singleton

void UCsManager_UnitTest::Add(ICsUnitTestPlan* Plan)
{
	checkf(Plan, TEXT("UCsManager_UnitTest::Add: Plan is NULL."));

	const FName& Name = Plan->GetFName();

	Plan->SetMyRoot(MyRoot);

	ICsUnitTestPlan** PlanPtr = PlanMap.Find(Name);

	checkf(!PlanPtr, TEXT("UCsManager_UnitTest::Add: Plan: %s has already been added."), *(Plan->GetName()));

	PlanMap.Add(Name, Plan);
	Plans.Add(Plan);
}

void UCsManager_UnitTest::Start()
{
	/*
	ICsUnitTestPlan** PlanPtr = PlanMap.Find(Name);

	if (!PlanPtr)
	{
		return;
	}
	*/

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(UpdateGroup);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindUObject(this, &UCsManager_UnitTest::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsManagerUnitTestCached::Name::Start_Internal);
	Payload->SetNameAsString(NCsManagerUnitTestCached::Str::Start_Internal);

	UE_LOG(LogCs, Log, TEXT("Starting Unit Test Plans."));
	UE_LOG(LogCs, Log, TEXT("- Processing %d Plans."), Plans.Num());

	Scheduler->Start(Payload);
}

char UCsManager_UnitTest::Start_Internal(FCsRoutine* R)
{
	int32& PlanIndex	  = R->GetValue_Indexer(CS_FIRST);
	ICsUnitTestPlan* Plan = Plans[PlanIndex];

	const FCsTime& CurrentTime = UCsManager_Time::Get(MyRoot)->GetTime(R->Group);
	FCsTime& StartTime		   = R->GetValue_Timer(CS_FIRST);

	FCsDeltaTime ElapsedTime = FCsDeltaTime::GetDeltaTime(CurrentTime, StartTime);

	CS_COROUTINE_BEGIN(R);

	StartTime = CurrentTime;

	do
	{
		UE_LOG(LogCs, Log, TEXT(""));
		UE_LOG(LogCs, Log, TEXT("Starting Plan[%d/%d]: %s."), PlanIndex + 1, Plans.Num(), *(Plan->GetDisplayName()));
		UE_LOG(LogCs, Log, TEXT(""));

		CurrentPlan = Plan;

		Plan->Start();

		CS_COROUTINE_WAIT_UNTIL(R, Plan->IsComplete());

		UE_LOG(LogCs, Log, TEXT(""));
		UE_LOG(LogCs, Log, TEXT("Completed Plan[%d/%d]: %s in %f seconds."), PlanIndex + 1, Plans.Num(), *(Plan->GetDisplayName()), (float)ElapsedTime.Timespan.GetTotalSeconds());

		++PlanIndex;
	} while (PlanIndex < Plans.Num());

	CurrentPlan = nullptr;

	CS_COROUTINE_END(R);
}

// Exec
#pragma region

void UCsManager_UnitTest::StartUnitTestPlans()
{
	Start();
}

#pragma endregion Exec