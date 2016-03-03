#pragma comment(lib, "d3dcompiler.lib")
#include "Model.h"
#include <d3dcompiler.h>

const int WIDTH = 800;
const int HEIGHT = 600;

Model::Model()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

Model::Model(ID3D11Device* device, ID3D11DeviceContext*devcon)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT n = ARRAYSIZE(layout);

	HRESULT hr;

	ID3D11VertexShader* VS;
	ID3D10Blob* VS_Buffer;
	hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "VS_MAIN", "vs_4_0", 0, 0, &VS_Buffer, 0);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error compiling VS", L"Lik mij bauls", MB_OK);
	}

	hr = device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error creating VS", L"Lik mij bauls", MB_OK);
	}

	ID3D11PixelShader* PS;
	ID3D10Blob* PS_Buffer;
	hr = D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "PS_MAIN", "ps_4_0", 0, 0, &PS_Buffer, 0);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error compiling PS", L"Lik mij bauls", MB_OK);
	}

	hr = device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error creating PS", L"Lik mij bauls", MB_OK);
	}

	devcon->VSSetShader(VS, 0, 0);
	devcon->PSSetShader(PS, 0, 0);

	Vertex vertices[] = {
		DirectX::XMFLOAT4(-0.5f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f),

		DirectX::XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f),

		DirectX::XMFLOAT4(-0.5f, 0.5f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f)
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ID3D11Buffer* triangleVerticeBuffer;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;
	hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleVerticeBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error creating Vertex Buffer", L"Lik mij bauls", MB_OK);
	}
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(9, 1, &triangleVerticeBuffer, &stride, &offset);

	ID3D11InputLayout* vertLayout;
	device->CreateInputLayout(layout, n, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertLayout);

	devcon->IASetInputLayout(vertLayout);

	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = WIDTH;
	viewport.Height = HEIGHT;

	devcon->RSSetViewports(1, &viewport);
}

Model::~Model()
{

}