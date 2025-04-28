# Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
AnimInstanceLibrary  = ue.CsScriptLibrary_AnimInstance
AnimSequenceLibrary  = ue.CsScriptLibrary_AnimSequence
AnimMontageLibrary   = ue.CsScriptLibrary_AnimMontage
BlendSpaceLibrary    = ue.CsScriptLibrary_BlendSpace

# "typedefs" - functions
check                   = CommonLibrary.check
IsClassChecked          = CommonLibrary.IsClassChecked
IsValidObjectChecked    = CommonLibrary.IsValidObjectChecked
IsStringChecked         = CommonLibrary.IsStringChecked
IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked
IsInstanceOfChecked     = CommonLibrary.IsInstanceOfChecked

class NPyTypes:
    class FAnimBlueprint:
        def __init__(self):
            self.Path: str = ""
            self.Blueprint_Internal: ue.AnimBlueprintGeneratedClass = None

        def GetName() -> str:
            return "NJsTypes.FAnimBlueprint"

        def Get(self) -> ue.AnimBlueprintGeneratedClass:
            return self.Blueprint_Internal
        
        def Set(self, ac: ue.AnimBlueprintGeneratedClass):
            self.Blueprint_Internal = ac

        def IsValidChecked(self, context: str) -> bool:
            IsStringChecked(context, self.Path)
            IsInstanceOfChecked(context, self.Blueprint_Internal, ue.AnimBlueprintGeneratedClass)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = PropertyLibrary.get_soft_object_ptr_as_string_by_path(context, o, memberPath + ".Blueprint")
            outSuccess: bool = result[1]
            check(outSuccess)
            outPath: str = result[0]
            IsStringNotEmptyChecked(context, outPath)
            self.Path = outPath;
            # AnimBlueprint Class
            result: ue.Tuple[ue.AnimBlueprintGeneratedClass, bool] = AnimInstanceLibrary.get_class_by_path(context, o, memberPath + ".Blueprint_Internal")
            outSuccess: bool = result[1]
            check(outSuccess)
            outClass: ue.AnimBlueprintGeneratedClass = result[0]
            IsInstanceOfChecked(context, outClass, ue.AnimBlueprintGeneratedClass)
            self.Blueprint_Internal = outClass

        def Load(self):
            context: str = self.GetName() + ".Load"

            self.Blueprint_Internal = AnimInstanceLibrary.load_and_get_generated_class_by_string_path(context, self.Path)

        def Unload(self):
            self.Blueprint_Internal = None

    class FAnimSequence:
        def __init__(self):
            self.Path: str = ""
            self.Anim_Internal: ue.AnimSequence = None

        def GetName(self) -> str:
            return "NJsTypes.FAnimSequence"

        def Get(self) -> ue.AnimSequence:
            return self.Anim_Internal
        
        def Set(self, a: ue.AnimSequence):
            self.Anim_Internal = a

        def IsValidChecked(self, context: str) -> bool:
            IsStringChecked(context, self.Path)
            IsInstanceOfChecked(context, self.Anim_Internal, ue.AnimSequence)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = PropertyLibrary.get_soft_object_ptr_as_string_by_path(context, o, memberPath + ".Anim");
            outSuccess: bool = result[1]
            check(outSuccess)
            outPath: str = result[0]
            IsStringNotEmptyChecked(context, outPath)
            self.Path = outPath
            # AnimSequence
            result: ue.Tuple[ue.AnimSequence, bool] = AnimSequenceLibrary.get_by_path(context, o, memberPath + ".Anim_Internal")
            outSuccess: bool = result[1]
            check(outSuccess)
            outAS: ue.AnimSequence = result[0]
            IsInstanceOfChecked(context, outAS, ue.AnimSequence)
            self.Anim_Internal = outAS

        def Load(self):
            context: str = self.GetName() + ".Load"

            self.Anim_Internal = AnimSequenceLibrary.load_by_string_path(context, self.Path)

        def Unload(self):
            self.Anim_Internal = None

    class FBlendSpace:
        def __init__(self):
            self.Path: str = ""
            self.Blend_Internal: ue.BlendSpace = None

        def GetName(self) -> str:
            return "NJsTypes.FBlendSpace"

        def Get(self) -> ue.BlendSpace:
            return self.Blend_Internal
        
        def Set(self, b: ue.BlendSpace):
            self.Blend_Internal = b

        def IsValidChecked(self, context: str):
            IsStringChecked(context, self.Path)
            IsInstanceOfChecked(context, self.Blend_Internal, ue.BlendSpace)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = PropertyLibrary.get_soft_object_ptr_as_string_by_path(context, o, memberPath + ".Blend")
            outSuccess = result[1]
            check(outSuccess)
            outPath = result[0]
            IsStringNotEmptyChecked(context, outPath)
            self.Path = outPath
            # BlendSpace
            result: ue.Tuple[ue.BlendSpace, bool]  = BlendSpaceLibrary.get_by_path(context, o, memberPath + ".Blend_Internal")
            outSuccess = result[1]
            check(outSuccess)
            bs: ue.BlendSpace = result[0]
            IsValidObjectChecked(context, bs)
            self.Blend_Internal = bs

        def Load(self):
            context: str = self.GetName() + ".Load"

            self.Blend_Internal = BlendSpaceLibrary.load1d_by_string_path(context, self.Path)

        def Unload(self):
            self.Blend_Internal = None

    class FBlendSpace1D:
        def __init__(self):
            self.Path: str = ""
            self.Blend_Internal: ue.BlendSpace1D = None

        def GetName(self) -> str:
            return "NJsTypes.FBlendSpace1D"

        def Get(self) -> ue.BlendSpace1D:
            return self.Blend_Internal
        
        def Set(self, b: ue.BlendSpace1D): 
            self.Blend_Internal = b

        def IsValidChecked(self, context: str) -> bool:
            IsStringChecked(context, self.Path)
            IsInstanceOfChecked(context, self.Blend_Internal, ue.BlendSpace1D)
            return True

        def OverrideByUObject(self, context: str, o: ue.Object, memberPath: str):
            # Path
            result: ue.Tuple[str, bool] = PropertyLibrary.get_soft_object_ptr_as_string_by_path(context, o, memberPath + ".Blend")
            outSuccess = result[1]
            check(outSuccess)
            outPath = result[0]
            IsStringNotEmptyChecked(outPath)
            self.Path = outPath
            # BlendSpace1D
            result: ue.Tuple[ue.BlendSpace1D, bool] = BlendSpaceLibrary.get1d_by_path(context, o, memberPath + ".Blend_Internal")
            outSucces = result[1]
            check(outSucces)
            bs: ue.BlendSpace1D = result[0]
            IsInstanceOfChecked(context, bs, ue.BlendSpace1D)
            self.Blend_Internal = bs

        def Load(self):
            context: str = self.GetName() + ".Load"

            self.Blend_Internal = BlendSpaceLibrary.load1d_by_string_path(context, self.Path)

        def Unload(self):
            self.Blend_Internal = None