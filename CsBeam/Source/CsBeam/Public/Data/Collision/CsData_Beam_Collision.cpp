// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Beam_Collision.h"
#include "CsBeam.h"

const FName NCsBeam::NData::NCollision::ICollision::Name = FName("NCsBeam::NData::NCollision::ICollision");

const FName ICsData_Beam_Collision::Name = FName("ICsData_Beam_Collision");

UCsData_Beam_Collision::UCsData_Beam_Collision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}