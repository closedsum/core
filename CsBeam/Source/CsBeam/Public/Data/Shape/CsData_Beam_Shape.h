// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Beam_Shape.generated.h"

namespace NCsBeam
{
	namespace NData
	{
		namespace NShape
		{
			/**
			* Interface for describing any shape information (non collision) related to a Beam.
			*/
			struct CSBEAM_API IShape : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IShape() {}
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam_Shape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any shape information (non collision) related to a Beam.
*/
class CSBEAM_API ICsData_Beam_Shape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};