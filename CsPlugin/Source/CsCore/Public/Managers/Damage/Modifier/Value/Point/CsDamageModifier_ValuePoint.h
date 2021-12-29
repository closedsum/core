// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			namespace NPoint
			{
				/**
				* Interface to describe modifying a damage value (implements the interfaces:
				* ValueType (NCsDamage::NValue::IValue) and ValuePointType (NCsDamage::NValue::NPoint::IPoint)).
				*/
				struct CSCORE_API IPoint : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IPoint(){}
				};
			}
		}
	}
}