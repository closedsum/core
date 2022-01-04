// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_StatusEffect.h"

#include "CsData_StatusEffect.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		/**
		*/
		struct CSSE_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IData(){}

			/**
			*
			*
			* return
			*/
			virtual const TArray<FECsStatusEffect>& GetChildren() const = 0;
		};
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual const TArray<FECsStatusEffect>& GetChildren() const = 0;
};