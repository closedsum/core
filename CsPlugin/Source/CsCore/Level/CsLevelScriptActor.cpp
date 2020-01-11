// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Level/CsLevelScriptActor.h"
#include "CsCore.h"

ACsLevelScriptActor::ACsLevelScriptActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Editor
#pragma region
#if WITH_EDITOR

void ACsLevelScriptActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// Payload
	{
		// Payload.DataTable
		/*
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsLevelScriptActor, Payload) &&
			MemberPropertyName == GET_MEMBER_NAME_CHECKED(FCsPayload, DataTable))
		{

		}
		*/
	}

	Super::PostEditChangeProperty(e);
}

void ACsLevelScriptActor::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// Payload
	{
		// Payload.DataTables[Index]
		{
			const int32 Index = e.GetArrayIndex(TEXT("DataTables"));

			if (Index != INDEX_NONE)
			{
				FCsPayload_DataTable& Entry = Payload.DataTables[Index];

				if (Entry.IsValid())
					Entry.Populate();
				else
					Entry.Reset();
				Payload.Populate();
			}
		}
	}
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR
#pragma endregion Editor