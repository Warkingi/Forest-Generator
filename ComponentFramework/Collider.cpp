#include "Collider.h"

#include "VMath.h"

#include <iostream>

using namespace GAME;

//This collision method uses the Minkowski Difference.
bool Collider::Collided(const Primitive& prim1, const Primitive& prim2) {

	//primVert holds the Vector points / vertices [vertex #][x, y, z] 

	std::vector<Vec3> verticesA = prim1.getVertices();
	std::vector<Vec3> verticesB = prim2.getVertices();

	std::vector<Vec3> newPoints;

	//First step to the Minkowski Difference is to subtract all our points.

	newPoints.push_back(Vec3(verticesA[0].x - verticesB[0].x, verticesA[0].y - verticesB[0].y, verticesA[0].z - verticesB[0].z));
	newPoints.push_back(Vec3(verticesA[0].x - verticesB[1].x, verticesA[0].y - verticesB[1].y, verticesA[0].z - verticesB[1].z));
	newPoints.push_back(Vec3(verticesA[0].x - verticesB[2].x, verticesA[0].y - verticesB[2].y, verticesA[0].z - verticesB[2].z));

	newPoints.push_back(Vec3(verticesA[1].x - verticesB[0].x, verticesA[1].y - verticesB[0].y, verticesA[1].z - verticesB[0].z));
	newPoints.push_back(Vec3(verticesA[1].x - verticesB[1].x, verticesA[1].y - verticesB[1].y, verticesA[1].z - verticesB[1].z));
	newPoints.push_back(Vec3(verticesA[1].x - verticesB[2].x, verticesA[1].y - verticesB[2].y, verticesA[1].z - verticesB[2].z));

	newPoints.push_back(Vec3(verticesA[2].x - verticesB[0].x, verticesA[2].y - verticesB[0].y, verticesA[2].z - verticesB[0].z));
	newPoints.push_back(Vec3(verticesA[2].x - verticesB[1].x, verticesA[2].y - verticesB[1].y, verticesA[2].z - verticesB[1].z));
	newPoints.push_back(Vec3(verticesA[2].x - verticesB[2].x, verticesA[2].y - verticesB[2].y, verticesA[2].z - verticesB[2].z));

	/*for (int i = 0; i < newPoints.size(); i++) {

		std::cout << newPoints[i].x << " , " << newPoints[i].y << " , " << newPoints[i].z << std::endl;

	}

	std::cout << "END" << std::endl;*/

	//CenterPoint stores the Center of both shapes. [0] being shape A and [1] being shape B.
	//The CenterPoint is (p1.x + p2.x + p3.x) / 3 , (p1.y + p2.y + p3.y) / 3 , (p1.z + p2.z + p3.z) / 3;
	Vec3 CenterA = Vec3((verticesA[0].x + verticesA[1].x + verticesA[2].x) / 3,
		(verticesA[0].y + verticesA[1].y + verticesA[2].y) / 3, 
		(verticesA[0].z + verticesA[1].z + verticesA[2].z) / 3);

	//std::cout << "CenterA = " << CenterA.x << " , " << CenterA.y << " , " << CenterA.z << std::endl;

	Vec3 CenterB = Vec3((verticesB[0].x + verticesB[1].x + verticesB[2].x) / 3,
		(verticesB[0].y + verticesB[1].y + verticesB[2].y) / 3,
		(verticesB[0].z + verticesB[1].z + verticesB[2].z) / 3);

	//std::cout << "CenterB = " << CenterB.x << " , " << CenterB.y << " , " << CenterB.z << std::endl;


	//Now we have some direction vectors.
	Vec3 dirVecs[3];
	dirVecs[0] = CenterB - CenterA;
	dirVecs[1] = CenterA - CenterB;
	//std::cout << "Dir1 = " << dir1.x << " , " << dir1.y << " , " << dir1.z << std::endl;
	//std::cout << "Dir2 = " << dir2.x << " , " << dir2.y << " , " << dir2.z << std::endl;

	dirVecs[0] = VMath::normalize(dirVecs[0]);
	dirVecs[1] = VMath::normalize(dirVecs[1]);

	//std::cout << "Dir1 = " << dir1.x << " , " << dir1.y << " , " << dir1.z << std::endl;
	//std::cout << "Dir2 = " << dir2.x << " , " << dir2.y << " , " << dir2.z << std::endl;

	//Find the highest with shape A and the lowest with shape B

	Vec3 points[3]; 
	points[0] = findHighest(dirVecs[0], verticesA) - findLowest(dirVecs[0], verticesB);

	points[1] = findHighest(dirVecs[1], verticesA) - findLowest(dirVecs[1], verticesB);

	points[2] = points[1] - points[0];

	Vec3 normalizedPoints[2];

	normalizedPoints[0].x = points[2].y * -1.0f;
	normalizedPoints[0].y = points[2].x;

	normalizedPoints[1].x = points[2].y;
	normalizedPoints[1].y = points[2].x * -1.0f;

	normalizedPoints[0] = VMath::normalize(normalizedPoints[0]);
	normalizedPoints[1] = VMath::normalize(normalizedPoints[1]);

	//std::cout << points[2].x << points[2].y << points[2].z << std::endl;

	//Find the center of the line using points[0] to points[1] t=0.5

	//Calculate the center of the line using equation (1 - t)A + tB;
	Vec3 centerofLine = (1.0f - 0.5f) * points[1] + 0.5f * points[0];

	//Negate the vector ASK ABOUT THIS WHEN GIVEN THE CHANCE
	centerofLine *= -1.0f;

	//std::cout << "Center of Line: " << centerofLine.x << centerofLine.y << centerofLine.z << std::endl;

	if (VMath::dot(normalizedPoints[0], centerofLine) > VMath::dot(normalizedPoints[1], centerofLine)) {

		dirVecs[2] = normalizedPoints[0];

	}
	else {

		dirVecs[2] = normalizedPoints[1];

	}

	points[2] = findHighest(dirVecs[2], verticesA) - findLowest(dirVecs[2], verticesB);

	Vec3 finalPoints[3];
	float dot[3];

	finalPoints[0] = (points[2] - points[0]) * (VMath::dot(points[1] - points[0], points[1] - points[0])) - (points[1] - points[0]) * (VMath::dot(points[1] - points[0], points[2] - points[0]));
	finalPoints[1] = (points[1] - points[0]) * (VMath::dot(points[2] - points[0], points[2] - points[0])) - (points[2] - points[0]) * (VMath::dot(points[2] - points[0], points[1] - points[0]));
	finalPoints[2] = (points[0] - points[1]) * (VMath::dot(points[2] - points[1], points[2] - points[1])) - (points[2] - points[1]) * (VMath::dot(points[2] - points[1], points[0] - points[1]));

	dot[0] = VMath::dot(finalPoints[0], (points[0] * -1.0f));
	dot[1] = VMath::dot(finalPoints[1], (points[0] * -1.0f));
	dot[2] = VMath::dot(finalPoints[2], (points[1] * -1.0f));

	if (dot[0] > 0 && dot[1] > 0 && dot[2] > 0) {
		return true;
	}
	else {
		return false;
	}
}


Vec3 Collider::findHighest(Vec3 dir_, std::vector<Vec3> vertices_) {

		//Need to find the vertex with the highest DoT value...

		float highestDot = 0;
		float highestVertex = 0;
	
		float largest_;

		for (int i = 0; i < vertices_.size(); i++) {
	
			largest_ = VMath::dot(dir_, vertices_[i]);
				if (highestDot < largest_) {
					highestDot = largest_;
					//std::cout << "highestDot: " << highestDot << std::endl;
					highestVertex = i;
				}
				else if (0 > largest_) {
					largest_ = largest_ * -1.0f;
					if (highestDot < largest_) {
						highestDot = largest_;
						//std::cout << "highestDot: " << highestDot << std::endl;
						highestVertex = i;
					}
					highestDot = highestDot * -1.0f;
				}
		}

		//std::cout << "findHighest method picked: " << vertices_[highestVertex].x << " , " << vertices_[highestVertex].y << " , " << vertices_[highestVertex].z << std::endl;

	return Vec3(vertices_[highestVertex]);
}

Vec3 Collider::findLowest(Vec3 dir_, std::vector<Vec3> vertices_) {

	//Need to find the vertex with the lowest DoT value...

	float lowestDot = 0;
	float lowestVertex = 0;
	
	//Smallest needs to be initalized because of the way I do this equation.
	lowestDot = VMath::dot(dir_, vertices_[0]);

	float smallest_;

	for (int i = 0; i < vertices_.size(); i++) {

		smallest_ = VMath::dot(dir_, vertices_[i]);

		if (lowestDot > smallest_) {
			lowestDot = smallest_;
			//std::cout << "lowestDot: " << lowestDot << std::endl;
			lowestVertex = i;
		}
	}

	//std::cout << "findLowest method picked: " << vertices_[lowestVertex].x << " , " <<vertices_[lowestVertex].y << " , " << vertices_[lowestVertex].z << std::endl;

	return Vec3(vertices_[lowestVertex]);
}

















//std::vector<Vec3> Collider::SupportFunction(Vec3 dir_, std::vector<Vec3> verticesA_, std::vector<Vec3> verticesB_) {
//
//	//Need to find the vertex with the highest DoT value...
//
//	std::vector<Vec3> vertexPoints;
//
//	float highestDot = 0, lowestDot = 0;
//	float lowestVertex = 0, highestVertex = 0;
//
//	//Smallest needs to be initalized because of the way I do this equation.
//	lowestDot = VMath::dot(dir_, verticesB_[0]);
//
//	for (int i = 0; i < verticesA_.size(); i++) {
//
//		float largest_, smallest_;
//
//		largest_ = VMath::dot(dir_, verticesA_[i]);
//		smallest_ = VMath::dot(dir_, verticesB_[i]);
//
//		if (highestDot < largest_) {
//			highestDot = largest_;
//			std::cout << "highestDot: " << highestDot << std::endl;
//			highestVertex = i;
//		}
//		if (lowestDot > smallest_) {
//			lowestDot = smallest_;
//			std::cout << "lowestDot: " << lowestDot << std::endl;
//			lowestVertex = i;
//		}
//	}
//
//	vertexPoints.push_back(verticesA_[highestVertex]);
//	vertexPoints.push_back(verticesB_[lowestVertex]);
//
//	return vertexPoints;
//}

void Collider::HandleCollision(Primitive& prim1, Primitive& prim2) {

}