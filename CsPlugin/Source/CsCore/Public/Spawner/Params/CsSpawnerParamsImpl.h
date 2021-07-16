// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParams.h"

#pragma once

struct FCsInterfaceMap;

namespace NCsSpawner
{
	namespace NParams
	{
	#define ParamsType NCsSpawner::NParams::IParams

		/**
		*/
		struct CSCORE_API FImpl final : public ParamsType
		{
		public:

			static const FName Name;

		#define CountParamsType NCsSpawner::NParams::FCount
		#define FrequencyParamsType NCsSpawner::NParams::FFrequency

		private:

			FCsInterfaceMap* InterfaceMap;

		public:

			// ParamsType (NCsSpawner::NParams::IParams)

			CountParamsType CountParams;

			FrequencyParamsType FrequencyParams;

			float TotalTime;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// ParamsType (NCsSpawner::NParams::IParams)
		#pragma region
		public:

			FORCEINLINE const CountParamsType& GetCountParams() const { return CountParams; }
			FORCEINLINE const FrequencyParamsType& GetFrequencyParams() const { return FrequencyParams; }
			FORCEINLINE const float& GetTotalTime() const { return TotalTime; }

		#pragma endregion ParamsType (NCsSpawner::NParams::IParams)

		#undef CountParamsType
		#undef FrequencyParamsType
		};

	#undef ParamsType
	}
}