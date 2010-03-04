-- This is the description for a simple machine.

-- a little bit similar to emc.ini
AXIS_X_MAX_VELOCITY = 0.100 --m/s
AXIS_Y_MAX_VELOCITY = 0.100 --m/s
AXIS_Z_MAX_VELOCITY = 0.100 --m/s

  TRAJ_MAX_VELOCITY = 0.300 --m/s

-- Dimensions of the machine

-- Size of machinebed
sizeX = 0.74; --m
sizeY = 0.43; --m
heightOfBed = 0.1; --m



-- Base of the machine

translate(0,0,0);
box(sizeX,sizeY,heightOfBed);

addcomponent("Bridge");

translate(0,sizeY/2+0.01,0.25);
box(0.1,0.02,0.5);

translate(0,-sizeY-0.02,0.0);
box(0.1,0.02,0.5);

translate(0,sizeY/2+0.01,0.25-0.05);
box(0.1,sizeY,0.1);


addcomponent("Head");
translate(-0.05-0.005,0.0,0.4);
box(0.01,0.15,0.4);
translate(-0.05,0,-0.1);
cylinder(0.2,0.04);
translate(0,0,-0.1-0.03);
cylinder(0.06,0.04,0.005);


X=-0.20;
Y=-0.10;
Z=-0.05;

identity();
translate(X,0,0);
placecomponent("Bridge");
identity();
translate(X,Y,Z);
placecomponent("Head");


function AssembleMachine()

print("Bar");
	

end


