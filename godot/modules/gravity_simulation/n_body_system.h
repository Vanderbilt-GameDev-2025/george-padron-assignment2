// A master node that all celestial bodies must be children of.
// Controls the physics and movement of each celestial body under
// it, and displays a path in the editor and in the game showing
// the predicted trajectory of a system with x amount of steps.
//
// This node allows the developer to tweak parameters on the
// celestial body simulation
#ifndef N_BODY_SYSTEM_H
#define N_BODY_SYSTEM_H

#include "core/object/object.h"
#include "core/object/worker_thread_pool.h"
#include "core/typedefs.h"
#include "modules/gravity_simulation/celestial_body.h"
#include "scene/3d/node_3d.h"

class NBodySystem : public Node3D {
	GDCLASS(NBodySystem, Node3D)

	struct SimulationState {
		Vector<Vector3> positions;
		Vector<Vector3> velocities;
	};

	// Defaults to real-world gravitational constant
	float gravitational_constant = 6.67408e-11;
	int steps_per_frame = 1;
	bool enable_collisions = true;
	bool running = false;

	// Shows debug information
	bool debug_logging = false;
	_FORCE_INLINE_ void LOG_DEBUG(const String &message) const;

	Vector<CelestialBody *> bodies;
	// Ensures that all of the celestial bodies under this node are
	// accounted for
	void _update_bodies_list();

protected:
	static void _bind_methods();
	void _notification(int p_what);
	void simulate_step(real_t delta);
	void compute_forces();
	void handle_collisions();
	void integrate_motion(real_t delta);

public:
	NBodySystem() = default;
	~NBodySystem() = default;

	// Getters and setters
	void set_gravitational_constant(float p_constant);
	float get_gravitational_constant() const;

	void set_steps_per_frame(int p_steps);
	int get_steps_per_frame() const;

	void set_collisions_enabled(bool p_enabled);
	bool are_collisions_enabled() const;

	void set_running(bool p_running);
	bool is_running() const;

	void set_debug_logging(bool p_debug);
	bool is_debug_logging_enabled() const;
};

#endif // N_BODY_SYSTEM_H
