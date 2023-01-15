//данные о фильмах должны быть записаны по шаблону

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

class Film
{

public:

	std::string name;
	std::string genre;
	std::string rate;
	std::string year;
	std::string price;

	Film(std::string _name, std::string _genre, std::string _rate, std::string _year, std::string _price)
		: name{ _name }, genre{ _genre }, rate{ _rate }, year{ _year }, price{_price} {}
	Film() :Film(" ", " ", " ", " ", " ") {}

	friend std::ostream& operator<<(std::ostream& out, Film obj)
	{
		out << "name: " << obj.name << ", genre: " << obj.genre << ", rate: " << obj.rate << ", year: " << obj.year << ", price: " << obj.price << std::endl;
		return out;
	}
	

};

//ввод данных в файл
void file_in(std::ofstream& movies, std::string _template, Film& film)
{

	std::regex name("<name>");
	_template = regex_replace(_template.c_str(), name, film.name);
	std::regex genre("<genre>");
	_template = regex_replace(_template.c_str(), genre, film.genre);
	std::regex rate("<rate>");
	_template = regex_replace(_template.c_str(), rate, film.rate);
	std::regex year("<year>");
	_template = regex_replace(_template.c_str(), year, film.year);
	std::regex price("<price>");
	_template = regex_replace(_template.c_str(), price, film.price);

	movies << _template;

}

//заполнение массива
void fill(Film array[], std::string text)
{
	int last_c =0;
	for (int i = 0; i < 5; i++)
	{
		last_c = (int)text.find(":", last_c) + 2;
		while (text[last_c] != ',')
		{
			array[i].name.append(1, text[last_c]);
			last_c++;
		}
		last_c = (int)text.find(":", last_c) + 2;
		while (text[last_c] != ',')
		{
			array[i].genre.append(1, text[last_c]);
			last_c++;
		}
		last_c = (int)text.find(":", last_c) + 2;
		while (text[last_c] != ',')
		{
			array[i].rate.append(1, text[last_c]);
			last_c++;
		}
		last_c = (int)text.find(":", last_c) + 2;
		while (text[last_c] != ',')
		{
			array[i].year.append(1, text[last_c]);
			last_c++;
		}
		last_c = (int)text.find(":", last_c);
		if (i != 5)
			last_c += 2;
		while (text[last_c] != '\n')
		{
			array[i].price.append(1, text[last_c]);
			last_c++;
		}
	}
}

int main()
{
	std::ofstream write_movies("movies.txt");

	//шаблон для записи
	std::string _template = "name: <name>, genre: <genre>, rate: <rate>, year: <year>, price: <price>\n";

	Film film1("The Green Mile", "Drama", "5", "1999", "800");
	Film film2("The Green Mile", "Drama", "5", "1999", "800");
	Film film3("The Green Mile", "Drama", "5", "1999", "800");
	Film film4("The Green Mile", "Drama", "5", "1999", "800");
	Film film5("The Green Mile", "Drama", "5", "1999", "800");

	file_in(write_movies, _template, film1);
	file_in(write_movies, _template, film2);
	file_in(write_movies, _template, film3);
	file_in(write_movies, _template, film4);
	file_in(write_movies, _template, film5);

	write_movies.close();

	std::ifstream read_movies;
	read_movies.open("movies.txt");

	std::string file_text;
	getline(read_movies, file_text, '\0');

	Film* array = new Film[5];

	fill(array, file_text);
	for (int i = 0; i < 5; i++)
		std::cout << array[i] << std::endl;
	return 0;
}