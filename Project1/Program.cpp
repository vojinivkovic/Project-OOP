#include "Exceptions.h"
#include "FindPathStrategy.h"
#include "PrintStrategyBusLine.h"
#include "PrintStrategyStation.h"
#include "PublicTransportNetwork.h"
#include "Simulator.h"
#include "StatisticsStrategyBusLine.h"
#include <iostream>
#include <string>

using namespace std;



int get_minutes_from_time(const string& time) 
{
	int index_of_dots;
	int hours = 0, minutes = 0;
	int i;
	for (i = 0; i < time.length(); i++) {
		if (time[i] == ':') {
			index_of_dots = i;
			break;
		}
	}
	for (i = 0; i < index_of_dots; i++) {
		hours = 10 * hours + time[i] - '0';
	}
	for (i = index_of_dots + 1; i < time.length(); i++) {
		minutes = minutes * 10 + time[i] - '0';

	}
	return (hours * 60 + minutes);
}


int string_to_integer(const string& line) {
	int number = 0;
	for (int i = 0; i < line.size(); i++) {
		number = 10 * number + line[i] - '0';
	}
	return number;
}


int main() {

	int start_of_program;
	int option;
	int simulator_strategy;
	string id_of_station;
	string id_of_first_station;
	string id_of_last_station;
	string arrival_at_station;
	string name_of_line;
	string file_with_set_of_stations, file_with_set_of_bus_lines;

	PublicTransportNetwork* network = nullptr;

	cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju: " << endl;
	cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
	cout << "0. Kraj rada" << endl;
	
	cin >> start_of_program;
	getchar();

	if (start_of_program) {

		cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
		getline(cin, file_with_set_of_stations);


		cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza" << endl;
		getline(cin, file_with_set_of_bus_lines);


		network = new PublicTransportNetwork(file_with_set_of_stations, file_with_set_of_bus_lines);

		while (true) {
			cout << endl;
			cout << "Mreza gradskog prevoza je uspesno ucitana. Molimo Vas, odaberite opciju: " << endl;
			cout << "1. Prikaz informacija o stajalistu" << endl;
			cout << "2. Prikaz osnovnih infomacija o liniji gradskog prevoza" << endl;
			cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
			cout << "4. Pronalaz putanje izmedju dva stajalista" << endl;
			cout << "0. Kraj rada" << endl;

			cin >> option;
			getchar();

			switch (option) {
			case 1:
			{
				while (true) {
					try {
						cout << endl;
						cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
						getline(cin, id_of_station);
						network->find_error_station(id_of_station);
						break;
					}
					catch (Exceptions& e) {
						cout << e.what() << endl;
					}
				}

				ofstream output("stajaliste_" + id_of_station + ".txt");
				PrintStrategyStation1 strategy{ output, network->get_set_of_bus_lines() };
				network->information_about_station(string_to_integer(id_of_station), strategy);
				cout << "Generisan je fajl stajaliste_" + id_of_station + ".txt sa osnovnim informacijama o stajalistu " + id_of_station + "." << endl;
				break;
			}

			case 2:
			{
				while (true) {
					try {
						cout << endl;
						cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
						getline(cin, name_of_line);
						network->find_error_bus_line(name_of_line);
						break;
					}
					catch (Exceptions& e) {
						cout << e.what() << endl;
					}
				}

				ofstream output("linija_" + name_of_line + ".txt");
				PrintStrategyBusLine1 strategy{ output, network->get_set_of_stations() };
				network->information_about_bus_line(name_of_line, strategy);
				cout << "Generisan je fajl linija_" + name_of_line + ".txt sa osnovnim informacijama o liniji "
					+ name_of_line + "." << endl;
				break;
			}

			case 3:
			{
				while (true) {
					try {
						cout << endl;
						cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
						getline(cin, name_of_line);
						network->find_error_bus_line(name_of_line);
						break;
					}
					catch (Exceptions& e) {
						cout << e.what() << endl;
					}
				}

				ofstream output("statistika_" + name_of_line + ".txt");
				StatisticsStrategyBusLine1 strategy{ output, network->get_set_of_bus_lines() };
				network->statistics_about_bus_line(name_of_line, strategy);
				cout << "Generisan je fajl statistika_" + name_of_line + ".txt sa statistickim informacijama o liniji "
					+ name_of_line + "." << endl;
				break;
			}

			case 4:
			{

				while (true) {
					try {
						cout << endl;
						cout << "Molimo Vas, unesite sifru pocetnog stajalista. " << endl;
						getline(cin, id_of_first_station);
						network->find_error_station(id_of_first_station);
						break;
					}
					catch (Exceptions& e) {
						cout << e.what() << endl;
					}
				}

				while (true) {
					try {
						cout << endl;
						cout << "Molimo Vas, unesite sifru krajnjeg stajalista. " << endl;
						getline(cin, id_of_last_station);
						network->find_error_station(id_of_last_station);
						break;
					}
					catch (Exceptions& e) {
						cout << e.what() << endl;
					}
				}

				cout << "Molimo Vas, unesite vreme dolaska na pocetno stajaliste. Vreme zadati u formatu hh:mm" << endl;
				cin.ignore();
				getline(cin, arrival_at_station);
				ofstream output("putanja_" + id_of_first_station + "_" + id_of_last_station + ".txt");
				network->activation_of_simulator(get_minutes_from_time(arrival_at_station),
					string_to_integer(id_of_first_station), string_to_integer(id_of_last_station));
				cout << "Molimo Vas, izaberite jednu od opcija: " << endl;
				cout << "1. Bilo koja putanja" << endl;
				cout << "2. Najbrza putanja" << endl;
				cout << "3. Putanja sa najmanjim brojem presedanja" << endl;
				cin >> simulator_strategy;
				switch (simulator_strategy) {
				case 1: 
				{
					AnyPathStrategy strategy{ output };
					network->find_path(strategy);
					break;
				}
				case 2: 
				{
					ShortestPathStrategy strategy{ output };
					network->find_path(strategy);
					break;
				}
				case 3:
				{
					MinimumBusChangeStrategy strategy{ output };
					network->find_path(strategy);
					break;
				}
				}
				cout << "Generisan je fajl putanja_" + id_of_first_station + "_" + id_of_last_station + ".txt koji sadrzi putanju izmedju pocetnog i krajnjeg stajalista." << endl;
				break;
			}
			case 0:
				cout << "Program se zavrsava.";
				delete network;
				exit(0);
			}
		}
	}

	
	return 0;
}