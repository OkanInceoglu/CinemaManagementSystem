#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric>
class Movie {
private:
	std::string name;
	std::string director;
	int year;
	std::string genre;
	int time;
public:
	Movie();
	Movie(std::string n, std::string d, int y, std::string g, int t);
	void Input();
	void setMovie(std::string n, std::string d, int y, std::string g, int t);
	void setName(std::string n);
	void setDirector(std::string d);
	void setYear(int y);
	void setGenre(std::string g);
	void setTime(int y);
	std::string getName() const;
	std::string getDirector() const;
	int getYear() const;
	std::string getGenre() const;
	int getTime() const;
	bool operator<(Movie other) const;
	bool operator>(Movie other) const;
	friend std::ostream& operator<<(std::ostream& out, Movie m);
};

Movie::Movie() {
	name = "";
	director = "";
	year = 0;
	genre = "";
	time = 0;
}

Movie::Movie(std::string n, std::string d, int y, std::string g, int t) {
	name = n;
	director = d;
	year = y;
	genre = g;
	time = t;
}

void Movie::Input() {
	std::cout << "Enter Name:";
	std::getline(std::cin >> std::ws,name);
	
	std::cout << "Enter Director:";
	std::getline(std::cin >> std::ws, director);

	std::cout << "Year:";
	std::cin >> year;
	
	std::cout << "Genre:";
	std::getline(std::cin >> std::ws, genre);

	std::cout << "Time:";
	std::cin >> time;
}

void Movie::setMovie(std::string n, std::string d, int y, std::string g, int t) {
	name = n;
	director = d;
	year = y;
	genre = g;
	time = t;
}

void Movie::setName(std::string n) {
	name = n;
}

void Movie::setDirector(std::string d) {
	director = d;
}

void Movie::setYear(int y) {
	year = y;
}

void Movie::setGenre(std::string g) {
	genre = g;
}

void Movie::setTime(int t) {
	time = t;
}

std::string Movie::getName() const {
	return name;
}

std::string Movie::getDirector() const {
	return director;
}

int Movie::getYear()const {
	return year;
}

std::string Movie::getGenre()const {
	return genre;
}

int Movie::getTime()const {
	return time;
}

bool Movie::operator<(Movie other) const {
	if (year < other.getYear())return true;
	if (year == other.getYear()) {
		return name < other.getName();
	}
	return false;
}

bool Movie::operator>(Movie other) const {
	if (year > other.getYear())return true;
	if (year == other.getYear()) {
		return name > other.getName();
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, Movie m) {
	out << "Name:" << m.name << std::endl;
	out << "Director:" << m.director << std::endl;
	out << "Year:" << m.year << std::endl;
	out << "Genre:" << m.genre << std::endl;
	out << "Time:" << m.time << std::endl;
	return out;
}

class Cinema {
private:
	std::string name;
	int countfilms;
	std::map<Movie, int> movies;
public:
	Cinema();
	Cinema(std::string n, int cf,std::map<Movie,int> m);
	void input();
	void getCinema();
	friend std::ostream& operator<<(std::ostream& out, Cinema c);
	void addMovie();
	bool deleteMovie(Movie m);
	bool searchMovieFromName(Movie m);
	void searchMovieFromDirector(std::string d);
	int getSumBoughtofTicketsforFilm(std::string name) const;
	int getSumBoughtofTicketsAll() const;
	std::multimap<int, std::string> getMoviesSortedByTickets() const;
	void buyTickets(std::string m, int count);
};

Cinema::Cinema() {
	name = "";
	countfilms = 0;
	movies = {};
}

Cinema::Cinema(std::string n, int cf, std::map<Movie, int> m) {
	name = n;
	countfilms = cf;
	movies = m;
}

void Cinema::input() {
	std::cout << "Enter name:";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter count of films:";
	std::cin >> countfilms;

	std::cout << "Enter Films:";
	for (int i = 0;i < countfilms;i++) {
		Movie m;
		std::cout << i + 1 << ".Film:";
		m.Input();
		movies.insert({ m,0 });
	}
}

void Cinema::getCinema() {
	std::cout << "Name:" << name << std::endl;
	std::cout << "Count of films:" << countfilms << std::endl;
	std::cout << "Films:";
	for (auto i : movies) {
		std::cout << "Name:";
		std::cout<<i.first.getName();
		std::cout << "Count of views:";
		std::cout<<i.second;
		std::cout << "--------------------------" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, Cinema c) {
	out << "Name:" << c.name << std::endl;
	out << "Count of films:" << c.countfilms << std::endl;
	out << "Films:";
	for (auto i : c.movies) {
		out << "Name:";
		out << i.first.getName();
		out << "Count of views:";
		out << i.second;
		out << "--------------------------" << std::endl;
	}
	return out;
}

void Cinema::addMovie() {
	Movie m;
	m.Input();
	movies.insert({ m,0 });
	countfilms++;
}

bool Cinema::deleteMovie(Movie m) {
	if (movies.erase(m) == 0)return false;
	countfilms--;
	return true;
}

bool Cinema::searchMovieFromName(Movie m) {
	for (auto i : movies) {
		if (i.first.getName() == m.getName())return true;
	}
	return false;
}

void Cinema::searchMovieFromDirector(std::string d) {
	std::vector<Movie> m;
	for (auto i : movies) {
		if (i.first.getDirector() == d) {
			m.push_back(i.first);
		}
	}
	if (m.empty()) {
		std::cout << "Not found a movie with this Director!!!\n";
	}
	else {
		for (auto a : m) {
			std::cout << "Director:";
			std::cout << a.getDirector();
			std::cout << "Movie";
			std::cout << a.getName();
			std::cout << "----------------------";
		}
	}
}

int Cinema::getSumBoughtofTicketsforFilm(std::string name) const{
	for (const auto& i : movies) {
		if (i.first.getName() == name) {
			return i.second;
		}
	}
	return 0;
}

int Cinema::getSumBoughtofTicketsAll() const {
	int sum = 0;
	for (const auto& i : movies) {
		sum += i.second;
	}
	return sum;
}


std::multimap<int, std::string> Cinema::getMoviesSortedByTickets() const {
	std::multimap<int, std::string> result;
	for (auto i : movies) {
		result.insert({ i.second, i.first.getName() });
	}
	return result;
}

void Cinema::buyTickets(std::string m, int count) {
	for (auto& i : movies) {
		if (i.first.getName() == m) {
			i.second += count;
			break;
		}
	}
}


int main() {
	std::map<Movie, int> films;

	Movie m1("Inception", "Christopher Nolan", 2010, "Sci-Fi", 148);
	Movie m2("Interstellar", "Christopher Nolan", 2014, "Sci-Fi", 169);
	Movie m3("The Godfather", "Francis Ford Coppola", 1972, "Crime", 175);
	Movie m4("The Dark Knight", "Christopher Nolan", 2008, "Action", 152);

	films.insert({ m1, 0 });
	films.insert({ m2, 0 });
	films.insert({ m3, 0 });
	films.insert({ m4, 0 });

	Cinema cinema("Cinema City", 4, films);

	std::cout << "\n===== 1. CINEMA INFORMATION =====\n";
	cinema.getCinema();

	std::cout << "\n===== 2. MOVIE INFORMATION =====\n";
	std::cout << m1;

	std::cout << "\n===== 3. COMPARISON =====\n";

	if (m1 < m2) {
		std::cout << "Inception comes before Interstellar.\n";
	}

	if (m2 > m1) {
		std::cout << "Interstellar comes after Inception.\n";
	}

	std::cout << "\n===== 4. SEARCH BY NAME =====\n";

	Movie searchMovie("Inception", "", 0, "", 0);

	if (cinema.searchMovieFromName(searchMovie)) {
		std::cout << "Movie found: " << searchMovie.getName() << "\n";
	}
	else {
		std::cout << "Movie not found.\n";
	}

	std::cout << "\n===== 5. SEARCH BY DIRECTOR =====\n";
	cinema.searchMovieFromDirector("Christopher Nolan");

	std::cout << "\n===== 6. BUY TICKETS =====\n";

	cinema.buyTickets("Inception", 10);
	cinema.buyTickets("Interstellar", 15);
	cinema.buyTickets("The Godfather", 7);
	cinema.buyTickets("The Dark Knight", 20);

	cinema.getCinema();

	std::cout << "\n===== 7. TICKETS FOR ONE MOVIE =====\n";

	std::cout << "Inception tickets: "
		<< cinema.getSumBoughtofTicketsforFilm("Inception")
		<< "\n";

	std::cout << "Unknown movie tickets: "
		<< cinema.getSumBoughtofTicketsforFilm("Avatar")
		<< "\n";

	std::cout << "\n===== 8. TOTAL TICKETS =====\n";

	std::cout << "Total tickets sold: "
		<< cinema.getSumBoughtofTicketsAll()
		<< "\n";

	std::cout << "\n===== 9. SORT BY TICKETS =====\n";

	std::multimap<int, std::string> sortedMovies =
		cinema.getMoviesSortedByTickets();

	for (const auto& i : sortedMovies) {
		std::cout << "Tickets: " << i.first
			<< " | Movie: " << i.second << "\n";
	}

	std::cout << "\n===== 10. DELETE MOVIE =====\n";

	Movie movieToDelete("The Godfather", "", 1972, "", 0);

	if (cinema.deleteMovie(movieToDelete)) {
		std::cout << "Movie deleted successfully.\n";
	}
	else {
		std::cout << "Movie could not be deleted.\n";
	}

	cinema.getCinema();

	std::cout << "\n===== 11. DELETE UNKNOWN MOVIE =====\n";

	Movie unknownMovie("Avatar", "", 2009, "Sci-Fi", 162);

	if (cinema.deleteMovie(unknownMovie)) {
		std::cout << "Movie deleted successfully.\n";
	}
	else {
		std::cout << "Movie not found.\n";
	}

	std::cout << "\n===== 12. FINAL TOTAL =====\n";

	std::cout << "Total tickets sold: "
		<< cinema.getSumBoughtofTicketsAll()
		<< "\n";

	return 0;
}
