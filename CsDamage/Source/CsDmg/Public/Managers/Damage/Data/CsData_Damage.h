// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Damage.h"

#include "CsData_Damage.generated.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NData
	{
		/**
		* Interface to describe Damage. Other interfaces can be "added" on top of this to
		* expose more functionality (i.e. NCsDamage::NShape::IShape, ... etc)
		*/
		struct CSDMG_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			// Allow clearer names without name collisions
			struct _
			{
				using ValueType = NCsDamage::NValue::IValue;
			};

		public:

			virtual ~IData(){}

			/**
			* Get the amount of damage.
			*
			* return Damage Value.
			*/
			virtual const _::ValueType* GetValue() const = 0;

			/**
			* Get the type of damage.
			*
			* return Damage Type.
			*/
			virtual const FECsDamageType& GetType() const = 0;
		};
	}
}

using CsDamageDataType = NCsDamage::NData::IData;

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

/**
* Interface to describe Damage. Other interfaces can be "added" on top of this to 
* expose more functionality (i.e. ICsData_DamageShape, ... etc)
*/
class CSDMG_API ICsData_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ValueType = NCsDamage::NValue::IValue;
	};

public:

	/**
	* Get the amount of damage.
	* 
	* return Damage Value.
	*/
	virtual const _::ValueType* GetValue() const = 0;

	/**
	* Get the type of damage.
	*
	* return Damage Type.
	*/
	virtual const FECsDamageType& GetType() const = 0;
};