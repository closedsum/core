﻿namespace CgCore
{
    using System;

    [Flags]
    public enum ECgConsoleVariableFlag
    {
        Default = 0,
        Console = 1
    }

    public interface ICgConsoleVariable
    {
        string Name { get; set; }
        string Description { get; set; }
        int Flag { get; set; }
    }

    public class TCgConsoleVariable<T> : ICgConsoleVariable where T : struct
    {
        #region "Data Members"

        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        private string description;
        public string Description
        {
            get
            {
                return description;
            }
            set
            {
                description = value;
            }
        }

        private int flag;
        public int Flag
        {
            get
            {
                return flag;
            }
            set
            {
                flag = value;
            }
        }

        public TCgPrimitiveType<T> Value;

        #endregion // Data Members

        public TCgConsoleVariable(string inName, T inValue, string inDescription, int inFlag)
        {
            Name = inName;
            Set(inValue);
            Description = inDescription;
            Flag = inFlag;

            ConsoleCommandsRepository.Instance.RegisterCommand(inName, Set);
        }

        public T Get()
        {
            return Value.Get();
        }

        public void Set(T inValue)
        {
            Value.Set(inValue);
        }

        public string Set(params string[] args)
        {
            if (args.Length == 0)
                return "Failed to set " + Name;

            Value.Set((T)Convert.ChangeType((object)args[0], typeof(T)));

            return Name + " set to " + Value.ToString();
        }

        public void AddEvent(TCgDelegate_OneParam<T>.Event_OneParam del)
        {
            Value.OnChange_Event.Add(del);
        }
    }

    public sealed class CgConsoleVariableLog : TCgConsoleVariable<bool>
    {
        public CgConsoleVariableLog(string inName, bool inValue, string inDescription, int inFlag) : base(inName, inValue, inDescription, inFlag) { }

        public bool Show()
        {
            return Get();
        }
    }

    public sealed class CgConsoleVariableDraw : TCgConsoleVariable<bool>
    {
        public CgConsoleVariableDraw(string inName, bool inValue, string inDescription, int inFlag) : base(inName, inValue, inDescription, inFlag) { }

        public bool Draw()
        {
            return Get();
        }
    }
}
