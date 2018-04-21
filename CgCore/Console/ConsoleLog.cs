using UnityEngine;
using System.Collections;

public class ConsoleLog
{
    private static ConsoleLog instance;
    public static ConsoleLog Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new ConsoleLog();
            }
            return instance;
        }
    }

    public string Output = "";
    public int ScrollLength;
    public bool Refresh = false;

    public void Log(string message)
    {
        Output       += message + "\n";
        Refresh       = true;
        ScrollLength += ((message + "\n").Split('\n').Length) * 20;
    }
}
