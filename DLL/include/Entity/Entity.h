#pragma once

#include "Utilities/Exporter.h"
#include "glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"

#include "Utilities/Vector3.h"

SIRENITO_API class Entity
{
private:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat();
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);;

	SIRENITO_API void SetTRS(glm::vec3 pos, glm::quat rot, glm::vec3 scale);
protected:

public:
	glm::mat4 trs = glm::mat4(1.0f);

	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();

	SIRENITO_API Vector3 GetPosition();
	SIRENITO_API glm::quat GetRotation();
	SIRENITO_API Vector3 GetEulerAngles();
	SIRENITO_API Vector3 GetScale();

	SIRENITO_API void SetPosition(Vector3 newPos);
	SIRENITO_API void SetRotation(Vector3 eulers);
	SIRENITO_API void SetRotation(glm::quat rotation);

	SIRENITO_API void SetRotation(float angle, Vector3 axis);
	SIRENITO_API void SetScale(Vector3 newScale);

	SIRENITO_API void Translate(Vector3 translation);
	SIRENITO_API void Rotate(Vector3 eulers);
	SIRENITO_API void Rotate(glm::quat rotation);
	SIRENITO_API void Scale(Vector3 scalation);
};