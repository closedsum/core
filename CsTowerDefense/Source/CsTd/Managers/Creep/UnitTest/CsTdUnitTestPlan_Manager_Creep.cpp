// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Managers/Creep/UnitTest/CsTdUnitTestPlan_Manager_Creep.h"
#include "CsCore.h"

// UnitTest
#include "Managers/Creep/UnitTest/CsTdUnitTest_Manager_Creep_CreatePool.h"

FCsTdUnitTestPlan_Manager_Creep::FCsTdUnitTestPlan_Manager_Creep()
{
	Name		  = TEXT("FCsUnitTestPlan_Manager_Creep");
	Name_Internal = FName(*Name);

	DisplayName  = TEXT("Manager Creep");
	DisplayFName = FName(*DisplayName);

	Start_Internal_Name  = Name + TEXT("::Start_Internal");
	Start_Internal_FName = FName(*Start_Internal_Name);

	Add<FCsTdUnitTest_Manager_Creep_CreatePool>();
}

FCsTdUnitTestPlan_Manager_Creep::~FCsTdUnitTestPlan_Manager_Creep()
{
}