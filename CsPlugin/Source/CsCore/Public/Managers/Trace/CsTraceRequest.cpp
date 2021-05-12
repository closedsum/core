// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTraceRequest.h"

#include "UniqueObject/CsUniqueObject.h"

namespace NCsTraceRequest
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(Type, "Type");
			CS_DEFINE_CACHED_STRING(Method, "Method");
			CS_DEFINE_CACHED_STRING(Query, "Query");
		}
	}
}

bool FCsTraceRequest::IsValidChecked(const FString& Context) const
{
	using namespace NCsTraceRequest::NCached;

	// Check Type is Valid
	check(EMCsTraceType::Get().IsValidEnumChecked(Context, Str::Type, Type));
	// Check Method is Valid
	check(EMCsTraceMethod::Get().IsValidEnumChecked(Context, Str::Method, Method));
	// Check Query is Valid
	check(EMCsTraceQuery::Get().IsValidEnumChecked(Context, Str::Query, Query));

	// Check Shape
	if (Type == ECsTraceType::Sweep)
	{
		checkf(!Shape.IsLine(), TEXT("%s: Shape should be Box, Sphere, or Capsule"), *Context);
	}
	// Check ObjectParams
	if (Query == ECsTraceQuery::ObjectType)
	{
		checkf(ObjectParams.IsValid(), TEXT("%s: ObjectParams is NOT Valid."), *Context);
	}
	return true;
}

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

namespace NCsTrace
{
	namespace NRequest
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_STRING(Type, "Type");
				CS_DEFINE_CACHED_STRING(Method, "Method");
				CS_DEFINE_CACHED_STRING(Query, "Query");
			}
		}

		bool FRequest::IsValidChecked(const FString& Context) const
		{
			using namespace NCsTrace::NRequest::NCached;

			// Check Type is Valid
			check(EMCsTraceType::Get().IsValidEnumChecked(Context, Str::Type, Type));
			// Check Method is Valid
			check(EMCsTraceMethod::Get().IsValidEnumChecked(Context, Str::Method, Method));
			// Check Query is Valid
			check(EMCsTraceQuery::Get().IsValidEnumChecked(Context, Str::Query, Query));

			// Check Shape
			if (Type == ECsTraceType::Sweep)
			{
				checkf(!Shape.IsLine(), TEXT("%s: Shape should be Box, Sphere, or Capsule"), *Context);
			}
			// Check ObjectParams
			if (Query == ECsTraceQuery::ObjectType)
			{
				checkf(ObjectParams.IsValid(), TEXT("%s: ObjectParams is NOT Valid."), *Context);
			}
			return true;
		}

		void FRequest::SetCaller(UObject* InCaller)
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

		UObject* FRequest::GetCaller() const
		{
			return Caller.IsValid() ? Caller.Get() : nullptr;
		}

		void FRequest::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}