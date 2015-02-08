-- This is the description file for an industrial robot.

-- Definition of the geometry

-- Base of the machine
setstyle(0.9,0.5,0.1);
loadgeometry("Staeubli RX90/rx90_base.stl");

setstyle(0.5,0.5,0.5);

translate(0.58,0.28,0.2);
box(0.2,0.2,0.4);

identity();
translate(0.5,0.2,0.4);
tableorigin(); -- sets the origin of the machine.
-- The tableorigin is the position, where the part to be milled is placed.
-- This command has to be in every machine description exactly once.


-- Part 1
addcomponent("Link1");
loadgeometry("Staeubli RX90/rx90_joint1.stl");
setstyle(0.9,0.5,0.1);

-- Part 2
addcomponent("Link2");
loadgeometry("Staeubli RX90/rx90_joint2.stl");
setstyle(0.9,0.5,0.1);

-- Part 3
addcomponent("Link3");
loadgeometry("Staeubli RX90/rx90_joint3.stl");
setstyle(0.9,0.5,0.1);

-- Part 4
addcomponent("Link4");
loadgeometry("Staeubli RX90/rx90_joint4.stl");
setstyle(0.9,0.5,0.1);

-- Part 5
addcomponent("Link5");
setstyle(0.6,0.6,0.6);
loadgeometry("Staeubli RX90/rx90_joint5.stl");

-- Part 6
addcomponent("Head");

translate(0,0,1.644);
rotate(90,0,90);

setstyle(0.6,0.3,0.1);
loadgeometry("Staeubli RX90/millinghead.stl");



translate(0,0.04,0.12813);
rotate(0,0,0);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.



-- The next function is called for assembling
-- the parts of the machine. 
function AssembleMachine()

	-- Fancy robot function is to be done next.
	-- [joint1,joint2,joint3,joint4,joint5,joint6] = RobotIK(AXIS_X,AXIS_Y,AXIS_Z,AXIS_A,AXIS_B,AXIS_C)

	-- For testing the joints are mapped to
        -- the CNC axes. 
     joint1 = AXIS_X*180;
     joint2 = AXIS_Y*180;
     joint3 = AXIS_Z*180;
     joint4 = AXIS_A;
     joint5 = AXIS_B;
     joint6 = AXIS_C;
     
	identity();
	rotate(0,0,joint1);
	placecomponent("Link1");
	rotate(0,joint2,0,-0.002,-0.201,0.43);
	placecomponent("Link2");
	rotate(0,joint3,0,-0.002,-0.201,0.886);
	placecomponent("Link3");
	rotate(0,0,joint4,-0.005,0.0,0.988);
	placecomponent("Link4");
	rotate(0,joint5,0,-0.002,0.0,1.562);
	placecomponent("Link5");
	rotate(0,0,joint6,0.0,0.0,0.0);
	placecomponent("Head");
	

end
