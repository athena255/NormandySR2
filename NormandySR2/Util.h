#pragma once
#include "math/Vector.hpp"
#include "math/QAngle.hpp"

#define RandInt(min, max)(rand() % (max - min + 1) + min)

#define CalcWithJitter(origvalue, jitter)(origvalue + RandInt(-jitter, jitter)/((DOUBLE)origvalue))

#define _PI  3.1415926535897932384626433832f
#define RAD2DEG(x)((float)(x)*(float)(180.f/_PI))

template <class T>
T read(LPVOID addr)
{
	//static MEMORY_BASIC_INFORMATION mbi{};
	//if (!NT_SUCCESS(
	//		NtQueryVirtualMemory(
	//			NtCurrentProcess(),
	//			addr,
	//			MemoryBasicInformation,
	//			&mbi,
	//			sizeof(MEMORY_BASIC_INFORMATION),
	//			nullptr)))
	//	{
	//		D(L"Cannot read Memory Basic Information");
	//		return reinterpret_cast<T>(nullptr);
	//	}
	//if (mbi.State == PAGE_NOACCESS)
	//{
	//	D(L"Bad Read");
	//	return reinterpret_cast<T>(nullptr);
	//}
	return *reinterpret_cast<T*>(addr);
}

template <class T>
T read(LPVOID baseAddr, ULONG offset)
{
	return read<T>(reinterpret_cast<LPBYTE>(baseAddr) + offset);
}

template< typename T >
T* GetInterface(HMODULE modBaseAddr, LPCSTR interfaceName)
{
	using CreateInterfaceFn = T*(*)(LPCSTR, int);
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(modBaseAddr, "CreateInterface");

	return CreateInterface(interfaceName, 0);
}

// Euler QAngle -> Basis Vectors
inline Vector AngleToVector(const QAngle& angle)
{
	float sYaw = sin(angle.yaw);
	float cYaw = cos(angle.yaw);

	float sPit = sin(angle.pitch);
	float cPit = cos(angle.pitch);
	return Vector(cPit * cYaw, cPit * sYaw, -sPit);
}

// Forward Direction vector -> Euler Angles
inline QAngle VectorToAngle(const Vector& vec)
{
	QAngle angle{};
	if (vec.x == 0.0f && vec.y == 0.0f)
	{
		angle.yaw = 0.0f;
		angle.pitch = (vec.z > 0.0f) ? 270.0f : 90.0f;
	}
	else
	{
		angle.yaw = (atan2(vec.y, vec.x) * 180 / _PI);
		if (angle.yaw < 0)
			angle.yaw += 360;
		angle.pitch = (atan2(-vec.z, vec.Length2D()) * -180 / _PI);

		if (angle.yaw > 90)
			angle.yaw -= 180;
		else if (angle.yaw < 90)
			angle.yaw += 180;
		else if (angle.yaw == 90)
			angle.yaw = 0;

		angle.roll = 0;

	}
	return angle;
}

Vector ExtrapolateTick(Vector p0, Vector v0);

inline float FOV(const QAngle& viewAngle, const QAngle& aimAngle)
{
	Vector view = AngleToVector(viewAngle);
	Vector aim = AngleToVector(aimAngle);

	return RAD2DEG(acos(view.Dot(aim) / view.LengthSqr()));
}

inline QAngle CalcAngle(Vector src, Vector dst)
{
	Vector delta = src - dst;
	delta.Normalized();
	return VectorToAngle(delta);
}

template<typename T>
T GetVFunc(LPVOID vTable, UINT idx)
{
	return *reinterpret_cast<T**>(vTable)[idx];
}

class VTHook
{
public:

	// A Virtual Method Table is an array of LPVOID
	// pVTable is the address of a virtual method table
	VOID Init(LPVOID** pVTable)
	{
		// Save the VTable address
		VTableAddr = pVTable;
		// Save the old VTable
		oldVT = *pVTable;
		// Count the number of entries in the old VTable
		while (!IsBadCodePtr((FARPROC)oldVT[numEntries++]))
			;
		// Create the new VTable
		newVT = new LPVOID[numEntries];
		// Copy the contents of the old VTable to the new VTable
		memcpy(newVT, oldVT, sizeof(LPVOID) * numEntries);
		// Redirect the vtable to point to the new VTable
		*VTableAddr = newVT;
	}

	VOID Restore()
	{
		*VTableAddr = oldVT;
	}

	LPVOID GetOldFunc(ULONG index)
	{
		if (index < numEntries && oldVT != nullptr)
			return oldVT[index];
		return nullptr;
	}
	LPVOID HookFunction(LPVOID newFunc, ULONG index)
	{
		if (newVT && oldVT && index < numEntries)
		{
			newVT[index] = newFunc;
			return oldVT[index];
		}
		return nullptr;
	}

	// Address of the original VMT
	LPVOID** VTableAddr{};
	// Beginning of the new VMT
	LPVOID* newVT{};
	// Beginning of the original VMT
	LPVOID* oldVT{};
	// Number of entries in the VMT
	ULONG numEntries{};
};
