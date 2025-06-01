#pragma once

#include "Model.h"

// libs
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>

namespace rex {

	struct TransformComponent {
		glm::vec3 translation{}; // used to move objects up, down, left and right (position offset)
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation{};
		// we use mat4 as we have 3 spatial dimensions and 1 homogeneous coordinates
		// Matrix corresponds to translate * Ry * Rx * Rz * scale transformation
		// Rotation convention uses tait - bryan angles with axis order Y(1), X(2), Z(3)
		glm::mat4 mat4();
		glm::mat3 normalMatrix();
	};

	class GameObject {
	public:
		using id_t = unsigned int;
		using Map = std::unordered_map<id_t, GameObject>;

		static GameObject createGameObject() {
			static id_t currentId = 0;
			return GameObject{ currentId++ };
		}

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;

		const id_t getId() { return id; }

		std::shared_ptr<Model> model{};
		glm::vec3 color{};
		TransformComponent transform{};

	private:
		GameObject(id_t objId) : id{ objId } {}

		id_t id;
	};
} //namespace rex