//
// Created by mark  gurin on 08/06/2018.
//

#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include <iostream>



class TestCase {
    std::string Line;
    std::ostream &output;
    int total_tests;
    int fail;
    int success;
    std::string getFailHeader(int val)const {return ": Failure in test #"+ std::to_string(val)+ ": ";}
    std::string getLine() const {return Line;}
    std::string getAnsNEQUAL()const {return " are should Equal "; }
    std::string getAnsAREEQUAL()const {return " are should not Equal "; }
    std::string FuncShould()const {return ": Function should return "; }
    std::string FuncResult()const {return " but returned  "; }
    int getFail()const{return fail;}
    int getSuccess()const{return success;}
    int getTotal()const{return total_tests;}

public:

    TestCase();
    TestCase(const std::string& line, std::ostream& stream ):
            Line(line),
            output(stream),
            fail(0),
            success(0),
            total_tests(0){}



    template <typename T1>
        TestCase& check_equal(T1 val1, T1 val2){
        ++total_tests;
        if(val1 == val2){
            ++success;
        }
        else{
            ++fail;
            std::ostringstream ss1;
            std::ostringstream ss2;
            ss1 << val1;
            ss2 << val2;
            std::string ans = getLine() + getFailHeader(total_tests)+ ss1.str() + getAnsNEQUAL() + ss2.str() ;
            output << ans << std::endl;

        }
        return *this;
    };

    template <typename T1>
    TestCase& check_different(T1 val1 , T1 val2){
        ++total_tests;
        if(val1 != val2){
            ++success;
            return *this;
        }
        else{
            ++fail;
            std::ostringstream ss1;
            std::ostringstream ss2;
            ss1 << val1;
            ss2 << val2;
            std::string ans = getLine() + getFailHeader(total_tests)  + ss1.str() + getAnsAREEQUAL() + ss2.str() ;
            output << ans << std::endl;
        }
    };



    template < typename T1 = int(*)(int), typename T2, typename T3>
    TestCase& check_function(T1 func, T2 val2, T3 val3){
        ++total_tests;
        int res = func(val2);
        if(res == val3){
            ++success;
            return *this;
        }
        else{

            ++fail;
            std::ostringstream ss2;
            std::ostringstream ss3;
            ss2 << val2;
            ss3 << val3;
            std::string ans = getLine() +
                              getFailHeader(total_tests) +
                              FuncShould() +ss3.str() +
                              FuncResult() + std::to_string(res);
            output << ans << '\n';
        }
        return *this;

    };

    template<typename T1>
    TestCase& check_output(T1 t, std::string s){
        ++total_tests;
        std::ostringstream ss ;
        ss << t;
        std::string t_str =  ss.str();
        if (s.compare(t_str) == 0 ) {
            ++success;
        }
        else{
            ++fail;
            std::string ans = getLine()+
                              getFailHeader(total_tests)+
                              FuncShould() + s
                              + FuncResult() + t_str;
            output << ans << '\n';
        }
            return *this;
    }

    void print(){ //	Test MyStruct operators: 4 failed, 1 passed, 5 total.

        std::string ans = getLine() + ": "+
                          std::to_string(getFail()) + " failed, "
                          + std::to_string(getSuccess()) + " passed, "
                          + std::to_string(getTotal()) + " total.";
        output << ans << '\n';


    }



};


