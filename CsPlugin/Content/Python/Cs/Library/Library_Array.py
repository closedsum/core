# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import unreal as ue
# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# ALIAS

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - functions
checkf = FPyCommonLibrary.checkf
check  = FPyCommonLibrary.check

class NPyArray:
    class FLibrary:
        @staticmethod
        def IsEmpty(a: list) -> bool:
            """
            Get whether the Array 'a' is empty or not.

            :param list a:
            :return: bool
            """
            if type(a) is list:
                return len(a) == 0
            return False
        @staticmethod
        def IsNotEmptyChecked(context: str, a: list) -> bool:
            """
            Get whether the Array 'a' is NOT empty or not.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread). 

            Args:
                context (str):  The calling context.
                a       (list): The array to check.
            Returns:
                bool: True if 'a' is NOT empty, False otherwise.
            """
            # Check is array
            checkf(type(a) is list, context + ": a is type: " + str(type(a)) + " and NOT an array.")
            # Check array.length is NOT 0
            checkf(len(a) != 0, context + ": a is EMPTY")
            return True
        @staticmethod
        def IsNotEmpty(a: list) -> bool:
            """
            Get whether the Array 'a' is NOT empty or not.

            Args:
                a (list): The array to check.
            Returns:
                bool: True if 'a' is NOT empty, False otherwise.
            """
            # Check is array
            if type(a) is not list:
                return False
            # Check array.length is NOT 0
            if len(a) == 0:
                return False
            return True
        @staticmethod
        def IsNotEmptyRaiseError(context: str, a: list) -> bool:
            """
            Get whether the Array 'a' is NOT empty or not.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str):  The calling context.
                a       (list): The array to check.
            Returns:
                bool: True if 'a' is NOT empty, False otherwise.
            """
            # Check is array
            if type(a) is not list:
                raise Exception(context + ": a is type: " + str(type(a)) + " and NOT an array.")    
            # Check array.length is NOT 0
            if len(a) == 0:
                raise Exception(context + ": a is EMPTY")
            return True
        @staticmethod
        def AllNotNoneChecked(context: str, a: list) -> bool:
            """
            Get whether any element in Array 'a' is None or not.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread). 
            
            Args:
                context (str):  The calling context.
                a       (list): The array to check.
            Returns:
                bool: True if any element in 'a' is NOT None, False otherwise.
            """
            # Check is array
            checkf(type(a) is list, context + ": a is type: " + str(type(a))+ " and NOT an array.")
            count: int = len(a)
            for i in range(0, count):
                checkf(a[i] != None, context + ": a[" + str(i) + "] is None")
            return True
        @staticmethod
        def IsSize(a: list, size: int) -> bool:
            if type(a) is not list:
                return False

            if type(size) is not int:
                return False
            return len(a) == size
        @staticmethod
        def IsSizeChecked(context: str, a: list, size: int) -> bool:
            ThisType = __class__

            ThisType.IsNotEmptyChecked(context, a)
            FPyCommonLibrary.IsIntChecked(context, size)
            checkf(len(a) == size, context + ": a is NOT of length: " + size)

            return True
        @staticmethod
        def AreAllElements_Class_Checked(context: str, a: list, classType: type) -> bool:
            ThisType = __class__

            # Check is array
            checkf(type(a) is list, context + ": a is type: " + type(a) + " and NOT an array.")

            for item in a:
                check(FPyCommonLibrary.IsInstanceOfChecked(context, item, classType))
            return True
        @staticmethod
        def AreAllElements_Class(a: list, classType: type) -> bool:
            # Check is array
            if type(a) is not list:
                return False

            for item in a:
                if isinstance(classType, type) == False or isinstance(item, classType) == False:
                    return False
            return True
        @staticmethod
        def Is2dChecked(context: str, a: list) -> bool:
            ThisType = __class__

            checkf(type(a) is list, context + ": a is type: " + type(a) + " and NOT an array.")
            ThisType.IsNotEmptyChecked(context, a)
            checkf(type(a[0]) is list, context + ": a is NOT a 2d array.")
            return True
        @staticmethod
        def Is2d(a: list) -> bool:
            if type(a) is not list:
                return False
            if len(a) == 0:
                return False
            if type(a[0]) is not list:
                return False
            return True
        @staticmethod
        def AreAllElements2d_Class_Checked(context: str, a: list, classType: type) -> bool:
            ThisType = __class__

            ThisType.Is2dChecked(context, a)

            for a2 in a:
                for item in a2:
                    check(FPyCommonLibrary.IsInstanceOfChecked(context, item, classType))
            return True
        @staticmethod
        def AreAllElements2d_Class(a: list, classType: type) -> bool:
            ThisType = __class__

            if isinstance(classType, type) == False:
                return False
            if ThisType.Is2d(a) == False:
                return False

            for a2 in a:
                for item in a2:
                    if FPyCommonLibrary.IsInstanceOf(item, classType) == False:
                        return False
            return True
        @staticmethod
        def IsNotEmptyAndAllElements_Class_Checked(context: str, a: list, classType: type) -> bool:
            ThisType = __class__

            check(ThisType.IsNotEmptyChecked(context, a))

            for item in a:
                check(FPyCommonLibrary.IsInstanceOfChecked(context, item, classType))
            return True
        @staticmethod
        def IsNotEmptyAndAllElements_Class(a: list, classType: type) -> bool:
            if type(a) is not list:
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
        def IsNotEmptyAndAllElements2d_Class_Checked(context: str, a: list, classType: any) -> bool:
            ThisType = __class__

            check(ThisType.Is2dChecked(context, a))

            for a2 in a:
                for item in a2:
                    check(FPyCommonLibrary.IsInstanceOfChecked(context, item, classType))
            return True
        @staticmethod
        def IsNotEmptyAndAllElements2d_Class(a: list, classType: type) -> bool:
            ThisType = __class__

            if ThisType.Is2d(a) == False:
                return False

            for a2 in a:
                for item in a2:
                    if isinstance(item, classType) == False:
                        return False
            return True
        @staticmethod
        def CopyFromTArrayChecked(context: str, in_list: list, in_arrary: ue.Array):
            # TODO: Do checks
            in_list.clear()

            for a in in_arrary:
                in_list.append(a)