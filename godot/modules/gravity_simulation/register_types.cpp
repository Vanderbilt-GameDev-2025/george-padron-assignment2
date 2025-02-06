#include "register_types.h"

#include "celestial_body.h"
#include "core/object/class_db.h"
#include "n_body_system.h"

void initialize_gravity_simulation_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<CelestialBody>();
	ClassDB::register_class<NBodySystem>();
}

void uninitialize_gravity_simulation_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
