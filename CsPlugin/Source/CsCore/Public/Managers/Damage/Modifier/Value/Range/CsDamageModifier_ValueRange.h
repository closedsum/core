// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			namespace NRange
			{
				/**
				* 
				*/
				struct CSCORE_API IRange : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IRange(){}
				};
			}
		}
	}
}