// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "SourceControl/Tool/CsGetSourceControlTool.h"

namespace NCsSourceControl
{
	namespace NTool
	{
		struct CSEDITOR_API FTool : CsSourceControlToolType
		{
		protected:
			FTool();

			FTool(const FTool &) = delete;
			FTool(FTool &&) = delete;
		public:
			~FTool();

			FORCEINLINE static FTool& Get()
			{
				static FTool Instance;
				return Instance;
			}

			FORCEINLINE static FTool* GetPtr() { return &FTool::Get(); }

		// CsSourceControlToolType (NCsSourceControl::NTool::ITool)
		#pragma region
		public:

			bool CheckOutFile(const FString& InFile, bool bSilent=false);

		#pragma endregion CsSourceControlToolType (NCsSourceControl::NTool::ITool)
		};
	}
}

using CsSourceControlToolImpl = NCsSourceControl::NTool::FTool;