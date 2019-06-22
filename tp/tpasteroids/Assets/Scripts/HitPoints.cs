using UnityEngine;
using UnityEngine.UI;

// DON'T USE THIS DEPRECATED!!!
public class HitPoints : MonoBehaviour {
    public int hitPoints = 1;
    void OnCollisionEnter(Collision collision)
    {
        var dmgComponent = collision.gameObject.GetComponent<Damage>();
        if (dmgComponent == null) return;
        int? damage = dmgComponent.getDamageFor(gameObject.tag);
        if (damage == null) return;
        hitPoints--;
        if(hitPoints <= 0)
            Destroy(gameObject);
    }

}
// DON'T USE THIS DEPRECATED!!!
