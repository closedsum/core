// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Beam_VisualStaticMesh.generated.h"
#pragma once

class UStaticMesh;

namespace NCsBeam
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				/**
				*/
				struct CSBEAM_API IStaticMesh : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IStaticMesh(){}

					virtual UStaticMesh* GetStaticMesh() const = 0;
				};
			}
		}
	}
}


UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam_VisualStaticMesh : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
*/
class CSBEAM_API ICsData_Beam_VisualStaticMesh : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual UStaticMesh* GetStaticMesh() const = 0;
};