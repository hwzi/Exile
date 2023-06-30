#include "stdafx.h"
#include "Vector2.h"

namespace Exile {
	Vector2 Vector2::Zero = Vector2();

	Vector2::Vector2() {
		this->X = 0.0f;
		this->Y = 0.0f;
	}

	Vector2::Vector2(float x, float y) {
		this->X = x;
		this->Y = y;
	}

	bool Vector2::IsValid() {
		return *this != Vector2::Zero;
	}

	float Vector2::Length() {
		return sqrtf(this->X * this->X + this->Y * this->Y);
	}

	float Vector2::LengthSquared() {
		return this->X* this->X + this->Y * this->Y;
	}

	void Vector2::Normalize() {
		auto length = this->Length();
		this->X /= length;
		this->Y /= length;
	}

	Vector2 Vector2::Normalized() {
		auto result = Vector2(this->X, this->Y);
		result.Normalize();
		return result;
	}

	void Vector2::Extend(Vector2 v, float distance) {
		auto normalized = (v - *this).Normalized();
		this->X = this->X + distance * normalized.X;
		this->Y = this->Y + distance * normalized.Y;
	}

	Vector2 Vector2::Extended(Vector2 v, float distance) {
		auto result = Vector2(this->X, this->Y);
		result.Extend(v, distance);
		return result;
	}

	void Vector2::Shorten(Vector2 v, float distance) {
		auto normalized = (v - *this).Normalized();
		this->X = this->X - distance * normalized.X;
		this->Y = this->Y - distance * normalized.Y;
	}

	Vector2 Vector2::Shortened(Vector2 v, float distance) {
		auto result = Vector2(this->X, this->Y);
		result.Shorten(v, distance);
		return result;
	}

	void Vector2::Rotate(float angle) {
		auto c = cosf(angle);
		auto s = sinf(angle);

		this->X = this->X * c - this->Y * s;
		this->Y = this->Y * c + this->X * s;
	}

	Vector2 Vector2::Rotated(float angle) {
		auto result = Vector2(this->X, this->Y);
		result.Rotate(angle);
		return result;
	}

	float Vector2::Distance(Vector2 v) {
		auto x = this->X - v.X;
		auto y = this->Y - v.Y;
		return sqrtf(x * x + y * y);
	}

	float Vector2::DistanceSquared(Vector2 v) {
		auto x = this->X - v.X;
		auto y = this->Y - v.Y;
		return x * x + y * y;
	}

	float Vector2::Dot(Vector2 v) {
		return this->X* v.X + this->Y * v.Y;
	}

	float Vector2::Cross(Vector2 v) {
		return this->X* v.Y - this->Y * v.X;
	}

	float Vector2::AngleBetween(Vector2 v) {
		auto vec = v - *this;
		return atan2f(vec.Y, vec.X) * 180.0f * M_1_PI;
	}

	Vector2 Vector2::Perpendicular() {
		return Vector2(-this->Y, this->X);
	}

	Vector2 Vector2::Perpendicular2() {
		return Vector2(this->Y, -this->X);
	}

	bool Vector2::IsInRange(Vector2 v, float range) {
		return this->DistanceSquared(v) < range* range;
	}
	
	bool Vector2::operator==(Vector2 v) {
		return this->X == v.X && this->Y == v.Y;
	}

	bool Vector2::operator!=(Vector2 v) {
		return this->X != v.X || this->Y != v.Y;
	}

	Vector2 operator+(Vector2 left, Vector2 right) {
		return Vector2(left.X + right.X, left.Y + right.Y);
	}

	Vector2 operator+(Vector2 v, float scalar) {
		return Vector2(v.X + scalar, v.Y + scalar);
	}

	Vector2 operator+(float scalar, Vector2 v) {
		return Vector2(scalar + v.X, scalar + v.Y);
	}

	Vector2 operator-(Vector2 v) {
		return Vector2(-v.X, -v.Y);
	}

	Vector2 operator-(Vector2 left, Vector2 right) {
		return Vector2(left.X - right.X, left.Y - right.Y);
	}

	Vector2 operator-(Vector2 v, float scalar) {
		return Vector2(v.X - scalar, v.Y - scalar);
	}

	Vector2 operator-(float scalar, Vector2 v) {
		return Vector2(scalar - v.X, scalar - v.Y);
	}

	Vector2 operator*(Vector2 left, Vector2 right) {
		return Vector2(left.X * right.X, left.Y * right.Y);
	}

	Vector2 operator*(Vector2 v, float scale) {
		return Vector2(v.X * scale, v.Y * scale);
	}

	Vector2 operator*(float scale, Vector2 v) {
		return Vector2(scale * v.X, scale * v.Y);
	}

	Vector2 operator/(Vector2 v, Vector2 scale) {
		return Vector2(v.X / scale.X, v.Y / scale.Y);
	}

	Vector2 operator/(Vector2 v, float scale) {
		return Vector2(v.X / scale, v.Y / scale);
	}

	Vector2 operator/(float scale, Vector2 v) {
		return Vector2(scale / v.X, scale / v.Y);
	}
}
