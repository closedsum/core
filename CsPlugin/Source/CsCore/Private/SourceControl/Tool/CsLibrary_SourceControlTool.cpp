// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "SourceControl/Tool/CsLibrary_SourceControlTool.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "SourceControl/Tool/CsGetSourceControlTool.h"
// Engine
#include "Engine/Engine.h"

namespace NCsSourceControl
{
	namespace NTool
	{
		bool FLibrary::CheckOutFileChecked(const FString& Context, const FString& InFile, bool bSilent/*=false*/)
		{
			ICsGetSourceControlTool* GetSourceControlTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetSourceControlTool);
			CsSourceControlToolType* SourceControlTool	  = GetSourceControlTool->GetSourceControlTool(); 
			
			return SourceControlTool->CheckOutFile(InFile, false);
		}
	}
}