using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Global
{
    public static int width = 100;
    public static int height = 100;
    public static float nodeSize = 5;
    public static float[] layerlengths = {9,7,5,3,1};
    public static float Spacing = 3;
}

public class NeuralNetwork : MonoBehaviour
{
    public GameObject nodePrefab;
    List<List<GameObject>> objs;

    List<List<List<float>>> weights;
    List<List<Node>> layers;

    // Start is called before the first frame update
    void Start()
    {
        //for (int i = 1; i < Global.layerlengths.Length; i++)
        //{
        //    weights.Add(new List<List<float>>());
        //    for (int j = 0; j < Global.layerlengths[i]; j++)
        //    {
        //        weights[i].Add(new List<float>());
        //        for (int k = 0; k < Global.layerlengths[i - 1]; k++)
        //        {
        //            weights[i][j].Add(Random.Range(0.0f, 1.0f));
        //        }
        //    }
        //}

        for (int i = 0; i < Global.layerlengths.Length; i++)
        {
            //layers.Add(new List<Node>());
            //objs.Add(new List<GameObject>());
            for (int j = 0; j < Global.layerlengths[i]; j++)
            {
                //layers[i].Add(new Node());
                Instantiate(nodePrefab, new Vector3(Global.Spacing * i, 0, Global.Spacing * j + Global.Spacing * Mathf.Abs(Global.layerlengths[i] - Global.layerlengths[0]) / 2), Quaternion.identity);
                
            }
        }
    }
}