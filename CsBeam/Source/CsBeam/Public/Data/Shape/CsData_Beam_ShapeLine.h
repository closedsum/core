// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Shape/CsTypes_Beam_Shape.h"

#include "CsData_Beam_ShapeLine.generated.h"

namespace NCsBeam
{
	namespace NData
	{
		namespace NShape
		{
			/**
			* Interface for describing any shape information (non collision) related to a Beam.
			*/
			struct CSBEAM_API ILine : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ILine() {}

				virtual const float& GetLineLength() const = 0;
			}; 
		}
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam_ShapeLine : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any shape information (non collision) related to a Beam.
*/
class CSBEAM_API ICsData_Beam_ShapeLine : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	virtual const float& GetLineLength() const = 0;
};