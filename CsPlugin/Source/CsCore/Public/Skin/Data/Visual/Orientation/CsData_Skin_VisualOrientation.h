// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_VisualOrientation.generated.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NOrientation
			{
				/**
				* Interface for determining the Orientation (Rotation) of the visual Skin.
				* The default Orientation is FRotator(0.0f, 0.0f, 0.0f).
				*/
				struct CSCORE_API IOrientation : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IOrientation() {}

					/**
					*/
					virtual const FRotator3f& GetRotation() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualOrientation : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the Orientation (Rotation) of the visual Skin.
* The default Orientation is FRotator(0.0f, 0.0f, 0.0f).
*/
class CSCORE_API ICsData_Skin_VisualOrientation : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FRotator3f& GetRotation() const = 0;
};