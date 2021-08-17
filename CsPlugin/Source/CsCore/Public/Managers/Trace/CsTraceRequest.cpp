// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTraceRequest.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Object
#include "UniqueObject/CsUniqueObject.h"
// Components
#include "Components/CapsuleComponent.h"

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

#define RequestType NCsTrace::NRequest::FRequest
void FCsTraceRequest::CopyToRequestAsValue(RequestType* Request) const
{
#undef RequestType

	Request->StaleTime = StaleTime;
	Request->SetCaller(Caller);
	Request->bAsync = bAsync;
	Request->Type = Type;
	Request->Method = Method;
	Request->Query = Query;
	Request->Start = Start;
	Request->End = End;
	Request->Rotation = Rotation;
	Request->Channel = Channel;
	Request->ProfileName = ProfileName;
	Request->Shape = Shape.ToShape();
	Params.CopyToParams(Request->Params);
	ObjectParams.CopyToParams(Request->ObjectParams);
	ResponseParams.CopyToParams(Request->ResponseParams);

	Request->OnResponse_ScriptEvent = OnResponse_Event;
	Request->OnResponse_AsyncScriptEvent = OnResponse_AsyncEvent;
}

bool FCsTraceRequest::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	using namespace NCsTraceRequest::NCached;

	// Check Type is Valid
	CS_IS_ENUM_VALID(EMCsTraceType, ECsTraceType, Type)
	// Check Method is Valid
	CS_IS_ENUM_VALID(EMCsTraceMethod, ECsTraceMethod, Method)
	// Check Query is Valid
	CS_IS_ENUM_VALID(EMCsTraceQuery, ECsTraceQuery, Query)

	// Check Shape
	if (!Shape.IsValid(Context, Log))
		return false;

	if (Shape.IsLine() &&
		Start == End)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Start == End."), *Context));
		return false;
	}

	if (Type == ECsTraceType::Sweep)
	{
		if (!Shape.IsLine())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Shape should be Box, Sphere, or Capsule"), *Context));
			return false;
		}
	}
	// Check ObjectParams
	if (Query == ECsTraceQuery::ObjectType)
	{
		if (!ObjectParams.IsValid(Context, Log))
			return false;
	}

	if (!Params.IsValid(Context, Log))
		return false;
	return true;
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

			if (Shape.IsLine())
			{
				checkf(Start != End, TEXT("%s: Start == End."), *Context);
			}

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

		bool FRequest::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Type is Valid
			CS_IS_ENUM_VALID(EMCsTraceType, ECsTraceType, Type)
			// Check Method is Valid
			CS_IS_ENUM_VALID(EMCsTraceMethod, ECsTraceMethod, Method)
			// Check Query is Valid
			CS_IS_ENUM_VALID(EMCsTraceQuery, ECsTraceQuery, Query)

			if (Shape.IsLine() &&
				Start == End)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Start == End."), *Context));
				return false;
			}

			// Check Shape
			if (Type == ECsTraceType::Sweep)
			{
				if (!Shape.IsLine())
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Shape should be Box, Sphere, or Capsule"), *Context));
					return false;
				}
			}
			// Check ObjectParams
			if (Query == ECsTraceQuery::ObjectType)
			{
				if (!ObjectParams.IsValid())
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ObjectParams is NOT Valid."), *Context));
					return false;
				}
			}
			return true;
		}

		void FRequest::SetCaller(UObject* InCaller)
		{
			Caller = InCaller;

			if (InCaller)
			{
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
		}

		UObject* FRequest::GetCaller() const
		{
			return Caller.IsValid() ? Caller.Get() : nullptr;
		}

		void FRequest::SetShape(UCapsuleComponent* Component)
		{
			Shape.SetCapsule(Component->GetScaledCapsuleRadius(), Component->GetScaledCapsuleHalfHeight());
		}

		void FRequest::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}