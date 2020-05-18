// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once
#include "Managers/Creep/CsTdTypes_Creep.h"
#include "Managers/UnitTest/CsUnitTest_Impl.h"

// Structs
#pragma region

#pragma endregion Structs

struct FCsRoutine;
class AGameStateBase;
struct FCsTdCreepPooled;

class CSTD_API FCsTdUnitTest_Manager_Creep_CreatePool : public ICsUnitTest_Impl
{
private:

	typedef ICsUnitTest_Impl Super;

public:

	FCsTdUnitTest_Manager_Creep_CreatePool();
	~FCsTdUnitTest_Manager_Creep_CreatePool();

	// ICsUnitTest
#pragma region
public:

	virtual void Start() override;

#pragma endregion ICsUnitTest

// ICsUnitTest_Impl
#pragma region
protected:

	char Start_Internal(FCsRoutine* R);

#pragma endregion ICsUnitTest_Impl

private:

	AGameStateBase* GameState;

	FECsTdCreep TypeA;
	FECsTdCreep TypeB;
	FECsTdCreep TypeC;

	void OnConstructObject_TypeA(const FCsTdCreepPooled* Creep);
};