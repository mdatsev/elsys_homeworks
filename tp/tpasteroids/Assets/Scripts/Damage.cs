using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Damage : MonoBehaviour {

    [Serializable]
    public struct TagDamage
    {
        public string tag;
        public int damage;
    }
    public TagDamage[] damages;
    
    public int? getDamageFor(string tag)
    {
        for(int i = 0; i < damages.Length; i++)
        {
            if (damages[i].tag == tag)
                return damages[i].damage;
        }
        return null;
    }
}
