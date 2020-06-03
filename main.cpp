#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <utility>
#include <exception>
//Creates grading criteria
std::vector<std::pair<std::string,double>> Choice_1= {{"A",4.0},{"B",3.5},
{"B-",3.0},{"C",2.5},{"C-",2.0},{"D",1.5},{"D-",1.0},{"E",0.5},{"F",0}};
std::vector<std::pair<std::string,double>> Choice_2= {{"A",4.0},{"A-",3.7},{"B+",3.3},
{"B",3.0},{"B-",2.7},{"C+",2.3},{"C",2.0},{"C-",1.7},{"D+",1.3},{"D",1.0},{"F",0.0}};
std::vector<std::pair<std::string,double>> Custom;
//creates variables used to store grade data
int num_of_classes, custom_class_amount, credits;
double grade_value, gpa_sum, credits_sum;
std::string letter_grade, line,choice,answer;
//Function that continues to take in input (the number of classes taken)
//until user gives valid input
int enter_num_of(){
    std::cin>>num_of_classes;
    std::cout<<std::endl;
    if(std::cin.fail()||num_of_classes<=0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
        std::cout<<"    Error with input, please try again."<<std::endl<<"    ";
        enter_num_of();
    }
    return num_of_classes;
}
//Prints out grade criteria in a formatted fashion
void print_out(std::vector<std::pair<std::string,double>> choice){
    for(auto [i,j]:choice){
        std::cout<<"           "<<i<<" = "<<j<<std::endl;
    }
}
//takes part in printing out the choice of grading criteria the user makes
void choice_print_out(){
    std::cout<<"    "<<std::string(70,'*')<<std::endl;
    std::cout<<"    You have chosen this GPA criteria:"<<std::string(2,'\n');
    std::cout<<"            CHOICE"<<std::endl<<"           ========"<<std::endl;
}
//Handles invalid input from user and reduces count by one
//the i is an iterator in a loop.
void error_output(int &i){
    i-=1;
    std::cout<<"    Error with input, please try again."<<std::endl;
}
//Strings used when printing out the criteria choice the user makes
std::string custom_print=std::string(50, '\n')+R"(
       _____ _    _  _____ _______ ____  __  __
      / ____| |  | |/ ____|__   __/ __ \|  \/  |
     | |    | |  | | (___    | | | |  | | \  / |
     | |    | |  | |\___ \   | | | |  | | |\/| |
     | |____| |__| |____) |  | | | |__| | |  | |
      \_____|\____/|_____/   |_|  \____/|_|  |_|
     *******************************************
     You have chose the custom option!)"+std::string(20, '\n');
std::string choice_one_print=std::string(50, '\n')+R"(
       _____ _    _  ____ _____ _____ ______    ____  _   _ ______
      / ____| |  | |/ __ \_   _/ ____|  ____|  / __ \| \ | |  ____|
     | |    | |__| | |  | || || |    | |__    | |  | |  \| | |__
     | |    |  __  | |  | || || |    |  __|   | |  | | . ` |  __|
     | |____| |  | | |__| || || |____| |____  | |__| | |\  | |____
      \_____|_|  |_|\____/_____\_____|______|  \____/|_| \_|______|)";
std::string choice_two_print=std::string(50, '\n')+R"(
       _____ _    _  ____ _____ _____ ______   _________          ______
      / ____| |  | |/ __ \_   _/ ____|  ____| |__   __\ \        / / __ \
     | |    | |__| | |  | || || |    | |__       | |   \ \  /\  / / |  | |
     | |    |  __  | |  | || || |    |  __|      | |    \ \/  \/ /| |  | |
     | |____| |  | | |__| || || |____| |____     | |     \  /\  / | |__| |
      \_____|_|  |_|\____/_____\_____|______|    |_|      \/  \/   \____/)";
//Goes through grading criteria, looks if inputted letter is in that grading criteria
//and returns its grade value (4.0,3.5,3.0,...). returns -1 if letter is not in grade criteria
double find_grade_value(std::string letter,std::vector<std::pair<std::string,double>> Choice){
    for(auto [i,j]:Choice){
        if(letter==i){
            return j;
        }
    }
    return -1;
}
//Function that creates a custom criteria with the users input.
void build_custom_criteria(){
    Custom.clear();
    std::cout<<"    How many possible letter grades do you want there to be?:";
    custom_class_amount=enter_num_of();
    std::cout<<"    please enter each individual grade in the format LETTER,GRADE"<<std::endl;
    std::cout<<"    (Do not use parenthesis)"<<std::endl;
    for(int i=1;i<=custom_class_amount;i++){
        try{
            std::cout<<"    Please enter grade #"<<i<<std::endl<<"    ";
            std::cin>>line;
            letter_grade=line.substr(0,line.find(","));
            grade_value=std::stod(line.substr(line.find(",")+1,3));
            if(find_grade_value(letter_grade,Custom)==-1&&grade_value>=0){
                Custom.push_back(std::make_pair(letter_grade,grade_value));
            }else{
                error_output(i);
                std::cout<<"    Please make sure that input is not only valid,"<<std::endl;
                std::cout<<"    but also that you are not trying to define a"<<std::endl;
                std::cout<<"    letter grade that you have already defined."<<std::endl;
            }
        }catch(...){
            error_output(i);
        }
    }
    std::cout<<"            CUSTOM"<<std::endl<<"           ========"<<std::endl;
    print_out(Custom);
}
//uses a grading criteria and gets users input in order to calculate the users GPA
void calculate_gpa(std::vector<std::pair<std::string,double>> Choice){
    gpa_sum=0;
    credits_sum=0;
    std::cout<<"    How many classes have you taken:"<<std::endl<<"    ";
    enter_num_of();
    std::cout<<"    please enter your classes in the format LETTER GRADE,CREDITS"<<std::endl;
    std::cout<<"    (Do not use parenthesis)"<<std::endl;
    for(int i=1;i<=num_of_classes;i++){
        try{
            std::cout<<"    Please enter class #"<<i<<std::endl<<"    ";
            std::cin>>line;
            letter_grade=line.substr(0,line.find(","));
            credits=std::stoi(line.substr(line.find(",")+1,3));
            if(find_grade_value(letter_grade,Choice)!=-1&&credits>0){
                credits_sum+=credits;
                gpa_sum+=(find_grade_value(letter_grade,Choice)*credits);
            }else{
                error_output(i);
            }
        }catch(...){
            error_output(i);
        }
    }
    std::cout<<"    Your Final GPA is: "<<(gpa_sum/credits_sum)<<std::endl;
    std::cout<<"    Do you want to calculate your gpa with this criteria again? Use YES or NO"<<std::endl<<"    ";
    std::cin>>answer;
    if(answer=="YES"){
        calculate_gpa(Choice);
    }else{
        std::cout<<"    Goodbye!";
    }
}
//Gets the criteria choice from the user
void choose_option(){
    std::cin>>choice;
    if(choice=="ONE"){
        std::cout<<choice_one_print<<std::endl;
        choice_print_out();
        print_out(Choice_1);
        std::cout<<std::string(8, '\n');
        calculate_gpa(Choice_1);
    }else if(choice=="TWO"){
        std::cout<<choice_two_print<<std::endl;
        choice_print_out();
        print_out(Choice_2);
        std::cout<<std::string(5, '\n');
        calculate_gpa(Choice_2);
    }else if(choice=="CUSTOM"){
        std::cout<<custom_print<<std::endl;
        build_custom_criteria();
        calculate_gpa(Custom);
    }else{
    std::cout<<"    Invalid option, please enter valid choice"<<std::endl<<"    ";
    choose_option();
    }
}
int main()
    {
        std::cout<<std::endl<< R"(
    ***************************************************************************************************
    *   _____ _____             _____          _      _____ _    _ _            _______ ____  _____   *
    *  / ____|  __ \ /\        / ____|   /\   | |    / ____| |  | | |        /\|__   __/ __ \|  __ \  *
    * | |  __| |__) /  \      | |       /  \  | |   | |    | |  | | |       /  \  | | | |  | | |__) | *
    * | | |_ |  ___/ /\ \     | |      / /\ \ | |   | |    | |  | | |      / /\ \ | | | |  | |  _  /  *
    * | |__| | |  / ____ \    | |____ / ____ \| |___| |____| |__| | |____ / ____ \| | | |__| | | \ \  *
    *  \_____|_| /_/    \_\    \_____/_/    \_\______\_____|\____/|______/_/    \_\_|  \____/|_|  \_\ *
    *                                                                                                 *
    ***************************************************************************************************
    )";
    std::cout<<"Welcome! please choose which GPA criteria you would like to use";
    std::cout<< R"(
                  CHOICE 1:     CHOICE 2:
                  ========      ========
                  A  = 4.0      A  = 4.0
                  B  = 3.5      A- = 3.7
                  B- = 3.0      B+ = 3.3
                  C  = 2.5      B  = 3.0
                  C- = 2.0      B- = 2.7
                  D  = 1.5      C+ = 2.3
                  D- = 1.0      C  = 2.0
                  E  = 0.5      C- = 1.7
                  F  = 0.0      D+ = 1.3
                                D  = 1.0
                                F  = 0.0)"+std::string(3, '\n');
    std::cout<<"    Please enter ONE for choice 1,and TWO for choice 2."<<std::endl;
    std::cout<<"    Also, if neither of these fit your criteria, enter CUSTOM to make your own!"<<std::endl<<"    Choice:";
    choose_option();
}
