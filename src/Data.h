#ifndef _DATA_H_
#define _DATA_H_

#include "Utils.h"


#include <vector>

namespace TerGen{

    // This hold all the data.
    class Node{
    public:
        float Temperature;
        float Humidity;         // When humidity is 1, then water.

        float Height;

        Node(float temp, float hum, float height){

            Temperature = temp;
            Humidity = hum;
            Height = height;

        }
    
    };

    class Chunk{
    public:
        Vector3 Position;
        Vector2 Dimensions;

        std::vector<Node> Childs;

        Chunk(std::vector<Node> childs = {}){
            Childs = childs;
        }

        Chunk(Vector3 position, Vector2 dimensions){
            Position = position;
            Dimensions = dimensions;
        }
    };

    inline std::map<Vector3, Chunk> Chunks;



}

#endif