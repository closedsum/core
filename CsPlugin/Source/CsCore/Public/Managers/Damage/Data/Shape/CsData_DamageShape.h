// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_DamageShape.generated.h"
#pragma once

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			/**
			* Interface to describe the shape of Damage. This should be used with
			* the interface "base" NCsDamage::NData::IData.
			*/
			struct CSCORE_API IShape : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsDamage::NValue::IValue ValueType;
				typedef NCsDamage::NRange::IRange RangeType;

			public:

				virtual ~IShape(){}

				/**
				*
				*
				* return
				*/
				virtual const RangeType* GetRange() const = 0;

				/**
				* Calculate damage given an origin and point.
				*
				* @param Value
				* @param Range
				* @param Origin		The center of the damage event.
				* @param Point		The location to evaluate for how much damage
				* return			Damage
				*
				*/
				virtual float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const = 0;

				/**
				* Check if a given Point is within the bounds of an Origin.
				*
				* @param Origin		The center of the bounds.
				* @param Point		The location to evaluate if in bounds.
				* return			Whether the point is in bounds of the origin.
				*/
				virtual bool IsInBounds(const FVector& Origin, const FVector& Point) const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_DamageShape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

/**
* Interface to describe the shape of Damage. This should be used with 
* the interface "base" ICsData_Damage.
*/
class CSCORE_API ICsData_DamageShape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	typedef NCsDamage::NValue::IValue ValueType;
	typedef NCsDamage::NRange::IRange RangeType;

public:

	/**
	*
	*
	* return
	*/
	virtual const RangeType* GetRange() const = 0;

	/**
	* Calculate damage given an origin and point.
	*
	* @param Value		
	* @param Range
	* @param Origin		The center of the damage event.
	* @param Point		The location to evaluate for how much damage
	* return			Damage
	*
	*/
	virtual float CalculateDamage(const ValueType* Value, const RangeType* Range, const FVector& Origin, const FVector& Point) const = 0;

	/**
	* Check if a given Point is within the bounds of an Origin.
	*
	* @param Origin		The center of the bounds.
	* @param Point		The location to evaluate if in bounds.
	* return			Whether the point is in bounds of the origin.
	*/
	virtual bool IsInBounds(const FVector& Origin, const FVector& Point) const = 0;
};