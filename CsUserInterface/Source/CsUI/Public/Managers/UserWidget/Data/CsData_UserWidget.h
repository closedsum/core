// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_UserWidget.generated.h"

namespace NCsUserWidget
{
	namespace NData
	{
		/**
		*
		*/
		struct CSUI_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IData() {}
		};
	}
}

UINTERFACE(BlueprintType)
class CSUI_API UCsData_UserWidget : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsData_UserWidget : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};