// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    public static class FCgCVars
    {
        #region "Input"

        public static FCgConsoleVariableLog LogInputs = new FCgConsoleVariableLog("log.inputs", false, "Log Inputs", (int)ECgConsoleVariableFlag.Console);
        public static FCgConsoleVariableLog LogInputAll = new FCgConsoleVariableLog("log.input.all", false, "Log Input All", (int)ECgConsoleVariableFlag.Console);
        public static FCgConsoleVariableLog LogInputActions = new FCgConsoleVariableLog("log.input.actions", false, "Log Input Actions", (int)ECgConsoleVariableFlag.Console);
        public static FCgConsoleVariableLog LogInputAxis = new FCgConsoleVariableLog("log.input.axis", false, "Log Input Axis", (int)ECgConsoleVariableFlag.Console);
        public static FCgConsoleVariableLog LogInputLocations = new FCgConsoleVariableLog("log.input.locations", false, "Log Input Locations", (int)ECgConsoleVariableFlag.Console);
        public static FCgConsoleVariableLog LogInputRotations = new FCgConsoleVariableLog("log.input.rotations", false, "Log Input Rotations", (int)ECgConsoleVariableFlag.Console);

        #endregion // Input
    }
}
