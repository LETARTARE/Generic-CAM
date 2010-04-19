-- This is the description file for an industrial robot.

-- Parameters of the machine

-- a little bit similar to emc.ini
AXIS_X_MAX_VELOCITY = 0.100 --m/s
AXIS_Y_MAX_VELOCITY = 0.100 --m/s
AXIS_Z_MAX_VELOCITY = 0.100 --m/s
  TRAJ_MAX_VELOCITY = 0.300 --m/s

-- Definition of the geometry

-- Base of the machine
translate(0, 0, 0); -- Actually this line does nothing at all.
loadstl("robot1.stl");



translate(3,2,0.5);
cylinder(0.6,0.2);

translate(0,0,0.3);
cylinder(0.3,0.01,0.05);

translate(0,0,0.15);
rotate(0,0,0);
toolholder(); -- This is the place where the milling tool is placed.
-- This command has to be in every machine description exactly once.


-- Part 1
addcomponent("Link1");
loadstl("robot2.stl");

-- Part 2
addcomponent("Link2");
loadstl("robot3.stl");

-- Part 3
addcomponent("Link3");
loadstl("robot4.stl");

-- Part 4
addcomponent("Link4");
loadstl("robot5.stl");

-- Part 5
addcomponent("Link5");
loadstl("robot6.stl");

-- Part 6
addcomponent("Link6");
loadstl("robot7.stl");

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
	  
     joint1 = 40;
     joint2 = -40;
     joint3 = 95;
     joint4 = 100;
     joint5 = -50;
     joint6 = 110;
     
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
