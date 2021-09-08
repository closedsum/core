// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSUI_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
		{
		};

	#undef DataType
	}
}