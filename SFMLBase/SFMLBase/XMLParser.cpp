#include "XMLParser.h"



xml_node<>* XMLParser::FindChildNode(xml_node<>* pNode, const char * name)
{
	return nullptr;
}

xml_attribute<>* XMLParser::FindAttribute(xml_node<>* pNode, const char * name)
{
	return nullptr;
}

void XMLParser::LoadXML(vector<GameScene*>* scenes)
{
	ifstream MyFile("Assets.xml", ios::binary);

	//get size
	streampos begin = MyFile.tellg();
	MyFile.seekg(0, ios::end);
	streampos end = MyFile.tellg();
	int nSize = end - begin;
	MyFile.seekg(0, ios::beg);
	//get file to string
	char *pText = new char[nSize + 1];
	memset(pText, 0, nSize + 1);
	MyFile.read(pText, nSize);
	MyFile.close();

	xml_document<>	doc;
	xml_attribute<>* attr;

	doc.parse<0>(pText);

	xml_node<>*	pRootNode = doc.first_node();
	xml_node<>* pNode = pRootNode;

	attr = FindAttribute(pNode, "title");
	if (attr != NULL) GameConfig.name.append(attr->value());
	attr = FindAttribute(pNode, "width");
	if (attr != NULL) GameConfig.width = atoi(attr->value());
	attr = FindAttribute(pNode, "height");
	if (attr != NULL) GameConfig.height = atoi(attr->value());
	attr = FindAttribute(pNode, "fps");
	if (attr != NULL) GameConfig.fps = atoi(attr->value());

	pNode = FindChildNode(pNode, "assetpath");
	if (pNode != NULL) GameConfig.assetPath.append(pNode->value());
	for (xml_node<>* pChild = pRootNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "scene") == 0) {
			GameScene* pScene = new GameScene();

			attr = FindAttribute(pChild, "name");
			if (attr != NULL) pScene->name.append(attr->value());
			pNode = FindChildNode(pChild, "assets");
			if (pNode != NULL) {
				for (xml_node<>* pAssets = pNode->first_node(); pAssets != NULL; pAssets = pAssets->next_sibling()) {
					if (strcmp(pAssets->name(), "asset") == 0) {
						GameAsset* pAsset = new GameAsset();
						pAsset->fileName.append(pAssets->value());
						attr = FindAttribute(pAssets, "id");
						if (attr != NULL) pAsset->ID.append(attr->value());
						attr = FindAttribute(pAssets, "type");
						if (strcmp(attr->value(), "sprite") == 0) pAsset->type = 0;
						if (strcmp(attr->value(), "audio") == 0) pAsset->type = 1;

						pScene->assets.push_back(pAsset);
					}
				}
			}
			scenes->push_back(pScene);
		}
	}
	doc.clear();
}

XMLParser::XMLParser()
{

}


XMLParser::~XMLParser()
{
}
