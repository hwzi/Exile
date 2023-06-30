#pragma once

namespace Exile {
	class Vector2;

	class Vector3 {
	public:
		static Vector3 Zero;

		float X, Y, Z;

		Vector3();
		Vector3(float x, float y, float z);

		bool IsValid();
		float Length();
		float LengthSquared();
		void Normalize();
		Vector3 Normalized();
		void Extend(Vector3 v, float distance);
		Vector3 Extended(Vector3 v, float distance);
		void Shorten(Vector3 v, float distance);
		Vector3 Shortened(Vector3 v, float distance);
		void Rotate(float angle);
		Vector3 Rotated(float angle);
		float Distance(Vector3 v);
		float DistanceSquared(Vector3 v);
		float Dot(Vector3 v);
		float Cross(Vector3 v);
		float AngleBetween(Vector3 v);
		Vector3 Perpendicular();
		Vector3 Perpendicular2();
		bool IsInRange(Vector3 v, float range);

		bool operator==(Vector3 v);
		bool operator!=(Vector3 v);
	};

	Vector3 operator+(Vector3 left, Vector3 right);
	Vector3 operator+(Vector3 v, float scalar);
	Vector3 operator+(float scalar, Vector3 v);
	Vector3 operator-(Vector3 v);
	Vector3 operator-(Vector3 left, Vector3 right);
	Vector3 operator-(Vector3 v, float scalar);
	Vector3 operator-(float scalar, Vector3 v);
	Vector3 operator*(Vector3 left, Vector3 right);
	Vector3 operator*(Vector3 v, float scale);
	Vector3 operator*(float scale, Vector3 v);
	Vector3 operator/(Vector3 v, Vector3 scale);
	Vector3 operator/(Vector3 v, float scale);
	Vector3 operator/(float scale, Vector3 v);
}
