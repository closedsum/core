// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Time/CsTypes_Time.h"
#include "CsMacro_Namespace.h"

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsStatusEffect::NData::NTrigger::ITrigger
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStatusEffect, NData, NTrigger, ITrigger)

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		namespace NFrequency
		{
			struct CSSE_API FInfo
			{
			public:

			#define DataType NCsStatusEffect::NData::IData
			#define TriggerDataType NCsStatusEffect::NData::NTrigger::ITrigger

				DataType* Data;

				TriggerDataType* TriggerData;

				float TotalTime;

				FCsDeltaTime ElapsedTotalTime;

				bool bDelayComplete;

				FCsDeltaTime ElapsedDelayTime;

				FCsDeltaTime ElapsedIntervalTime;

				int32 Count;

				FInfo() :
					Data(nullptr),
					TriggerData(nullptr),
					TotalTime(0.0f),
					ElapsedTotalTime(),
					bDelayComplete(false),
					ElapsedDelayTime(),
					ElapsedIntervalTime(),
					Count(0)
				{
				}

				void SetData(DataType* InData);

				bool CanApply() const;

				void Increment();

				bool IsComplete() const;

				void Update(const FCsDeltaTime& DeltaTime);

				void Reset();

			#undef DataType
			#undef TriggerDataType
			};
		}
	}
}