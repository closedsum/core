// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    public static class CgCVars
    {
        #region "Input"

        public static CgConsoleVariableLog LogInputs = new CgConsoleVariableLog("log.inputs", false, "Log Inputs", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputAll = new CgConsoleVariableLog("log.input.all", false, "Log Input All", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputActions = new CgConsoleVariableLog("log.input.actions", false, "Log Input Actions", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputAxis = new CgConsoleVariableLog("log.input.axis", false, "Log Input Axis", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputLocations = new CgConsoleVariableLog("log.input.locations", false, "Log Input Locations", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputRotations = new CgConsoleVariableLog("log.input.rotations", false, "Log Input Rotations", (int)ECgConsoleVariableFlag.Console);

        #endregion // Input

        #region "Coroutine"

        public static CgConsoleVariableLog LogCoroutineTransactions = new CgConsoleVariableLog("log.coroutine.transactions", false, "Log Coroutine Scheduler Allocation and DeAllocation.", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogCoroutineRunning = new CgConsoleVariableLog("log.coroutine.running", false, "Log Coroutines currently running.", (int)ECgConsoleVariableFlag.Console);

        #endregion // Coroutine
    }
}
