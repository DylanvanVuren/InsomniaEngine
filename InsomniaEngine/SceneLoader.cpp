#include "SceneLoader.h"
#include "Scene.h"
#include "iostream"

SceneLoader::SceneLoader() {

}

SceneLoader::~SceneLoader() {

}

void SceneLoader::loadEntitiesList(Scene* scene) {
	scene->setScene(this);
	list<Entity> sceneList;
	scene.drawEntity(sceneList);
}

/*list<Entity> loadEntitiesList(){
  list<Entity> entityLijst = new list<>();
  return entityLijst;
}
*/


void SceneLoader::Save()
{
	//*save entities to XML file*
	TiXmlDocument file;

	XmlWriter saveEntityFile;
	Elem entities = saveEntityFile.Element("entities");
	list<Entity>::iterator itr;
	list<Entity> enList;
	enList.loadEntitiesList();

	for (itr = <enList>.begin();itr != <enList>.end();++itr)
	{
		entityName = enList(itr*).getEntityName();
		entities.addText(entityName + '');
	}

	file.SaveFile("EntityFile.xml");

	/* - old vb van JSON file -
	std::ofstream saveEntityFile;
	saveEntityFile.open("Save/EntityFileSave.json", std::ofstream::trunc); //.json file || truncate	Any contents that existed in the file before it is open are discarded.
	list<Entity>::iterator itr;
	list<Entity> enList;
	enList.loadEntitiesList();

	for(itr=<enList>.begin();itr != <enList>.end();++itr)
	{saveEntityFile<<itr->Json::Value(itr*)}}
	*/
}

	void SceneLoader::Load()
	{
		//load/get file -> iteration threw file -> then print/draw every entity from file
		//XML

		/* not done yet/still working on Load/reading the file */

		string line;
		ifstream in("EntityFile.xml");

		if (xmlDoc->load(_T("EntityFile.xml")) != VARIANT_TRUE) {
			printf("Unable to load input.xml\n");
		}
		else {
			printf("XML was successfully loaded\n");

			while (getline(in, line))
			{
				std::string tmp; // strip whitespaces from the beginning
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == ' ' && tmp.size() == 0) {}
					else
					{
						tmp += line[i];
					}
				}

				//cout << "-->" << tmp << "<--" << endl;
				if (tmp == "<entities>")
				{
					//cout << "Found <Package>" << endl;
					//print/draw entities
					//create loop
				}



				/* - old vb van JSON file -
				std::ifstream loadEntityFile;  loadEntityFile.open("Save/EntityFileSave.JSON", std::ofstream::in);
				loadEntityFile >> entities;
				cout<<entities;
				// iterate via "iterator loop"
				System.out.println("\n==> Iterator Example...");
				Iterator<String> Iterator = List.iterator();
				while (cIterator.hasNext()) {System.out.println(Iterator.next());}
				for( Json::Value::const_iterator itr = root.begin() ; itr != root.end() ; itr++ ) {}
				*/
			}
		}