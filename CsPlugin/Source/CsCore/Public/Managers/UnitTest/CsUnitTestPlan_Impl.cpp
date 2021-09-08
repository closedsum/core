// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsUnitTestPlan_Impl.h"
#include "CsCore.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// UnitTest
#include "Managers/UnitTest/CsUnitTest.h"

FCsUnitTestPlan_Impl::FCsUnitTestPlan_Impl()
{
	Name		  = TEXT("FCsUnitTestPlan_Impl");
	Name_Internal = FName(*Name);

	DisplayName  = TEXT("Test Plan Impl");
	DisplayFName = FName(*DisplayName);

	MyRoot = nullptr;

	Start_Internal_Name  = Name + TEXT("::Start_Internal");
	Start_Internal_FName = FName(*Start_Internal_Name);

	bComplete = false;
}

FCsUnitTestPlan_Impl::~FCsUnitTestPlan_Impl()
{
	for (TPair<FName, ICsUnitTest*>& Pair : TestMap)
	{
		Pair.Value = nullptr;
	}
	TestMap.Reset();

	const int32 Count = Tests.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ICsUnitTest* Test = Tests[I];
		delete Test;
		Tests[I] = nullptr;
	}
	Tests.Reset();
}

// ICsUnitTestPlan
#pragma region

void FCsUnitTestPlan_Impl::SetMyRoot(UObject* InRoot)
{
	checkf(InRoot, TEXT("%s::SetMyRoot: InRoot is NULL."));

	MyRoot = InRoot;

	for (ICsUnitTest* Test : Tests)
	{
		Test->SetMyRoot(MyRoot);
	}
}

void FCsUnitTestPlan_Impl::Add(ICsUnitTest* Test)
{
	checkf(Test, TEXT("%s::Add: Test is NULL."), *Name);

	const FName& TestName = Test->GetFName();

	if (MyRoot)
		Test->SetMyRoot(MyRoot);

	ICsUnitTest** TestPtr = TestMap.Find(TestName);

	checkf(!TestPtr, TEXT("%s::Add: Test: %s has already been added."), *Name, *(Test->GetName()));

	TestMap.Add(TestName, Test);
	Tests.Add(Test);
}

void FCsUnitTestPlan_Impl::Start()
{
	CurrentTest = nullptr;
	bComplete   = false;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler		= UCsCoroutineScheduler::Get(MyRoot);
	NCsCoroutine::NPayload::FImpl* Payload	= Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindRaw(this, &FCsUnitTestPlan_Impl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);

	Payload->SetName(Start_Internal_Name);
	Payload->SetFName(Start_Internal_FName);

	UE_LOG(LogTemp, Log, TEXT("%s: Starting Unit Tests."), *DisplayName);
	UE_LOG(LogTemp, Log, TEXT("- Processing %d Tests."), Tests.Num());

	Scheduler->Start(Payload);
}

#pragma endregion ICsUnitTestPlan

char FCsUnitTestPlan_Impl::Start_Internal(FCsRoutine* R)
{
	int32& TestIndex  = R->GetValue_Int(CS_FIRST);
	ICsUnitTest* Test = Tests[TestIndex];

	const FCsTime& CurrentTime = UCsManager_Time::Get(MyRoot)->GetTime(R->GetGroup());
	FCsTime& StartTime		   = R->GetValue_Timer(CS_FIRST);

	FCsDeltaTime ElapsedTime = FCsDeltaTime::GetDeltaTime(CurrentTime, StartTime);

	CS_COROUTINE_BEGIN(R);

	do
	{
		StartTime = CurrentTime;

		UE_LOG(LogTemp, Log, TEXT(" "));
		UE_LOG(LogTemp, Log, TEXT("Starting Test[%d/%d]: %s."), TestIndex + 1, Tests.Num(), *(Test->GetDisplayName()));
		UE_LOG(LogTemp, Log, TEXT(" "));

		CurrentTest = Test;

		Test->Start();

		CS_COROUTINE_WAIT_UNTIL(R, Test->IsComplete());

		UE_LOG(LogTemp, Log, TEXT(" "));
		UE_LOG(LogTemp, Log, TEXT("Completed Test[%d/%d]: %s in %f seconds."), TestIndex + 1, Tests.Num(), *(Test->GetDisplayName()), (float)ElapsedTime.Timespan.GetTotalSeconds());

		++TestIndex;
	} while (TestIndex < Tests.Num());

	CurrentTest = nullptr;
	bComplete = true;

	CS_COROUTINE_END(R);
}