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
	rotate(0,0,-AXIS_C,0.0,-0.6,0.447);
	placecomponent("Table");

        C = math.cos(AXIS_C/180*math.pi);
        S = math.sin(AXIS_C/180*math.pi);

        X = AXIS_X*C + AXIS_Y*S;
        Y = AXIS_Y*C - AXIS_X*S;
        Z = AXIS_Z;

        C = math.cos(AXIS_A/180*math.pi);
        S = math.sin(AXIS_A/180*math.pi);

        H = Y;
        Y = Y*C +Z*S;
        Z = Z*C - H*S;

        X = X + AXIS_U;
        Y = Y + AXIS_V;
        Z = Z + AXIS_W;

        Z = Z - 0.3976;

	identity();
	translate(X,0,0);
        placecomponent("Telescope 1");
	translate(0,0,Z/2);
	placecomponent("Telescope 2");
	translate(0,0,Z/2);
	placecomponent("Telescope 3");
	translate(0,Y,0);
	placecomponent("Head");
	

end
