#ifndef _DATA_H_
#define _DATA_H_

#include "Utils.h"


#include <vector>

namespace TerGen{

    // This hold all the data.
    class Node{
    public:
        double Temperature;
        double Humidity;         // When humidity is 1, then water.
        Vector2 Wind_Current;

        double Height;

        Node(){}

        Node(double height, double humidity, double temperature){
            Height = height;
            Humidity = humidity;
            Temperature = temperature;
            Wind_Current = Vector2(0, 0);
        }

    };

    class Chunk{
    public:
        Vector3 Position;
        Vector2 Dimensions;

        std::vector<Node> Childs;
        
        Chunk(){}

        // NOTE: This automatically setups the elevation for its contents.
        Chunk(Vector3 position, Vector2 dimensions);
    };

    inline std::map<Vector3, Chunk> Chunks;



}

#endif