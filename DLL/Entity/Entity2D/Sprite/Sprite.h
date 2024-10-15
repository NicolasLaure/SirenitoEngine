#include "Entity/Entity2D/Entity2D.h"
#include "glm.hpp"
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"
#include "Utilities/Color.h"

SIRENITO_API class Sprite : public Entity2D
{
protected:
	float width;
	float height;
	unsigned int texture;
	Color color;

	SIRENITO_API float* GetVertices(float width, float height);
	SIRENITO_API unsigned int* GetIndices();
public:

	SIRENITO_API Sprite(glm::vec3 position, glm::vec3 eulers, float width, float height, Color color, Renderer* rendererInstance);
	SIRENITO_API Sprite(float width, float height, Color color, Renderer* rendererInstance);
	SIRENITO_API ~Sprite();

	SIRENITO_API void SetTexture(const char* path);
	SIRENITO_API void Draw() override;
};