#include "../include/Maths.h"

namespace MathLib
{
	namespace Complex
	{
		// Base class for imaginary numbers

		imaginaryBase::imaginaryBase()
			: num(1)
		{

		}
		imaginaryBase::imaginaryBase(const double &num)
			: num(num)
		{

		}
		imaginaryBase imaginaryBase::operator+(const imaginaryBase &other)
		{
			return num + other.num;
		}
		imaginaryBase imaginaryBase::operator-(const imaginaryBase &other)
		{
			return num - other.num;
		}
		double imaginaryBase::operator*(const imaginaryBase &other)
		{
			if (num == other.num)
				return -1;
			else
				return num * other.num;
		}
		double imaginaryBase::operator/(const imaginaryBase &other)
		{
			return num / other.num;
		}
		bool imaginaryBase::operator==(const imaginaryBase &other)
		{
			return num == other.num;
		}
		bool imaginaryBase::operator!=(const imaginaryBase &other)
		{
			return num != other.num;
		}
		bool imaginaryBase::operator>=(const imaginaryBase &other)
		{
			return num >= other.num;
		}
		bool imaginaryBase::operator<=(const imaginaryBase &other)
		{
			return num <= other.num;
		}
		bool imaginaryBase::operator>(const imaginaryBase &other)
		{
			return num > other.num;
		}
		bool imaginaryBase::operator<(const imaginaryBase &other)
		{
			return num < other.num;
		}
		imaginaryBase& imaginaryBase::operator++()
		{
			++num;
			return *this;
		}
		imaginaryBase& imaginaryBase::operator--()
		{
			--num;
			return *this;
		}
		imaginaryBase& imaginaryBase::operator++(int)
		{
			num++;
			return *this;
		}
		imaginaryBase& imaginaryBase::operator--(int)
		{
			num--;
			return *this;
		}

		imaginaryBase operator-(const imaginaryBase &num)
		{
			return imaginaryBase(-num.num);
		}

		// Special imaginary nums

		imagI::imagI()
			: imaginaryBase()
		{

		}
		imagI::imagI(const double &num)
			: imaginaryBase(num)
		{

		}
		imagI::imagI(const imaginaryBase &base)
			: imaginaryBase(base)
		{

		}
		double imagI::operator*(const imagI &other)
		{
			if (num != other.num)
				return num * other.num;
			else if (num == 0)
				return 0;
			else
				return -1;
		}
		imagK imagI::operator*(const imagJ &other)
		{
			return imagK(num * other.num);
		}
		imagJ imagI::operator*(const imagK &other)
		{
			return imagJ(-num * other.num);
		}

		imagJ::imagJ()
			: imaginaryBase()
		{

		}
		imagJ::imagJ(const double &num)
			: imaginaryBase(num)
		{

		}
		imagJ::imagJ(const imaginaryBase &base)
			: imaginaryBase(base)
		{

		}
		double imagJ::operator*(const imagJ &other)
		{
			if (num != other.num)
				return num * other.num;
			else if (num == 0)
				return 0;
			else
				return -1;
		}
		imagI imagJ::operator*(const imagK &other)
		{
			return imagI(num * other.num);
		}
		imagK imagJ::operator*(const imagI &other)
		{
			return imagK(-num * other.num);
		}

		imagK::imagK()
			: imaginaryBase()
		{

		}
		imagK::imagK(const double &num)
			: imaginaryBase(num)
		{

		}
		imagK::imagK(const imaginaryBase &base)
			: imaginaryBase(base)
		{

		}
		double imagK::operator*(const imagK &other)
		{
			if (num != other.num)
				return num * other.num;
			else if (num == 0)
				return 0;
			else
				return -1;
		}
		imagJ imagK::operator*(const imagI &other)
		{
			return imagJ(num * other.num);
		}
		imagI imagK::operator*(const imagJ &other)
		{
			return imagI(-num * other.num);
		}

		// Quaternion class

		Quaternion::Quaternion()
			: real(1), i(0), j(0), k(0)
		{

		}
		Quaternion::Quaternion(const double &real, const imagI &i, const imagJ &j, const imagK &k)
			: real(real), i(i), j(j), k(k)
		{

		}
		Quaternion::Quaternion(const Primitives::Point3D &point)
			: real(0), i(point.x), j(point.y), k(point.z)
		{

		}
		Quaternion Quaternion::operator+(const Quaternion &other)
		{
			return Quaternion(real + other.real, i + other.i, j + other.j, k + other.k);
		}
		Quaternion Quaternion::operator*(const Quaternion &other)
		{
			double retReal;
			imagI retI;
			imagJ retJ;
			imagK retK;

			retReal = real * other.real - i * other.i - j * other.j - k * other.k;
			retI = real * other.i + imagI(imaginaryBase(i) * other.real) + j * other.k + k * other.j;
			retJ = real * other.j + i * other.k + imagJ(imaginaryBase(j) * other.real) + k * other.i;
			retK = real * other.k + i * other.j + j * other.i + imagK(imaginaryBase(k) * other.real);

			return Quaternion(retReal, retI, retJ, retK);
		}
		Quaternion Quaternion::GetInverse()
		{
			return Quaternion(real, -i, -j, -k);
		}
		Primitives::Point3D Quaternion::GetPoint()
		{
			return Primitives::Point3D(i.num, j.num, k.num);
		}
		Quaternion Quaternion::RotateQuaternion(const Quaternion &quat)
		{
			return Quaternion(*this * quat * this->GetInverse());
		}
		Primitives::Point3D Quaternion::RotatePoint(const Primitives::Point3D &point)
		{
			Quaternion pQuat(point);
			return Quaternion(*this * pQuat * this->GetInverse()).GetPoint();
		}

		Quaternion QuaternionRotation(const double &angle, const double &iAxis, const double &jAxis, const double &kAxis)
		{
			Quaternion retQuat(cos(Utility::Deg2Rad(angle)), 0, 0, 0);
			double sinAngle = sin(Utility::Deg2Rad(angle));
			retQuat.i = imagI(iAxis * sinAngle);
			retQuat.j = imagJ(jAxis * sinAngle);
			retQuat.k = imagK(kAxis * sinAngle);
			return retQuat;
		}
		Quaternion QuaternionRotation(const double &angle, const Primitives::Point3D &axis)
		{
			Quaternion retQuat(cos(Utility::Deg2Rad(angle)), 0, 0, 0);
			double sinAngle = sin(Utility::Deg2Rad(angle));
			retQuat.i = imagI(axis.x * sinAngle);
			retQuat.j = imagJ(axis.y * sinAngle);
			retQuat.k = imagK(axis.z * sinAngle);
			return retQuat;
		}
		void PrintProperties(const Quaternion &quat)
		{
			printf("Real: %.3f, i: %.3f, j: %.3f, k: %.3f\n", quat.real, quat.i, quat.j, quat.k);
		}
	}
}