// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Managers/Creep/UnitTest/CsTdUnitTestPlan_Manager_Creep.h"
#include "CsCore.h"

// UnitTest
#include "Managers/Creep/UnitTest/CsTdUnitTest_Manager_Creep_CreatePool.h"

FCsTdUnitTestPlan_Manager_Creep::FCsTdUnitTestPlan_Manager_Creep()
{
	NameAsString = TEXT("FCsUnitTestPlan_Manager_Creep");
	Name		 = FName(*NameAsString);

	DisplayNameAsString = TEXT("Manager Creep");
	DisplayName			= FName(*DisplayNameAsString);

	Start_Internal_NameAsString = NameAsString + TEXT("::Start_Internal");
	Start_Internal_Name			= FName(*Start_Internal_NameAsString);

	Add<FCsTdUnitTest_Manager_Creep_CreatePool>();
}

FCsTdUnitTestPlan_Manager_Creep::~FCsTdUnitTestPlan_Manager_Creep()
{
}