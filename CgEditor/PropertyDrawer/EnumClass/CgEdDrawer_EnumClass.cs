namespace CgEditor
{
    using System;
    using System.Reflection;

    using UnityEditor;
    using UnityEngine;

    using CgCore;
    
    public class FCgEdDrawer_EnumClass<EnumMap, EnumClass, EnumType> : PropertyDrawer
        where EnumMap : TCgEnumMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        private static EnumMap Map;

        private static readonly string[] EnumNames;

        private string Name;

        static FCgEdDrawer_EnumClass()
        {
            // Get Static Instance of Map
            MemberInfo[] members = typeof(EnumMap).GetMember("Instance");

            Map = (EnumMap)((PropertyInfo)members[0]).GetValue(null, null);
            // Populate Enum Names
            EnumNames = GetEnumNames();
        }

        public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
        {
            // Property Name
            GUIContent name      = new GUIContent(property.displayName);
            Rect contentPosition = EditorGUI.PrefixLabel(position, name);

            // Value
            property.serializedObject.Update();

            EnumClass e = (EnumClass)property.objectReferenceValue;
            int newIndex = EditorGUI.Popup(contentPosition, e == null ? 0 : (int)(object)(e.Value), EnumNames);
            Debug.Log(Map.GetEnumAt(newIndex).Value);
            property.objectReferenceValue = Map.GetEnumAt(newIndex);

            property.serializedObject.ApplyModifiedProperties();
        }

        private static string[] GetEnumNames()
        {
            int count = Map.Count;

            string[] result = new string[count];

            for (int i = 0; i < count; ++i)
            {
                EnumClass e = Map.GetEnumAt(i);

                result[i] = e.Name;
            }
            return result;
        }
    }
}
