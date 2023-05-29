#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>


std::vector<std::string> Read_from_file_to_vector(std::string filename){
    std::ifstream ifstream_for_use(filename);
    std::stringstream buffer;
    buffer << ifstream_for_use.rdbuf();
    std::string bigtext = buffer.str();
    ifstream_for_use.close();

    std::vector<std::string> trigramm_vector;
    std::string tmpstring;
    size_t size = bigtext.length();

    for (size_t i=0; i<size-2; i++){
        std::string trigramochka = bigtext.substr(i, 3);
        for (int j=0; j<3; j++){
            if (trigramochka[j] == ' '){
                trigramochka[j] = '_';
            }
        }
        trigramm_vector.push_back(trigramochka);
    }
    return trigramm_vector;
}

std::vector<std::pair<std::string, int>> Sort_trigrams(std::vector<std::string> trigramm_vector){
    std::map<std::string, int> karta;
    for (auto element : trigramm_vector){
        karta[element] ++;
    }

    std::vector<std::pair<std::string, int>> pair_vector;
    for (auto element : karta){
        pair_vector.push_back(std::make_pair(element.first, element.second));
    }

    std::sort(pair_vector.begin(), pair_vector.end(), [](const auto& p1, const auto& p2){return p1.second > p2.second;});

    return pair_vector;
}



int main(int argc, char *argv[]) {
    auto pair_vector = Sort_trigrams(Read_from_file_to_vector(argv[1]));
    if (pair_vector.size() < 10){
        for (int i=0; i < pair_vector.size(); i++){
            std::cout << (i+1) << ") " << pair_vector[i].first << std::endl;
        }
    } else {
        for (int i=0; i<10; i++){
            std::cout << (i+1) << ") " << pair_vector[i].first << std::endl;
        }
    }
}