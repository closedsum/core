# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check           = CommonLibrary.check
checkf          = CommonLibrary.checkf
IsNumberChecked = CommonLibrary.IsNumberChecked
IsIntChecked    = CommonLibrary.IsIntChecked
IsFloatChecked  = CommonLibrary.IsFloatChecked

class NPyMath:
    class FLibrary:
        class NCached:
            class NStr:
                # Number
                IsGreaterThanChecked          = "NPyMath.FLibrary.IsGreaterThanChecked"
                IsGreaterThanOrEqualChecked   = "NPyMath.FLibrary.IsGreaterThanOrEqualChecked"
                IsLessThanChecked             = "NPyMath.FLibrary.IsLessThanChecked"
                IsLessThanOrEqualChecked      = "NPyMath.FLibrary.IsLessThanOrEqualChecked"
                # Int
                IsPositiveIntChecked             = "NPyMath.FLibrary.IsPositiveIntChecked"
                IsNonNegativeIntChecked          = "NPyMath.FLibrary.IsNonNegativeIntChecked"
                IsIntGreaterThanChecked          = "NPyMath.FLibrary.IsIntGreaterThanChecked"
                IsIntGreaterThanOrEqualChecked   = "NPyMath.FLibrary.IsIntGreaterThanOrEqualChecked"
                IsIntLessThanChecked             = "NPyMath.FLibrary.IsIntLessThanChecked"
                IsIntLessThanOrEqualChecked      = "NPyMath.FLibrary.IsIntLessThanOrEqualChecked"
                IsIntInRangeInclusiveChecked     = "NPyMath.FLibrary.IsIntInRangeInclusiveChecked"
                # Float
                IsFloatGreaterThanChecked          = "NPyMath.FLibrary.IsFloatGreaterThanChecked"
                IsFloatGreaterThanOrEqualChecked   = "NPyMath.FLibrary.IsFloatGreaterThanOrEqualChecked"
                IsFloatLessThanChecked             = "NPyMath.FLibrary.IsFloatLessThanChecked"
                IsFloatLessThanOrEqualChecked      = "NPyMath.FLibrary.IsFloatLessThanOrEqualChecked"
        # Number
        @staticmethod
        def IsGreaterThanChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.

            :param str context:
            :param any a:
            :param any b:
            :return bool:
            """ 
            IsNumberChecked(context, a)
            IsNumberChecked(context, b)

            checkf(a > b, context + ": " + str(a) + " is NOT > " + str(b) + " .")
            return True
        @staticmethod
        def IsGreaterThanChecked2(a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.

            :param any a:
            :param any b:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsGreaterThanChecked

            return lib.IsGreaterThanChecked(context, a, b)
        @staticmethod
        def IsGreaterThanOrEqualChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.

            :param str context: The call context.
            :param any a:
            :param any b:
            :return bool:
            """ 
            IsNumberChecked(context, a)
            IsNumberChecked(context, b)

            checkf(a >= b, context + ": " + str(a) + " is NOT >= " + str(b) + " .")
            return True
        @staticmethod
        def IsGreaterThanOrEqualChecked2(a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.

            :param any a:
            :param any b:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsGreaterThanOrEqualChecked
        
            return lib.IsGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsLessThanChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param any a:
            :param any b:
            :return bool:
            """ 
            IsNumberChecked(context, a)
            IsNumberChecked(context, b)

            checkf(a < b, context + ": " + str(a) + " is NOT < " + str(b) + " .")
            return True
        @staticmethod
        def IsLessThanChecked2(a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param any a:
            :param any b:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsLessThanChecked

            return lib.IsLessThanChecked(context, a, b)
        @staticmethod
        def IsLessThanOrEqualChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param any a:
            :param any b:
            :return bool:
            """ 
            IsNumberChecked(context, a)
            IsNumberChecked(context, b)

            checkf(a <= b, context + ": " + str(a) + " is NOT <= " + str(b) + " .")
            return True
        def IsLessThanOrEqualChecked2(a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             
            :param any a:
            :param any b:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsLessThanOrEqualChecked

            return lib.IsLessThanOrEqualChecked(context, a, b)
        # Int
        @staticmethod
        def IsPositiveInt(a: int) -> bool:
            return (type(a) is int) and (a > 0)
        @staticmethod
        def IsPositiveIntChecked(context: str, a: int) -> bool:
            """
            Get whether or not 'a' is a positive integer (a > 0).
             Assert if NOT.
             
            :param str context: The calling context.
            :param int a:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary

            result: bool = lib.IsPositiveInt(a)
            checkf(result, context + ": a: " + str(a) + " is NOT BOTH an integer AND > 0.")
            return result
        @staticmethod
        def IsPositiveIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is a positive integer (a > 0).
             Assert if NOT.
             
            :param int a:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsPositiveIntChecked

            return lib.IsPositiveIntChecked(context, a)
        @staticmethod
        def IsNonNegativeInt(a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             
            :param int a:
            :return bool:
            """ 
            return (type(a) is int) and (a >= 0) 
        @staticmethod
        def IsNonNegativeIntChecked(context: str , a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             Assert if NOT. 

            :param str context: The calling context.
            :param int a:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary

            result: bool = lib.IsNonNegativeInt(a)
            checkf(result, context + ": a: " + str(a) + " is NOT BOTH an integer AND >= 0.")
            return result
        @staticmethod
        def IsNonNegativeIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             Assert if NOT.
             
            :param int a:
            :return bool:
            """ 
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsNonNegativeIntChecked

            return lib.IsNonNegativeIntChecked(context, a)
        @staticmethod
        def IsIntGreaterThanChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param int a:
            :param int b:
            :return bool:
            """
            IsIntChecked(context, a)
            IsIntChecked(context, b)

            checkf(a > b, context + ": " + str(a) + " is NOT > " + str(b) + " .")
            return True
        @staticmethod
        def IsIntGreaterThanChecked2(a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
             
            :param int a:
            :param int b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsIntGreaterThanChecked

            return lib.IsIntGreaterThanChecked(context, a, b)
        @staticmethod
        def IsIntGreaterThanOrEqualChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
             
            :param str context:
            :param int a:
            :param int b:
            :return bool:
            """
            IsIntChecked(context, a)
            IsIntChecked(context, b)

            checkf(a >= b, context + ": " + str(a) + " is NOT >= " + str(b) + " .")
            return True
        @staticmethod
        def IsIntGreaterThanOrEqualChecked2(a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
             
            :param int a:
            :param int b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsIntGreaterThanOrEqualChecked

            return lib.IsIntGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsIntLessThanChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param str context: The calling context
            :param int a:
            :param int b:
            :return bool:
            """
            IsIntChecked(context, a)
            IsIntChecked(context, b)

            checkf(a < b, context + ": " + str(a) + " is NOT < " + str(b) + " .")
            return True
        @staticmethod
        def IsIntLessThanChecked2(a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param int a:
            :param int b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsIntLessThanChecked

            return lib.IsIntLessThanChecked(context, a, b)
        @staticmethod
        def IsIntLessThanOrEqualChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param int a:
            :param int b:
            :return bool:
            """
            IsIntChecked(context, a)
            IsIntChecked(context, b)

            checkf(a <= b, context + ": " + str(a) + " is NOT <= " + str(b) + " .")
            return True
        @staticmethod
        def IsIntLessThanOrEqualChecked2(a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             
            :param int a:
            :param int b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsIntLessThanOrEqualChecked

            return lib.IsIntLessThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsIntInRangeInclusiveChecked(context: str, a: int, l: int, r: int) -> bool:
            """
            Get whether or not 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE.
             Assert if NOT.
             
            :param str context: The calling context.
            :param int a:
            :param int l:
            :param int r:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            
            return lib.IsIntGreaterThanOrEqualChecked(context, a, l) and lib.IsIntLessThanOrEqualChecked(context, a, r)
        @staticmethod
        def IsIntInRangeInclusiveChecked2(a: int, l: int, r: int) -> bool:
            """
            Get whether or not 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE.
             Assert if NOT.
             
            :param int a:
            :param int l:
            :param int r:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsIntInRangeInclusiveChecked

            return lib.IsIntInRangeInclusiveChecked(context, a, l, r)
        # Flag
        @staticmethod
        def BitFlag_Test(bitmask: int, bit: int) -> bool:
            lib: NPyMath.FLibrary = NPyMath.FLibrary

            check(lib.IsNonNegativeInt(bitmask))
            check(lib.IsNonNegativeInt(bit))
            return (bitmask & bit) == bit
        @staticmethod
        def BitFlag_Set(bitmask: int, bit: int) -> int:
            lib: NPyMath.FLibrary = NPyMath.FLibrary

            check(lib.IsNonNegativeInt(bitmask))
            check(lib.IsNonNegativeInt(bit))

            return (bitmask | bit)
        @staticmethod
        def BitFlag_Clear(bitmask: int, bit: int) -> int:
            lib: NPyMath.FLibrary = NPyMath.FLibrary

            check(lib.IsNonNegativeInt(bitmask))
            check(lib.IsNonNegativeInt(bit))
            
            return (bitmask & (~bit))
        # Float
        @staticmethod
        def IsFloatGreaterThanChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param float a:
            :param float b:
            :return bool:
            """
            IsFloatChecked(context, a)
            IsFloatChecked(context, b)

            checkf(a > b, context + ": " + str(a) + " is NOT > " + str(b) + " .")
            return True
        @staticmethod
        def IsFloatGreaterThanChecked2(a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
             
            :param float a:
            :param float b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsFloatGreaterThanChecked

            return lib.IsFloatGreaterThanChecked(context, a, b)
        @staticmethod
        def IsFloatGreaterThanOrEqualChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param float a:
            :param float b:
            :return bool:
            """
            IsFloatChecked(context, a)
            IsFloatChecked(context, b)

            checkf(a >= b, context + ": " + str(a) + " is NOT >= " + str(b) + " .")
            return True
        @staticmethod
        def IsFloatGreaterThanOrEqualChecked2(a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
             
            :param float a:
            :param float b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsFloatGreaterThanOrEqualChecked

            return lib.IsFloatGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsFloatLessThanChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param str context. The calling context.
            :param float a:
            :param float b:
            :return bool:
            """
            IsFloatChecked(context, a)
            IsFloatChecked(context, b)

            checkf(a < b, context + ": " + str(a) + " is NOT < " + str(b) + " .")
            return True
        @staticmethod
        def IsFloatLessThanChecked2(a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
             
            :param float a:
            :param float b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsFloatLessThanChecked

            return lib.IsFloatLessThanChecked(context, a, b)
        @staticmethod
        def IsFloatLessThanOrEqualChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             
            :param str context: The calling context.
            :param float a:
            :param float b:
            :return bool:
            """
            IsFloatChecked(context, a)
            IsFloatChecked(context, b)

            checkf(a <= b, context + ": " + str(a) + " is NOT <= " + str(b) + " .")
            return True
        @staticmethod
        def IsFloatLessThanOrEqualChecked2(a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
             

            :param float a:
            :param float b:
            :return bool:
            """
            lib: NPyMath.FLibrary = NPyMath.FLibrary
            context: str = NPyMath.FLibrary.NCached.NStr.IsFloatLessThanOrEqualChecked

            return lib.IsFloatLessThanOrEqualChecked(context, a, b)