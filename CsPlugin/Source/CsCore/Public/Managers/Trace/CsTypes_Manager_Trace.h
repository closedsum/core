// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Trace/CsTypes_Trace.h"
#include "UniqueObject/CsTypes_UniqueObject.h"

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

namespace NCsTrace
{
	namespace NManager
	{
		struct CSCORE_API FCountInfo
		{
		#define RequestType NCsTrace::NRequest::FRequest

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

			FCountInfo() :
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

			void Increment(RequestType* Reqeust);

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

		#undef RequestType
		};
	}
}

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

namespace NCsTrace
{
	namespace NManager
	{
		struct CSCORE_API FPendingRequests
		{
		#define RequestType NCsTrace::NRequest::FRequest

		public:

			/** */
			TMap<FTraceHandle, RequestType*> RequestsByTraceHandle;

			/** */
			TMap<FCsUniqueObjectId, TMap<FTraceHandle, RequestType*>> RequestsById;

			/** */
			TMap<ECsTraceType, TMap<FTraceHandle, RequestType*>> RequestsByType;

			/** */
			TMap<ECsTraceMethod, TMap<FTraceHandle, RequestType*>> RequestsByMethod;

			/** */
			TMap<ECsTraceQuery, TMap<FTraceHandle, RequestType*>> RequestsByQuery;

			FPendingRequests() :
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

			RequestType* Get(const FTraceHandle& Handle) const;

			void Add(RequestType* Request);
			void Remove(RequestType* Request);

		#undef RequestType
		};
	}
}