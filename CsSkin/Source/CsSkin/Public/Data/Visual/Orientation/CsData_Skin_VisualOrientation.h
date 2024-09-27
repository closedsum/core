// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
				struct CSSKIN_API IOrientation : public ICsGetInterfaceMap
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

using CsOrientationSkinDataType = NCsSkin::NData::NVisual::NOrientation::IOrientation;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualOrientation : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the Orientation (Rotation) of the visual Skin.
* The default Orientation is FRotator(0.0f, 0.0f, 0.0f).
*/
class CSSKIN_API ICsData_Skin_VisualOrientation : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FRotator3f& GetRotation() const = 0;
};