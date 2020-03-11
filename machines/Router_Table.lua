-- This is the description file for a 3-axis CNC router.

-- Parameters of the machine
sizeX = 0.74 --m  Length of machinebed
sizeY = 0.43 --m  Width of machinebed
heightOfBed = 0.1 --m  Height of machinebed
heightOfBridge = 0.4 --m  Height of bridge
thicknessOfBridge = 0.05 --m 
offset = 0.05 --m Toolhead offset from edge of machine

-- Definition of the geometry

-- Base of the machine
identity();
setstyle(0.5,0.5,0.5);
box(sizeX, sizeY, heightOfBed);

translate(offset-sizeX/2, offset-sizeY/2, heightOfBed/2);
tableorigin(); -- sets the origin of the workpiece.
-- The tableorigin is the position, where the part to be milled is placed.
-- This command has to be in every machine description exactly once.

-- Bridge of the machine
addcomponent("Bridge");
setstyle(0.6,0.1,0.1);
translate(0,sizeY/2+0.01,heightOfBridge/2);
box(thicknessOfBridge, 0.02, heightOfBridge);

translate(0, -sizeY-0.02, 0.0);
box(thicknessOfBridge, 0.02, heightOfBridge);

translate(0, sizeY/2+0.01, heightOfBridge/2-thicknessOfBridge/2);
box(thicknessOfBridge, sizeY, thicknessOfBridge);

-- The machinehead
addcomponent("Head");
setstyle(0.6,0.1,0.1);

translate(-thicknessOfBridge/2-0.005,0.0,0.4);
box(0.01,0.15,0.4);

translate(-0.05,0,-0.10);
cylinder(0.2,0.04);
translate(0,0,-0.1-0.03);
cylinder(0.06,0.04,0.005);

translate(0,0,-0.03);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.


-- The next function is called for assembling
-- the parts of the machine. 
function AssembleMachine()

  -- The base of the machine is placed automatically.
  -- So only the moving parts have to be placed here.
  -- Variables for the axis positions are provided as
  -- global variables (AXIS_1, ..., AXIS_9). The axes
  -- can be used in a arbitrary order. GenericCAM checks
  -- the type and orientation of every axis later.
  -- The following code puts all the parts of the
  -- machine in their positions using the above
  -- mentioned variables.
     
	identity();
	translate(AXIS_1+thicknessOfBridge/2+0.01+0.045-sizeX/2+offset, 0, 0);
	placecomponent("Bridge");

	translate(0, AXIS_2-sizeY/2+offset, 0);
	translate(0, 0, AXIS_3+0.20-0.4+0.1+0.1+0.06+heightOfBed/2);
	placecomponent("Head");

end

