#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "network.h"
#include "person.h"
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

class RecommendationEngine {
public:
    RecommendationEngine(const Network& network);
    vector<std::pair<Person*, double>> recommendFriends(const Person* person, int numRecommendations);

private:
    const Network& network;

    bool isAlreadyFriend(const Person* person1, const Person* person2);
    double calculateSimilarity(const Person* person1, const Person* person2);
    double calculateAgeDifference(const Person* person1, const Person* person2);
    double calculateAreaCodeDifference(const Person* person1, const Person* person2);
    double calculateEmailServiceSimilarity(const Person* person1, const Person* person2);
};

#endif // RECOMMENDATION_ENGINE_H