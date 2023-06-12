#pragma once
#include <d3d9.h>
#include <vector>
#include <iostream>
#include "../driver.h"
#define M_PI 3.14159265358979323846264338327950288419716939937510

using namespace std;
class Vector2
{
public:
	double x;
	double y;

	inline bool is_Zero() {
		return (x == 0) && (y == 0);
	}
};

struct FRotator
{
public:
	double Pitch;
	double Yaw;
	double Roll;
};
class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double Distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}


	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float number) const {
		return Vector3(x * number, y * number, z * number);
	}
};

namespace pointer
{
	inline uintptr_t uworld;
	inline uintptr_t gobjects;
	inline uintptr_t game_instance;
	inline uintptr_t local_players;
	inline uintptr_t player_controller;
	inline uintptr_t local_pawn;
	inline uintptr_t root_component;
	inline uintptr_t player_state;
	inline uintptr_t game_state;
	inline uintptr_t player_array;
	inline uintptr_t AFortPlayerState;
	inline Vector3 local_relative_location;
	 Vector3 BaseAddress;
}

struct Camera
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	double zoom;
};

struct FQuat
{
	double x;
	double y;
	double z;
	double w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m{};
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;
		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.y;
		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;
		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;
		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;
		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;
		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut{};
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
	return pOut;
}

D3DMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

Vector3 GetBoneWithRotation(uintptr_t mesh, int bone_id)
{
	uintptr_t bone_array = Rpm<uintptr_t>(mesh + 0x5f0);
	if (bone_array == NULL) bone_array = Rpm<uintptr_t>(mesh + 0x5f0 + 0x10);
	FTransform bone = Rpm<FTransform>(bone_array + (bone_id * 0x60));
	FTransform component_to_world = Rpm<FTransform>(mesh + 0x240);
	D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
	return Vector3(matrix._41, matrix._42, matrix._43);
}


bool IsVisible(uintptr_t mesh)
{
	auto fLastSubmitTime = Rpm<float>(mesh + 0x360);
	auto fLastRenderTimeOnScreen = Rpm<float>(mesh + 0x368);
	bool OverlappingBuildings = Rpm<BYTE>(pointer::local_pawn + 0x1b10);
	const float fVisionTick = 0.015f;
	return fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime && !OverlappingBuildings;
}


double __fastcall Atan2(double a1, double a2)
{
	double result; // xmm0_8

	result = 0.0;
	if (a2 != 0.0 || a1 != 0.0)
		return atan2(a1, a2);
	return result;
}
double __fastcall FMod(double a1, double a2)
{
	if (fabs(a2) > 0.00000001)
		return fmod(a1, a2);
	else
		return 0.0;
}
double ClampAxis(double Angle)
{
	// returns Angle in the range (-360,360)
	Angle = FMod(Angle, (double)360.0);

	if (Angle < (double)0.0)
	{
		// shift to [0,360) range
		Angle += (double)360.0;
	}

	return Angle;
}
double NormalizeAxis(double Angle)
{
	// returns Angle in the range [0,360)
	Angle = ClampAxis(Angle);

	if (Angle > (double)180.0)
	{
		// shift to (-180,180]
		Angle -= (double)360.0;
	}

	return Angle;
}

FRotator Rotator(FQuat* F)
{
	const double SingularityTest = F->z * F->x - F->w * F->y;
	const double YawY = 2.f * (F->w * F->z + F->x * F->y);
	const double YawX = (1.f - 2.f * ((F->y * F->y) + (F->z * F->z)));

	const double SINGULARITY_THRESHOLD = 0.4999995f;
	const double RAD_TO_DEG = 57.295776;
	double Pitch, Yaw, Roll;

	if (SingularityTest < -SINGULARITY_THRESHOLD)
	{
		Pitch = -90.f;
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = NormalizeAxis(-Yaw - (2.f * Atan2(F->x, F->w) * RAD_TO_DEG));
	}
	else if (SingularityTest > SINGULARITY_THRESHOLD)
	{
		Pitch = 90.f;
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = NormalizeAxis(Yaw - (2.f * Atan2(F->x, F->w) * RAD_TO_DEG));
	}
	else
	{
		Pitch = (asin(2.f * SingularityTest) * RAD_TO_DEG);
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = (Atan2(-2.f * (F->w * F->x + F->y * F->z), (1.f - 2.f * ((F->x * F->x) + (F->y * F->y)))) * RAD_TO_DEG);
	}

	FRotator RotatorFromQuat = FRotator{ Pitch, Yaw, Roll };
	return RotatorFromQuat;
}
struct CamewaDescwipsion
{
	float FieldOfView;
	Vector3 Rotation;
	Vector3 Location;
};
CamewaDescwipsion UndetectedCamera(__int64 a1)
{
	CamewaDescwipsion VirtualCamera;
	__int64 ViewStates;
	__int64 ViewState;

	ViewStates = Rpm<__int64>(pointer::local_players + 0xD0);
	ViewState = Rpm<__int64>(ViewStates + 8);

	VirtualCamera.FieldOfView = Rpm<float>(pointer::player_controller + 0x38C) * 90.f;

	VirtualCamera.Rotation.x = Rpm<double>(ViewState + 0x9C0);
	//VirtualCamera.Rotation.y = read<double>(a1 + 0x148);
	__int64 ViewportClient = Rpm<__int64>(pointer::local_players + 0x78);
	if (!ViewportClient) return VirtualCamera;
	__int64 AudioDevice = Rpm<__int64>(ViewportClient + 0x98);
	if (!AudioDevice) return VirtualCamera;
	__int64 FListener = Rpm<__int64>(AudioDevice + 0x1E0);
	if (!FListener) return VirtualCamera;
	FQuat Listener = Rpm<FQuat>(FListener);
	VirtualCamera.Rotation.y = Rotator(&Listener).Yaw;
	//cout << VirtualCamera.Rotation.y;
	//cout << VirtualCamera.Rotation.x;
	VirtualCamera.Location = Rpm<Vector3>(Rpm<uintptr_t>(pointer::uworld + 0x110));
	return VirtualCamera;
}

uintptr_t base_address;

std::string find_object_class(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = Rpm<uint64_t>(base_address + 0xF237A00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	uint16_t nameEntry = Rpm<uint16_t>(NamePoolChunk);

	int nameLength = nameEntry >> 6;
	char buff[1024];
	if ((uint32_t)nameLength)
	{
		for (unsigned long x = 0; x < nameLength; ++x)
		{
			buff[x] = Rpm<char>(NamePoolChunk + 4 + x);
		}

		char* v2 = buff; // rdi
		int v4 = nameLength; // ebx
		int v5; // r8d
		unsigned int v6; // eax
		unsigned int v7; // r9d
		__int16 v8; // dx

		v6 = Rpm<int>(base_address + 0xF177D18);
		v5 = 0;
		v7 = v6 >> 5;
		if (v4) {
			do {
				v8 = HIBYTE(*v2) | (v7 ^ (*v2 << 8)) & 0xFF00;
				v7 += 16 * v5;
				*v2 = v8;
				++v5;
				++v2;
			} while (v5 < v4);
		}
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else
	{
		return "";
	}
}

std::string find_object_name(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = Rpm<uint64_t>(base_address + 0xF237A00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); // ERROR_NAME_SIZE_EXCEEDED
	if (Rpm<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = Rpm<DWORD>(NamePoolChunk + 4);
		return find_object_class(a1);
	}
	else
	{
		return find_object_class(key);
	}
}

//static std::string name_dec(DWORD_PTR PlayerState)
//{
//	__int64 FString =  Rpm<__int64>(PlayerState + 0xAC0);
//	int Length =  Rpm<int>(FString + 16);
//	__int64 v6 = Length;
//	if (!v6) return std::string("");
//	uintptr_t FText =  Rpm<__int64>(FString + 8);
//
//	wchar_t* NameBuffer = new wchar_t[Length];
//	ReadMemoryFromKernel(FText, NameBuffer, Length * sizeof(wchar_t));
//
//	char v21;
//	int v22;
//	int i;
//	int v25;
//	_WORD* v23;
//
//	v21 = v6 - 1;
//	if (!(_DWORD)v6)
//		v21 = 0;
//	v22 = 0;
//	v23 = (_WORD*)NameBuffer;
//	for (i = (v21) & 3; ; *v23++ += i & 7)
//	{
//		v25 = v6 - 1;
//		if (!(_DWORD)v6)
//			v25 = 0;
//		if (v22 >= v25)
//			break;
//		i += 3;
//		++v22;
//	}
//
//	std::wstring Temp{ NameBuffer };
//	return std::string(Temp.begin(), Temp.end());
//}

//std::string decrypt_player_name(uintptr_t pState)
//{
//	int pNameLength; // rsi
//	WORD* pNameBufferPointer;
//	int i; // ecx
//	char v25; // al
//	int v26; // er8
//	int v29; // eax
//
//	uintptr_t pNameStructure = Rpm<uintptr_t>(pState + 0xac0); // you won't get help for that offset though
//	pNameLength = Rpm<int>(pNameStructure + 0x10);
//	if (pNameLength <= 0) return "";
//
//	wchar_t* pNameBuffer = new wchar_t[pNameLength];
//	uintptr_t pNameEncryptedBuffer = Rpm<uintptr_t>(pNameStructure + 0x8);
//	ReadMemoryFromKernel((PVOID)pNameEncryptedBuffer, pNameBuffer, pNameLength * sizeof(wchar_t));
//
//	v25 = pNameLength - 1;
//	v26 = 0;
//	pNameBufferPointer = (WORD*)pNameBuffer;
//
//	for (i = (v25) & 3; ; *pNameBufferPointer++ += i & 7)
//	{
//		v29 = pNameLength - 1;
//		if (!(DWORD)pNameLength)
//			v29 = 0;
//
//		if (v26 >= v29)
//			break;
//
//		i += 3;
//		++v26;
//	}
//
//	std::wstring temp_wstring(pNameBuffer);
//	delete[] pNameBuffer;
//	return std::string(temp_wstring.begin(), temp_wstring.end());
//}
CamewaDescwipsion GetViewPoint()
{
	char v1; // r8
	CamewaDescwipsion ViewPoint = Rpm<CamewaDescwipsion>(base_address + 0xf0d7a50);
	BYTE* v2 = (BYTE*)&ViewPoint;
	int i; // edx
	__int64 result; // rax

	v1 = 0x40;
	for (i = 0; i < 0x40; ++i)
	{
		*v2 ^= v1;
		result = (unsigned int)(i + 0x17);
		v1 += i + 0x17;
		v2++;
	}

	return ViewPoint;
}

Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	CamewaDescwipsion vCamera = GetViewPoint();
	D3DMATRIX tempMatrix = Matrix(vCamera.Rotation, Vector3(0, 0, 0));
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f) vTransformed.z = 1.f;
	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}
Vector3 RotatePoint(Vector3 EntityPos, Vector3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool angleInRadians)
{
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;

	float Yaw = angle - 90.0f;

	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

	x_1 *= zoom;
	y_1 *= zoom;

	int sizX = sizeX / 2;
	int sizY = sizeY / 2;

	x_1 += sizX;
	y_1 += sizY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;

	x_1 += posX;
	y_1 += posY;

	return Vector3(x_1, y_1, 0);
}

void draw_rect(int x, int y, int w, int h, ImColor color, int thickness) {
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 3.f, 15, thickness);
}

void draw_rect_filled(int x, int y, int w, int h, ImColor color, int thickness) {
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 3.f, 15);
}

void box_esp(float OffsetW, float OffsetH, int X, int Y, int W, int H, ImU32 Color, int thickness, bool filled, bool outlined) {
	if (filled) {
		ImU32 sdfg = ImColor(0, 0, 0, 100);
		draw_rect_filled(X, Y, W, H, sdfg, thickness);
	}

	if (outlined) {
		draw_rect(X, Y, W, H, ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
	}

	draw_rect(X, Y, W, H, Color, thickness);
}

void corner_esp(float OffsetW, float OffsetH, int X, int Y, int W, int H, ImU32 Color, int thickness, bool filled, bool outlined) {
	ImDrawList* p = ImGui::GetBackgroundDrawList();

	float lineW = (W / OffsetW);
	float lineH = (H / OffsetH);

	if (filled) {
		ImU32 sdfg = ImColor(0, 0, 0, 100);
		draw_rect_filled(X, Y, W, H, sdfg, 0.f);
	}

	if (outlined) {
		p->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
		p->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness + 1);
	}

	p->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), Color, thickness);
	p->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), Color, thickness);
	p->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), Color, thickness);
	p->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), Color, thickness);
	p->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), Color, thickness);
	p->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), Color, thickness);
	p->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), Color, thickness);
	p->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), Color, thickness);

}

void ThreeD_Box(bool StartIsCenter, float Offset, float Thickness, ImU32 Clr, Vector3 Start, float Top)
{
	ImDrawList* pDrawList = ImGui::GetBackgroundDrawList();

	if (StartIsCenter)
	{
		Vector3 BottomOneW2S = Vector3(Start.x + Offset, Start.y + Offset, Start.z - Offset);
		Vector3 BottomTwoW2S = Vector3(Start.x - Offset, Start.y - Offset, Start.z - Offset);
		Vector3 BottomThreeW2S = Vector3(Start.x + Offset, Start.y - Offset, Start.z - Offset);
		Vector3 BottomFourW2S = Vector3(Start.x - Offset, Start.y + Offset, Start.z - Offset);
		Vector3 TopOneW2S = Vector3(Start.x + Offset, Start.y + Offset, Start.z + Offset);
		Vector3 TopTwoW2S = Vector3(Start.x - Offset, Start.y - Offset, Start.z + Offset);
		Vector3 TopThreeW2S = Vector3(Start.x + Offset, Start.y - Offset, Start.z + Offset);
		Vector3 TopFourW2S = Vector3(Start.x - Offset, Start.y + Offset, Start.z + Offset);

		pDrawList->AddLine(ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImGui::GetColorU32(Clr), Thickness);

		pDrawList->AddLine(ImVec2(TopOneW2S.x, TopOneW2S.y), ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImVec2(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopFourW2S.x, TopFourW2S.y), ImVec2(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32(Clr), Thickness);

		pDrawList->AddLine(ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImVec2(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImVec2(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
	}
	else
	{
		Vector3 BottomOneW2S = Vector3(Start.x + Offset, Start.y + Offset, Start.z);
		Vector3 BottomTwoW2S = Vector3(Start.x - Offset, Start.y - Offset, Start.z);
		Vector3 BottomThreeW2S = Vector3(Start.x + Offset, Start.y - Offset, Start.z);
		Vector3 BottomFourW2S = Vector3(Start.x - Offset, Start.y + Offset, Start.z);
		Vector3 TopOneW2S = Vector3(Start.x + Offset, Start.y + Offset, Top);
		Vector3 TopTwoW2S = Vector3(Start.x - Offset, Start.y - Offset, Top);
		Vector3 TopThreeW2S = Vector3(Start.x + Offset, Start.y - Offset, Top);
		Vector3 TopFourW2S = Vector3(Start.x - Offset, Start.y + Offset, Top);

		pDrawList->AddLine(ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImGui::GetColorU32(Clr), Thickness);

		pDrawList->AddLine(ImVec2(TopOneW2S.x, TopOneW2S.y), ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImVec2(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(TopFourW2S.x, TopFourW2S.y), ImVec2(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32(Clr), Thickness);

		pDrawList->AddLine(ImVec2(BottomOneW2S.x, BottomOneW2S.y), ImVec2(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomTwoW2S.x, BottomTwoW2S.y), ImVec2(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomThreeW2S.x, BottomThreeW2S.y), ImVec2(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32(Clr), Thickness);
		pDrawList->AddLine(ImVec2(BottomFourW2S.x, BottomFourW2S.y), ImVec2(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32(Clr), Thickness);
	}
}

void ADrawText(ImFont* Font, ImVec2 pos, ImU32 color, const char* text, float size = 18.0f, bool outline = false)
{
	if (outline) {
		ImVec2 textSize = Font->CalcTextSizeA(size, FLT_MAX, 0.0f, text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2((pos.x) + 1, (pos.y + textSize.y) + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2((pos.x) - 1, (pos.y + textSize.y) - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2((pos.x) + 1, (pos.y + textSize.y) - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2((pos.x) - 1, (pos.y + textSize.y) + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text);
	}

	ImGui::GetBackgroundDrawList()->AddText(Font, size, pos, ImGui::GetColorU32(color), text);
}