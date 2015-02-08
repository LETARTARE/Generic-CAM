-- This is the description file for an industrial robot.

-- Definition of the geometry
identity();

-- Base of the machine
setstyle(0.3,0.3,0.3);
loadgeometry("Swiveltable Mill/base.stl");

-- Part 1
addcomponent("Swing");
setstyle(0.9,0.3,0.1);
loadgeometry("Swiveltable Mill/swing.stl");

-- Part 2
addcomponent("Table");
setstyle(0.9,0.5,0.1);
loadgeometry("Swiveltable Mill/table.stl");

identity();
translate(0.0,-0.6,0.483);
translate(-0.15,-0.15,0);
tableorigin(); -- sets the origin of the machine.
-- The tableorigin is the position, where the part to be milled is placed.
-- This command has to be in every machine description exactly once.

-- Part 3
addcomponent("Telescope 1");
setstyle(0.8,0.3,0.1);
loadgeometry("Swiveltable Mill/telescope1.stl");

-- Part 4
addcomponent("Telescope 2");
setstyle(0.9,0.3,0.1);
loadgeometry("Swiveltable Mill/telescope2.stl");

-- Part 5
addcomponent("Telescope 3");
setstyle(0.9,0.3,0.1);
loadgeometry("Swiveltable Mill/telescope3.stl");

-- Part 6
addcomponent("Head");
setstyle(0.9,0.5,0.1);
loadgeometry("Swiveltable Mill/head.stl");

translate(0,-0.6,0.8806);
rotate(180,0,0);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.

-- The next function is called for assembling
-- the parts of the machine. 
function AssembleMachine()

	identity();
	rotate(-AXIS_A,0,0,0,-0.6,0.48);
	placecomponent("Swing");
	rotate(0,0,-AXIS_B,0.0,-0.6,0.447);
	placecomponent("Table");

	identity();
	translate(AXIS_X,0,0);
        placecomponent("Telescope 1");
	translate(0,0,AXIS_Z/2);
	placecomponent("Telescope 2");
	translate(0,0,AXIS_Z/2);
	placecomponent("Telescope 3");
	translate(0,AXIS_Y,0);
	placecomponent("Head");
	

end
