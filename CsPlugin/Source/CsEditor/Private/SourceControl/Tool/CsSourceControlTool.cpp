// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "SourceControl/Tool/CsSourceControlTool.h"

// SourceControl
#include "SourceControlHelpers.h"

namespace NCsSourceControl
{
	namespace NTool
	{
		FTool::FTool()
		{
		}

		FTool::~FTool()
		{
		}

		// CsSourceControlToolType (NCsSourceControl::NTool::ITool)
		#pragma region

		bool FTool::CheckOutFile(const FString& InFile, bool bSilent/*=false*/)
		{
			return USourceControlHelpers::CheckOutFile(InFile, bSilent);
		}

		#pragma endregion CsSourceControlToolType (NCsSourceControl::NTool::ITool)
	}
}