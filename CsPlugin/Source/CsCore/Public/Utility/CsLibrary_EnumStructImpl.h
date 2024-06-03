// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/NameTypes.h"

class UStruct;

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			namespace NImpl
			{
				struct CSCORE_API FLibrary final
				{
				public:

					static void ConditionalAddLayout(const FName& EnumName, const TArray<FName>& Names, UDataTable* DataTable);

					static void AddPropertyChange(const FName& EnumName, UStruct* EnumStruct);
				};
			}
		}
	}
}