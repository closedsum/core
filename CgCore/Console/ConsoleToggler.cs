using UnityEngine;
using System.Collections;

public class ConsoleToggler : MonoBehaviour
{
    private bool Enabled = false;
    public ConsoleAction OpenAction;
    public ConsoleAction CloseAction;

    void Update ()
    {
        if (Input.GetKeyDown(KeyCode.BackQuote))
        {
            ToggleConsole();
        }
    }

    private void ToggleConsole()
    {
        Enabled = !Enabled;

        if (Enabled)
        {
            OpenAction.Activate();
        }
        else
        {
            CloseAction.Activate();
        }
    }
}
