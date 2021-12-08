#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "MathHelper.h"
#include "GraphicEngineManager.h"

using namespace ParserData;

std::map<std::string, ModelData*>			LoadManager::ModelList;
std::map<std::string, TextureBuffer*>		LoadManager::TextureList;
std::map<std::string, ModelAnimationData*>	LoadManager::AnimationList;
LoadManager::LoadManager()
{
	GEngine = nullptr;
	EaterParser = nullptr;
}

LoadManager::~LoadManager()
{

}

void LoadManager::Initialize(GraphicEngineManager* Graphic)
{
	//�׷��� ���� �޾ƿ���
	GEngine = Graphic;
	EaterParser = ModelParser::Create(ModelParser::FBX);

	EaterParser->Initialize();
}

ModelData* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, ModelData*>::iterator temp = ModelList.find(Name);
	if (temp == ModelList.end())
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET,"Mesh",Name,true);
		return nullptr;
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET, "Mesh", Name, false);
		return temp->second;
	}

}

TextureBuffer* LoadManager::GetTexture(std::string Name)
{
	std::map<std::string, TextureBuffer*>::iterator temp = TextureList.find(Name);
	if (temp == TextureList.end())
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET, "Texture", Name, true);
		return nullptr;
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET, "Texture", Name, false);
		return temp->second;
	}
}

ModelAnimationData* LoadManager::GetAnimation(std::string Name)
{
	if (AnimationList.find(Name) != AnimationList.end())
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET, "Animation", Name, false);
		return AnimationList[Name];
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_GET, "Animation", Name,true);
		return nullptr;
	}
}

void LoadManager::LoadMesh(std::string Name, bool Scale, bool LoadAnime)
{
	// "../ �̰ſ� .fbx �̰Ÿ� �ٿ��ش�"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;

	ModelData* SaveMesh = new ModelData();

	//�ļ��� ���ؼ� �Ž��� �ε�
	ParserData::Model* temp = EaterParser->LoadModel(FullName, Scale, LoadAnime);
	if (temp == nullptr)
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_LOAD, "Mesh", Name, true);
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_LOAD, "Mesh", Name, false);
	}


	//�ִϸ��̼� ������ �־���
	LoadAnimation(SaveMesh,temp, Name);

	//�ִϸ��̼� ������ �����Ÿ� ���⼭ ����
	if (LoadAnime == true) { return; }

	

	//�������� TM�� ������Ʈ�� �����о�������� 
	int MeshCount = (int)temp->m_MeshList.size();
	for (int i = 0; i < MeshCount; i++)
	{
		//����Ʈ�� �Ž� ����
		ParserData::Mesh* mesh = temp->m_MeshList[i];

		//�ֻ��� �Ž��� �ƴ϶�� �ƹ��͵� ��������
		if (mesh->m_TopNode != true) { continue; }

		//�Ž��̰� ��Ű�� ������Ʈ���
		if (mesh->m_IsBone == false && mesh->m_IsSkinningObject == true)
		{
			//���� ������ ������ �о�� ������ �ؿ��� 
			SaveMesh->BoneOffsetList	= &mesh->m_BoneTMList;
			SaveMesh->BoneList			= &mesh->m_BoneMeshList;
		}

		//�Ž��̰� ž ������Ʈ���
		if (mesh->m_IsBone == false && mesh->m_TopNode)
		{
			LoadMeshData* TopMesh = CreateMeshObjeect(mesh);
			SaveMesh->TopMeshList.push_back(TopMesh);
		}
	}
	

	////�о�� BoneOffset �� ����Ʈ�� ������� �����ϰ� �������� ������ �ֻ������̾ƿ´�
	LoadMeshData* TopBone = CreateBoneObjeect(SaveMesh);
	if (TopBone != nullptr) { SaveMesh->TopBoneList.push_back(TopBone); }


	//�ֻ��� ������Ʈ�� ����Ʈ�� �־��ش�
	std::string::size_type End = Name.rfind('_');
	std::string::size_type start = 0;
	std::string SaveName = Name.substr(start, End);
	ModelList.insert({ SaveName,SaveMesh });
}

void LoadManager::LoadTexture(std::string Name)
{
	std::string TextureName = TexturePath + Name;


	TextureBuffer* Tbuffer = GEngine->CreateTextureBuffer(TextureName);
	
	if (Tbuffer == nullptr || Tbuffer->TextureBufferPointer == nullptr)
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_LOAD, "Texture", Name, true);
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_LOAD, "Texture", Name, false);
		//�̸��� .dds , .png �� ���� �����Ѵ�
		std::string::size_type End = Name.rfind('.');
		std::string::size_type start = 0;
		std::string SaveName = Name.substr(start, End);

		TextureList.insert({ SaveName,Tbuffer });
	}
}

void LoadManager::LoadPrefap(std::string Name)
{
	///���߿� ����
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	//�� ��� �Է�
	MeshPath = mPath;
}

void LoadManager::LoadTexturePath(std::string mPath)
{
	//�ؽ��� ��� �Է�
	TexturePath = mPath;
	ModelParser::SetTextureRoute(TexturePath);
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//�޸𸮿� �Ҵ��� �Ž��� ������ ������Ŵ
	std::map<std::string, ModelData*>::iterator temp = ModelList.find(mMeshName);
	if (temp == ModelList.end())
	{
		return;
	}
	else
	{
		ModelList.erase(mMeshName);
	}
}

void LoadManager::DeleteMeshAll()
{
	ModelList.clear();
}

LoadMeshData* LoadManager::CreateMeshObjeect(ParserData::Mesh* mesh)
{
	//�������� �ޱ�
	LoadMeshData* box = new LoadMeshData();

	SetData(box, mesh);

	//���۰� �о����
	box->IB = GEngine->CreateIndexBuffer(mesh);
	box->IB->Count = (int)mesh->m_IndexList.size() * 3;

	box->VB = GEngine->CreateVertexBuffer(mesh);
	box->VB->Count = (int)mesh->m_VertexList.size();

	//�ڽİ�ü�� �ִٸ� �����о��
	int ChildCount = (int)mesh->m_ChildList.size();
	for (int i = 0; i < ChildCount; i++)
	{
		LoadMeshData* temp = CreateMeshObjeect(mesh->m_ChildList[i]);
		box->Child.push_back(temp);
		temp->Parent = box;
	}

	return box;
}

LoadMeshData* LoadManager::CreateBoneObjeect(ModelData* SaveData)
{
	///�о�� �� ����Ʈ�� ���� �����ϰ� BoneOffset�� ��������
	if (SaveData->BoneList == nullptr) { return nullptr; }

	//���� ������ŭ ���� ������Ŵ
	int boneCount = (int)SaveData->BoneList->size();

	//ũ������
	std::vector<LoadMeshData*> TempBoneList;
	TempBoneList.resize(boneCount);

	for (int i = 0; i < boneCount; i++)
	{
		ParserData::Mesh* mesh = (*SaveData->BoneList)[i];
		if (mesh == nullptr) { continue; }

		LoadMeshData* data = new LoadMeshData();
		TempBoneList[i] = data;
		SetData(data, mesh);
		data->BoneOffset = &(*SaveData->BoneOffsetList)[i];
		data->BoneList	 = &(SaveData->BoneList)[i];
	}

	///������ ������ �θ��ڽİ���� ��ũ������
	LoadMeshData* TOP_BONE = nullptr;
	for (int i = 0; i < boneCount; i++)
	{
		for (int j = 0; j < boneCount; j++)
		{
			//�ڱ� �ڽŰ��� �˻������ʴ´�
			if (TempBoneList[i] == TempBoneList[j]) { continue; }
			//���°ſ� ����������
			if (TempBoneList[i] == nullptr || TempBoneList[j] == nullptr) { continue; }

			LoadMeshData* Front = TempBoneList[i];
			LoadMeshData* Back = TempBoneList[j];
			//���� �θ��̸��� �ڱ��ڽ��� �̸��϶� ����
			if (Front->ParentName == Back->Name)
			{
				Front->Parent = Back;
				Back->Child.push_back(Front);
			}

			if (Front->Top_Object == true)
			{
				TOP_BONE = Front;
			}
		}
	}

	///��� ����� ���¿��� �ֻ��� ������Ʈ�� �������ش�
	return TOP_BONE;
}

void LoadManager::LoadAnimation(ModelData* SaveMesh, ParserData::Model* MeshData, std::string Name)
{
	if (MeshData->m_isAnimation == false)
	{
		return;
	}
	else
	{
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_LOAD, "Animation", Name, false);
		CreateAnimationKeyFrame( &(MeshData->m_AnimationList) ,10);
	}

	//������ �̸� ���� ù��° key
	//���� string�� �Ǿպ���"_"�������д´�
	std::string::size_type start = 0;
	std::string::size_type End = Name.rfind('_');
	std::string SaveName = Name.substr(start, End);
	//Enemy_Run �̶�� Enemy�� ù��° Ű 

	if (AnimationList.find(SaveName) == AnimationList.end())
	{
		//ã�� �̸��� ���ٸ� ������ش�
		ModelAnimationData* data = new ModelAnimationData();
		AnimationList.insert({ SaveName,data});
	}

	//������ �̸� ���� �ι�° key
	//"_"���� string ����������
	//Enemy_Run �̶�� Run �ι�° Ű 
	start = End+1;
	End = Name.length();
	std::string key = Name.substr(start, End);


	//������ ����
	ModelAnimationData* temp = AnimationList[SaveName];
	temp->AnimList.insert({key, &(MeshData->m_AnimationList)});
}

void LoadManager::CreateAnimationKeyFrame(std::vector<ParserData::OneAnimation*>* Anime,int InputKeyCount)
{
	//���� �ִϸ��̼�
	std::vector<ParserData::OneAnimation*>::iterator it = Anime->begin();

	for (it; it != Anime->end(); it++)
	{
		std::vector<ParserData::OneFrame*> data = (*it)->m_AniData;
		//���Ӱ� ���� ������ ����Ʈ
		std::vector<ParserData::OneFrame*> CreateData;

		int Size = (int)data.size();
		for (int i = 0; i < Size-1; i++)
		{
			//������ ó����
			DirectX::SimpleMath::Vector3 Start_Pos		= data[i]->m_Pos;
			DirectX::SimpleMath::Quaternion Start_Rot	= data[i]->m_RotQt;
			DirectX::SimpleMath::Vector3 Start_Scl		= data[i]->m_Scale;
			float Start_Time = data[i]->m_Time;

			//������ ������
			int NextIndex = i + 1;
			DirectX::SimpleMath::Vector3 End_Pos		= data[NextIndex]->m_Pos;
			DirectX::SimpleMath::Quaternion End_Rot		= data[NextIndex]->m_RotQt;
			DirectX::SimpleMath::Vector3 End_Scl		= data[NextIndex]->m_Scale;
			float End_Time = data[NextIndex]->m_Time;

			///ó���� �־��ֱ�
			CreateData.push_back(data[i]);
			
			int KeyCount = InputKeyCount;		//������ Ű������
			float CountLerp = (float)(1/InputKeyCount);	//������ Ű������ ������ ��ġ��������
			for (int j = 0; j < KeyCount; j++)
			{
				//���ο� Ű ������ ����
				ParserData::OneFrame* temp = new OneFrame();
				temp->m_Pos		= Vector3::Lerp(Start_Pos, End_Pos, CountLerp);
				temp->m_RotQt	= Quaternion::Lerp(Start_Rot, End_Rot, CountLerp);
				temp->m_Scale	= Vector3::Lerp(Start_Scl, End_Scl, CountLerp);
				temp->m_Time	= MathHelper::Lerp(Start_Time, End_Time, CountLerp);

				CreateData.push_back(temp);
				CountLerp += 0.1f;
			}

			///�������� �־��ֱ�
			CreateData.push_back(data[NextIndex]);
		}

		(*it)->m_AniData = CreateData;
		(*it)->m_TicksPerFrame /= (InputKeyCount +2);
		(*it)->m_EndFrame = (Size * (InputKeyCount + 2)) - (InputKeyCount + 2);
	}
}

void LoadManager::SetData(LoadMeshData* MeshData, ParserData::Mesh* LoadData)
{
	MeshData->Name				= LoadData->m_NodeName;
	MeshData->ParentName		= LoadData->m_ParentName;
	MeshData->Top_Object		= LoadData->m_TopNode;
	MeshData->Bone_Object		= LoadData->m_IsBone;
	MeshData->Skinning_Object	= LoadData->m_IsSkinningObject;
	MeshData->BoneIndex			= LoadData->m_BoneIndex;

	//���� ������ �׳� �о��
	MeshData->Animation = LoadData->m_Animation;
	MeshData->Material = LoadData->m_MaterialData;
	
	// Texture Buffer ����..
	CMaterial* mat = LoadData->m_MaterialData;
	if (mat != nullptr)
	{
		if (mat->m_IsDiffuseMap == true)
		{
			MeshData->Albedo = GEngine->CreateTextureBuffer(mat->m_DiffuseMap->m_BitMap);
		}
		if (mat->m_IsBumpMap == true)
		{
			MeshData->Normal = GEngine->CreateTextureBuffer(mat->m_BumpMap->m_BitMap);
		}
	}

	//��Ʈ���� ���� �ޱ�
	MeshData->WorldTM = &LoadData->m_WorldTM;
	MeshData->LocalTM = &LoadData->m_LocalTM;
}











