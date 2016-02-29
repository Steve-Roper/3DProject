#pragma once
#ifndef MODEL_H
#define MODEL_H

#pragma comment (lib, "d3d11.lib")

#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>


class Model
{
private:
	struct Vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};
	ID3D11Buffer* vertexBuffer, *indexBuffer;

public:
	Model();
	Model(ID3D11Device* device, ID3D11DeviceContext* devcon);
	Model(const Model&);
	~Model();
};

#endif