#include <map>
#include <iostream>
#include <string>
#include <sstream>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"


//PARTE1

//b)
class item
{
public:
	virtual void getInfo()
	{

	}

};

class arma : public item
{
public:
	std::string tipo;
	std::string alcance;



	void getInfo(int test)
	{
		std::cout << "IT WORKS!!";
	}
};

struct entidad {
	int vitalidad;
	entidad()
	{

	}
	entidad(int givVitalidad, int t)
	{
		std::cout << "IT vfygccfg!!";
	}
};

struct enemigo : entidad {

};



std::map < std::string, entidad> enemigos;

int main()
{
	item* testItem;
	arma test();
	testItem = &test;
	testItem->getInfo(2);

	return 0;
}

/*
int main() {

	//CREACIÓN DEL DOCUMENTO XML DES DEL FICHERO XML (PARA LEERLO)
	rapidxml::xml_document<> doc;
	std::ifstream file("../res/files/config.xml"); //"...xbciusabciousabc" LOCALIZACIÓN DEL ARCHIVO XML MIRAR PDF
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);


	//PASAMOS LOS DATOS DEL XML DEL DOC A LA ESTRUCTURA DE "B)"
	rapidxml::xml_node<> *pRoot = doc.first_node();

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemigo"); pNode; pNode = pNode->next_sibling()) //PARA RECORRER LOS ENEMIGOS (que son nodes)
	{
		for (rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) //PARA RECORRER LOS ATRIBUTOS (de enemigos en este caso nombre)
		{
			//el pAttr su value es una string que es el nombre y lo pondremos en la creación del enemigo en STL map (key)
		};
		for (rapidxml::xml_node<> *pNodeI = pRoot->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			//AQUI IRÁ LA CREACIÓN DEL ENEMIGO EN TIPO MAP PASANDOLE LOS VALORES DE LOS NODES DENTRO DE ENEMIGO
			//tambien en ARMAS tiene un map que hay que pasarle un map con el identificador (pAttr) y los values
			for (rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute(); pAttr; pAttr = pAttr->next_attribute())
			{
				//En este puntero hay que pasarle 2 atributos que son el value del map del arma
			}
		}
	}

}
*/