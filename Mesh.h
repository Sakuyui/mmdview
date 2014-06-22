#pragma once

#include <vector>

// 3D�x�N�g���̒�`
typedef struct MMD3DVECTOR {
    float x;
    float y;
    float z;
} MMD3DVECTOR;

// 2D�x�N�g���̒�`
typedef struct MMD2DXVECTOR {
    float x;
    float y;
} MMD2DXVECTOR;

/// ���b�V���̒��_�f�[�^
struct Vertex {
	MMD3DVECTOR position;	// ���_�ʒu
	MMD3DVECTOR normal;		// �@���x�N�g��
	MMD2DXVECTOR texture;	// �e�N�X�`�����W
};

/// ���b�V���̃|���S���f�[�^
struct Face {
	unsigned short indices[3];		// 3���_�̃C���f�b�N�X
	unsigned long material_number;	// �ޗ��ԍ�
};

// ���b�V���f�[�^�ꎞ�ۑ��p�\���́B�Ǝ��`���f�[�^�͈�x���̍\���̂Ɋi�[���AMesh::SetMesh()��Mesh::pMesh�ɃZ�b�g����B
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
//	std::vector<D3DMATERIAL9> material;
//	std::vector<string> texture_filename;
};

/// ���b�V���̃x�[�X
class Mesh {
protected:
//	LPDIRECT3DDEVICE9 pDevice;			// Direct3D�f�o�C�X�I�u�W�F�N�g
//	LPD3DXMESH pMesh;					// ���b�V��
//	D3DMATERIAL9* pMeshMaterials;		// �}�e���A���z��
//	LPDIRECT3DTEXTURE9*	pMeshTextures;	// �e�N�X�`���z��
//	DWORD dwNumMaterials;				// �}�e���A���E�e�N�X�`���z��̑傫��
	void AddNormalVector(MeshData& meshData);// MeshData�ɖ@���x�N�g����ǉ�
	void SetMesh(MeshData meshData);	// MeshData��pMesh�ɃZ�b�g
public:
//	Mesh(LPDIRECT3DDEVICE9 pDevice);
//	virtual void Draw(MMD3DVECTOR position, D3DXMATRIX rotation);
//	virtual LPD3DXMESH GetMesh();
//	virtual int GetNumMaterial();

	Mesh(void);
	virtual ~Mesh();
//	virtual void Draw(MMD3DVECTOR position, D3DXMATRIX rotation);
//	virtual LPD3DXMESH GetMesh();
//	virtual int GetNumMaterial();
};

#if 0
/// ���b�V���̃r���[�ϊ��A�ˉe�ϊ����s�Ȃ��J����
class MeshCamera {
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	MeshCamera(LPDIRECT3DDEVICE9 pDev);
	void Look(MMD3DVECTOR eyePoint, MMD3DVECTOR lookAtPoint);
};
#endif

#if 0
/// ���b�V���p���C�g
class MeshLight sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
	D3DLIGHT9 light;
public:
	MeshLight(LPDIRECT3DDEVICE9 pDev);
	void Illume(MMD3DVECTOR direction);
};
#endif


/// PMD�t�@�C������Ǎ��񂾃��b�V��
class PmdMesh : public Mesh {
/// PMD�\���̒�`
#pragma pack(push,1)	//�A���C�������g������I�t
	struct PmdHeader {
		unsigned char magic[3];
		float version;
		unsigned char model_name[20];
		unsigned char comment[256];
	} pmdHeader;
	struct PmdVertex{
		float pos[3];
		float normal_vec[3];
		float uv[2];
		unsigned short bone_num[2];
		unsigned char bone_weight;
		unsigned char edge_flag;
	};
	struct PmdMaterial{
		float diffuse_color[3];
		float alpha;
		float specularity;
		float specular_color[3];
		float mirror_color[3];
		unsigned char toon_index;
		unsigned char edge_flag;
		unsigned long face_vert_count;	// ���̍ޗ��̖ʒ��_�� �� �ޗ��ԍ�i�̃|���S���ԍ��F pmdMaterial[i - 1].face_vert_count/3 �` pmdMaterial[i].face_vert_count/3 - 1
		char texture_file_name[20];
	};
#pragma pack(pop)
//	void CopyMaterial(D3DMATERIAL9& material, PmdMaterial& pmdMaterial);	// PmdMaterial����D3DMATERIAL9�Ƀf�[�^���R�s�[
public:
//	PmdMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice);
	PmdMesh(LPCTSTR filename);
};
