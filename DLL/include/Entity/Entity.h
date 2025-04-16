#pragma once

#include "Utilities/Exporter.h"
#include "glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"

#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"
#include "Utilities/MY4X4.h"

SIRENITO_API class entity
{
private:
	Vector3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Quaternion rotation = Quaternion(0, 0, 0, 1);
	Vector3 scale = glm::vec3(1.0f, 1.0f, 1.0f);;

	SIRENITO_API void SetTRS(Vector3 pos, Quaternion rot, Vector3 scale);
protected:

public:
	MY4X4 trs = MY4X4::identity();

	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();

	SIRENITO_API Vector3 GetPosition();
	SIRENITO_API Quaternion GetRotation();
	SIRENITO_API Vector3 GetEulerAngles();
	SIRENITO_API Vector3 GetScale();

	SIRENITO_API void SetPosition(Vector3 newPos);
	SIRENITO_API void SetRotation(Vector3 eulers);
	SIRENITO_API void SetRotation(Quaternion rotation);

	SIRENITO_API void SetRotation(float angle, Vector3 axis);
	SIRENITO_API void SetScale(Vector3 newScale);

	SIRENITO_API void Translate(Vector3 translation);
	SIRENITO_API void Rotate(Vector3 eulers);
	SIRENITO_API void Rotate(Quaternion rotation);
	SIRENITO_API void Scale(Vector3 scalation);
};