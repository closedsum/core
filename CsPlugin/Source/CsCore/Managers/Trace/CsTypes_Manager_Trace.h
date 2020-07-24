// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#pragma once

struct CSCORE_API FCsManagerTraceCountInfo
{
public:

	/** */
	int64 TotalCount;

	/** */
	TMap<FCsUniqueObjectId, int64> CountById;

	/** */
	int64 CountByType[(uint8)ECsTraceType::ECsTraceType_MAX];

	/** */
	int64 CountByMethod[(uint8)ECsTraceMethod::ECsTraceMethod_MAX];

	/** */
	int64 CountByQuery[(uint8)ECsTraceQuery::ECsTraceQuery_MAX];

	FCsManagerTraceCountInfo() :
		TotalCount(0ll),
		CountById()
	{
		// Type
		for (int64& Count : CountByType)
		{
			Count = 0ll;
		}
		// Method
		for (int64& Count : CountByMethod)
		{
			Count = 0ll;
		}
		// Query
		for (int64& Count : CountByQuery)
		{
			Count = 0ll;
		}
	}

	void Increment(const FCsUniqueObjectId& Id, const ECsTraceType& Type, const ECsTraceMethod& Method, const ECsTraceQuery& Query)
	{
		int64& Count = CountById.FindOrAdd(Id);
		++Count;

		++(CountByType[(uint8)Type]);
		++(CountByMethod[(uint8)Method]);
		++(CountByQuery[(uint8)Query]);

		++TotalCount;
	}

	void Reset()
	{
		TotalCount = 0ll;

		CountById.Reset();

		// Type
		for (int64& Count : CountByType)
		{
			Count = 0ll;
		}
		// Method
		for (int64& Count : CountByMethod)
		{
			Count = 0ll;
		}
		// Query
		for (int64& Count : CountByQuery)
		{
			Count = 0ll;
		}
	}
};

struct FCsResource_TraceRequest;

struct CSCORE_API FCsManagerTracePendingRequests
{
public:

	/** */
	TMap<FTraceHandle, FCsResource_TraceRequest*> RequestsByTraceHandle;

	/** */
	TMap<FCsUniqueObjectId, TMap<FTraceHandle, FCsResource_TraceRequest*>> RequestsById;

	/** */
	TMap<ECsTraceType, TMap<FTraceHandle, FCsResource_TraceRequest*>> RequestsByType;

	/** */
	TMap<ECsTraceMethod, TMap<FTraceHandle, FCsResource_TraceRequest*>> RequestsByMethod;

	/** */
	TMap<ECsTraceQuery, TMap<FTraceHandle, FCsResource_TraceRequest*>> RequestsByQuery;

	FCsManagerTracePendingRequests() :
		RequestsByTraceHandle(),
		RequestsById(),
		RequestsByType(),
		RequestsByMethod(),
		RequestsByQuery()
	{
	}
}