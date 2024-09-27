// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#define CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(__Interface) const FName __Interface::Name = FName(#__Interface)
#define CS_CLASS_DEFINE_STATIC_CONST_FNAME(__Class) const FName __Class::Name = FName(#__Class)
#define CS_STRUCT_DEFINE_STATIC_CONST_FNAME(__Struct) const FName __Struct::Name = FName(#__Struct)