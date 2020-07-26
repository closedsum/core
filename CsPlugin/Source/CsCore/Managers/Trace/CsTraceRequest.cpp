// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTraceRequest.h"

#include "UniqueObject/CsUniqueObject.h"

void FCsTraceRequest::SetCaller(UObject* InCaller)
{
	Caller = InCaller;

	UClass* Class = InCaller->GetClass();

	if (Class->ImplementsInterface(UCsUniqueObject::StaticClass()))
	{
		// Interface
		if (ICsUniqueObject* Interface = Cast<ICsUniqueObject>(InCaller))
		{
			UniqueObject = Interface;
		}
		// Script Interface
	}
}

UObject* FCsTraceRequest::GetCaller() const
{
	return Caller.IsValid() ? Caller.Get() : nullptr;
}

void FCsTraceRequest::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}