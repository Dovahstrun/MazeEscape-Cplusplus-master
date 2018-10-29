//Includes
#include "Score.h"
#include "AssetManager.h"

Score::Score()
	: TextObject()
{
	m_text.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));
	m_text.setString("Score: 0");
}