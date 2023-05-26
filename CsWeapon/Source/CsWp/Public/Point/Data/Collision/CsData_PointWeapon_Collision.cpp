// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/Collision/CsData_PointWeapon_Collision.h"
#include "CsWp.h"

const FName NCsWeapon::NPoint::NData::NCollision::ICollision::Name = FName("NCsWeapon::NPoint::NData::NCollision::ICollision");

const FName ICsData_PointWeapon_Collision::Name = FName("ICsData_PointWeapon_Collision");

UCsData_PointWeapon_Collision::UCsData_PointWeapon_Collision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}