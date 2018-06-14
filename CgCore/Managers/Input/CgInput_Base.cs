// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    public abstract class FCgInput_Base
    {
        public ECgInputAction Action;
        public FCgInputInfo Info;
        public int ActionMap;
        public FCgManager_Input Manager_Input;

        public FCgInput_Base()
        {
            Action = null;
            ActionMap = 0;
            Manager_Input = null;
        }
    }
}
