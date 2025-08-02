from enum import Enum
import importlib

# IMPORT

# Library
import Cs.Library.Library_Common as CsLibrary_Common

# ALIAS

# "alias" - library (py)
FPyCommonLibrary = CsLibrary_Common.NPyCommon.FLibrary

# "alias" - function (py)
check                   = FPyCommonLibrary.check
checkf                  = FPyCommonLibrary.checkf
IsStringNotEmptyChecked = FPyCommonLibrary.IsStringNotEmptyChecked
IsEnumChecked           = FPyCommonLibrary.IsEnumChecked

class FPyLog:
    class EType(Enum):
        PRINT = 0
        UE_LOG = 1
        UE_LOG_WARNING = 2
        UE_LOG_ERROR = 3
        UE_LOG_FATAL = 4

        @staticmethod
        def ToEnumChecked(context: str, value: str) -> 'FPyLog.EType':
            """
            Converts a string to an EType enum value.

            Args:
                context: (str): The context of the caller.
                value:   (str): The value to convert to an EService enum value.

            Returns:
                NPyGenAI.EService: Enum associated with value.
            """

            checkf(IsStringNotEmptyChecked(context, value), f"{context}: value is NOT a valid string.")

            value = value.upper()

            try:
                return FPyLog.EType[value]
            except KeyError:
                checkf(False, f"{context}: {value} is NOT a Value FPyLog.EType member.")
                return FPyLog.EType.PRINT
            
    @staticmethod
    def Log(log_type: str | EType, message: str):
        context: str = __class__.Log.__qualname__

        if isinstance(log_type, str):
            log_type = FPyLog.EType.ToEnumChecked(context, log_type)

        check(IsEnumChecked(context, log_type, FPyLog.EType))
        check(IsStringNotEmptyChecked(context, message))

        # Print
        if log_type == FPyLog.EType.PRINT:
            print(message)
        else:
            ue = importlib.import_module("unreal")

            if ue is None:
                checkf(False, f"{context}: unreal is NOT imported.")
                return
            
            # UE Logs
            match log_type:
                # Log
                case FPyLog.EType.UE_LOG:
                    ue.log(message)
                # Warning
                case FPyLog.EType.UE_LOG_WARNING:
                    ue.log_warning(message)
                # Error
                case FPyLog.EType.UE_LOG_ERROR:
                    ue.log_error(message)
                # Fatal
                case FPyLog.EType.UE_LOG_FATAL:
                    ue.log_fatal(message)