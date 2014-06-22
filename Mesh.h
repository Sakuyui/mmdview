#pragma once

/// ���b�V���̒��_�f�[�^
struct Vertex {
	D3DXVECTOR3 position;	// ���_�ʒu
	D3DXVECTOR3 normal;		// �@���x�N�g��
	D3DXVECTOR2 texture;	// �e�N�X�`�����W
};

/// ���b�V���̃|���S���f�[�^
struct Face {
	unsigned short indices[3];		// 3���_�̃C���f�b�N�X
	unsigned long material_number;	// �ޗ��ԍ�
};

// ���b�V���f�[�^�ꎞ�ۑ��p�\���́B�Ǝ��`���f�[�^�͈�x���̍\���̂Ɋi�[���AMesh::SetMesh()��Mesh::pMesh�ɃZ�b�g����B
struct MeshData {
	vector<Vertex> vertices;
	vector<Face> faces;
	vector<D3DMATERIAL9> material;
	vector<string> texture_filename;
};

/// ���b�V���̃x�[�X
class Mesh {
protected:
	LPDIRECT3DDEVICE9 pDevice;			// Direct3D�f�o�C�X�I�u�W�F�N�g
	LPD3DXMESH pMesh;					// ���b�V��
	D3DMATERIAL9* pMeshMaterials;		// �}�e���A���z��
	LPDIRECT3DTEXTURE9*	pMeshTextures;	// �e�N�X�`���z��
	DWORD dwNumMaterials;				// �}�e���A���E�e�N�X�`���z��̑傫��
	void AddNormalVector(MeshData& meshData);// MeshData�ɖ@���x�N�g����ǉ�
	void SetMesh(MeshData meshData);	// MeshData��pMesh�ɃZ�b�g
public:
	Mesh(LPDIRECT3DDEVICE9 pDevice);
	virtual ~Mesh();
	virtual void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);
	virtual LPD3DXMESH GetMesh();
	virtual int GetNumMaterial();
};

/// ���b�V���̃r���[�ϊ��A�ˉe�ϊ����s�Ȃ��J����
class MeshCamera sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	MeshCamera(LPDIRECT3DDEVICE9 pDev);
	void Look(D3DXVECTOR3 eyePoint, D3DXVECTOR3 lookAtPoint);
};

/// ���b�V���p���C�g
class MeshLight sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
	D3DLIGHT9 light;
public:
	MeshLight(LPDIRECT3DDEVICE9 pDev);
	void Illume(D3DXVECTOR3 direction);
};

/// X�t�@�C������Ǎ��񂾃��b�V��
class XFileMesh sealed : public Mesh {
public:
	XFileMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice);
};

/// ���^�Z�R�C�A�t�@�C������Ǎ��񂾃��b�V��
class MqoMesh sealed : public Mesh {
private:
	template <typename T> vector<T> MaterialPickOut(string str, char* name, int n); // �}�e���A���s�̕����񂩂�w�肵�����O�̒l�̔z����擾
	void LoadMaterial(ifstream& ifs, MeshData& meshData);
	void LoadObject(ifstream& ifs, MeshData& meshData);
	MeshData GetMeshDataFromMQO(LPCTSTR filename); // ���^�Z�R�C�A�t�@�C�����烁�b�V���f�[�^��Ǎ���
public:
	MqoMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice);
};

/// PMD�t�@�C������Ǎ��񂾃��b�V��
class PmdMesh sealed : public Mesh {
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
	void CopyMaterial(D3DMATERIAL9& material, PmdMaterial& pmdMaterial);	// PmdMaterial����D3DMATERIAL9�Ƀf�[�^���R�s�[
public:
	PmdMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice);
};