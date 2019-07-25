#include "Player.h"

Player::Player(std::string playerName)
{
	m_name = playerName;
	m_playerModel = new MD2Model();

	pickedUpItem = new Object();
}

void Player::LoadFromFilePath(const char* filePath)
{
	m_playerModel->LoadModel(filePath);
}

const void Player::Destroy()
{
	return void();
}

void Player::setPickedUpItem(Object* newObject) 
{
	pickedUpItem = newObject;
}
