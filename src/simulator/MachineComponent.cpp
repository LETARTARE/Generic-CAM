/*
 * MachineComponent.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachineComponent.h"

#include <wx/glcanvas.h>
#include <wx/log.h>

MachineComponent::MachineComponent(wxString nameOfComponent)
{
	this->nameOfComponent = nameOfComponent;
}

MachineComponent::~MachineComponent()
{
}

void MachineComponent::InsertBox(AffineTransformMatrix matrix, float x,
		float y, float z)
{
	float x2 = x / 2;
	float y2 = y / 2;
	float z2 = z / 2;
	Vector3 p0(x2, y2, z2);
	Vector3 p1(-x2, y2, z2);
	Vector3 p2(-x2, -y2, z2);
	Vector3 p3(x2, -y2, z2);
	Vector3 p4(x2, y2, -z2);
	Vector3 p5(-x2, y2, -z2);
	Vector3 p6(-x2, -y2, -z2);
	Vector3 p7(x2, -y2, -z2);

	geometry.AddQuad(matrix, p0, p1, p2, p3);
	geometry.AddQuad(matrix, p0, p3, p7, p4);
	geometry.AddQuad(matrix, p1, p0, p4, p5);
	geometry.AddQuad(matrix, p2, p1, p5, p6);
	geometry.AddQuad(matrix, p3, p2, p6, p7);
	geometry.AddQuad(matrix, p4, p5, p6, p7);
}
void MachineComponent::InsertCylinder(AffineTransformMatrix matrix, float h,
		float r)
{
	InsertCone(matrix, h, r, r);
}

void MachineComponent::InsertCone(AffineTransformMatrix matrix, float h,
		float r1, float r2)
{
	const unsigned char N = 32;
	unsigned char i;
	float ss[N + 1], cc[N + 1];
	for(i = 0; i <= N; i++){
		ss[i] = sin(2*M_PI / N * i);
		cc[i] = cos(2*M_PI / N * i);
	}

	Vector3 m0(0, 0, h / 2);
	Vector3 m1(0, 0, -h / 2);
	Vector3 p0, p1, p2, p3;
	for(i = 0; i <= N; i++){
		p1.Set(r1 * cc[i], r1 * ss[i], h / 2);
		if(i > 0){
			geometry.AddTriangle(matrix, m0, p0, p1);
		}
		p0 = p1;
	}
	for(i = 0; i <= N; i++){
		p1.Set(r2 * cc[i], r2 * ss[i], -h / 2);
		if(i > 0){
			geometry.AddTriangle(matrix, m1, p1, p0);
		}
		p0 = p1;
	}
	for(i = 0; i <= N; i++){
		p2.Set(r1 * cc[i], r1 * ss[i], h / 2);
		p3.Set(r2 * cc[i], r2 * ss[i], -h / 2);
		if(i > 0){
			geometry.AddQuad(matrix, p0, p1, p3, p2);
		}
		p0 = p2;
		p1 = p3;
	}
}

bool MachineComponent::InsertSTL(AffineTransformMatrix matrix, wxFileName file)
{
	return geometry.ReadSTL(file.GetFullPath());
}

void MachineComponent::Paint(void)
{
	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	geometry.Paint();
	::glPopMatrix();
}
