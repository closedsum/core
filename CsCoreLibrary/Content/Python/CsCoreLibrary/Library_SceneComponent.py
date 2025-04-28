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
ObjectLibrary = ue.CsScriptLibrary_Object

# "typedefs" - functions
check   = CommonLibrary.check
checkf  = CommonLibrary.checkf

class NPySceneComponent:
    class FLibrary:
        class NCached:
            class NStr:
                # Number
                AttachToComponent_KeepRelativeTransform          = "NPySceneComponent.FLibrary.AttachToComponent_KeepRelativeTransform"
                AttachToComponentChecked2_KeepRelativeTransform  = "NPySceneComponent.FLibrary.AttachToComponentChecked2_KeepRelativeTransform"

        # class FDisableCheck:
        #     # Number
        #     //static /*boolean*/ IsGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
        #     //static /*boolean*/ IsGreaterThanChecked2(a /*number*/, b /*number*/) { return true; }

        @staticmethod
        def AttachToComponent_KeepRelativeTransform(child: ue.SceneComponent, parent: ue.SceneComponent, socket: ue.Name) -> bool:
            lib: NPySceneComponent.FLibrary = NPySceneComponent.FLibrary
            
            context: str = lib.NCached.NStr.AttachToComponent_KeepRelativeTransform

            if ObjectLibrary.safe_is_valid(context, child) == False:
                return False
            if ObjectLibrary.safe_is_valid(context, parent) == False:
                return False

            # TODO:
            # If socket is Valid, check socket Exists

            child.attach_to_component(parent, socket, ue.DetachmentRule.KEEP_RELATIVE, ue.DetachmentRule.KEEP_RELATIVE, ue.DetachmentRule.KEEP_RELATIVE, False)
            return True
        @staticmethod
        def AttachToComponentChecked_KeepRelativeTransform(context: str, child: ue.SceneComponent, parent: ue.SceneComponent, socket: ue.Name):
            check(ObjectLibrary.safe_is_valid(context, child))
            check(ObjectLibrary.safe_is_valid(context, parent))
            # TODO:
            # If socket is Valid, check socket Exists

            child.attach_to_component(parent, socket, ue.DetachmentRule.KEEP_RELATIVE, ue.DetachmentRule.KEEP_RELATIVE, ue.DetachmentRule.KEEP_RELATIVE, False)
        @staticmethod
        def AttachToComponentChecked2_KeepRelativeTransform(child: ue.SceneComponent, parent: ue.SceneComponent, socket: ue.Name):
            lib: NPySceneComponent.FLibrary = NPySceneComponent.FLibrary

            context: str = lib.NCached.NStr.AttachToComponentChecked2_KeepRelativeTransform

            lib.AttachToComponentChecked2_KeepRelativeTransform(context, child, parent, socket)