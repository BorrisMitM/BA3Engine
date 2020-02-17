#include "TextCallback.h"
#include "GameManager.h"


void TextCallback::Setup(xml_node<>* callbackNode, string assetPath)
{
	for (xml_node<>* pChild = callbackNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "part") == 0) {
			texts.push_back(pChild->value());
		}
	}
}

void TextCallback::Invoke()
{
	GameManager::instance->StartDialog(texts);
}

TextCallback::TextCallback()
{
}


TextCallback::~TextCallback()
{
}
