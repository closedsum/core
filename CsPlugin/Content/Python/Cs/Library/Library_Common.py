# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

class NPyCommon:
    class FLibrary:
        class NCached:
            class NStr:
                IsIntChecked2 = "NPyCommon.FLibary.IsIntChecked2"
                IsFloatChecked2 = "NPyCommon.FLibary.IsFloatChecked2"
        @staticmethod
        def checkf(condition: bool, message: str) -> bool:
            """
            Assert if condition is FALSE and display a message.

            :param bool condition:
            :param str message:
            :return: bool
            """ 
            # NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
            assert type(condition) is bool, "condition is NOT of type: bool"
            assert condition, message
            return True
        @staticmethod
        def check(condition: bool) -> bool:
            """
            Assert if condition is FALSE

            :param bool condition:
            :return: bool
            """ 
            # NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
            assert type(condition) is bool, "condition is NOT of type: bool"
            assert condition
            return True
        @staticmethod
        def IsStringChecked(context: str, s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 

            :param str context:
            :param str s:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            result: bool = type(s) is str
            lib.checkf(result, context + ": s: " + str(s) + " is NOT a string.")
            return result
        @staticmethod
        def IsStringChecked2(s: str) -> bool:
            """
            Get whether or not 's' is a string.
             Assert if NOT. 

            :param str s:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            result: bool = type(s) is str
            lib.checkf(result, "NPyCommon.FLibrary: s: " + str(s) + " is NOT a string.")
            return result
        @staticmethod
        def IsStringNotEmptyChecked(context, s) -> bool:
            """
            Get whether or not 's' is NOT empty ('').
             Assert if NOT. 

            :param str context:
            :param str s:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.check(lib.IsStringChecked(context, s))
            lib.checkf(s != "", context + ": s: " + s + " is EMPTY.")
            return True
        @staticmethod
        def IsNotNoneChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is NOT None.
             Assert if NOT.

            :param str context 
            :param any o:
            :return:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            lib.checkf(o != None, context + ": o: is None.")
            return True
        @staticmethod
        def IsValidObject(o: any) -> bool:
            """
            Get whether or not 'o' is a valid object.

            :param any o:
            :return:
            """ 
            return o != None and isinstance(o, object)
        @staticmethod
        def IsValidObjectChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is a valid object.
             Assert if NOT.

            :param str context 
            :param any o:
            :return:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            result: bool = lib.IsValidObject(o)
            lib.checkf(result, context + ": o: " + str(o) + " is NOT a Valid Object.")
            return result
        @staticmethod
        def IsClassChecked(context: str, c: type) -> bool:
            """
            Get whether or not 'c' is a class.
             Assert if NOT.

            :param str context 
            :param any c:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            result: bool = isinstance(c, type)
            lib.checkf(result, context + ": c: " + str(c) + " is NOT a class.")
            return result
        @staticmethod
        def IsInstanceOfChecked(context: str, a: any, c: type) -> bool:
            """
            Get whether or not 'a' is an instance of 'c'.
             Assert if NOT.

            :param str context 
            :param any a:
            :param any c:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsValidObjectChecked(context, a)
            lib.IsClassChecked(context, c)

            result: bool = isinstance(a, c)
            lib.checkf(result, context + ": a: " + str(a) + " is NOT an instance of c: " + str(c))
            return result
        @staticmethod
        def IsInstanceOf(a: any, c: any) -> bool:
            """
            Get whether or not 'a' is an instance of 'c'.

            :param any a:
            :param any c:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            if lib.IsValidObject(a) == False:
                return False
            if c == None:
                return False
            if isinstance(c, type) == False:
                return False
            return isinstance(a, c)
        @staticmethod
        def IsFunction(func: any) -> bool:
            """
            Get whether or not 'func' is a function. 

            :param any func:
            :return bool:
            """ 
            return callable(func)
        @staticmethod
        def IsFunctionChecked(context: str, func: any) -> bool:
            """
            Get whether or not 'func' is a function. 
             Assert if NOT. 

            :param str context:
            :param any func:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            result: bool = lib.IsFunction(func)
            lib.checkf(result, context + ": func: " + str(func) + " is NOT a function.")
            return result
        @staticmethod
        def IsValidDict(o: any) -> bool:
            """
            Get whether or not 'o' is a valid dictionary or not.

            :param any o:
            :return:
            """ 
            return type(o) is dict
        @staticmethod
        def IsValidDictChecked(context: str, o: any) -> bool:
            """
            Get whether or not 'o' is a valid dictionary / dict.
             Assert if NOT.

            :param str context 
            :param any o:
            :return:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            result: bool = lib.IsValidDict(o)
            lib.checkf(result, context + ": o: " + str(o) + " is NOT a Valid Dictionary.")
            return result
        @staticmethod
        def DoesKeyExistChecked(context: str, d: dict, key: str) -> bool:
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.check(lib.IsValidDictChecked(context, d))
            lib.check(lib.IsStringChecked(context, key))
            lib.checkf(key in dict, context + ": o does NOT contain key: " + key)
            return True
        @staticmethod
        def DoesKeyExist(d: dict, key: str) -> bool:
            """
            Get wheter or not 'key' is a key for dictionary 'd'. 
             Assert if NOT.

            :param dict d: 
            :param str key:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            if lib.IsValidDict(d) == False:
                return False
            return key in dict
        @staticmethod
        def DoesKeyOfInstanceExistChecked(context: str, d: dict, key: str, classType: any) -> bool:
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.check(lib.DoesKeyExistChecked(context, d, key))
            lib.check(lib.IsInstanceOfChecked(context, d[key], classType))
            return True
        @staticmethod
        def DoesKeyOfBoolExist(d: dict, key: str) -> bool:
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            if lib.DoesKeyExist(d, key) == False:
                return False
            return type(d[key]) is bool
        @staticmethod
        def DoesKeyOfBoolExistChecked(context: str, d: dict, key: str) -> bool:
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.check(lib.DoesKeyExistChecked(context, d, key))
            lib.checkf(type(d[key]) is bool, context + " d[" + str + "]: " + str(d[key]) + " is NOT of type: bool")
            return True
        @staticmethod
        def IsIntChecked(context: str, a: int) -> bool:
            """
            Get whether or not 'a' is an int (number). 
             Assert if NOT.

            :param str context:
            :param int a:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            result: bool = type(a) is int
            lib.checkf(result, context + ": a: " + str(a) + " is NOT a int.")
            return result
        @staticmethod
        def IsIntChecked2(a: int) -> bool:
            """
            Get whether or not 'a' is an int (number). 
             Assert if NOT.

            :param int a:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary
            context: str = lib.NCached.NStr.IsIntChecked2

            return lib.IsIntChecked(context, a)
        @staticmethod
        def IsFloatChecked(context: str, a: float) -> bool:
            """
            Get whether or not 'a' is an float / double (number). 
             Assert if NOT.

            :param str context:
            :param float a:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary

            lib.IsStringChecked2(context)
            result: bool = type(a) is float
            lib.checkf(result, context + ": a: " + str(a) + " is NOT a float.")
            return result
        @staticmethod
        def IsFloatChecked2(a: float) -> bool:
            """
            Get whether or not 'a' is an float / double (number). 
             Assert if NOT.

            :param float a:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary
            context: str = lib.NCached.NStr.IsFloatChecked2

            return lib.IsFloatChecked(context, a)
        @staticmethod
        def IsIntOrFloat(a: any) -> bool:
            """
            Get whether or not 'a' is a int or float. 

            :param any a:
            :return bool:
            """ 
            return (type(a) is int) or (type(a) is float)
        @staticmethod
        def IsNumberChecked(context: str, a: any) -> bool:
            """
            Get whether or not 'a' is a number (int or float). 
             Assert if NOT.
            
            :param str context:
            :param any a:
            :return bool:
            """ 
            lib: NPyCommon.FLibrary = NPyCommon.FLibrary
            return lib.checkf((type(a) is int) or (type(a) is float), context + " a: " + str(a) + " is NOT a number (int or float)")
        class FDisableCheck:
            @staticmethod
            def checkf(condition, method):
                return True
            @staticmethod
            def Setup():
                NPyCommon.FLibrary.checkf = NPyCommon.FLibrary.FDisableCheck.checkf