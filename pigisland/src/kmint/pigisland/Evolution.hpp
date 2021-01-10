#pragma once

#include "../../../include/kmint/pigisland/pig.hpp"
#include "../../../../libkmint/include/kmint/random.hpp"

#include <vector>
#include <map>

namespace kmint {
    namespace pigisland {


        class Evolution
        {
            struct pair
            {
                std::vector<uint16_t> key;
                int value;
            };

            using compare = std::function<bool(const pair&, const pair&)>;

        public:
            static Evolution& getInstance()
            {
                static Evolution    instance;
                return instance;
            }

            void addPig(const std::vector<uint16_t>& data, int fitness) {
                _oldGeneration[fitness].push_back(data);
            }

            std::vector<std::vector<uint16_t>> generateGeneration(size_t populationCount) {
                std::vector<std::vector<uint16_t>> newGeneration;
                newGeneration.reserve(populationCount);

                while (newGeneration.size() < populationCount)
                {
                    int parent1Index = generateIndex();
                    int parent2Index = generateIndex();

                    newGeneration.push_back(    giveBearth(_oldGeneration[parent1Index].at(random_int(0, _oldGeneration[parent1Index].size())),
                                                           _oldGeneration[parent2Index].at(random_int(0, _oldGeneration[parent2Index].size()))));
                    
                    int oldOne = generateIndex();
                    newGeneration.push_back(_oldGeneration[oldOne][random_int(0, _oldGeneration[oldOne].size())]);
                }       


                _oldGeneration.clear();

                return newGeneration;
            }

        private:
            Evolution() {}

            int generateIndex() {
                int r = random_int(0, 70);

                if (r < 10 && _oldGeneration.find(1) != _oldGeneration.end())
                {
                    return 1;
                }
                else if (r < 30 && _oldGeneration.find(2) != _oldGeneration.end()) {
                    return 2;
                }
                else if(_oldGeneration.find(4) != _oldGeneration.end()){
                    return 4;
                }

                auto& it = _oldGeneration.begin();
                return (*it).first;
            }

            void mutate(uint16_t& chromosome) const{
                if (random_int(0, 100) == 1) {
                    int i = random_int(0, 16);
                    chromosome |= (1 << i);
                }
            }

            std::vector<uint16_t> giveBearth(const std::vector<uint16_t>& parent1, const std::vector<uint16_t>& parent2) {
                std::vector<uint16_t> child;
                child.resize(parent1.size());

                for (size_t i = 0; i < parent1.size(); i++)
                {
                    bool parent1First = (random_int(1, 100) % 2);

                    child[i] = (parent1First) ? (parent1[i] & 0xFF00) + (parent2[i] & 0x00FF) : (parent2[i] & 0xFF00) + (parent1[i] & 0x00FF);
                    mutate(child[i]);
                }

                return child;
            }

        public:
            Evolution(Evolution const&) = delete;
            void operator=(Evolution const&) = delete;

        private:
            std::map<int, std::vector<std::vector<uint16_t>>> _oldGeneration;
        };


    }
}