using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ConsoleGUI : MonoBehaviour
{
    public ConsoleAction EscapeAction;
    public ConsoleAction SubmitAction;

    [HideInInspector]
    public string CurrentInput = "";
    private ConsoleLog Log;
    private Rect consoleRect;
    private bool Focus = false;
    private const int WINDOW_ID = 50;
    private const int MIN_CONSOLE_HEIGHT = 300;

    private ConsoleCommandsRepository CommandsRepository;

    private int MaxHistorySize = 100;
    private int HistoryPosition = 0;
    private List<string> HistoryCommands = new List<string>();
    // A hack because the up arrow moves the cursor to the first position.
    private bool FixPositionNextFrame = false; 

    private float ScrollPosition;


    private void Start()
    {
        consoleRect        = new Rect(0, 0, Screen.width, Mathf.Min(MIN_CONSOLE_HEIGHT, Screen.height));
        Log                = ConsoleLog.Instance;
        CommandsRepository = ConsoleCommandsRepository.Instance;
    }

    private void OnEnable()
    {
        Focus = true;
    }

    private void OnDisable()
    {
        Focus = true;
    }

    public void OnGUI()
    {
        GUILayout.Window(WINDOW_ID, consoleRect, RenderWindow, "Console");
    }

    private void RenderWindow(int id)
    {
        if (FixPositionNextFrame)
        {
            MoveCursorToPos(CurrentInput.Length);
            FixPositionNextFrame = false;
        }

        HandleSubmit();
        HandleEscape();
        HandleTab();
        HandleUp();
        HandleDown();

        ScrollPosition = GUILayout.BeginScrollView(new Vector2(0, ScrollPosition), false, true).y;

        if (Log.Refresh)
        {
            ScrollPosition  = Log.ScrollLength;
            Log.Refresh     = false;
        }

        GUILayout.Label(Log.Output);
        GUILayout.EndScrollView();
        GUI.SetNextControlName("CurrentInput");

        CurrentInput = GUILayout.TextField(CurrentInput);

        if (Focus)
        {
            GUI.FocusControl("CurrentInput");
            Focus = false;
        }
    }

    // takes two strings and returns the largest matching substring.
    private string LargestSubString(string in1, string in2) 
    {
        string output = "";
        int smallestLen = Mathf.Min(in1.Length, in2.Length);

        for (int i = 0; i < smallestLen; ++i)
        {
            if (in1[i] == in2[i])
                output += in1[i];
            else
                return output;
        }
        return output;
    }

    private void MoveCursorToPos(int position)
    {
        TextEditor editor = (TextEditor)GUIUtility.GetStateObject(typeof(TextEditor), GUIUtility.keyboardControl);
        editor.selectIndex = position;
        editor.cursorIndex = position;
        return;
    }

    private void HandleTab()
    {
        if (!KeyDown("tab")) 
            return;
        // If NO Input, Exit
        if (CurrentInput == "")
            return;

        List<string> search = CommandsRepository.SearchCommands(CurrentInput);

        // NO Command found
        if (search.Count == 0)
        {
            Log.Log("No commands start with \"" + CurrentInput + "\".");
            // Clear CurrentInput
            CurrentInput = ""; 
        }
        // ONE Command found, Auto-complete the Command
        else
        if (search.Count == 1)
        {
            CurrentInput = search[0] + " "; 
            MoveCursorToPos(CurrentInput.Length);
        }
        // MULTIPLE Commands found.
        else
        {
            Log.Log("Commands starting with \"" + CurrentInput + "\":");
            // Keep track of the largest substring that matches all searches
            string largestMatch = search[0]; 

            foreach (string command in search)
            {
                Log.Log(command);
                largestMatch = LargestSubString(largestMatch, command);
            }
            CurrentInput = largestMatch;
            MoveCursorToPos(CurrentInput.Length);
        }
    }

    private void HandleUp()
    {
        if (!KeyDown("up"))
            return;

        HistoryPosition += 1;

        if (HistoryPosition > HistoryCommands.Count - 1)
            HistoryPosition = HistoryCommands.Count - 1;

        CurrentInput         = HistoryCommands[HistoryPosition];
        FixPositionNextFrame = true;
    }

    private void HandleDown()
    {
        if (!KeyDown("down"))
            return;

        --HistoryPosition;

        if (HistoryPosition < 0)
        {
            HistoryPosition = -1;
            CurrentInput = "";
        }
        else
        {
            CurrentInput = HistoryCommands[HistoryPosition];
        }
        MoveCursorToPos(CurrentInput.Length);
    }

    private void HandleSubmit()
    {
        if (KeyDown("[enter]") || KeyDown("return"))
        {
            // Up arrow or down arrow will set it to 0, which is the last command typed.
            HistoryPosition = -1; 

            if (SubmitAction != null)
            {
                SubmitAction.Activate();
                HistoryCommands.Insert(0, CurrentInput);

                if (HistoryCommands.Count > MaxHistorySize)
                    HistoryCommands.RemoveAt(HistoryCommands.Count - 1);
            }
            CurrentInput = "";
        }
    }

    private void HandleEscape()
    {
        if (KeyDown("escape") || KeyDown("`"))
        {
            EscapeAction.Activate();
            CurrentInput = "";
        }
    }

    private void Update()
    {
        if (CurrentInput == "`")
            CurrentInput = "";
    }

    private bool KeyDown(string key)
    {
        return Event.current.Equals(Event.KeyboardEvent(key));
    }
}
