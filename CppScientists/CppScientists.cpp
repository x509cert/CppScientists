#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <iterator>

using namespace std::chrono;

enum class Gender {
    Male,
    Female
};

class Scientist {
public:
    Scientist(const std::string_view& ln,
        const std::string_view& fn,
        const Gender gender,
        const year_month_day dob,
        const year_month_day dod,
        const std::string_view& country,
        const std::string_view& town,
        const std::string_view& knownFor)
        : lastName(ln), firstName(fn),
        gender(gender),
        dob(dob), dod(dod),
        countryOfBirth(country), townOfBirth(town),
        knownFor(knownFor) {}

    std::string getGender() const {
        return gender == Gender::Female ? "Female" : "Male";
    }

    std::string lastName;
    std::string firstName;
    Gender gender;
    year_month_day dob; 
    year_month_day dod; 
    std::string countryOfBirth;
    std::string townOfBirth;
    std::string knownFor;
};

void Dump(const std::string qry,
          const std::vector<Scientist> v) {

    std::cout << "\n" << qry << "\n";
    for (const auto& s : v) {
        std::cout << s.lastName << ", "
            << s.firstName << " ("
            << s.dob.year() << " - "
            << s.dod.year() << ") "
            << s.getGender() << "\n";
    }
}

int main() {
    std::vector<Scientist> scientists = {
        Scientist({"Curie"}, {"Marie"}, Gender::Female, {1867y / November / 7}, {1934y / July/ 4}, {"Poland"},{"Warsaw"}, {"Radioactivity"}),
        Scientist("Einstein", "Albert", Gender::Male, {1879y / March / 14}, {1955y / April / 18}, "Germany", "Ulm", "Theory of Relativity"),
        Scientist("Lovelace", "Ada", Gender::Female, {1815y / December / 10}, {1852y / November / 27}, "United Kingdom", "London", "Computing"),
        Scientist("Newton", "Isaac", Gender::Male, {1643y / January / 4}, {1727y / March / 31}, "United Kingdom", "Lincolnshire", "Classical Mechanics"),
        Scientist("Meitner", "Lise", Gender::Female, {1878y / November / 7}, {1968y / October / 27}, "Austria", "Vienna", "Nuclear Physics"),
        Scientist("Darwin", "Charles", Gender::Male, {1809y / February / 12}, {1882y / April / 19}, "United Kingdom", "Shrewsbury", "Evolution"),
        Scientist("Franklin", "Rosalind", Gender::Female, {1920y / July / 25}, {1958y / April / 16}, "United Kingdom", "London", "DNA Structure"),
        Scientist("Tesla", "Nikola", Gender::Male, {1856y / July / 10}, {1943y / January / 7}, "Austrian Empire", "Smiljan", "Electromagnetism"),
        Scientist("Hodgkin", "Dorothy", Gender::Female, {1910y / May / 12}, {1994y / July / 29}, "Egypt", "Cairo", "X-ray Crystallography"),
        Scientist("Planck", "Max", Gender::Male, {1858y / April / 23}, {1947y / October / 4}, "Germany", "Kiel", "Quantum Theory"),
        Scientist("Noether", "Emmy", Gender::Female, {1882y / March / 23}, {1935y / April / 14}, "Germany", "Erlangen", "Abstract Algebra"),
        Scientist("Pasteur", "Louis", Gender::Male, {1822y / December / 27}, {1895y / September / 28}, "France", "Dole", "Microbiology"),
        Scientist("Leavitt", "Henrietta", Gender::Female, {1868y / July / 4}, {1921y / December / 12}, "United States", "Lancaster", "Astronomy"),
        Scientist("Galilei", "Galileo", Gender::Male, {1564y / February / 15}, {1642y / January / 8}, "Italy", "Pisa", "Astronomy"),
        Scientist("Mendel", "Gregor", Gender::Male, {1822y / July / 20}, {1884y / January / 6}, "Austrian Empire", "Heinzendorf", "Genetics"),
        Scientist("Cori", "Gerty", Gender::Female, {1896y / August / 15}, {1957y / October / 26}, "Austrian Empire", "Prague", "Biochemistry"),
        Scientist("Faraday", "Michael", Gender::Male, {1791y / September / 22}, {1867y / August / 25}, "United Kingdom", "London", "Electromagnetism"),
        Scientist("McClintock", "Barbara", Gender::Female, {1902y / June / 16}, {1992y / September / 2}, "United States", "Hartford", "Cytogenetics"),
        Scientist("Maxwell", "James Clerk", Gender::Male, {1831y / June / 13}, {1879y / November / 5}, "United Kingdom", "Edinburgh", "Electromagnetism"),
        Scientist("Lavoisier", "Antoine", Gender::Male, {1743y / August / 26}, {1794y / May / 8}, "France", "Paris", "Chemistry"),
        Scientist("Mayer", "Maria Goeppert", Gender::Female, {1906y / June / 28}, {1972y / February / 20}, "Germany", "Kattowitz", "Nuclear Physics"),
        Scientist("Kepler", "Johannes", Gender::Male, {1571y / December / 27}, {1630y / November / 15}, "Holy Roman Empire", "Weil der Stadt", "Astronomy"),
        Scientist("Wu", "Chien-Shiung", Gender::Female, {1912y / May / 31}, {1997y / February / 16}, "China", "Liuhe", "Nuclear Physics"),
        Scientist("Da Vinci", "Leonardo", Gender::Male, {1452y / April / 15}, {1519y / May / 2}, "Italy", "Vinci", "Renaissance Polymath"),
        Scientist("Ball", "Alice", Gender::Female, {1892y / July / 24}, {1916y / December / 31}, "United States", "Seattle", "Chemistry")
    };

    // find scientists born in the 19th century
    std::vector<Scientist> result{};
    std::copy_if(scientists.begin(), scientists.end(), std::back_inserter(result),
        [](const Scientist& s) {
            return s.dob.year() >= 1800y && s.dob.year() < 1900y;
        });
    Dump("Born in the 19th century", result);

    // find female scientists
    result.clear();
    std::copy_if(scientists.begin(), scientists.end(), std::back_inserter(result),
        [](const Scientist& s) {
            return s.gender == Gender::Female;
        });
    Dump("Female scientists", result);

    // count female scientists born in the 19th century
    auto count = std::ranges::count_if(scientists, 
        [](const Scientist& s) {
            return (s.gender == Gender::Female 
                    && s.dob.year() >= 1800y 
                    && s.dob.year() < 1900y);
            });
    std::cout << "\nNumber of female 19th century scientists: " << count << "\n";

    return 0;
}
