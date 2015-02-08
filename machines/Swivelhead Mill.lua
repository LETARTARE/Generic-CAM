-- This is the description file for an industrial robot.

-- Definition of the geometry

-- Base of the machine
setstyle(0.9,0.5,0.1);
loadgeometry("Swivelhead Mill/base.stl");



-- Part 1
addcomponent("Bench");
setstyle(0.9,0.5,0.1);
loadgeometry("Swivelhead Mill/bench.stl");

translate(0.0,-0.2,0.6);
translate(0,-0.1,0);
tableorigin(); -- sets the origin of the machine.
-- The tableorigin is the position, where the part to be milled is placed.
-- This command has to be in every machine description exactly once.

-- Part 2
addcomponent("Column");
setstyle(0.9,0.5,0.1);
loadgeometry("Swivelhead Mill/column.stl");

-- Part 3
addcomponent("Link");
setstyle(0.9,0.5,0.1);
loadgeometry("Swivelhead Mill/connector.stl");

-- Part 4
addcomponent("Head");
setstyle(0.9,0.5,0.1);
loadgeometry("Swivelhead Mill/head.stl");

translate(0,-0.2,0.647);
rotate(180,0,0);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.

-- The next function is called for assembling
-- the parts of the machine. 
function AssembleMachine()

	identity();
	translate(-AXIS_X,-AXIS_Y,0);
	placecomponent("Bench");
	identity();
        translate(0,0,AXIS_Z);
	placecomponent("Column");
	rotate(0,AXIS_B,0,0,-0.2,1.2);
	placecomponent("Link");
        translate(0,0,AXIS_W);
	placecomponent("Head");
	

end
