// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Beam.generated.h"

namespace NCsBeam
{
	namespace NData
	{
		/**
		*/
		struct CSBEAM_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

			/**
			*
			*
			* return
			*/
			virtual const float& GetLifeTime() const = 0;
		};
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsData_Beam : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const float& GetLifeTime() const = 0;
};