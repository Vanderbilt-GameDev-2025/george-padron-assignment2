#include "n_body_system.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/string/print_string.h"
#include "core/typedefs.h"
#include "core/variant/variant.h"
#include "modules/gravity_simulation/celestial_body.h"
#include "scene/main/node.h"

void NBodySystem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_gravitational_constant", "constant"), &NBodySystem::set_gravitational_constant);
	ClassDB::bind_method(D_METHOD("get_gravitational_constant"), &NBodySystem::get_gravitational_constant);
	ClassDB::bind_method(D_METHOD("set_steps_per_frame", "steps"), &NBodySystem::set_steps_per_frame);
	ClassDB::bind_method(D_METHOD("get_steps_per_frame"), &NBodySystem::get_steps_per_frame);
	ClassDB::bind_method(D_METHOD("set_collisions_enabled", "enabled"), &NBodySystem::set_collisions_enabled);
	ClassDB::bind_method(D_METHOD("are_collisions_enabled"), &NBodySystem::are_collisions_enabled);
	ClassDB::bind_method(D_METHOD("predict_positions", "steps"), &NBodySystem::predict_positions);
	ClassDB::bind_method(D_METHOD("set_running", "running"), &NBodySystem::set_running);
	ClassDB::bind_method(D_METHOD("is_running"), &NBodySystem::is_running);
	ClassDB::bind_method(D_METHOD("set_debug_logging", "debug_logging"), &NBodySystem::set_debug_logging);
	ClassDB::bind_method(D_METHOD("is_debug_logging_enabled"), &NBodySystem::is_debug_logging_enabled);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravitational_constant"), "set_gravitational_constant", "get_gravitational_constant");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "steps_per_frame"), "set_steps_per_frame", "get_steps_per_frame");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "collisions_enabled"), "set_collisions_enabled", "are_collisions_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "debug_logging"), "set_debug_logging", "is_debug_logging_enabled");
}

// A simple logging function for testing purposes
_FORCE_INLINE_ void NBodySystem::LOG_DEBUG(const String &message) const {
	if (debug_logging) {
		print_line(vformat("[NBodySystem][DEBUG] %s", message));
	}
}

// Run certain code when certain events happen
void NBodySystem::_notification(int p_what) {
	switch (p_what) {
		// Whenever a node is added or removed from the scene
		case NOTIFICATION_ENTER_TREE:
		case NOTIFICATION_PARENTED:
		case NOTIFICATION_UNPARENTED:
			LOG_DEBUG("Updating Bodies");
			_update_bodies_list();
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			if (!running) {
				return;
			}

			LOG_DEBUG("Beginning Physics Process");
			real_t delta = get_physics_process_delta_time();

			for (int i = 0; i < steps_per_frame; ++i) {
				simulate_step(delta / steps_per_frame);
			}
			break;
	}
}

// Updates body list when changes are made
void NBodySystem::_update_bodies_list() {
	bodies.clear();

	for (auto child : get_children()) {
		if (CelestialBody *body = Object::cast_to<CelestialBody>(child)) {
			bodies.push_back(body);
			LOG_DEBUG("Added body: " + body->to_string());
		}
	}
}

// Getters and setters
void NBodySystem::set_gravitational_constant(float p_constant) {
	gravitational_constant = p_constant;
}
float NBodySystem::get_gravitational_constant() const {
	return gravitational_constant;
}

void NBodySystem::set_steps_per_frame(int p_steps) {
	steps_per_frame = p_steps;
}
int NBodySystem::get_steps_per_frame() const { return steps_per_frame; }

void NBodySystem::set_collisions_enabled(bool p_enabled) {
	enable_collisions = p_enabled;
}
bool NBodySystem::are_collisions_enabled() const {
	return enable_collisions;
}

void NBodySystem::set_running(bool p_running) { running = p_running; }
bool NBodySystem::is_running() const { return running; }

void NBodySystem::set_debug_logging(bool p_debug_logging) {
	debug_logging = p_debug_logging;
}
bool NBodySystem::is_debug_logging_enabled() const {
	return debug_logging;
}

void NBodySystem::simulate_step(real_t delta) {
	LOG_DEBUG("Computing Forces");
	compute_forces();
	if (enable_collisions) {
		LOG_DEBUG("Computing Collisions");
		handle_collisions();
	}
	LOG_DEBUG("Integrating Motion");
	integrate_motion(delta);
}

void NBodySystem::compute_forces() {
	for (CelestialBody *body : bodies) {
		if (body->is_static_body()) {
			LOG_DEBUG(body->to_string() + " is static, skipping forces");
			continue;
		}

		Vector3 total_force;
		for (CelestialBody *other : bodies) {
			if (other == body) {
				continue;
			}

			call_deferred_thread_group("test");
			Vector3 distance = other->get_position() - body->get_position();

			// Gravitational force
			real_t force_mag = gravitational_constant * (body->get_mass() * other->get_mass()) / distance.length_squared();
			total_force += distance.normalized() * force_mag;
		}

		LOG_DEBUG("Total force for " + body->to_string() + ": " + total_force);
		body->apply_acceleration(total_force / body->get_mass());
	}
}

void NBodySystem::integrate_motion(real_t delta) {
	for (CelestialBody *body : bodies) {
		if (body->is_static_body()) {
			continue;
		}

		body->set_velocity(body->get_velocity() + body->get_acceleration() * delta);
		body->set_position(body->get_position() + body->get_velocity() * delta);
		body->reset_acceleration();
		// TODO: Make this prettier
		LOG_DEBUG("Moving " + body->to_string() + " to " + (body->get_position() + body->get_velocity() * delta));
	}
}

void NBodySystem::handle_collisions() {
	for (int i = 0; i < bodies.size(); ++i) {
		CelestialBody *a = bodies[i];
		if (a->is_static_body()) {
			continue;
		}

		for (int j = i + 1; j < bodies.size(); ++j) {
			CelestialBody *b = bodies[j];

			Vector3 delta(b->get_position() - a->get_position());
			real_t distance = delta.length();
			real_t min_distance = a->get_radius() + b->get_radius();

			if (distance < min_distance) {
				// Simple elastic collision response
				Vector3 normal(delta.normalized());
				Vector3 relative_velocity(b->get_velocity() - a->get_velocity());
				float impulse = 2.0 * relative_velocity.dot(normal) /
						(1.0 / a->get_mass() + 1.0 / b->get_mass());

				a->set_velocity(a->get_velocity() + impulse / a->get_mass() * normal);
				if (!b->is_static_body()) {
					b->set_velocity(b->get_velocity() - impulse / b->get_mass() * normal);
				}
			}
		}
	}
}
