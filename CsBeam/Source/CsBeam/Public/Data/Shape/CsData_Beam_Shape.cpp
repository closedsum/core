// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Shape/CsData_Beam_Shape.h"
#include "CsBeam.h"

const FName NCsBeam::NData::NShape::IShape::Name = FName("NCsBeam::NData::NShape::IShape");

const FName ICsData_Beam_Shape::Name = FName("ICsData_Beam_Shape");

UCsData_Beam_Shape::UCsData_Beam_Shape(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}