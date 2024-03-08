// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;
class UStruct;

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			struct CSEDITOR_API FTool
			{
				static void DetermineChanges(TMap<FName, UStruct*>& OutStructMap);

				static void ResolveChanges(const TMap<FName, UStruct*>& StructMap, bool bForce = false);
			};
		}
	}
}