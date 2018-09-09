namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using System.Reflection;
    using System;
    using UnityEngine;
    using UnityEditor;

    public class FCgPlayInEditor
    {
        #region "Data Members"

        private static FCgPlayInEditor _Instance;
        public static FCgPlayInEditor Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgPlayInEditor();
                }
                return _Instance;
            }
        }

        public Assembly EditorAssembly;
        public EditorWindow GameEditorWindow;

        public FieldInfo GizmoField;
        public bool GizmoFieldInitialValue;
        public bool GizmoFieldCurrentValue;
        public int GizmoFieldCounter;

        #endregion // Data Members

        public FCgPlayInEditor()
        {
            MCgGameInstance.Get().OnExitingPlayMode_Event.Add(OnExitingPlayMode);

            EditorAssembly   = Assembly.GetAssembly(typeof(UnityEditor.Editor));
            Type type        = EditorAssembly.GetType("UnityEditor.GameView");
            GameEditorWindow = EditorWindow.GetWindow(type);

            // GizmoField
            GizmoField = type.GetField("m_Gizmos", BindingFlags.NonPublic | BindingFlags.Instance);

            GizmoFieldInitialValue = (bool)GizmoField.GetValue(GameEditorWindow);
            GizmoFieldCurrentValue = GizmoFieldInitialValue;
        }

        public static FCgPlayInEditor Get()
        {
            return Instance;
        }

        public void OnExitingPlayMode()
        {
            GizmoField.SetValue(GameEditorWindow, GizmoFieldInitialValue);
        }

        public void SetGizmoField()
        {
            if (!GizmoFieldCurrentValue)
                GizmoField.SetValue(GameEditorWindow, true);

            GizmoFieldCurrentValue = true;
            ++GizmoFieldCounter;
        }

        public void ClearGizmoField()
        {
            --GizmoFieldCounter;

            if (GizmoFieldCounter <= 0)
            {
                if (GizmoFieldCurrentValue)
                    GizmoField.SetValue(GameEditorWindow, false);

                GizmoFieldCurrentValue = false;
                GizmoFieldCounter      = 0;
            }
        }
    }
}
