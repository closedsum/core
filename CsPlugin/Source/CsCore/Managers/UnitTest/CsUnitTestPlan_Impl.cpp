// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	NameAsString = TEXT("FCsUnitTestPlan_Impl");
	Name		 = FName(*NameAsString);

	DisplayNameAsString = TEXT("Test Plan Impl");
	DisplayName			= FName(*DisplayNameAsString);

	Start_Internal_NameAsString = NameAsString + TEXT("::Start_Internal");
	Start_Internal_Name			= FName(*Start_Internal_NameAsString);

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
	MyRoot = InRoot;
}

void FCsUnitTestPlan_Impl::Add(ICsUnitTest* Test)
{
	checkf(Test, TEXT("%s::Add: Test is NULL."), *NameAsString);

	const FName& TestName = Test->GetFName();

	Test->SetMyRoot(MyRoot);

	ICsUnitTest** TestPtr = TestMap.Find(TestName);

	checkf(!TestPtr, TEXT("%s::Add: Test: %s has already been added."), *NameAsString, *(Test->GetName()));

	TestMap.Add(TestName, Test);
	Tests.Add(Test);
}

void FCsUnitTestPlan_Impl::Start()
{
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(UpdateGroup);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindRaw(this, &FCsUnitTestPlan_Impl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);

	Payload->SetName(Start_Internal_Name);
	Payload->SetNameAsString(Start_Internal_NameAsString);

	UE_LOG(LogCs, Warning, TEXT("%s: Starting Unit Tests."), *DisplayNameAsString);
	UE_LOG(LogCs, Warning, TEXT("- Processing %d Tests."), Tests.Num());
	UE_LOG(LogCs, Warning, TEXT(""));

	Scheduler->Start(Payload);
}

#pragma endregion ICsUnitTestPlan

char FCsUnitTestPlan_Impl::Start_Internal(FCsRoutine* R)
{
	int32& TestIndex  = R->GetValue_Indexer(CS_FIRST);
	ICsUnitTest* Test = Tests[TestIndex];

	const FCsTime& CurrentTime = UCsManager_Time::Get(Test->GetMyRoot())->GetTime(R->Group);
	FCsTime& StartTime		   = R->GetValue_Timer(CS_FIRST);

	FCsDeltaTime ElapsedTime = FCsDeltaTime::GetDeltaTime(CurrentTime, StartTime);

	CS_COROUTINE_BEGIN(R);

	StartTime = CurrentTime;

	do
	{
		UE_LOG(LogCs, Warning, TEXT(""));
		UE_LOG(LogCs, Warning, TEXT("Starting Test[%d/%d]: %s."), TestIndex + 1, Tests.Num(), *(Test->GetDisplayName()));
		UE_LOG(LogCs, Warning, TEXT(""));

		CurrentTest = Test;

		Test->Start();

		CS_COROUTINE_WAIT_UNTIL(R, Test->IsComplete());

		UE_LOG(LogCs, Warning, TEXT(""));
		UE_LOG(LogCs, Warning, TEXT("Completed Test[%d/%d]: %s in %f seconds."), *NameAsString, TestIndex + 1, Tests.Num(), *(Test->GetDisplayName()), (float)ElapsedTime.Timespan.GetTotalSeconds());

		++TestIndex;
	} while (TestIndex < Tests.Num());

	CurrentTest = nullptr;
	bComplete = true;

	CS_COROUTINE_END(R);
}