// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Trace.generated.h"

namespace NCsTrace
{
	namespace NData
	{
		/**
		*/
		struct CSPHYSICS_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IData() {}
		};
	}
}

UINTERFACE(BlueprintType)
class CSPHYSICS_API UCsData_Trace : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPHYSICS_API ICsData_Trace : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};