#include "Model.h"
#include <d3dcompiler.h>

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

	hr = device->CreateVertexShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
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

}