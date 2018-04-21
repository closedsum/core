// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    public static class CgCVars
    {
        public static CgConsoleVariableLog LogInputs = new CgConsoleVariableLog("log.inputs", false, "Log Inputs", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogInputAll = new CgConsoleVariableLog("log.inputs.all", false, "Log Input All", (int)ECgConsoleVariableFlag.Console);
    }
}
