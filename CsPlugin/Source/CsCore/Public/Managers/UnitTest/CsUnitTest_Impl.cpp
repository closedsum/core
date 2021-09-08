// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsUnitTest_Impl.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

#include "UObject/Object.h"

ICsUnitTest_Impl::ICsUnitTest_Impl()
{
	Name		  = TEXT("ICsUnitTest_Impl");
	Name_Internal = FName(*Name);

	DisplayName  = TEXT("Unit Test Impl");
	DisplayFName = FName(*DisplayName);

	MyRoot = nullptr;

	bComplete = false;
}

// ICsUnitTest
#pragma region

void ICsUnitTest_Impl::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

void ICsUnitTest_Impl::Start()
{
	bComplete = false;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler		= UCsCoroutineScheduler::Get(MyRoot);
	NCsCoroutine::NPayload::FImpl* Payload	= Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindRaw(this, &ICsUnitTest_Impl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);

	Payload->SetName(Start_Internal_Name);
	Payload->SetFName(Start_Internal_FName);

	UE_LOG(LogTemp, Log, TEXT("%s: Starting Unit Test."), *DisplayName);

	Scheduler->Start(Payload);
}

#pragma endregion ICsUnitTest