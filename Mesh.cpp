
#include "Mesh.h"

//�T���v���R�[�h�ł�DirectX�𗘗p����O��ɂȂ��Ă���̂ŁA
// ���̈ʒu��DirectX��Windows�̓Ǝ��R�[�h��u�������鏈�u������
#define SAFE_RELEASE(X){if(X){ X->release() X=NULL;}}
#define	DWORD	uint32_t;

// ���������̃���
// �E�e�N�X�`���̕ێ��G���A
// �E�}�e���A���̕ێ��G���A
// �E�@���x�N�g�������߂�֐�(D3DX���g���Ă����̂ō폜)

///// Mesh�N���X /////
//Mesh::Mesh(LPDIRECT3DDEVICE9 pDev) : pDevice(pDev), pMesh(0), pMeshTextures(0), pMeshMaterials(0) {
Mesh::Mesh(void)
{
}

Mesh::~Mesh()
{
}

void Mesh::SetMesh(MeshData meshData)
{
#if 0	// DirectX�ˑ��̏����Ȃ̂œ��ʂ̓R�����g�A�E�g
	D3DXCreateMeshFVF(meshData.faces.size(), meshData.vertices.size(), D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, pDevice, &pMesh);
	Vertex* vertexBuffer;
	pMesh->LockVertexBuffer(0, (void**)&vertexBuffer);
	for (unsigned int i = 0; i < meshData.vertices.size(); ++i) {
		vertexBuffer[i].position = meshData.vertices[i].position;
		vertexBuffer[i].normal = meshData.vertices[i].normal;
		vertexBuffer[i].texture = meshData.vertices[i].texture;
	}
	pMesh->UnlockVertexBuffer();
	unsigned short* indexBuffer;
	pMesh->LockIndexBuffer(0, (void**)&indexBuffer);
	for (unsigned int i = 0; i < meshData.faces.size(); ++i) for (unsigned int j = 0; j < 3; ++j) indexBuffer[3*i + j] = meshData.faces[i].indices[j];
	pMesh->UnlockIndexBuffer();
	unsigned long* attributeBuffer;
	pMesh->LockAttributeBuffer(0, &attributeBuffer);
	for (unsigned int i = 0; i < meshData.faces.size(); ++i) attributeBuffer[i] = meshData.faces[i].material_number;
	pMesh->UnlockAttributeBuffer();
	dwNumMaterials = meshData.material.size();
    pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
    pMeshTextures  = new LPDIRECT3DTEXTURE9[dwNumMaterials];
	for (DWORD i = 0; i < dwNumMaterials; ++i) pMeshTextures[i] = 0;
	for (DWORD i = 0; i < dwNumMaterials; ++i) { 
		pMeshMaterials[i] = meshData.material[i];
		char tex_filename[256] = {0};		// UNICODE���Ή��e�N�X�`���t�@�C����
		TCHAR textureFilename[256] = {0};	// UNICODE/�}���`�o�C�g���Ή��e�N�X�`���t�@�C����
		if (strcpy_s(tex_filename, meshData.texture_filename[i].c_str())) throw TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���");
		if (strlen(tex_filename) > 0) strcpy_s(textureFilename, tex_filename);
		if (lstrlen(textureFilename) > 0) // UNICODE/�}���`�o�C�g���Ή��e�N�X�`���t�@�C��������e�N�X�`�����쐬
			if(FAILED(D3DXCreateTextureFromFileEx(pDevice, textureFilename, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &pMeshTextures[i]))) throw TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���");
	}
#endif
}

//void Mesh::Draw(MMD3DVECTOR position, D3DXMATRIX rotation)
void Mesh::Draw(void)
{
#if 0	// DirectX�ˑ��̏����Ȃ̂œ��ʂ̓R�����g�A�E�g
	D3DXMATRIX matWorld, matTrans;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	matWorld = rotation*matTrans;
    pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �|���S����Diffuse�F�̓����x���e�N�X�`���ɔ��f������
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	for (DWORD i = 0; i < dwNumMaterials; ++i) {
		pDevice->SetMaterial(&pMeshMaterials[i]);
		pDevice->SetTexture(0, pMeshTextures[i]); 
		pMesh->DrawSubset(i);
	}
#endif
}

#if 0
///// ���b�V���p�J���� /////
MeshCamera::MeshCamera(LPDIRECT3DDEVICE9 pDev) : pDevice(pDev) {
}

void MeshCamera::Look(MMD3DVECTOR eyePoint, MMD3DVECTOR lookAtPoint) {
	const MMD3DVECTOR upVec(0, 1, 0);									// ����x�N�g��
	const float viewAngle = D3DX_PI/4;									// ����p
	const float aspect = (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT;		// �A�X�y�N�g�� = �r���[��Ԃ̕�/���� (MSDN�ł͍���/���ɂȂ��Ă��邪�ԈႢ)
	const float nearZ = 0.1f;											// �ŋߓ_ (0�ɂ���ƃ|���S�����߂����Ƀ`���c�L���N����)
	const float farZ = 2000.0f;											// �ŉ��_
	D3DXMATRIXA16 matView, matProj;
	D3DXMatrixLookAtLH(&matView, &eyePoint, &lookAtPoint, &upVec);
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	pDevice->SetTransform(D3DTS_VIEW, &matView);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

///// ���b�V���p���C�g /////
MeshLight::MeshLight(LPDIRECT3DDEVICE9 pDev) : pDevice(pDev) {
	const D3DCOLORVALUE diffuse = {1, 1, 1, 0};
	const D3DCOLORVALUE specular = {1, 1, 1, 0};
	const D3DCOLORVALUE ambient = {1, 1, 1, 0};
	const float range = 200.0f;
	const MMD3DVECTOR direction(-0.1f, -1.0f, -0.1f);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient	= ambient;
	light.Diffuse	= diffuse;
	light.Specular	= specular;
	light.Range     = range;
	light.Direction = direction;
}

void MeshLight::Illume(MMD3DVECTOR direction) {
	light.Direction = direction;
	pDevice->SetLight(0, &light );
	pDevice->LightEnable(0, TRUE );
}
#endif

/// PmdMesh�N���X
PmdMesh::PmdMesh(char* filename)
{
	// PMD�t�@�C������PMD�f�[�^�𒊏o
    std::ifstream ifs(filename, std::ios::binary);
	if ( ifs.fail() ){
		perror("�t�@�C���ǂݍ��߂Ȃ�����\n");
	}
	ifs.read((char*)&pmdHeader, sizeof(pmdHeader));
	unsigned long numPmdVertex;
	ifs.read((char*)&numPmdVertex, sizeof(numPmdVertex));
	PmdVertex* pmdVertices = new PmdVertex[numPmdVertex];
	ifs.read((char*)pmdVertices, sizeof(PmdVertex)*numPmdVertex);
	unsigned long numPmdFace;
	ifs.read((char*)&numPmdFace, sizeof(numPmdFace));
	unsigned short *pmdFaces = new unsigned short[numPmdFace];
	ifs.read((char*)pmdFaces, sizeof(unsigned short)*numPmdFace);
	unsigned long numPmdMaterial;
	ifs.read((char*)&numPmdMaterial, sizeof(numPmdMaterial));
	PmdMaterial* pmdMaterial = new PmdMaterial[numPmdMaterial];
	ifs.read((char*)pmdMaterial, sizeof(PmdMaterial)*numPmdMaterial);

	// PMD�f�[�^����MeshData�ɃR�s�[
	MeshData meshData;
	for (unsigned int i = 0; i < numPmdVertex; ++i) {
		Vertex v;
		v.position = MMD3DVECTOR(pmdVertices[i].pos[0], pmdVertices[i].pos[1], pmdVertices[i].pos[2]);
		v.position.x *= 0.1f;			// �{��
		v.position.y *= 0.1f;			// �{��
		v.position.z *= 0.1f;			// �{��
		v.normal= MMD3DVECTOR(pmdVertices[i].normal_vec[0], pmdVertices[i].normal_vec[1], pmdVertices[i].normal_vec[2]);
		v.texture = MMD2DXVECTOR(pmdVertices[i].uv[0], pmdVertices[i].uv[1]);
		meshData.vertices.push_back(v);
	}
	delete pmdVertices;
	Face f;
	for (unsigned int i = 0; i < numPmdFace; ++i) {
		f.indices[i%3] = pmdFaces[i];
		if (i%3 == 2) meshData.faces.push_back(f);
	}
	delete pmdFaces;
#if 0
	D3DMATERIAL9 material = {0};
	unsigned int j = 0, material_end = 0;
	for (unsigned int i = 0; i < numPmdMaterial; ++i) {
		CopyMaterial(material, pmdMaterial[i]);
		meshData.material.push_back(material);
		char tex[21] = {0};	// �t�@�C������20byte�̂Ƃ��̂��߂ɍŌ��0��ǉ�
		memcpy(tex, pmdMaterial[i].texture_file_name, 20);
		string s(tex);
		s = s.substr(0, s.find("*"));	// temp
		meshData.texture_filename.push_back(s);
		material_end += pmdMaterial[i].face_vert_count;
		for (; j < material_end; ++j) meshData.faces[j/3].material_number = i;
	}
	delete pmdMaterial;
#endif
	// MeshData���O���t�B�b�N�{�[�h�̃������ɃZ�b�g
	SetMesh(meshData);
}

#if 0
void PmdMesh::CopyMaterial(D3DMATERIAL9& material, PmdMaterial& pmdMaterial) {
	material.Ambient.a = pmdMaterial.alpha;
	material.Ambient.r = pmdMaterial.mirror_color[0];
	material.Ambient.g = pmdMaterial.mirror_color[1];
	material.Ambient.b = pmdMaterial.mirror_color[2];
	material.Diffuse.a = pmdMaterial.alpha;
	material.Diffuse.r = pmdMaterial.diffuse_color[0];
	material.Diffuse.g = pmdMaterial.diffuse_color[1];
	material.Diffuse.b = pmdMaterial.diffuse_color[2];
	material.Power = pmdMaterial.specularity;
	material.Specular.a = pmdMaterial.alpha;
	material.Specular.r = pmdMaterial.specular_color[0];
	material.Specular.g = pmdMaterial.specular_color[1];
	material.Specular.b = pmdMaterial.specular_color[2];
}
#endif
