-- This is the description file for an industrial robot.

-- Definition of the geometry

-- http://www.robotmatrix.org/RobotConfiguration.htm

-- Base of the machine
translate(0, 0, 0); -- Actually this line does nothing at all.
setstyle(0,0.5,0)
loadgeometry("6-Axis Robot/robot1.stl");

setstyle(0.4,0.4,0.4)
translate(3,2,0.5);
cylinder(0.6,0.2);

translate(0,0,0.3);
setstyle(0.8,0.5,0.1)
cylinder(0.3,0.01,0.05);

translate(0,0,0.15);
rotate(0,0,0);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.


-- Part 1
addcomponent("Link1");
setstyle(0,0.7,0)
loadgeometry("6-Axis Robot/robot2.stl");

-- Part 2
addcomponent("Link2");
setstyle(0,0.7,0)
loadgeometry("6-Axis Robot/robot3.stl");

-- Part 3
addcomponent("Link3");
setstyle(0,0.7,0)
loadgeometry("6-Axis Robot/robot4.stl");

-- Part 4
addcomponent("Link4");
setstyle(0,0.7,0)
loadgeometry("6-Axis Robot/robot5.stl");

-- Part 5
addcomponent("Link5");
setstyle(0,0.7,0)
loadgeometry("6-Axis Robot/robot6.stl");

-- Part 6
addcomponent("Link6");
setstyle(0,0.3,0)
loadgeometry("6-Axis Robot/robot7.stl");

translate(5.149,0,1.6);
rotate(0,90,0);
translate(-0.2,-0.15,0.0);
tableorigin(); -- sets the origin of the machine.
-- The tableorigin is the position, where the part to be milled is placed.
-- This command has to be in every machine description exactly once.


-- The next function is called for assembling
-- the parts of the machine. 
function AssembleMachine()

	-- Fancy robot function is to be done next.
	-- [joint1,joint2,joint3,joint4,joint5,joint6] = RobotIK(AXIS_X,AXIS_Y,AXIS_Z,AXIS_A,AXIS_B,AXIS_C)
	  
     joint1 = AXIS_X*180;
     joint2 = AXIS_Y*180;
     joint3 = AXIS_Z*180;
     joint4 = AXIS_A;
     joint5 = AXIS_B;
     joint6 = AXIS_C;
     
	identity();
	rotate(0,0,joint1);
	placecomponent("Link1");
	rotate(0,joint2,0,0.6,0.0,1.6);
	placecomponent("Link2");
	rotate(0,joint3,0,2.952,0.0,1.6);
	placecomponent("Link3");
	rotate(joint4,0,0,4.134,0.0,1.6);
	placecomponent("Link4");
	rotate(0,joint5,0,4.586,0.0,1.6);
	placecomponent("Link5");
	rotate(joint6,0,0,5.083,0.0,1.6);
	placecomponent("Link6");
	

end
