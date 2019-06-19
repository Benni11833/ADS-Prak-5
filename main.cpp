#include "Graph.h"
#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

void print_menu() {
	std::cout << "Graph-Menue" << std::endl
		<< "1) Graph einlesen" << std::endl
		<< "2) Tiefensuche" << std::endl
		<< "3) Breitensuche" << std::endl
		<< "4) Prim" << std::endl
		<< "5) Kruskal" << std::endl
		<< "6) Print Graph" << std::endl
		<< "?> ";
}

int main() {

	//UnitTests:
	Catch::Session().run();
	system("pause");
	return 0;

	Graph g1;
	/*g1.init("graph1.txt");
	g1.printAll();
	int tmp1, tmp2;
	std::cout << "tmp1: ";	std::cin >> tmp1;
	std::cout << "tmp2: ";	std::cin >> tmp2;
	if (g1.check_if_connected(tmp1, tmp2))
		std::cout << "Zyklus zwischen " << tmp1 << " - " << tmp2 << " existiert.\n";
	else
		std::cout << "Kein Zyklus zwischen " << tmp1 << " - " << tmp2 << " existiert.\n";
	
	system("Pause");
	return 0;*/


	char choice = '\0';
	std::string file;
	bool flag = true;
	int tmp;
	while (flag) {
		print_menu();
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (choice - '0') {
		case 1:
			std::cout << "Datei: ";
			std::getline(std::cin, file);
			if (g1.init(file))
				std::cout << "Datei " << file << " wurde erfolgreich eingelesen.\n";
			break;
		case 2:
			//TODO
			std::cout << "StartKnoten: ";
			std::cin >> tmp;
			if (g1.getAnzKnoten() != 0) {
				if (g1.depthSearchRek(tmp))
					std::cout << "Alle Knoten wurden besucht" << std::endl;
				else
					std::cout << "Nicht alle Knoten wurden besucht" << std::endl;
			}else{
				std::cout << "Graph hat keine Knoten, vorher initialisieren" << std::endl;
			}
			break;
		case 3:
			//TODO
			if (g1.getAnzKnoten() != 0) {
				if (g1.breadthSearchiter(0))
					std::cout << "Alle Knoten wurden besucht" << std::endl;
				else
					std::cout << "Nicht alle Knoten wurden besucht" << std::endl;
			}else {
				std::cout << "Graph hat keine Knoten, vorher initialisieren" << std::endl;
			}
			break;
		case 4:
			//TODO
			std::cout << "Gewicht von MST mit Prim: " << g1.prim(0)
				<< std::endl;
			break;
		case 5:
			//TODO
			std::cout << "Gewicht von MST mit Kruskal: " << g1.kruskal()
				<< std::endl;
			break;
		case 6:
			g1.printAll();
			break;
		default:
			flag = false;
		}
	}

	system("pause");
	return 0;
}