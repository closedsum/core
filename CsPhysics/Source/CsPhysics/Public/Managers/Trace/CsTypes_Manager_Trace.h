// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Trace/CsTypes_Trace.h"
#include "WorldCollision.h"

// RequestType (NCsTrace::NRequest::FRequest)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

namespace NCsTrace
{
	namespace NManager
	{
		struct CSPHYSICS_API FCountInfo
		{
		private:

			using RequestType = NCsTrace::NRequest::FRequest;

		public:

			/** */
			int64 TotalCount;

			/** */
			TMap<uint32, int64> CountById;

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
		};
	}
}

// RequestType (NCsTrace::NRequest::FRequest0
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

namespace NCsTrace
{
	namespace NManager
	{
		struct CSPHYSICS_API FPendingRequests
		{
		private:

			using RequestType = NCsTrace::NRequest::FRequest;

		public:

			/** */
			TMap<FTraceHandle, RequestType*> RequestsByTraceHandle;

			/** */
			TMap<uint32, TMap<FTraceHandle, RequestType*>> RequestsById;

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
		};
	}
}