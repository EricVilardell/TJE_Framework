#include "entityCollider.h"


bool EntityCollider::checkPlayerCollisions(const Vector3& target_pos, std::vector<sCollisionData>& ground_collisions, std::vector<sCollisionData>& wall_collisions)
{
    //first ball, the one on of the body.
    Vector3 center = target_pos + Vector3(0.0f, 1.f, 0.0f);
    float sphereRadius = 0.6f;
    Vector3 colPoint, colNormal;
    //second ball, the one on the floor
    Vector3 center2 = target_pos + Vector3(0.0f, 0.2f, 0.0f);
    float sphereRadius2 = 0.2f;

    // For each collider entity “e” in root:

    if (mesh->testSphereCollision(model, center, sphereRadius, colPoint, colNormal)) {
        ground_collisions.push_back({ colPoint, colNormal.normalize() });
    }
    // End loop

    if (mesh->testSphereCollision(model, center2, sphereRadius2, colPoint, colNormal)) {
        wall_collisions.push_back({ colPoint, colNormal.normalize() });
    }

    return !ground_collisions.empty() || !wall_collisions.empty();
}
