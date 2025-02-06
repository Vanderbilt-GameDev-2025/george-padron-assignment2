// A Node used to represent celestial bodies
// A normal celestial body has its own mass, acceleration
// and gravitational force that is applied on other
// bodies. It can be static and non-moving, like the sun in a
// simulation of just our solar system. Or it can be dynamic,
// like the planets that revolve around the sun.
#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "core/math/vector3.h"
#include "core/object/object.h"
#include "scene/3d/node_3d.h"

class CelestialBody : public Node3D {
	GDCLASS(CelestialBody, Node3D)

	float radius;
	float mass;
	Vector3 velocity;
	Vector3 acceleration;
	bool is_static = false;

protected:
	static void _bind_methods();

public:
	CelestialBody() = default;
	~CelestialBody() = default;

	// Getters and setters
	void set_mass(const float p_mass);
	float get_mass() const;

	void set_radius(const float p_radius);
	float get_radius() const;

	void set_velocity(const Vector3 p_velocity);
	Vector3 get_velocity() const;

	void set_static(const bool p_static);
	bool is_static_body() const;

	// For internal use
	void apply_acceleration(Vector3 p_acc);
	Vector3 get_acceleration() const;
	void reset_acceleration();
};

#endif // CELESTIAL_BODY_H
