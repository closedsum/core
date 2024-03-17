// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#define CS_INT32_BIT_MAX 15
#define CS_UINT32_BIT_MAX 31
#define CS_INT64_BIT_MAX 31
#define CS_UINT64_BIT_MAX 63

#define CS_TEST_BLUEPRINT_BITFLAG(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)
#define CS_SET_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint32>(Bit))
#define CS_CLEAR_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint32>(Bit)))

#define CS_TEST_BITFLAG(Bitmask, Bit) ((Bitmask & static_cast<uint32>(Bit)) == static_cast<uint32>(Bit))
#define CS_SET_BITFLAG(Bitmask, Bit) (Bitmask |= static_cast<uint32>(Bit))
#define CS_CLEAR_BITFLAG(Bitmask, Bit) (Bitmask &= ~static_cast<uint32>(Bit))