#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;
int main(){

    ifstream f("./Tests/Part2.txt"); 
    //reads from the test file
    string nextInput;

    double minimumTime = -1; 
    //sets the minimum time to an initial value 

    std::list<string> minimumStringValues;
    //creates a list to store the values that have the lowest type times

    while(f>>nextInput)
    {
        double totalTime = 0;
        //totalTime stores the total time for a word to be typed
   
        char keypadArray [8][4] = { 
            {'a','b','c', 0}, 
            {'d','e','f', 0}, 
            {'g','h','i', 0},
            {'j','k','l', 0}, 
            {'m','n','o', 0}, 
            {'p','q','r', 's'}, 
            {'t','u','v', 0}, 
            {'w','x','y', 'z'} 
        };

        //keypad array sorts the buttons with their respective letters

        int previousLetterIndex = -1;
        
        //loops through each character of each word
        for (size_t ch = 0; ch < nextInput.length(); ch++)
        {
            char currentLetter = nextInput[ch];
            int currentLetterIndex = -1;


            if(isupper(currentLetter)){
                totalTime += 2;
                //if the letter is uppercase 2s is added to the total time
                currentLetter = tolower(currentLetter);
            }

            //looping through the 2d array 
            for (size_t i = 0; i < 8; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    //if the letter is found, increasment the time if there was a previous value
                    if (currentLetter == keypadArray[i][j]){
                        currentLetterIndex = i;
                        if(ch != 0){
                            if(currentLetterIndex == previousLetterIndex){
                                totalTime += 0.5;
                            }
                            else {
                                totalTime += 0.25;
                            }
                        }

                        //if the button has to be pressed multiple times, the total time is incremented accordingly
                        if(j == 1){
                            totalTime += 0.25;
                        } 
                        else if (j == 2){
                            totalTime += 0.5;
                        }
                        else if (j == 3){
                            totalTime += 0.75;
                        }
                    }
                }
            }
            previousLetterIndex = currentLetterIndex;
            
        }

        if (minimumTime == -1){
            //sets the minimum time to the first value
            minimumTime = totalTime;
            minimumStringValues.push_front(nextInput);

        } else if (totalTime == minimumTime){
            //if there are multiple words with the same typing time 
            minimumStringValues.push_front(nextInput);

        }
        else if (totalTime < minimumTime){
            //if the minimum time should be replaced
            minimumTime = totalTime;
            minimumStringValues.clear();
            minimumStringValues.push_front(nextInput);
        }
    }

    while (!minimumStringValues.empty())
    {
        //prints the words with the lowest typing time with their associated typing time
        std::cout << minimumStringValues.back() << " = " << minimumTime << "s \n";
        minimumStringValues.pop_back();
    }
}
