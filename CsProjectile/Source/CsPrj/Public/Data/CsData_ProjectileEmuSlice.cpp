// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileEmuSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileEmuSlice::Name = FName("FCsData_ProjectileEmuSlice");

FCsData_ProjectileEmuSlice::FCsData_ProjectileEmuSlice() :
		InterfaceMap(nullptr),
		InitialSpeed(nullptr),
		MaxSpeed(nullptr),
		GravityScale(nullptr)
{
}

FCsData_ProjectileEmuSlice::~FCsData_ProjectileEmuSlice()
{
}