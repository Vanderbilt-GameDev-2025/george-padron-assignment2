extends CelestialBody

@onready var display: CSGSphere3D = $Display

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	resize_display()
	#set_color()
	
#func set_color() -> void: 
	#var r = randi_range(0, 255)
	#var g = randi_range(0, 255)
	#var b = randi_range(0, 255)
	#
	#if not display.material: 
		#push_error("Material not set for planet!")
		#return
		#
	#display.material = display.material.duplicate() 
	#display.material.albedo_color = Color8(r, g, b)

# To be called whene
func resize_display() -> void: 
	display.radius = radius
	
