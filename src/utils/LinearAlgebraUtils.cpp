#include "LinearAlgebraUtils.h"
#include <iostream>


float angleCCW(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) 
{
    glm::vec3 AB = A - B;
    glm::vec3 BC = C - B;

    if (glm::length(AB) > 0.001f)
        AB = glm::normalize(AB);

    if (glm::length(BC) > 0.001f)
        BC = glm::normalize(BC);

    float dot = glm::dot(AB, BC);
    float angle = std::acos(dot);

    glm::vec3 cross = glm::cross(AB, BC);
    float sign = glm::dot(glm::vec3(0, 0, 1), cross);

    if (sign < 0)
    {
        angle = 2 * M_PI - angle;
    }

    return angle;
}

bool isConvex(const glm::vec3& vertex_prev, const glm::vec3& vertex, const glm::vec3& vertex_next) 
{
    return angleCCW(vertex_next, vertex, vertex_prev) <= M_PI;
}

bool insideTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& P)
{

    // Calculates the distance of the point to the plane
    // if the distance d > 0.001 then too far from plane
    glm::vec3 n = glm::cross(B - A, C - A);
    if (glm::length(n) > 0.001f)
        n = glm::normalize(n);

    float d = glm::dot(n, P - B);
    if (abs(d) > 0.001f)
        return false;

    // Calculates the barycentric coordinates to determine if point is in triangle
    // Taken from Christer Ericson's Real-Time Collision Detections
    glm::vec3 v0 = C - A;
    glm::vec3 v1 = B - A;
    glm::vec3 v2 = P - A;

    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    float w = 1.0f - u - v;

    return (u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1);
}