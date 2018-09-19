namespace CgEditor
{
    using UnityEngine;
    using UnityEditor;
    using System.Collections;

    using CgCore;

    [CustomPropertyDrawer(typeof(FCgReadOnlyAttribute))]
    public class ReadOnlyPropertyDrawer : PropertyDrawer
    {
        public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
        {
            GUI.enabled = false;
            EditorGUI.PropertyField(position, property, label);
            GUI.enabled = true;
        }
    }
}
