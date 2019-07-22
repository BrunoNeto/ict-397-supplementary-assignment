#include "Object.h"

Object::Object(std::string assetName)
{
	m_assetType = ASS_OBJECT;
	m_assetName = assetName;
	m_model = new MD2Model();
}

void Object::LoadFromFilePath(const char *filename)
{
	m_model->LoadModel(filename);
}

const void Object::Destroy()
{
	// Todo: destroy all items of Object class
}

void Object::AddTexutre(GLuint textureId, std::string textureFilePath)
{
	//Texture texture;

	//texture.m_id = textureId;
	//texture.m_path = textureFilePath;
	//texture.m_type = "texture_diffuse";

	//m_model->GetTextures().push_back(texture);
	//m_model->GetMeshBatch()[0].GetTextures().push_back(texture);
}
