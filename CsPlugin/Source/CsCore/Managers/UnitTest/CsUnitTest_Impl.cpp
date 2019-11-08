// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UnitTest/CsUnitTest_Impl.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

void ICsUnitTest_Impl::Start()
{
	const FERsTimeGroup& TimeGroup = NRsTimeGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler					 = UCsCoroutineScheduler::Get();
	FCsMemoryResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(TimeGroup);
	FCsCoroutinePayload* Payload						 = PayloadContainer->Get();

	Payload->Coroutine.BindRaw(this, &ICsUnitTest_Impl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get()->GetTime(TimeGroup);
	Payload->Owner.SetOwner(this);
	Payload->bPerformFirstRun = true;
	Payload->Name			  = Start_Internal_Name;
	Payload->NameAsString	  = Start_Internal_NameAsString;

	UE_LOG(LogCs, Warning, TEXT("%s::Start: Starting Unit Test."), *NameAsString);

	Scheduler->Start(Payload);
}