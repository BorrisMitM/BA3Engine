#include "Player.h"
#include "GameManager.h"
#include "MyTime.h"

void Player::SetScale()
{
	//linear interpolation to scale player depending on y value to simulate a 3d environment
	float playFieldHeight = -(topBorder - botBorder);
	float relativPos = -(pos.y - botBorder);
	float scaleDifference = topScale - botScale;
	if(playFieldHeight > 0)
		scale = scaleDifference * relativPos / playFieldHeight  + botScale;
	//determine direction to face
	if(moveDir.x != 0)
		spriteScale.x = abs(spriteScale.x) * moveDir.x / abs(moveDir.x);
}

void Player::Setup(xml_node<>* playerNode, map<string, GameAsset*>& assets)
{
	xml_attribute<>* attr = GameManager::FindAttribute(playerNode, "spritescalex");
	if (attr != NULL) spriteScale.x = atof(attr->value());
	else spriteScale.x = 1;
	attr = GameManager::FindAttribute(playerNode, "spritescaley");
	if (attr != NULL) spriteScale.y = atof(attr->value());
	else spriteScale.y = 1;
	attr = GameManager::FindAttribute(playerNode, "botscale");
	if (attr != NULL) botScale = atof(attr->value());
	attr = GameManager::FindAttribute(playerNode, "idle");
	if (attr != NULL) idleAnimation = (DrawableAsset*)assets[attr->value()];
	attr = GameManager::FindAttribute(playerNode, "walk");
	if (attr != NULL) walkAnimation = (DrawableAsset*)assets[attr->value()];
}

void Player::Update(Vector2f mousePos, bool mouseDown)
{
	if (mouseDown) {
		targetPos = mousePos;
		moveDir = targetPos - pos;
		//normalizing direction vector
		float distance = sqrtf((pos.x - targetPos.x) * (pos.x - targetPos.x) + (pos.y - targetPos.y) * (pos.y - targetPos.y));
		if (distance > 0) {
			moveDir.x /= distance;
			moveDir.y /= distance;
			moving = true;
		}
		if (targetPos.y < topBorder) {
			//I guess this is the right math for calculating the point on the border if you click outside of it
			targetPos.x = pos.x + moveDir.x * (topBorder - pos.y) / moveDir.y;
			targetPos.y = topBorder;
		}
		else if (targetPos.y > botBorder) {
			targetPos.x = pos.x + moveDir.x * (botBorder - pos.y) / moveDir.y;
			targetPos.y = botBorder;
		}
	}
	int currentTime = MyTime::clock->getElapsedTime().asMilliseconds();
	float deltaTime = (currentTime - lastFrameTime) / 1000.0;
	lastFrameTime = currentTime;
	if (!moving) return;
	float travelDistance = speed * deltaTime;
	float travelDistanceLeft = sqrtf((pos.x - targetPos.x) * (pos.x - targetPos.x) + (pos.y - targetPos.y) * (pos.y - targetPos.y)); // pythagoras
	if (travelDistance >= travelDistanceLeft) {
		pos = targetPos;
		moving = false;
	}
	else {
		pos += (moveDir * travelDistance);
	}
	SetScale();
}

void Player::SetIntoScene(Vector2f _pos)
{
	pos = _pos;
	SetScale();
}

void Player::Render(RenderWindow & window)
{
	if (moving) {
		walkAnimation->Update(window, pos, spriteScale * scale);
	}
	else idleAnimation->Update(window, pos, spriteScale * scale);
}

Player::Player()
{
}


Player::~Player()
{
}
