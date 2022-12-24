# How TerGen works:

TerGen works by generating a 2D map of Nodes, where one node contains the 
Height (double) and a colour (unsigned char). The Height represents the height of the node as if it would be in a 3D space.
The colour of a node represents what type a node is. 
If a function is set to represent the bushes, let�s say it has the colour 1, then the output maps all Nodes that have the colour 1 represent a bush.
If a single node has the Height value of 1, and it has nodes surrounding at height 0, and this single node colour is different from its surrounding nodes,
then the surrounding nodes will be its floor nodes below it, and this single node is above them, like a tree is above ground.

TerGen works by giving it a pool of functions that it will generate the 2D space according to the order of the functions given.
This means that the first function needs to represent the floor generating function (e.g. Perlin noise).
All functions will automatically allocate a colour for themselves, this of course implies that the user needs to know the order of the functions given to Tergen, color counting will always start from 0, and go on until 255. 
TerGen can support 3D spaces, by layering 2D chunks above each other. TerGen should be able to generate whole cities simply by algorithmic functions. 
