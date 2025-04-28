# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Array.py
import Cs.Library.Library_Unreal_Array as Cs_Library_Unreal_Array

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
UnrealArrayLibrary = Cs_Library_Unreal_Array.NPyUnreal.NArray.FLibrary

# "typedefs" - library (c++)
MaterialLibrary  = ue.CsScriptLibrary_Material

# "typedefs" - functions
check                   = CommonLibrary.check
IsValidObjectChecked    = CommonLibrary.IsValidObjectChecked
IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked
IsNotEmptyChecked       = UnrealArrayLibrary.IsNotEmptyChecked

class NPyTypes:
    class FMaterialInterface:
        def __init__(self):
            self.Path: str = ""
            self.Material_Internal: ue.MaterialInterface = None

        def GetName(self) -> str:
            return "NJsTypes.FMaterialInterface"

        def Get(self) -> ue.MaterialInterface:
            return self.Material_Internal

        def Set(self, mat: ue.MaterialInterface): 
            self.Material_Internal = mat

        def IsValidChecked(self, context: str) -> bool:
            IsStringNotEmptyChecked(context, self.Path)
            CommonLibrary.IsInstanceOfChecked(context, self.Material_Internal, ue.MaterialInterface)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = MaterialLibrary.get_soft_object_as_string_by_path(context, o, memberPath + ".Material")
            outSuccess: bool = result[1]
            check(outSuccess)
            outPath: str = result[0]
            IsStringNotEmptyChecked(context, outPath)
            self.Path = outPath
            # Material
            result: ue.Tuple[ue.MaterialInterface, bool] = MaterialLibrary.get_by_path(context, o, memberPath + ".Material_Internal")
            outSuccess: bool = result[1]
            check(outSuccess)
            m: ue.MaterialInterface = result[0]
            CommonLibrary.IsInstanceOfChecked(context, m, ue.MaterialInterface)
            self.Material_Internal = m

        def Load(self):
            context: str = self.GetName() + ".Load"

            result: ue.MaterialInterface = MaterialLibrary.load_by_string_path(context, self.Path)
            CommonLibrary.IsInstanceOfChecked(context, result, ue.MaterialInterface)
            self.Material_Internal = result

        def Unload(self):
            self.Material_Internal = None

    class FTArrayMaterialInterface:
        def __init__(self):
            self.Paths: ue.Array[str] = ue.Array(str)
            """
            ue.Array[str]:
            """
            self.Materials_Internal: ue.Array[ue.MaterialInterface] = ue.Array(ue.MaterialInterface)
            """
            ue.Array[ue.MaterialInterface]:
            """

        def GetName(self) -> str:
            return "NJsTypes.FTArrayMaterialInterface"

        def Get(self) -> ue.Array[ue.MaterialInterface]:
            """
            :return ue.Array[ue.MaterialInterface]:
            """
            return self.Materials_Internal

        def Set(self, mats: ue.Array[ue.MaterialInterface]):
             self.Materials_Internal = mats.copy()

        def IsValidChecked(self, context: str) -> bool:
            IsNotEmptyChecked(context, self.Paths)
            IsNotEmptyChecked(context, self.Materials_Internal)
            # TODO: Need to check Array has valid objects.
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Paths
            result: ue.Tuple[ue.Array, bool] = MaterialLibrary.get_soft_object_array_as_string_by_path(context, o, memberPath + ".Materials")
            outSuccess: bool = result[1]
            check(outSuccess)
            self.Paths = result[0].copy()
            # Materials
            result: ue.Tuple[ue.Array, bool] = MaterialLibrary.get_array_by_path(context, o, memberPath + ".Materials_Internal")
            outSuccess: bool = result[1]
            check(outSuccess)
            IsNotEmptyChecked(context, result[0])
            self.Materials_Internal = result[0].copy()

        def Load(self):
            context: str = self.GetName() + ".Load"

            result: ue.Tuple[ue.Array, bool] = MaterialLibrary.load_by_string_paths(context, self.Paths)
            outSuccess: bool = result[1]
            check(outSuccess)
            IsNotEmptyChecked(context, result[0])
            self.Materials_Internal = result[1].copy()

        def Unload(self):
            self.Materials_Internal.resize(0)