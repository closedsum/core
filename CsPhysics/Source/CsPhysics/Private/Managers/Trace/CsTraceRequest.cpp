// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsTraceRequest.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "PhysicsEngine/PhysicsSettings.h"
// Object
#include "UniqueObject/CsUniqueObject.h"
// Components
#include "Components/CapsuleComponent.h"

#define RequestType NCsTrace::NRequest::FRequest
void FCsTraceRequest::CopyToRequestAsValue(RequestType* Request) const
{
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
#undef RequestType

bool FCsTraceRequest::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsPhysics::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsTraceType, ECsTraceType, Type)
	CS_IS_ENUM_VALID(EMCsTraceMethod, ECsTraceMethod, Method)
	CS_IS_ENUM_VALID(EMCsTraceQuery, ECsTraceQuery, Query)

	// Check Shape
	CS_IS_VALID(Shape)

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
		CS_IS_VALID(ObjectParams)
	}

	CS_IS_VALID(Params)
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
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NRequest::FRequest, SetShape);
			}
		}

		#define USING_NS_CACHED using namespace NCsTrace::NRequest::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsTrace::NRequest::NCached; \
			const FString& Context = Str::__FunctionName

		bool FRequest::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsTraceType, Type)
			CS_IS_ENUM_VALID_CHECKED(EMCsTraceMethod, Method)
			CS_IS_ENUM_VALID_CHECKED(EMCsTraceQuery, Query)

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
			if (Params.bReturnFaceIndex)
			{
				checkf(!UPhysicsSettings::Get()->bSuppressFaceRemapTable, TEXT("%s: Returning Face Index is DISABLED globally."));
			}
			return true;
		}

		bool FRequest::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsPhysics::FLog::Warning*/) const
		{
			CS_IS_ENUM_VALID(EMCsTraceType, ECsTraceType, Type)
			CS_IS_ENUM_VALID(EMCsTraceMethod, ECsTraceMethod, Method)
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
			if (Params.bReturnFaceIndex)
			{
				if (UPhysicsSettings::Get()->bSuppressFaceRemapTable)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Returning Face Index is DISABLED globally.")));
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

		void FRequest::SetShape(const UCapsuleComponent* Component)
		{
			SET_CONTEXT(SetShape);

			CS_IS_PENDING_KILL_CHECKED(Component)

			Shape.SetCapsule(Component->GetScaledCapsuleRadius(), Component->GetScaledCapsuleHalfHeight());
		}

		void FRequest::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}