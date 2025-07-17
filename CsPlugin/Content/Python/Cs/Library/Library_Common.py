# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import enum
from typing import Dict

# IMPORT

# Library
# - CsThread/Library/Library_Thread.py
import CsThread.Library.Library_Thread as CsThread_Library_Thread
# Utility
# - Cs/Utility/SysExceptHookHandler.py
import Cs.Utility.SysExceptHookHandler as Cs_SysExceptHookHandler

# ALIAS

# "alias" - library (py)
FPyThreadLibrary = CsThread_Library_Thread.NPyThread.FLibrary

# "alias" - class (py)
FPySysExceptHookHandler = Cs_SysExceptHookHandler.FPySysExceptHookHandler

class NPyCommon:
    class FLibrary:
        @staticmethod
        def checkf(condition: bool, message: str) -> bool:
            """
            Assert if condition is FALSE and display a message.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
            
            Args:
                condition   (bool): The condition to check.
                message     (str):  The message to display.
            Returns:
                bool: True if 'condition' is TRUE, False otherwise.
            """ 
            # NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
            try:
                FPyThreadLibrary.IsMainThreadChecked(f"{__class__.checkf.__qualname__}: message: {message}")
                assert type(condition) is bool, "condition is NOT of type: bool"
                assert condition, message
                return True
            except AssertionError:
                FPySysExceptHookHandler.Get().Assertion(message)
                return False
        @staticmethod
        def check(condition: bool) -> bool:
            """
            Assert if condition is FALSE
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                condition (bool): The condition to check.
            Returns:
                bool: True if 'condition' is TRUE, False otherwise.
            """ 
            # NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
            try:
                FPyThreadLibrary.IsMainThreadChecked(__class__.check.__qualname__)
                assert type(condition) is bool, "condition is NOT of type: bool"
                assert condition
                return True
            except AssertionError:
                FPySysExceptHookHandler.Get().Assertion("")
                return False
        @staticmethod
        def IsStringChecked(context: str, s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 
                NOTE: Allowed ONLY on Main Thread (Game Thread).
                
            Args:
                context (str): The calling context.
                s:      (str): The string to check.
            Returns:
                bool: True if 's' is a string, False otherwise.
            """ 
            ThisType = __class__

            result: bool = type(s) is str
            ThisType.checkf(result, f"{context}: s: {str(s)} is NOT a string.")
            return result
        @staticmethod
        def IsStringChecked2(s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                s: (str): The string to check.
            Returns:
                bool: True if 's' is a string, False otherwise.
            """ 
            ThisType = __class__

            result: bool = type(s) is str
            ThisType.checkf(result, f"{__class__.IsStringChecked2.__qualname__}: s: {str(s)} is NOT a string.")
            return result
        @staticmethod
        def IsStringRaiseError(context: str, s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                s:      (str): The string to check.
            Returns:
                bool: True if 's' is a string, False otherwise.
            """ 
            ThisType = __class__

            result: bool = type(s) is str

            if not result:
                raise Exception(f"{context}: s: {str(s)} is NOT a string.")
            return result
        @staticmethod
        def IsStringRaiseError2(s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                s:      (str): The string to check.
            Returns:
                bool: True if 's' is a string, False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsStringRaiseError2.__qualname__

            result: bool = type(s) is str

            if not result:
                raise Exception(f"{context}: s: {str(s)} is NOT a string.")
            return result
        @staticmethod
        def IsStringNotEmptyChecked(context, s) -> bool:
            """
            Get whether or not 's' is NOT empty ('').
             Assert if NOT. 
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                s:      (str): The string to check.
            Returns:
                bool: True if 's' is NOT empty, False otherwise.
            """ 
            ThisType = __class__

            ThisType.check(ThisType.IsStringChecked(context, s))
            ThisType.checkf(s != "", f"{context}: s: {s} is EMPTY.")
            return True
        @staticmethod
        def IsStringNotEmptyRaiseError(context, s) -> bool:
            """
            Get whether or not 's' is NOT empty ('').
             Assert if NOT. 
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                s:      (str): The string to check.
            Returns:
                bool: True if 's' is NOT empty, False otherwise.
            """ 
            ThisType = __class__

            try:
                ThisType.IsStringRaiseError(context, s)
            except Exception as e:
                raise e
            
            if s == "":
                raise Exception(f"{context}: s: {s} is EMPTY.")
            return True
        @staticmethod
        def IsNotNoneChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is NOT None.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                o:      (any): The object to check.
            Returns:
                bool: True if 'o' is NOT None, False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            ThisType.checkf(o != None, f"{context}: o: is None.")
            return True
        @staticmethod
        def IsValidObject(o: any) -> bool:
            """
            Get whether or not 'o' is a valid object.
            
            Args:
                o: (any): The object to check.
            Returns:
                bool: True if 'o' is a valid object, False otherwise.
            """ 
            return o != None and isinstance(o, object)
        @staticmethod
        def IsValidObjectChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is a valid object.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                o:      (any): The object to check.
            Returns:
                bool: True if 'o' is a valid object, False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            result: bool = ThisType.IsValidObject(o)
            ThisType.checkf(result, f"{context}: o: {str(o)} is NOT a Valid Object.")
            return result
        @staticmethod
        def IsValidObjectRaiseError(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is a valid object.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                o:      (any): The object to check.
            Returns:
                bool: True if 'o' is a valid object, False otherwise.
            """ 
            ThisType = __class__

            try:
                ThisType.IsStringRaiseError2(context)
            except Exception as e:
                raise e

            result: bool = ThisType.IsValidObject(o)

            if not result:
                raise Exception(f"{context}: o: {str(o)} is NOT a Valid Object.")
            return result
        @staticmethod
        def IsClassChecked(context: str, c: type) -> bool:
            """
            Get whether or not 'c' is a class.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
             
            Args:
                context (str): The calling context.
                c:      (any): The class type to check.
            Returns:
                bool: True if 'c' is a class, False otherwise.
            """ 
            ThisType = __class__

            result: bool = isinstance(c, type)
            ThisType.checkf(result, f"{context}: c: {type(c)} is NOT a class.")
            return result
        @staticmethod
        def IsClassRaiseError(context: str, c: type) -> bool:
            """
            Get whether or not 'c' is a class.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
             
            Args:
                context (str): The calling context.
                c:      (any): The class type to check.
            Returns:
                bool: True if 'c' is a class, False otherwise.
            """ 
            ThisType = __class__

            try:
                ThisType.IsStringRaiseError2(context)
            except Exception as e:
                raise e

            result: bool = isinstance(c, type)

            if not result:
                raise Exception(f"{context}: c: {type(c)} is NOT a class.")
            return result
        @staticmethod
        def IsClassQualNameChecked(context: str, o: any, qual_name: str) -> bool:
            """
            Get whether or not 'o' is an object of a class with the given 'qual_name'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
             
            Args:
                context     (str): The calling context.
                o:          (any): The object to check.
                qual_name:  (str): The class qual name to check.
            Returns:
                bool: True if 'o' is an object of a class with the given 'qual_name', False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsValidObjectChecked(context, o)
            ThisType.IsStringChecked(context, qual_name)

            result: bool = o.__class__.__qualname__ == qual_name
            ThisType.checkf(result, f"{context}: o: {o.__class__.__qualname__} is NOT a class with the given qual_name: {qual_name}.")
            return result
        @staticmethod
        def IsInstanceOfChecked(context: str, a: any, c: type) -> bool:
            """
            Get whether or not 'a' is an instance of 'c'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a:      (any): The object to check.
                c:      (any): The class type to check.
            Returns:
                bool: True if 'a' is an instance of 'c', False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsValidObjectChecked(context, a)
            ThisType.IsClassChecked(context, c)

            result: bool = isinstance(a, c)
            ThisType.checkf(result, f"{context}: a: {str(a)} of type: {type(a)} is NOT an instance of c: {type(c)} | {c.__module__}.{c.__qualname__ }.")
            return result
        @staticmethod
        def IsInstanceOf(a: any, c: any) -> bool:
            """
            Get whether or not 'a' is an instance of 'c'.

            Args:
                a: (any): The object to check.
                c: (any): The class type to check.
            Returns:
                bool: True if 'a' is an instance of 'c', False otherwise.
            """ 
            ThisType = __class__

            if ThisType.IsValidObject(a) == False:
                return False
            if c == None:
                return False
            if isinstance(c, type) == False:
                return False
            return isinstance(a, c)
        @staticmethod
        def IsInstanceOfRaiseError(context: str, a: any, c: type) -> bool:
            """
            Get whether or not 'a' is an instance of 'c'.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                a:      (any): The object to check.
                c:      (any): The class type to check.
            Returns:
                bool: True if 'a' is an instance of 'c', False otherwise.
            """ 
            ThisType = __class__

            try:
                ThisType.IsValidObjectRaiseError(context, a)
            except Exception as e:
                raise e

            try:
                ThisType.IsClassRaiseError(context, c)
            except Exception as e:
                raise e

            result: bool = isinstance(a, c)

            if not result:
                raise Exception(f"{context}: a: {str(a)} of type: {type(a)} is NOT an instance of c: {type(c)} | {c.__module__}.{c.__qualname__ }.")
            return result
        @staticmethod
        def IsTypeChecked(context: str, a: any, c: type) -> bool:
            """
            Get whether or not 'a' is of type 'c'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a:      (any): The object to check.
                c:      (type): The class type to check.
            Returns:
                bool: True if 'a' is an instance of 'c', False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsValidObjectChecked(context, a)
            ThisType.checkf(issubclass(c, type), f"{context}: c: {type(c)} is NOT a class.")

            result: bool = type(a) is c
            ThisType.checkf(result, f"{context}: a: {str(a)} of type: {type(a)} is NOT of type: {type(c)} | {c.__module__}.{c.__qualname__ }.")
            return result
        @staticmethod
        def IsEnumChecked(context: str, a: any, c: any) -> bool:
            """
            Get whether or not 'a' is of an enum of type 'c'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a:      (any): The object to check.
                c:      (type): The enum type to check.
            Returns:
                bool: True if 'a' is an instance of 'c', False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsValidObjectChecked(context, a)
            ThisType.checkf(issubclass(c, enum.Enum), f"{context}: c: {type(c)} is NOT a class.")

            result: bool = str(type(a)) == str(c)
            ThisType.checkf(result, f"{context}: a: {str(a)} of type: {type(a)} is NOT of type: {type(c)} | {c.__module__}.{c.__qualname__ }.")
            return result
        @staticmethod
        def IsFunction(func: any) -> bool:
            """
            Get whether or not 'func' is a function. 

            Args:
                func: (any): The function to check.
            Returns:
                bool: True if 'func' is a function, False otherwise.
            """ 
            return callable(func)
        @staticmethod
        def IsFunctionChecked(context: str, func: any) -> bool:
            """
            Get whether or not 'func' is a function. 
             Assert if NOT. 
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                func:   (any): The function to check.
            Returns:
                bool: True if 'func' is a function, False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            result: bool = ThisType.IsFunction(func)
            ThisType.checkf(result, f"{context}: func: {str(func)} is NOT a function.")
            return result
        @staticmethod
        def IsValidDict(o: any) -> bool:
            """
            Get whether or not 'o' is a valid dictionary or not.

            Args:
                o: (any): The object to check.
            Returns:
                bool: True if 'o' is a valid dictionary / dict, False otherwise.
            """ 
            return type(o) is dict
        @staticmethod
        def IsValidDictChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is a valid dictionary / dict.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                o:      (any): The object to check.
            Returns:
                bool: True if 'o' is a valid dictionary / dict, False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            result: bool = ThisType.IsValidDict(o)
            ThisType.checkf(result, f"{context}: o: {str(o)} of type: {type(o)} is NOT a Valid Dictionary.")
            return result
        @staticmethod
        def IsValidDictRaiseError(context: str, o: Dict) -> bool:
            """
            Get whether or not 'o' is a valid dictionary / dict.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str):  The calling context.
                o:      (Dict): The object to check is a dictionary.
            Returns:
                bool: True if 'o' is a valid dictionary / dict, False otherwise.
            """ 
            ThisType = __class__

            try:
                ThisType.IsStringRaiseError2(context)
            except Exception as e:
                raise e

            result: bool = ThisType.IsValidDict(o)

            if not result:
                raise Exception(f"{context}: o: {str(o)} of type: {type(o)} is NOT a Valid Dictionary.")
            return result
        @staticmethod
        def DoesKeyExistChecked(context: str, d: dict, key: str) -> bool:
            """
            Get whether or not 'key' is a key for dictionary 'd'.
             Assert if NOT.

            Args:
                context (str): The calling context.
                d:      (dict): The dictionary to check.
                key:    (str):  The key to check.
            Returns:
                bool: True if 'key' is a key for dictionary 'd', False otherwise.
            """ 
            ThisType = __class__

            ThisType.check(ThisType.IsValidDictChecked(context, d))
            ThisType.check(ThisType.IsStringChecked(context, key))
            ThisType.checkf(key in d, f"{context}: o does NOT contain key: {key}")
            return True
        @staticmethod
        def DoesKeyExist(d: dict, key: str) -> bool:
            """
            Get wheter or not 'key' is a key for dictionary 'd'. 
             Assert if NOT.

            Args:
                d:      (dict): The dictionary to check.
                key:    (str):  The key to check.
            Returns:
                bool: True if 'key' is a key for dictionary 'd', False otherwise.
            """ 
            ThisType = __class__

            if ThisType.IsValidDict(d) == False:
                return False
            return key in d
        @staticmethod
        def DoesKeyNotExistChecked(context: str, d: dict, key: str) -> bool:
            """
            Get whether or not 'key' is NOT a key for dictionary 'd'.
             Assert if key ALREADY exists.

            Args:
                context (str): The calling context.
                d:      (dict): The dictionary to check.
                key:    (str):  The key to check.
            Returns:
                bool: True if 'key' is NOT a key for dictionary 'd', False otherwise.
            """ 
            ThisType = __class__

            ThisType.check(ThisType.IsValidDictChecked(context, d))
            ThisType.check(ThisType.IsStringChecked(context, key))
            ThisType.checkf(key not in d, f"{context}: o does contain key: {key}")
            return True
        @staticmethod
        def DoesKeyOfInstanceExistChecked(context: str, d: dict, key: str, classType: any) -> bool:
            """
            Get whether or not 'key' is a key for dictionary 'd' and is of type 'classType'.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context     (str):  The calling context.
                d:          (dict): The dictionary to check.
                key:        (str):  The key to check.
                classType:  (any):  The class type to check.
            Returns:
                bool: True if 'key' is a key for dictionary 'd' and is of type 'classType', False otherwise.
            """
            ThisType = __class__

            ThisType.check(ThisType.DoesKeyExistChecked(context, d, key))
            ThisType.check(ThisType.IsInstanceOfChecked(context, d[key], classType))
            return True
        @staticmethod
        def DoesKeyOfBoolExist(d: dict, key: str) -> bool:
            """
            Get whether or not 'key' is a key for dictionary 'd' and is of type bool.

            Args:
                d:      (dict): The dictionary to check.
                key:    (str):  The key to check.
            Returns:
                bool: True if 'key' is a key for dictionary 'd' and is of type bool, False otherwise.
            """
            ThisType = __class__

            if ThisType.DoesKeyExist(d, key) == False:
                return False
            return type(d[key]) is bool
        @staticmethod
        def DoesKeyOfBoolExistChecked(context: str, d: dict, key: str) -> bool:
            """
            Get whether or not 'key' is a key for dictionary 'd' and is of type bool.
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str):  The calling context.
                d:      (dict): The dictionary to check.
                key:    (str):  The key to check.
            Returns:
                bool: True if 'key' is a key for dictionary 'd' and is of type bool, False otherwise.
            """
            ThisType = __class__

            ThisType.check(ThisType.DoesKeyExistChecked(context, d, key))
            ThisType.checkf(type(d[key]) is bool, f"{context}: d[{key}]: {str(d[key])} is NOT of type: bool")
            return True
        @staticmethod
        def IsIntChecked(context: str, a: int) -> bool:
            """
            Get whether or not 'a' is an int (number). 
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context (str): The calling context.
                a:      (int): The value to check.
            Returns:
                bool: True if 'a' is an int (number), False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            result: bool = type(a) is int
            ThisType.checkf(result, f"{context}: a: {str(a)} is NOT a int.")
            return result
        @staticmethod
        def IsIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is an int (number). 
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a: (int): The value to check.
            Returns:
                bool: True if 'a' is an int (number), False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsIntChecked2.__qualname__

            return ThisType.IsIntChecked(context, a)
        @staticmethod
        def IsIntRaiseError(context: str, a: float) -> bool:
            """
            Get whether or not 'a' is an int (number). 
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                a:      (int): The value to check.
            Returns:
                bool: True if 'a' is an int (number), False otherwise.
            """
            ThisType = __class__

            ThisType.IsStringRaiseError2(context)

            if type(a) is not int:
                raise Exception(f"{context}: a: {str(a)} is NOT a int.")
            return True
        @staticmethod
        def IsFloatChecked(context: str, a: float) -> bool:
            """
            Get whether or not 'a' is an float / double (number). 
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                context    (str):   The calling context.
                a:         (float): The value to check.
            Returns:
                bool: True if 'a' is an float / double (number), False otherwise.
            """ 
            ThisType = __class__

            ThisType.IsStringChecked2(context)
            result: bool = type(a) is float
            ThisType.checkf(result, f"{context}: a: {str(a)} is NOT a float.")
            return result
        @staticmethod
        def IsFloatChecked2(a: float) -> bool:
            """
            Get whether or not 'a' is an float / double (number). 
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Args:
                a: (float): The value to check.
            Returns:
                bool: True if 'a' is an float / double (number), False otherwise.
            """ 
            ThisType = __class__
            context: str = __class__.IsFloatChecked2.__qualname__

            return ThisType.IsFloatChecked(context, a)
        @staticmethod
        def IsFloatRaiseError(context: str, a: float) -> bool:
            """
            Get whether or not 'a' is an float / double (number). 
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str):   The calling context.
                a:      (float): The value to check.
            Returns:
                bool: True if 'a' is an float / double (number), False otherwise.
            """
            ThisType = __class__

            ThisType.IsStringRaiseError2(context)

            if type(a) is not float:
                raise Exception(f"{context}: a: {str(a)} is NOT a float.")
            return True
        @staticmethod
        def IsIntOrFloat(a: any) -> bool:
            """
            Get whether or not 'a' is a int or float. 

            Args:
                a: (float): The value to check.
            Returns:
                bool: True if 'a' is an float / double (number), False otherwise.
            """ 
            return (type(a) is int) or (type(a) is float)
        @staticmethod
        def IsNumberChecked(context: str, a: any) -> bool:
            """
            Get whether or not 'a' is a number (int or float). 
             Assert if NOT.
                NOTE: Allowed ONLY on Main Thread (Game Thread).
            
            Args:
                context (str): The calling context.
                a:      (any): The value to check.
            Returns:
                bool: True if 'a' is a number (int or float), False otherwise.
            """ 
            ThisType = __class__
            return ThisType.checkf((type(a) is int) or (type(a) is float), f"{context}: a: {str(a)} is NOT a number (int or float)")
        class FDisableCheck:
            @staticmethod
            def checkf(condition, method):
                return True
            @staticmethod
            def Setup():
                NPyCommon.FLibrary.checkf = NPyCommon.FLibrary.FDisableCheck.checkf