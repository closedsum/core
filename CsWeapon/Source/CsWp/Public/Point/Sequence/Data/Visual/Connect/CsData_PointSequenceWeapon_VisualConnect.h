// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Sequence/Types/CsTypes_PointSequenceWeapon_VisualConnect.h"

#include "CsData_PointSequenceWeapon_VisualConnect.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NData
			{
				namespace NVisual
				{
					namespace NConnect
					{
						/**
						*/
						struct CSWP_API IConnect : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

						#define ConnectVisualInfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::FInfo

							/**
							* Get the Visual Connect information.
							* 
							* return	Visual Connect information
							*/
							virtual const ConnectVisualInfoType& GetConnectVisualInfo() const = 0;

						#undef ConnectVisualInfoType
						};
					}
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointSequenceWeapon_VisualConnect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsData_PointSequenceWeapon_VisualConnect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
#define ConnectVisualInfoType NCsWeapon::NPoint::NSequence::NVisual::NConnect::FInfo

	/**
	* Get the Visual Connect information.
	*
	* return	Visual Connect information
	*/
	virtual const ConnectVisualInfoType& GetConnectVisualInfo() const = 0;

#undef ConnectVisualInfoType
};