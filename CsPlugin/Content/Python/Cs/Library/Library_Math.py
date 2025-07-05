# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check           = FPyCommonLibrary.check
checkf          = FPyCommonLibrary.checkf
IsNumberChecked = FPyCommonLibrary.IsNumberChecked
IsIntChecked    = FPyCommonLibrary.IsIntChecked
IsIntRaiseError = FPyCommonLibrary.IsIntRaiseError
IsFloatChecked  = FPyCommonLibrary.IsFloatChecked
IsFloatRaiseError = FPyCommonLibrary.IsFloatRaiseError

class NPyMath:
    class FLibrary:
        # Number
        @staticmethod
        def IsGreaterThanChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsGreaterThanChecked2.__qualname__

            return ThisType.IsGreaterThanChecked(context, a, b)
        @staticmethod
        def IsGreaterThanOrEqualChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsGreaterThanOrEqualChecked2.__qualname__

            return ThisType.IsGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsLessThanChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsLessThanChecked2.__qualname__

            return ThisType.IsLessThanChecked(context, a, b)
        @staticmethod
        def IsLessThanOrEqualChecked(context: str, a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
            """ 
            IsNumberChecked(context, a)
            IsNumberChecked(context, b)

            checkf(a <= b, context + ": " + str(a) + " is NOT <= " + str(b) + " .")
            return True
        def IsLessThanOrEqualChecked2(a: any, b: any) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (any): The first value to compare.
                b       (any): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsLessThanOrEqualChecked2.__qualname__

            return ThisType.IsLessThanOrEqualChecked(context, a, b)
        # Int
        @staticmethod
        def IsPositiveInt(a: int) -> bool:
            """
            Get whether or not 'a' is a positive integer (a > 0).
            
            Args:
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a positive integer (a > 0), False otherwise.
            """ 
            return (type(a) is int) and (a > 0)
        @staticmethod
        def IsPositiveIntChecked(context: str, a: int) -> bool:
            """
            Get whether or not 'a' is a positive integer (a > 0).
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a positive integer (a > 0), False otherwise.
            """ 
            ThisType = __class__

            result: bool = ThisType.IsPositiveInt(a)
            checkf(result, context + ": a: " + str(a) + " is NOT BOTH an integer AND > 0.")
            return result
        @staticmethod
        def IsPositiveIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is a positive integer (a > 0).
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a positive integer (a > 0), False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsPositiveIntChecked2.__qualname__

            return ThisType.IsPositiveIntChecked(context, a)
        @staticmethod
        def IsNonNegativeInt(a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             
            Args:
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a non-negative integer (a >= 0), False otherwise.
            """ 
            return (type(a) is int) and (a >= 0) 
        @staticmethod
        def IsNonNegativeIntChecked(context: str , a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             Assert if NOT. 
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a non-negative integer (a >= 0), False otherwise.
            """ 
            ThisType = __class__

            result: bool = ThisType.IsNonNegativeInt(a)
            checkf(result, context + ": a: " + str(a) + " is NOT BOTH an integer AND >= 0.")
            return result
        @staticmethod
        def IsNonNegativeIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is a non-negative integer (a >= 0).
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (int): The value to check.
            Returns:
                bool: True if 'a' is a non-negative integer (a >= 0), False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsNonNegativeIntChecked2.__qualname__

            return ThisType.IsNonNegativeIntChecked(context, a)
        @staticmethod
        def IsIntGreaterThanChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsIntGreaterThanChecked2.__qualname__

            return ThisType.IsIntGreaterThanChecked(context, a, b)
        @staticmethod
        def IsIntGreaterThanRaiseError(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
            """
            IsIntRaiseError(context, a)
            IsIntRaiseError(context, b)

            if a <= b:
                raise Exception(f"{context}: a: {str(a)} is NOT > b: {str(b)} .")
            return True
        @staticmethod
        def IsIntGreaterThanOrEqualChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsIntGreaterThanOrEqualChecked2.__qualname__

            return ThisType.IsIntGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsIntLessThanChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsIntLessThanChecked2.__qualname__

            return ThisType.IsIntLessThanChecked(context, a, b)
        @staticmethod
        def IsIntLessThanOrEqualChecked(context: str, a: int, b: int) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (int): The first value to compare.
                b       (int): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsIntLessThanOrEqualChecked2.__qualname__

            return ThisType.IsIntLessThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsIntInRangeInclusiveChecked(context: str, a: int, l: int, r: int) -> bool:
            """
            Get whether or not 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (int): The value to check.
                l       (int): The lower bound of the range.
                r       (int): The upper bound of the range.
            Returns:
                bool: True if 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE, False otherwise.
            """
            ThisType = __class__
            
            return ThisType.IsIntGreaterThanOrEqualChecked(context, a, l) and ThisType.IsIntLessThanOrEqualChecked(context, a, r)
        @staticmethod
        def IsIntInRangeInclusiveChecked2(a: int, l: int, r: int) -> bool:
            """
            Get whether or not 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (int): The value to check.
                l       (int): The lower bound of the range.
                r       (int): The upper bound of the range.
            Returns:
                bool: True if 'a' is in the RANGE [l, r] (l <= a <= r) INCLUSIVE, False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsIntInRangeInclusiveChecked2.__qualname__

            return ThisType.IsIntInRangeInclusiveChecked(context, a, l, r)
        # Flag
        @staticmethod
        def BitFlag_Test(bitmask: int, bit: int) -> bool:
            ThisType = __class__

            check(ThisType.IsNonNegativeInt(bitmask))
            check(ThisType.IsNonNegativeInt(bit))
            return (bitmask & bit) == bit
        @staticmethod
        def BitFlag_Set(bitmask: int, bit: int) -> int:
            ThisType = __class__

            check(ThisType.IsNonNegativeInt(bitmask))
            check(ThisType.IsNonNegativeInt(bit))

            return (bitmask | bit)
        @staticmethod
        def BitFlag_Clear(bitmask: int, bit: int) -> int:
            ThisType = __class__

            check(ThisType.IsNonNegativeInt(bitmask))
            check(ThisType.IsNonNegativeInt(bit))
            
            return (bitmask & (~bit))
        # Float
        @staticmethod
        def IsFloatGreaterThanChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsFloatGreaterThanChecked2.__qualname__

            return ThisType.IsFloatGreaterThanChecked(context, a, b)
        @staticmethod
        def IsFloatGreaterThanRaiseError(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN (>) 'b'.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is greater than 'b', False otherwise.
            """
            IsFloatRaiseError(context, a)
            IsFloatRaiseError(context, b)

            if a <= b:
                raise Exception(f"{context}: a: {str(a)} is NOT > b: {str(b)} .")
            return True
        @staticmethod
        def IsFloatGreaterThanOrEqualChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is greater than or equal to 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsFloatGreaterThanOrEqualChecked2.__qualname__

            return ThisType.IsFloatGreaterThanOrEqualChecked(context, a, b)
        @staticmethod
        def IsFloatLessThanChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN (<) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is less than 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsFloatLessThanChecked2.__qualname__

            return ThisType.IsFloatLessThanChecked(context, a, b)
        @staticmethod
        def IsFloatLessThanOrEqualChecked(context: str, a: float, b: float) -> bool:
            """
            Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
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
                NOTE: Allowed ONLY on Main Thread (Game Thread).
             
            Args:
                a       (float): The first value to compare.
                b       (float): The second value to compare.
            Returns:
                bool: True if 'a' is less than or equal to 'b', False otherwise.
            """
            ThisType = __class__
            context: str = __class__.IsFloatLessThanOrEqualChecked2.__qualname__

            return ThisType.IsFloatLessThanOrEqualChecked(context, a, b)