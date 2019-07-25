#include "Object.h"

Object::Object(std::string assetName)
{
	m_assetType = ASS_OBJECT;
	m_assetName = assetName;
	m_model = new MD2Model();
	position = vec3(0, 0, 0);
	rotation = vec3(1, 0, 0);
	angle = 0;
	itemType = 0;//set to default
}

void Object::LoadFromFilePath(const char * modelFileName, const char * modelSkinFileName)
{
	m_model->LoadModel(modelFileName);
	m_model->LoadSkin(modelSkinFileName);
}

void Object::SetAnimation(int animEnumeration) { m_model->SetAnim(animEnumeration); }
const void Object::Destroy()
{
	delete m_model;
	// Todo: destroy all items of Object class
}

void Object::SetScale(float scale)
{
	m_model->ScaleModel(scale);
}

void Object::SetPosition(vec3 pos)
{
	position = pos;
}

void Object::SetPosition(float x, float z, Terrain& t)
{
	position.x = x;
	position.z = z;
	position.y = t.getHeight(x, z);
}

void Object::SetRotation(vec3 rot)
{
	rotation = rot;
}

void Object::Update(float deltaTime, Terrain& t)
{
	// this function will be used to update world positions and do state stuuf
		//SetHeight(y+25);
	//NPCSM->update();


	//Move(deltaTime, t);

}

void Object::Draw(float time)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	m_model->DrawModel(time);
	glPopMatrix();
}




//void Object::AddTexutre(GLuint textureId, std::string textureFilePath)
//{
	//Texture texture;

	//texture.m_id = textureId;
	//texture.m_path = textureFilePath;
	//texture.m_type = "texture_diffuse";

	//m_model->GetTextures().push_back(texture);
	//m_model->GetMeshBatch()[0].GetTextures().push_back(texture);
//}
