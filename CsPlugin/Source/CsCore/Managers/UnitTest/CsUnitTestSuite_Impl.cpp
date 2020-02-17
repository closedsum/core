// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsUnitTestSuite_Impl.h"
#include "CsCore.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// UnitTest
#include "Managers/UnitTest/CsUnitTest.h"

FCsUnitTestSuite_Impl::FCsUnitTestSuite_Impl()
{
	NameAsString = TEXT("FCsUnitTestSuite_Impl");
	Name		 = FName(*NameAsString);

	Start_Internal_NameAsString = NameAsString + TEXT("::Start_Internal");
	Start_Internal_Name			= FName(*Start_Internal_NameAsString);

	bComplete = false;
}

FCsUnitTestSuite_Impl::~FCsUnitTestSuite_Impl()
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

// ICsUnitTestSuite
#pragma region

void FCsUnitTestSuite_Impl::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

void FCsUnitTestSuite_Impl::Add(ICsUnitTest* Test)
{
	checkf(Test, TEXT("%s::Add: Test is NULL."), *NameAsString);

	const FName& TestName = Test->GetFName();

	Test->SetMyRoot(MyRoot);

	ICsUnitTest** TestPtr = TestMap.Find(TestName);

	checkf(!TestPtr, TEXT("%s::Add: Test: %s has already been added."), *NameAsString, *(Test->GetName()));

	TestMap.Add(TestName, Test);
	Tests.Add(Test);
}

void FCsUnitTestSuite_Impl::Start()
{
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(MyRoot);
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(UpdateGroup);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindRaw(this, &FCsUnitTestSuite_Impl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);

	Payload->SetName(Start_Internal_Name);
	Payload->SetNameAsString(Start_Internal_NameAsString);

	UE_LOG(LogCs, Warning, TEXT("%s::Start: Starting Unit Tests."), *NameAsString);
	UE_LOG(LogCs, Warning, TEXT("%s::Start: - Processing %d Tests."), *NameAsString, Tests.Num());

	Scheduler->Start(Payload);
}

#pragma endregion ICsUnitTestSuite

char FCsUnitTestSuite_Impl::Start_Internal(FCsRoutine* R)
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
		UE_LOG(LogCs, Warning, TEXT("%s::Start: Starting Test[%d/%d]: %s."), *NameAsString, TestIndex + 1, Tests.Num(), *(Test->GetName()));

		Test->Start();

		CS_COROUTINE_WAIT_UNTIL(R, Test->IsComplete());

		UE_LOG(LogCs, Warning, TEXT("%s::Start: Completed Test[%d/%d]: %s in %f seconds."), *NameAsString, TestIndex + 1, Tests.Num(), *(Test->GetName()), (float)ElapsedTime.Timespan.GetTotalSeconds());

		++TestIndex;
	} while (TestIndex < Tests.Num());

	bComplete = true;

	CS_COROUTINE_END(R);
}