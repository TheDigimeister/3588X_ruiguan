#include "main.h"

struct SensorData {
    float offsetX;
    float offsetY;
    std::string direction;
    float measuredDistance;
};

// Helper function to calculate X or Y coordinate given sensor and wall parameters
float positionFromRaycast(float sensorReading, float sensorOffset, WALL wall) {
    switch (wall) {
        case NORTH:
        case EAST:
            return 72.0 - (sensorReading + sensorOffset);
            break;
        case SOUTH:
        case WEST:
            return (sensorReading + sensorOffset) - 72.0;
            break;
        default:
            std::printf("Invalid Wall\n");
            return -1.0;
            break;
    }
}

float cheap_std_norm(float x) {
    return -0.5 * x * x;
}

float normalizeAngle (float angle) {
    while (angle > 360) angle -= 360;
    while (angle <= 0) angle += 360;
    return angle;
}