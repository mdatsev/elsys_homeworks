using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {
    public static ScoreManager Instance { get; private set; }
    public Text text;
    public float scorePerSecond = 1f;
    private float score;
    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Use this for initialization
    void Start () {
        score = 0;
	}
	
	// Update is called once per frame
	void Update () {
        string str = "Score: " + (int)score;
        text.text = str;
        score += scorePerSecond * Time.deltaTime;
    }

    internal void Increase(float v)
    {
        score += v;
    }
}
