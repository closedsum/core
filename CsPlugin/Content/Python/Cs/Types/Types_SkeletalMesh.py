# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - library (c++)
PropertyLibrary      = ue.CsScriptLibrary_Property
SkeletalMeshLibrary  = ue.CsScriptLibrary_SkeletalMesh

# "typedefs" - functions
check                   = CommonLibrary.check
IsStringChecked         = CommonLibrary.IsStringChecked
IsValidObjectChecked    = CommonLibrary.IsValidObjectChecked
IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked
IsInstanceOfChecked     = CommonLibrary.IsInstanceOfChecked

class NPyTypes:
    class FSkeletalMesh:
        def __init__(self):
            self.Path: str = ""
            self.Mesh_Internal: ue.SkeletalMesh = None

        def GetName(self) -> str:
            return "NJsTypes.FSkeletalMesh"

        def Get(self) -> ue.SkeletalMesh:
            return self.Mesh_Internal
        
        def Set(self, mesh: ue.SkeletalMesh):
            self.Mesh_Internal = mesh

        def IsValidChecked(self, context: str) -> bool:
            IsStringChecked(context, self.Path)
            IsInstanceOfChecked(context, self.Mesh_Internal, ue.SkeletalMesh)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = PropertyLibrary.get_soft_object_ptr_as_string_by_path(context, o, memberPath + ".Mesh")
            outSuccess: bool = result[1]
            check(outSuccess)
            outPath: str = result[0]
            self.Path = outPath
            # SkeletalMesh
            result: ue.Tuple[ue.SkeletalMesh, bool] = SkeletalMeshLibrary.get_by_path(context, o, memberPath + ".Mesh_Internal")
            outSuccess: bool = result[1]
            check(outSuccess)
            skm: ue.SkeletalMesh = result[0]
            IsInstanceOfChecked(context, skm, ue.SkeletalMesh)
            self.Mesh_Internal = skm

        def Load(self):
            context: str = self.GetName() + ".Load"

            self.Mesh_Internal = SkeletalMeshLibrary.load_by_string_path(context, self.Path)

        def Unload(self):
            self.Mesh_Internal = None