#include "celestial_body.h"
#include "core/math/vector3.h"

void CelestialBody::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mass", "mass"), &CelestialBody::set_mass);
	ClassDB::bind_method(D_METHOD("get_mass"), &CelestialBody::get_mass);
	ClassDB::bind_method(D_METHOD("set_radius", "radius"), &CelestialBody::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &CelestialBody::get_radius);
	ClassDB::bind_method(D_METHOD("set_velocity", "velocity"), &CelestialBody::set_velocity);
	ClassDB::bind_method(D_METHOD("get_velocity"), &CelestialBody::get_velocity);
	ClassDB::bind_method(D_METHOD("set_static", "is_static"), &CelestialBody::set_static);
	ClassDB::bind_method(D_METHOD("is_static_body"), &CelestialBody::is_static_body);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mass"), "set_mass", "get_mass");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "velocity"), "set_velocity", "get_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "static"), "set_static", "is_static_body");
}

// Getters and setters
void CelestialBody::set_mass(const float p_mass) { mass = p_mass; }
float CelestialBody::get_mass() const { return mass; }

void CelestialBody::set_radius(const float p_radius) { radius = p_radius; }
float CelestialBody::get_radius() const { return radius; }

void CelestialBody::set_velocity(const Vector3 p_velocity) { velocity = p_velocity; }
Vector3 CelestialBody::get_velocity() const { return velocity; }

void CelestialBody::set_static(const bool p_static) { is_static = p_static; }
bool CelestialBody::is_static_body() const { return is_static; }

// Acceleration functionality
void CelestialBody::apply_acceleration(Vector3 p_acc) { acceleration += p_acc; }
Vector3 CelestialBody::get_acceleration() const { return acceleration; }
void CelestialBody::reset_acceleration() { acceleration = Vector3(); }
