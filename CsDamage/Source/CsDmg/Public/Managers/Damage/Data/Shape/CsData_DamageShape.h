// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsData_DamageShape.generated.h"

// ValueType (NCsDamage::NValue::IValue)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// RangeType (NCsDamage::NRange::IRange)
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
			struct CSDMG_API IShape : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ValueType = NCsDamage::NValue::IValue;
					using RangeType = NCsDamage::NRange::IRange;
				};

			public:

				virtual ~IShape(){}

				/**
				*
				*
				* return
				*/
				virtual const _::RangeType* GetRange() const = 0;

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
				virtual float CalculateDamage(const _::ValueType* Value, const _::RangeType* Range, const FVector3f& Origin, const FVector3f& Point) const = 0;

				/**
				* Check if a given Point is within the bounds of an Origin.
				*
				* @param Origin		The center of the bounds.
				* @param Point		The location to evaluate if in bounds.
				* return			Whether the point is in bounds of the origin.
				*/
				virtual bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const = 0;

				/**
				* Check if the Direction from Origin is "Facing" the Point
				* 
				* @param Direction	The orientation.
				* @param Origin		The center.
				* @param Point		The location to evaluate.
				* return			Whether Direction from Origin is "Facing" the Point or not.
				*/
				virtual bool IsFacing(const FVector3f& Direction, const FVector3f& Origin, const FVector3f& Point) const = 0;
			};
		}
	}
}

using CsDamageShapeDataType = NCsDamage::NData::NShape::IShape;
using CsDmgShapeDataType = NCsDamage::NData::NShape::IShape;

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_DamageShape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// ValueType (NCsDamage::NValue::IValue)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// RangeType (NCsDamage::NRange::IRange)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

/**
* Interface to describe the shape of Damage. This should be used with 
* the interface "base" ICsData_Damage.
*/
class CSDMG_API ICsData_DamageShape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ValueType = NCsDamage::NValue::IValue;
		using RangeType = NCsDamage::NRange::IRange;
	};

public:

	/**
	*
	*
	* return
	*/
	virtual const _::RangeType* GetRange() const = 0;

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
	virtual float CalculateDamage(const _::ValueType* Value, const _::RangeType* Range, const FVector3f& Origin, const FVector3f& Point) const = 0;

	/**
	* Check if a given Point is within the bounds of an Origin.
	*
	* @param Origin		The center of the bounds.
	* @param Point		The location to evaluate if in bounds.
	* return			Whether the point is in bounds of the origin.
	*/
	virtual bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const = 0;

	/**
	* Check if the Direction from Origin is "Facing" the Point
	* 
	* @param Direction	The orientation.
	* @param Origin		The center.
	* @param Point		The location to evaluate.
	* return			Whether Direction from Origin is "Facing" the Point or not.
	*/
	virtual bool IsFacing(const FVector3f& Direction, const FVector3f& Origin, const FVector3f& Point) const = 0;
};