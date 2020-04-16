#ifndef COLLIDER_H
#define COLLIDER_H

#include "Primitive.h"

namespace GAME {

	class Collider {

	public:

		static bool Collided(const Primitive& prim1, const Primitive& prim2);
		static void HandleCollision(Primitive& prim1, Primitive& prim2);


	private:

		static Vec3 findHighest(Vec3 dir_, std::vector<Vec3> vertices_);
		static Vec3 findLowest(Vec3 dir_, std::vector<Vec3> vertices_);

	};
}
#endif
