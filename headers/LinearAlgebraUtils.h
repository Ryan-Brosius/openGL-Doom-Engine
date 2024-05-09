#pragma once
#ifndef LINEAR_ALGEBRA_UTIL_H
#define LINEAR_ALGEBRA_UTIL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cmath>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

/**
 * @file LinearAlgebraUtils.h
 * @desc this file contains utility functions for calculating various
 *		 linear algebra functions. Mainly used to triangulate shapes
 *		 using the ear clipping algorithm
 */


/**
 * @desc returns the angle between three vertices in a counter clockwise rotation
 * @param A, B, C, all glm::vec3's where B is the vertex of the angle. It is important
 *		  that the verticies are put in CCW order where A -> B -> C
 * @return CCW angle around the center vertex
*/
float angleCCW(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);

/**
 * @desc returns if angle between 3 points are convex
 * @param A, B, C, all glm::vec3's where B is the pivot point
 * @return Bool
*/
bool isConvex(const glm::vec3& vertex_prev, const glm::vec3& vertex, const glm::vec3& vertex_next);

/**
 * @desc returns a bool if the point P is on the plane of the triangle ABC creates
 * @param A, B, C are points that create the plane of the triangle in a 3D space,
 *		  P is the point to check exists on that plane
 * @return Bool
*/
bool insideTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& P);

#endif // !LINEAR_ALGEBRA_UTIL_H
