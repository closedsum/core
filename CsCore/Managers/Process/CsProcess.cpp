// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsProcess.h"
#include "CsCore.h"

/*
namespace ECsProcessTest
{
	const FCsProcess Default = EMCsProcess::Get().Create(TEXT("Default"));
	const FCsProcess MAX = EMCsProcess::Get().Create(TEXT("MAX"));
}
*/

UCsProcess::UCsProcess(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Interface
#pragma region

void UCsProcess::Init(const int32 &Index, const FECsProcess &Type)
{
}

void UCsProcess::OnCreatePool()
{
}

void UCsProcess::Allocate(const int32 &Index, FCsProcessPayload* Payload)
{

}

void UCsProcess::DeAllocate()
{
}

#pragma endregion Interface

void UCsProcess::RunCommand(const FString &Command){}