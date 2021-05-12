// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Manager_Trace.h"

// Trace
#include "Managers/Trace/CsTraceRequest.h"
// UniqueObject
#include "UniqueObject/CsUniqueObject.h"

// FCsManagerTraceCountInfo
#pragma region

namespace NCsManagerTraceCountInfo
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsManagerTraceCountInfo, Increment);
		}
	}
}

#define RequestType NCsTrace::NRequest::FRequest
void FCsManagerTraceCountInfo::Increment(RequestType* Request)
{
#undef RequestType

	using namespace NCsManagerTraceCountInfo::NCached;

	const FString& Context = Str::Increment;

	// Id
	if (ICsUniqueObject* UniqueObject = Request->UniqueObject)
	{
		const FCsUniqueObjectId& Id = UniqueObject->GetId();

		int64& Count = CountById.FindOrAdd(Id);
		++Count;
	}
	// Type
	++(CountByType[(uint8)Request->Type]);
	// Method
	++(CountByMethod[(uint8)Request->Method]);
	// Query
	++(CountByQuery[(uint8)Request->Query]);

	++TotalCount;
}

#pragma endregion FCsManagerTraceCountInfo

// FCsManagerTracePendingRequests
#pragma region

#define RequestType NCsTrace::NRequest::FRequest

RequestType* FCsManagerTracePendingRequests::Get(const FTraceHandle& Handle) const
{
	return RequestsByTraceHandle[Handle];
}

void FCsManagerTracePendingRequests::Add(RequestType* Request)
{
	const FTraceHandle& Handle = Request->Handle;

	// Handle
	RequestsByTraceHandle.Add(Handle, Request);
	// Id
	if (ICsUniqueObject* UniqueObject = Request->UniqueObject)
	{
		const FCsUniqueObjectId& Id = UniqueObject->GetId();

		TMap<FTraceHandle, RequestType*>& Map = RequestsById.FindOrAdd(Id);

		Map.Add(Handle, Request);
	}
	// Type
	RequestsByType[Request->Type].Add(Handle, Request);
	// Method
	RequestsByMethod[Request->Method].Add(Handle, Request);
	// Query
	RequestsByQuery[Request->Query].Add(Handle, Request);
}

void FCsManagerTracePendingRequests::Remove(RequestType* Request)
{
	const FTraceHandle& Handle = Request->Handle;

	// Handle
	RequestsByTraceHandle.Remove(Handle);
	// Id
	if (ICsUniqueObject* UniqueObject = Request->UniqueObject)
	{
		const FCsUniqueObjectId& Id = UniqueObject->GetId();

		if (TMap<FTraceHandle, RequestType*>* Map = RequestsById.Find(Id))
		{
			Map->Remove(Handle);
		}
	}
	// Type
	RequestsByType[Request->Type].Remove(Handle);
	// Method
	RequestsByMethod[Request->Method].Remove(Handle);
	// Query
	RequestsByQuery[Request->Query].Remove(Handle);
}

#undef RequestType

#pragma endregion FCsManagerTracePendingRequests