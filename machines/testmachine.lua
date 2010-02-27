-- This is the description for a simple machine.

-- Parameters
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

print("FooBar");

function AssembleMachine()
	

end


