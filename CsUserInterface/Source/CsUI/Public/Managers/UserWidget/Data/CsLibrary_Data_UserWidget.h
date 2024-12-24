// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
// Library
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsUserWidget
{
	namespace NData
	{
		namespace NLibrary
		{
			using DataType = NCsUserWidget::NData::IData;

			/**
			*/
			struct CSUI_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
			{
			};
		}
	}
}