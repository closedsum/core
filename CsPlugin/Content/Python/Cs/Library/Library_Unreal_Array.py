# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
checkf = CommonLibrary.checkf
check  = CommonLibrary.check

class NPyUnreal:
    class NArray:
        class FLibrary:
            @staticmethod
            def ToList(a: ue.Array) -> list:
                l: list = []
                for item in a:
                    l.append(item)
                return l
            @staticmethod
            def IsEmpty(a: ue.Array) -> bool:
                """
                Get whether the Array 'a' is empty or not.

                :param ue.Array a:
                :return: bool
                """
                if isinstance(a, ue.Array):
                    return len(a) == 0
                return False
            @staticmethod
            def IsNotEmptyChecked(context: str, a: ue.Array) -> bool:
                """
                Get whether the Array 'a' is NOT empty or not.
                Assert if NOT.

                :param str context:
                :param ue.Array a:
                :return: bool
                """
                # Check is array
                checkf(isinstance(a, ue.Array), context + ": a is NOT an instance of unreal.Array.")
                # Check array.length is NOT 0
                checkf(len(a) != 0, context + ": a is EMPTY")
                return True
            @staticmethod
            def IsNotEmpty(a: ue.Array) -> bool:
                """
                Get whether the Array 'a' is NOT empty or not.

                :param ue.Array a:
                :return: bool
                """
                # Check is array
                if isinstance(a, ue.Array) == False:
                    return False
                # Check array.length is NOT 0
                if len(a) == 0:
                    return False
                return True
            @staticmethod
            def IsSize(a: ue.Array, size: int) -> bool:
                if isinstance(a, ue.Array) == False:
                    return False

                if type(size) is not int:
                    return False
                return len(a) == size
            @staticmethod
            def IsSizeChecked(context: str, a: ue.Array, size: int) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                lib.IsNotEmptyChecked(context, a)
                CommonLibrary.IsIntChecked(context, size)
                checkf(len(a) == size, context + ": a is NOT of length: " + size)

                return True
            @staticmethod
            def AreAllElements_Class_Checked(context: str, a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                # Check is array
                checkf(isinstance(a, ue.Array), context + ": a is NOT an instance of unreal.Array.")

                for item in a:
                    check(CommonLibrary.IsInstanceOfChecked(context, item, classType))
                return True
            @staticmethod
            def AreAllElements_Class(a: ue.Array, classType: type) -> bool:
                # Check is array
                if isinstance(a, ue.Array) == False:
                    return False

                for item in a:
                    if isinstance(classType, type) == False or isinstance(item, classType) == False:
                        return False
                return True
            @staticmethod
            def Is2dChecked(context: str, a: ue.Array) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                checkf(isinstance(a, ue.Array), context + ": a is NOT an instance of unreal.Array.")
                lib.IsNotEmptyChecked(context, a)
                checkf(isinstance(a[0], ue.Array), context + ": a is NOT a 2d array.")
                return True
            @staticmethod
            def Is2d(a: ue.Array) -> bool:
                if isinstance(a, ue.Array) == False:
                    return False
                if len(a) == 0:
                    return False
                if isinstance(a[0], ue.Array) == False:
                    return False
                return True
            @staticmethod
            def AreAllElements2d_Class_Checked(context: str, a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                lib.Is2dChecked(context, a)

                for a2 in a:
                    for item in a2:
                        check(CommonLibrary.IsInstanceOfChecked(context, item, classType))
                return True
            @staticmethod
            def AreAllElements2d_Class(a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                if isinstance(classType, type) == False:
                    return False
                if lib.Is2d(a) == False:
                    return False

                for a2 in a:
                    for item in a2:
                        if CommonLibrary.IsInstanceOf(item, classType) == False:
                            return False
                return True
            @staticmethod
            def IsNotEmptyAndAllElements_Class_Checked(context: str, a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                check(lib.IsNotEmptyChecked(context, a))

                for item in a:
                    check(CommonLibrary.IsInstanceOfChecked(context, item, classType))
                return True
            @staticmethod
            def IsNotEmptyAndAllElements_Class(a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                if isinstance(a, ue.Array) == False:
                    return False
                if len(a) == 0:
                    return False
                if isinstance(classType, type) == False:
                    return False

                for item in a:
                    if isinstance(item, classType) == False:
                        return False
                return True
            @staticmethod
            def IsNotEmptyAndAllElements2d_Class_Checked(context: str, a: ue.Array, classType: any) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                check(lib.Is2dChecked(context, a))

                for a2 in a:
                    for item in a2:
                        check(CommonLibrary.IsInstanceOfChecked(context, item, classType))
                return True
            @staticmethod
            def IsNotEmptyAndAllElements2d_Class(a: ue.Array, classType: type) -> bool:
                lib: NPyUnreal.NArray.FLibrary = NPyUnreal.NArray.FLibrary

                if lib.Is2d(a) == False:
                    return False

                for a2 in a:
                    for item in a2:
                        if isinstance(item, classType) == False:
                            return False
                return True