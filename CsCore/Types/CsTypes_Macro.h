// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
//#include "CsTypes_Macro.generated.h"
#pragma once

#define CS_EMPTY 0
#define CS_FIRST 0
#define CS_SINGLETON 1

#define CS_TEST_BLUEPRINT_BITFLAG(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)
#define CS_SET_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint32>(Bit))
#define CS_CLEAR_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint32>(Bit)))