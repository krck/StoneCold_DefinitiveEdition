
#ifndef STONECOLD_VEC4_H
#define STONECOLD_VEC4_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <utility>
#include <cmath>

namespace StoneCold::Base {

template <typename T>
struct _Vec4 {
public:
	T X, Y, W, H;

public:
	_Vec4() : X(0), Y(0), W(0), H(0) {}
	_Vec4(T v) : X(v), Y(v), W(v), H(v) {}
	_Vec4(T x, T y, T w, T h) : X(x), Y(y), W(w), H(h) {}
	_Vec4(const _Vec4& rhs) : X(rhs.X), Y(rhs.Y), W(rhs.W), H(rhs.H) {}
	_Vec4(_Vec4&& rhs) noexcept : X(std::move(rhs.X)), Y(std::move(rhs.Y)), W(std::move(rhs.W)), H(std::move(rhs.H)) {}

	//
	// Assignment Operator (Copy-and-Swap idiom)
	//
	_Vec4& operator=(_Vec4 rhs) noexcept {
		std::swap(X, rhs.X);
		std::swap(Y, rhs.Y);
		std::swap(W, rhs.W);
		std::swap(H, rhs.H);
		return *this;
	}

	//
	// Arithmetic Operators
	//
	_Vec4& operator+=(const T& v) { X += v; Y += v; W += v; H += v; return *this; }
	_Vec4& operator-=(const T& v) { X -= v; Y -= v; W -= v; H -= v; return *this; }
	_Vec4& operator*=(const T& v) { X *= v; Y *= v; W *= v; H *= v; return *this; }
	_Vec4& operator/=(const T& v) { X /= v; Y /= v; W /= v; H /= v; return *this; }
	_Vec4& operator+=(const _Vec4& rhs) { X += rhs.X; Y += rhs.Y; W += rhs.W; H += rhs.H; return *this; }
	_Vec4& operator-=(const _Vec4& rhs) { X -= rhs.X; Y -= rhs.Y; W -= rhs.W; H -= rhs.H; return *this; }
	_Vec4& operator*=(const _Vec4& rhs) { X *= rhs.X; Y *= rhs.Y; W *= rhs.W; H *= rhs.H; return *this; }
	_Vec4& operator/=(const _Vec4& rhs) { X /= rhs.X; Y /= rhs.Y; W /= rhs.W; H /= rhs.H; return *this; }
	friend _Vec4 operator+(_Vec4 lhs, const T& v) { lhs += v; return lhs; }
	friend _Vec4 operator-(_Vec4 lhs, const T& v) { lhs -= v; return lhs; }
	friend _Vec4 operator*(_Vec4 lhs, const T& v) { lhs *= v; return lhs; }
	friend _Vec4 operator/(_Vec4 lhs, const T& v) { lhs /= v; return lhs; }
	friend _Vec4 operator+(_Vec4 lhs, const _Vec4& rhs) { lhs += rhs; return lhs; }
	friend _Vec4 operator-(_Vec4 lhs, const _Vec4& rhs) { lhs -= rhs; return lhs; }
	friend _Vec4 operator*(_Vec4 lhs, const _Vec4& rhs) { lhs *= rhs; return lhs; }
	friend _Vec4 operator/(_Vec4 lhs, const _Vec4& rhs) { lhs /= rhs; return lhs; }

	//
	// Increment and Decrement Operators
	//
	_Vec4& operator++() { X++; Y++; W++; H++; return *this; }
	_Vec4& operator--() { X--; Y--; W--; H--; return *this; }
	_Vec4 operator++(int) { _Vec4 tmp(*this); operator++(); return tmp; }
	_Vec4 operator--(int) { _Vec4 tmp(*this); operator--(); return tmp; }

	//
	// Comparison Operators (As non-member "friends" inside the class to access .length())
	//
	friend inline bool operator==(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return (lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.W == rhs.W && lhs.H == rhs.H); }
	friend inline bool operator!=(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return !(lhs == rhs); }
	friend inline bool operator< (const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return (lhs.length() < rhs.length()); }
	friend inline bool operator> (const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return (rhs < lhs); }
	friend inline bool operator<=(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return !(lhs > rhs); }
	friend inline bool operator>=(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return !(lhs < rhs); }

	//
	// Vector specific calculations
	//
	T length() const { return std::sqrt((X * X) + (Y * Y) + (W * W) + (H * H)); }
	T dot(const _Vec4& rhs) const { return ((X * rhs.X) + (Y * rhs.Y) + (W * rhs.W) + (H * rhs.H)); }
	T cross(const _Vec4& rhs) const { return ((X * rhs.Y) - (Y * rhs.X) - (W * rhs.W) - (H * rhs.H)); }
	void normalize() { X = (X / length()); Y = (Y / length()); W = (W / length()); H = (H / length()); }
	_Vec4 normal() const { return _Vec4(X / length(), Y / length(), W / length(), H / length()); }

	//
	// SDL2 specific transformations
	//
	SDL_Rect ToSDLRect() { return SDL_Rect{ static_cast<int>(X), static_cast<int>(Y), static_cast<int>(W), static_cast<int>(H) }; }
	SDL_FRect ToSDLFRect() { return SDL_FRect{ static_cast<float>(X), static_cast<float>(Y), static_cast<float>(W), static_cast<float>(H) }; }

	~_Vec4() = default;
};

typedef _Vec4<uint8> Rect;
typedef _Vec4<int> Vec4i;
typedef _Vec4<uint32> Vec4u;
typedef _Vec4<float> Vec4;
typedef _Vec4<double> Vec4d;

}

#endif
