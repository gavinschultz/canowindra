// Defines the limits and geography of the world, using its own internal units

// arrays of coordinates, defining the terrain over which the player moves.
// 0.0, 0.0 (x-axis, y-axis) is beginning of world, sea-level.
// units are in meters
const float world_terrain[][] = { { 0.0, 1.0 }, { 1.0, 1.0 }, { 10.0, 1.5 } };

// distance of the background plane from the front terrain. Ultimately determines how fast the background plan parallax scrolls
const int world_background_plane_distance = 10000;


