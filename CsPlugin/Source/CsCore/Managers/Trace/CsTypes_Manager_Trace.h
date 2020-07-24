// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#pragma once

struct FCsTraceRequest;

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

	void Increment(FCsTraceRequest* Reqeust);

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

struct FCsTraceRequest;

struct CSCORE_API FCsManagerTracePendingRequests
{
public:

	/** */
	TMap<FTraceHandle, FCsTraceRequest*> RequestsByTraceHandle;

	/** */
	TMap<FCsUniqueObjectId, TMap<FTraceHandle, FCsTraceRequest*>> RequestsById;

	/** */
	TMap<ECsTraceType, TMap<FTraceHandle, FCsTraceRequest*>> RequestsByType;

	/** */
	TMap<ECsTraceMethod, TMap<FTraceHandle, FCsTraceRequest*>> RequestsByMethod;

	/** */
	TMap<ECsTraceQuery, TMap<FTraceHandle, FCsTraceRequest*>> RequestsByQuery;

	FCsManagerTracePendingRequests() :
		RequestsByTraceHandle(),
		RequestsById(),
		RequestsByType(),
		RequestsByMethod(),
		RequestsByQuery()
	{
		// Type 
		for (const ECsTraceType& Type : EMCsTraceType::Get())
		{
			RequestsByType.Add(Type);
		}
		// Method
		for (const ECsTraceMethod& Method : EMCsTraceMethod::Get())
		{
			RequestsByMethod.Add(Method);
		}
		// Method
		for (const ECsTraceMethod& Method : EMCsTraceMethod::Get())
		{
			RequestsByMethod.Add(Method);
		}
	}

	FCsTraceRequest* Get(const FTraceHandle& Handle) const;

	void Add(FCsTraceRequest* Request);
	void Remove(FCsTraceRequest* Request);
};