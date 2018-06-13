// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Character.h"

// CharacterAnim
EMCsCharacterAnim* EMCsCharacterAnim::Instance;

EMCsCharacterAnim& EMCsCharacterAnim::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnim();
	return *Instance;
}

// CharacterBlendSpace
EMCsCharacterBlendSpace* EMCsCharacterBlendSpace::Instance;

EMCsCharacterBlendSpace& EMCsCharacterBlendSpace::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterBlendSpace();
	return *Instance;
}

// CharacterAnimBlueprint
EMCsCharacterAnimBlueprint* EMCsCharacterAnimBlueprint::Instance;

EMCsCharacterAnimBlueprint& EMCsCharacterAnimBlueprint::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnimBlueprint();
	return *Instance;
}

// CharacterAnimVariation
EMCsCharacterAnimVariation* EMCsCharacterAnimVariation::Instance;

EMCsCharacterAnimVariation& EMCsCharacterAnimVariation::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnimVariation();
	return *Instance;
}