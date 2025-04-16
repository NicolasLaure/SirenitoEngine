#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/MY4X4.h"
#include "Utilities/Quaternion.h"
#include "Utilities/Vector3.h"
#include "List.h"

SIRENITO_API enum Space
{
	Self,
	World
};
SIRENITO_API class Transform
{
#pragma region Variables
private:
	MY4X4 matrixTRS;

	Vector3 localPosition;
	Vector3 rotationEulers;
	Quaternion localRotation = Quaternion::identity();
	Vector3 scale;
	Transform* parent = nullptr;
	Transform* root = nullptr;

	Vector3 _worldPosition;
	Quaternion _worldRotation = Quaternion::identity();
	Vector3 _localScale;
	Vector3 _lossyScale;
	List<Transform*> _children = List<Transform*>();

	const char* _name;

#pragma endregion
public:
#pragma region Constructors

	SIRENITO_API Transform(const char* name);

	SIRENITO_API Transform(const char* name, Vector3 pos, Quaternion q, Vector3 s);

#pragma endregion

#pragma region Properties

	/// <summary>
	///   Matrix that transforms a point from world space into local space (Read Only).
	/// </summary>
	SIRENITO_API MY4X4 WorldToLocalMatrix();

	/// <summary>
	///   Matrix that transforms a point from local space into world space (Read Only).
	/// </summary>
	SIRENITO_API MY4X4 LocalToWorldMatrix();

	/// <summary>
	///   The world space position of the MyTransform.
	/// </summary>
	SIRENITO_API Vector3 GetPosition();

	SIRENITO_API void SetPosition(Vector3 value);

	/// <summary>
	///   Position of the MyTransform relative to the parent MyTransform.
	/// </summary>
	SIRENITO_API Vector3 GetLocalPosition();
	SIRENITO_API void SetLocalPosition(Vector3 value);

	/// <summary>
	///   The rotation as Euler angles in degrees.
	/// </summary>
	SIRENITO_API Vector3 GetEulerAngles();
	SIRENITO_API void SetEulerAngles(Vector3 value);

	/// <summary>
	///   The rotation as Euler angles in degrees relative to the parent MyTransform's rotation.
	/// </summary>
	SIRENITO_API Vector3 GetLocalEulerAngles();
	SIRENITO_API void SetLocalEulerAngles(Vector3 value);

	/// <summary>
	///   The red axis of the MyTransform in world space.
	/// </summary>
	SIRENITO_API Vector3 GetRight();
	SIRENITO_API void SetRight(Vector3 value);

	/// <summary>
	///   The green axis of the MyTransform in world space.
	/// </summary>
	SIRENITO_API Vector3 GetUp();
	SIRENITO_API void SetUp(Vector3 value);

	/// <summary>
	///   Returns a normalized vector representing the blue axis of the MyTransform in world space.
	/// </summary>
	SIRENITO_API Vector3 GetForward();
	SIRENITO_API void SetForward(Vector3 value);

	/// <summary>
	///   A MyMyQuaternion that stores the rotation of the MyTransform in world space.
	/// </summary>
	SIRENITO_API Quaternion GetRotation();
	SIRENITO_API void SetRotation(Quaternion value);

	/// <summary>
	///   The rotation of the MyTransform relative to the MyTransform rotation of the parent.
	/// </summary>
	SIRENITO_API Quaternion GetLocalRotation();
	SIRENITO_API void SetLocalRotation(Quaternion value);

	/// <summary>
	///   The scale of the MyTransform relative to the GameObjects parent.
	/// </summary>
	SIRENITO_API Vector3 GetLocalScale();
	SIRENITO_API void SetLocalScale(Vector3 value);

	/// <summary>
	///   The global scale of the object (Read Only).
	/// </summary>
	SIRENITO_API Vector3 GetlossyScale();

	/// <summary>
	///   The parent of the MyTransform.
	/// </summary>
	SIRENITO_API Transform* GetParent();

	/// <summary>
	///   Returns the topmost MyTransform in the hierarchy.
	/// </summary>
	SIRENITO_API Transform* Root();

	SIRENITO_API int ChildCount();

#pragma endregion

#pragma region Functions

	/*	void TestUpdate()
	{
		localRotation = Quaternion.Euler(rotationEulers);

		matrixTRS.SetTRS(localPosition, localRotation, scale);
		_worldPosition = LocalToWorldMatrix.GetPosition();
		_worldRotation = Rotation;
		_localScale = LocalScale;
		_lossyScale = lossyScale;

		root = Root;

		foreach(MyTransform child in _children)
		{
			child.TestUpdate();
		}
	}*/

#pragma region Hierarchy

	/// <summary>
	///   Set the parent of the MyTransform.
	/// </summary>
	SIRENITO_API void SetParent(Transform* newParent);

	/// <summary>
	///   Set the parent of the MyTransform.
	/// </summary>
	/// <param name="newParent">The parent MyTransform to use.</param>
	/// <param name="worldPositionStays">If true, the parent-relative position, scale and rotation are modified such that the object keeps the same world space position, rotation and scale as before.</param>
	SIRENITO_API void SetParent(Transform* newParent, bool worldPositionStays);

	SIRENITO_API void RemoveChild(Transform* child);

	SIRENITO_API void AddChild(Transform* child);

	SIRENITO_API void AddChild(Transform* child, int position);

	/// <summary>
	///   Unparents all children.
	/// </summary>
	SIRENITO_API void DetachChildren();

	/// <summary>
	///   Move the MyTransform to the start of the local MyTransform list.
	/// </summary>
	SIRENITO_API void SetAsFirstSibling();
	/// <summary>
	///   Move the MyTransform to the end of the local MyTransform list.
	/// </summary>
	SIRENITO_API void SetAsLastSibling();

	/// <summary>
	///   Sets the sibling index.
	/// </summary>
	/// <param name="index">Index to set.</param>
	SIRENITO_API void SetSiblingIndex(int index);

	/// <summary>
	///   Gets the sibling index.
	/// </summary>
	SIRENITO_API int GetSiblingIndex();

	/// <summary>
	///   Finds a child by name n and returns it.
	/// </summary>
	/// <param name="n">Name of child to be found.</param>
	/// <returns>
	///   The found child MyTransform. Null if child with matching name isn't found.
	/// </returns>
	SIRENITO_API Transform* Find(char* n);

	SIRENITO_API int GetChildIndex(Transform* child);

#pragma endregion

	/// <summary>
	///   Sets the world space position and rotation of the MyTransform component.
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	SIRENITO_API void SetPositionAndRotation(Vector3 position, Quaternion rotation);

	/// <summary>
	///   Sets the position and rotation of the MyTransform component in local space (i.e. relative to its parent MyTransform).
	/// </summary>
	/// <param name="newLocalPosition"></param>
	/// <param name="newLocalRotation"></param>
	SIRENITO_API void SetLocalPositionAndRotation(Vector3 newLocalPosition, Quaternion newLocalRotation);

	SIRENITO_API void GetPositionAndRotation(Vector3* position, Quaternion* rotation);
	SIRENITO_API void GetLocalPositionAndRotation(Vector3* localPosition, Quaternion* localRotation);
#pragma region Translates

	/// <summary>
	///   Moves the MyTransform in the direction and distance of translation.
	/// </summary>
	/// <param name="translation"></param>
	/// <param name="relativeTo"></param>
	SIRENITO_API void Translate(Vector3 translation, Space relativeTo);

	/// <summary>
	///   Moves the MyTransform in the direction and distance of translation.
	/// </summary>
	/// <param name="translation"></param>
	SIRENITO_API void Translate(Vector3 translation);

	/// <summary>
	///   Moves the MyTransform by x along the x axis, y along the y axis, and z along the z axis.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="relativeTo"></param>
	SIRENITO_API void Translate(float x, float y, float z, Space relativeTo);

	/// <summary>
	///   Moves the MyTransform by x along the x axis, y along the y axis, and z along the z axis.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API void Translate(float x, float y, float z);

	/// <summary>
	///   Moves the MyTransform in the direction and distance of translation.
	/// </summary>
	/// <param name="translation"></param>
	/// <param name="relativeTo"></param>
	SIRENITO_API void Translate(Vector3 translation, Transform relativeTo);

	/// <summary>
	///   Moves the MyTransform by x along the x axis, y along the y axis, and z along the z axis.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="relativeTo"></param>
	SIRENITO_API void Translate(float x, float y, float z, Transform relativeTo);

#pragma endregion

#pragma region Rotates

	/// <summary>
	///   Applies a rotation of eulerAngles.z degrees around the z-axis, eulerAngles.x degrees around the x-axis, and eulerAngles.y degrees around the y-axis (in that order).
	/// </summary>
	/// <param name="eulers">The rotation to apply in euler angles.</param>
	/// <param name="relativeTo">Determines whether to rotate the GameObject either locally to  the GameObject or relative to the Scene in world space.</param>
	SIRENITO_API void Rotate(Vector3 eulers, Space relativeTo);

	/// <summary>
	///   Applies a rotation of eulerAngles.z degrees around the z-axis, eulerAngles.x degrees around the x-axis, and eulerAngles.y degrees around the y-axis (in that order).
	/// </summary>
	/// <param name="eulers">The rotation to apply in euler angles.</param>
	SIRENITO_API void Rotate(Vector3 eulers);

	/// <summary>
	///   The implementation of this method applies a rotation of zAngle degrees around the z axis, xAngle degrees around the x axis, and yAngle degrees around the y axis (in that order).
	/// </summary>
	/// <param name="xAngle">Degrees to rotate the GameObject around the X axis.</param>
	/// <param name="yAngle">Degrees to rotate the GameObject around the Y axis.</param>
	/// <param name="zAngle">Degrees to rotate the GameObject around the Z axis.</param>
	/// <param name="relativeTo">Determines whether to rotate the GameObject either locally to the GameObject or relative to the Scene in world space.</param>
	SIRENITO_API void Rotate(float xAngle, float yAngle, float zAngle, Space relativeTo);
	/// <summary>
	///   The implementation of this method applies a rotation of zAngle degrees around the z axis, xAngle degrees around the x axis, and yAngle degrees around the y axis (in that order).
	/// </summary>
	/// <param name="xAngle">Degrees to rotate the GameObject around the X axis.</param>
	/// <param name="yAngle">Degrees to rotate the GameObject around the Y axis.</param>
	/// <param name="zAngle">Degrees to rotate the GameObject around the Z axis.</param>
	SIRENITO_API void Rotate(float xAngle, float yAngle, float zAngle);

	/// <summary>
	///   Rotates the object around the given axis by the number of degrees defined by the given angle.
	/// </summary>
	/// <param name="axis">The axis to apply rotation to.</param>
	/// <param name="angle">The degrees of rotation to apply.</param>
	/// <param name="relativeTo">Determines whether to rotate the GameObject either locally to the GameObject or relative to the Scene in world space.</param>
	SIRENITO_API void Rotate(Vector3 axis, float angle, Space relativeTo);

	/// <summary>
	///   Rotates the object around the given axis by the number of degrees defined by the given angle.
	/// </summary>
	/// <param name="axis">The axis to apply rotation to.</param>
	/// <param name="angle">The degrees of rotation to apply.</param>
	SIRENITO_API void Rotate(Vector3 axis, float angle);

#pragma endregion

	/// <summary>
	///   Rotates the MyTransform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="point"></param>
	/// <param name="axis"></param>
	/// <param name="angle"></param>
	SIRENITO_API void RotateAround(Vector3 point, Vector3 axis, float angle);

	/// <summary>
	///   Rotates the MyTransform so the forward vector points at target's current position.
	/// </summary>
	/// <param name="target">Object to point towards.</param>
	/// <param name="worldUp">Vector specifying the upward direction.</param>
	SIRENITO_API void LookAt(Transform target, Vector3 worldUp);

	/// <summary>
	///   Rotates the MyTransform so the forward vector points at target's current position.
	/// </summary>
	/// <param name="target">Object to point towards.</param>
	SIRENITO_API void LookAt(Transform target);

	/// <summary>
	///   Rotates the MyTransform so the forward vector points at worldPosition.
	/// </summary>
	/// <param name="worldPosition">Point to look at.</param>
	/// <param name="worldUp">Vector specifying the upward direction.</param>
	SIRENITO_API void LookAt(Vector3 worldPosition, Vector3 worldUp);

	/// <summary>
	///   Rotates the MyTransform so the forward vector points at worldPosition.
	/// </summary>
	/// <param name="worldPosition">Point to look at.</param>
	SIRENITO_API void LookAt(Vector3 worldPosition);

	/// <summary>
	///   MyTransforms direction from local space to world space.
	/// </summary>
	/// <param name="direction"></param>
	SIRENITO_API Vector3 TransformDirection(Vector3 direction);

	/// <summary>
	///   MyTransforms direction x, y, z from local space to world space.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 TransformDirection(float x, float y, float z);

	/// <summary>
	///   Transforms a direction from world space to local space. The opposite of MyTransform.TransformDirection.
	/// </summary>
	/// <param name="direction"></param>
	SIRENITO_API Vector3 InverseTransformDirection(Vector3 direction);

	/// <summary>
	///   MyTransforms the direction x, y, z from world space to local space. The opposite of MyTransform.MyTransformDirection.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 InverseTransformDirection(float x, float y, float z);


	/// <summary>
	///   MyTransforms vector from local space to world space.
	/// </summary>
	/// <param name="vector"></param>
	SIRENITO_API Vector3 TransformVector(Vector3 vector);

	/// <summary>
	///   MyTransforms vector x, y, z from local space to world space.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 TransformVector(float x, float y, float z);

	/// <summary>
	///   MyTransforms a vector from world space to local space. The opposite of MyTransform.MyTransformVector.
	/// </summary>
	/// <param name="vector"></param>
	SIRENITO_API Vector3 InverseTransformVector(Vector3 vector);

	/// <summary>
	///   MyTransforms the vector x, y, z from world space to local space. The opposite of MyTransform.MyTransformVector.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 InverseTransformVector(float x, float y, float z);

	/// <summary>
	///   MyTransforms position from local space to world space.
	/// </summary>
	/// <param name="position"></param>
	SIRENITO_API Vector3 TransformPoint(Vector3 position);

	/// <summary>
	///   MyTransforms the position x, y, z from local space to world space.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 TransformPoint(float x, float y, float z);

	/// <summary>
	///   transforms position from world space to local space.
	/// </summary>
	/// <param name="position"></param>
	SIRENITO_API Vector3 InverseTransformPoint(Vector3 position);

	SIRENITO_API Vector3 RelativeInverseTransformPoint(Vector3 position, Transform relativeTo);

	/// <summary>
	///   MyTransforms the position x, y, z from world space to local space.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SIRENITO_API Vector3 InverseTransformPoint(float x, float y, float z);

	/// <summary>
	///   Is this MyTransform a child of parent?
	/// </summary>
	/// <param name="parent"></param>
	SIRENITO_API bool IsChildOf(Transform* parent);

#pragma endregion
};