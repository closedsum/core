// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
// Library
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsUserWidget
{
	namespace NData
	{
	#define DataType NCsUserWidget::NData::IData

		/**
		*/
		struct CSUI_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
		{
		};

	#undef DataType
	}
}