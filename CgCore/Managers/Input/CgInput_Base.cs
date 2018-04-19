// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    public abstract class CgInput_Base
    {
        public ECgInputAction Action;
        public CgInputInfo Info;
        public int ActionMap;
        public CgManager_Input Manager_Input;

        public CgInput_Base()
        {
            Action = null;
            ActionMap = 0;
            Manager_Input = null;
        }
    }
}
