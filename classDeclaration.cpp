#include <memory>
#include <cmath>
#include <iostream>

//Rough outline of the classes

class paramters_cb {
    public:
    int size;
    int characterNum;
}

class guess_cb {
    public:
    paramters_cb parameters;
    int guess [parameters.size];
};


class problem_cb {

    public:
    paramters_cb parameters;
    guess_cb guess;
    int solution [parameters.size];

    response_cb response;

    //for(int i=0;i<parameters.size;i++)
    //{
    //if(solution[i]==guess_cb.guess[i])
    //bull++;
    //
    //
    //
    //}

    return response;
};

class response_cb {

    public:
    int bull;
    int cow;
    int count;
};

class solution_cb {

    public:
    virtual int goal() const = 0;

};

class tsp_solution_cb : public solution_cb {
    public:
    std::shared_ptr<problem_cb> problem;
    response_cb response; 
    double goal() const {
       // if (response.bull == parameters.size)
       // = success
    }

}