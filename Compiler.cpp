// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <vector>
using namespace std;

char getType(char a) 
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
    {
        return 'L';
    }
    else if (a >= '0' && a <= '9')
    {
        return 'D';
    }
    else
    {
        return a;
    }
}
char getSpace(char a)
{
    if (isspace(a))
    {
        return 'S';
    }
    else
    {
        return a;
    }
}
string convert(char a, char b)
 {   
    
    switch (a)
    {
    case 'L':
        if (b != a)
            return string(1,b);
        else
            return string(1,a);
        break;
    case 'D':
        if (b != a)
            return string(1,b);
        else
            return string(1,a);
        break;
    case 'S':
        if (b != a)
            return (" ");
        else
            return string(1,a);
        break;
    default:
        return string(1, a);


    }
 }


void scanner()
{
    string reserved[13] = { "CONST", "IF", "VAR", "THEN", "PROCEDURE", "WHILE", "CALL", "DO", "ODD","CLASS","ELSE","GET","PUT"};
    int DFSA[30][18] = { {5,3,2,7,11,14,0,1,17,18,19,20,21,22,23,24,25,26},
                         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                         {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                         {4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                         {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                         {5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},  //5
                         {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
                         {10,10,8,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {8,8,9,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
                         {8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {12,12,12,12,13,12,12,12,12,12,12,12,12,12,12,12,12,12},
                         {12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
                         {13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13},
                         {15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15}, //14
                         {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15}, //15
                         {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
                         {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
                         {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18}, //15
                         {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19},
                         {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20},
                         {21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
                         {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22},
                         {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
                         {24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
                         {26,26,26,26,27,26,26,26,26,26,26,26,26,26,26,26,26,26}, //25
                         {26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26}, //26
                         {27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27}, //27
                         {1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1}, //28
                         {29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29}  }; //29
 

    
    string fileName = ("C:/Users/Hadyn/source/repos/Compiler/input.txt");
    string outFile = ("C:/Users/Hadyn/source/repos/Compiler/output.txt");
    string outFile2 = ("C:/Users/Hadyn/source/repos/Compiler/output2.txt");
    ifstream input_file(fileName);
    fstream output_file(outFile);
   
    fstream input(outFile);
    ofstream output(outFile2);

    output << "Token\t\t\tClass\t\t\tValue\t\t\tAddress\t\t\tSegment\n";
    

    char currentChar;
    string token = ""; //pushes chars into token until it reaches endstate
    char letDig; //helps handle any let and digit states
    bool isDelim; //helps leave off on last delmiter grabbed
    string special = "";
    


    int currentState = 0;

    while(input_file.get(currentChar))
    {
        isDelim = false;
        letDig = currentChar;
        currentChar = getType(currentChar);
        currentChar = getSpace(currentChar);
        do
        {
            switch (currentState)
            {
            case 0:
                switch (currentChar)
                {
                case 'L':
                    currentState = DFSA[0][0];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;

                    break;
                case 'D':
                    currentState = DFSA[0][1];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '*':
                    currentState = DFSA[0][2];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '/':
                    currentState = DFSA[0][3];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '=':
                    currentState = DFSA[0][4];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '<':
                    currentState = DFSA[0][5];
                    token = token + convert(currentChar, letDig);
                    
                    break;
                case 'S':
                    currentState = DFSA[0][6];
  
                    isDelim = false;
                    break;
                case '{':
                    currentState = DFSA[0][8];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '}':
                    currentState = DFSA[0][9];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '(':
                    currentState = DFSA[0][10];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case ')':
                    currentState = DFSA[0][11];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case ',':
                    currentState = DFSA[0][12];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case ';':
                    currentState = DFSA[0][13];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '+':
                    currentState = DFSA[0][14];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '-':
                    currentState = DFSA[0][15];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                case '>':
                    currentState = DFSA[0][16];
                    token = token + convert(currentChar, letDig); 
                    isDelim = false;
                    break;
                case '!':
                    currentState = DFSA[0][16];
                    token = token + convert(currentChar, letDig);
                    isDelim = false;
                    break;
                default:
                    currentState = 1;
                    isDelim = false;
                }
                break;
            case 1:
                output_file << token << " ERROR\n";
                currentState = 0;
                token = "";
                break;
            case 2:
                output_file << token << " <mop>\n";
                currentState = 0;
                token = "";
                break;
            case 3:
                switch (currentChar)
                {
                case 'D':
                    currentState = DFSA[3][1];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 4;
                    isDelim = true;

                }
                break;
            case 4:
                output_file << token << " <int>\n";
                currentState = 0;
                token = "";
                break;
            case 5:
                switch (currentChar)
                {
                case 'L':
                    currentState = DFSA[5][0];
                    token = token + convert(currentChar, letDig);
                    break;
                case 'D':
                    currentState = DFSA[5][1];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 6;
                    isDelim = true;
                }
                break;
            case 6:
                for (int x = 0; x < 13; x++)
                {
                    if (reserved[x] == token)
                    {
                        special = "$" + reserved[x];
                        break;
                    }
                    else
                    {
                        special = "<var>";
                    }
                        

                }
                output_file << token << " " << special << "\n";
                currentState = 0;
                token = "";
                break;
            case 7:
                switch (currentChar)
                {
                case '*':
                    currentState = DFSA[7][2];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 10;
                    isDelim = true;

                }
                break;
            case 8:
                switch (currentChar)
                {
                case '*':
                    currentState = DFSA[8][2];
                    break;
                default:
                    currentState = 8;
                }
            case 9:
                switch (currentChar)
                {
                case '/':
                    currentState = 0;
                    token = token + convert(currentChar, letDig);
                    output_file << token << "\n";
                    token = "";
                    break;
                default:
                    currentState = 8;
                    token = token + convert(currentChar, letDig);
                }
                break;
            case 10:
                output_file << token << " <mop>\n";
                currentState = 0;
                token = "";
                break;
            case 11:
                switch (currentChar)
                {
                case '=':
                    currentState = DFSA[11][4];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 12;
                    isDelim = true;
                }
                break;
            case 12:
                output_file << token << " <assignment>\n";
                currentState = 0;
                token = "";
                
                break;
            case 13:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                
                break;
            case 14:
                switch (currentChar)
                {
                case '=':
                    currentState = DFSA[16][4];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 15;
                    isDelim = true;
                }
            case 15:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                break;
            case 16:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                break;
            case 17:
                output_file << token << " <$LB>\n";
                currentState = 0;
                token = "";
                
                break;
            case 18:
                output_file << token << " <$RB>\n";
                currentState = 0;
                token = "";
                
                
                break;
            case 19:
                output_file << token << " <$LP>\n";
                currentState = 0;
                token = "";
                isDelim = true;
                
                break;
            case 20:
                output_file << token << " <$RP>\n";
                currentState = 0;
                token = "";
                
                break;
            case 21:
                output_file << token << " <$Comma>\n";
                currentState = 0;
                token = "";
                
                break;
            case 22:
                output_file << token << " <$Semi>\n";
                currentState = 0;
                token = "";
                
                break;
            case 23:
                output_file << token << " <addop>\n";
                currentState = 0;
                token = "";
                break;
            case 24:
                output_file << token << " <addop>\n";
                currentState = 0;
                token = "";
                break;
            case 25:
                switch (currentChar)
                {
                case '=':
                    currentState = DFSA[25][4];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 26;
                    isDelim = true;
                }
                break;
            case 26:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                break;
            case 27:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                break;
            case 28:
                switch (currentChar)
                {
                case '=':
                    currentState = DFSA[28][4];
                    token = token + convert(currentChar, letDig);
                    break;
                default:
                    currentState = 1;
                    isDelim = true;
                }
            case 29:
                output_file << token << " <relop>\n";
                currentState = 0;
                token = "";
                break;




            }
        }
        while (isDelim);
           
        
    }
    token = "";
    string nextTok = "";
    string prevTok = "";
    string classification = ""; //helps convert <var> to a reserved classification
    string nextClass = "";
    string prevClass = "";
    string segment = "CS"; //helps create symbol table
    string line;
    int num = 0;
    int address = 0;
    string value = "";
    bool firstZero = true;
    vector<string> list;
    
    while (getline(input, line))
    {
        
        for (int z = 0; z < line.length(); z++)
        {
            switch (num)
            {
            case 0:
                token = token + line[z];
                if(line[z] == ' ')
                num = 1;
                
                break;
            case 1:
                classification = classification + line[z];
                
                break;
            
            }
            
        }
        num = 0; 
        if (nextClass != "")
        {
            classification = nextClass;
            nextClass = "";
        }
        
        if (!(count(list.begin(), list.end(), token)))
        {
            list.push_back(token);

            if (classification == "$CLASS")
            {
                nextClass = "<Program Name>";
               
            }
            else if (classification == "<Program Name>")
            {
                output << token << " " <<  classification << "\t" << value << "\t\t\t" << address<< "\t\t\t" << segment <<"\n";
                segment = "DS";

            }
            else if (classification == "$CONST")
            {
                nextClass = "<Const>";
                prevClass = "<Const>";
            }
            else if (classification == "<Const>")
            {
                prevTok = token;
                prevClass = "<Const>";
            }
            else if (classification == "<var>")
            {
                if (prevClass == "<Const>")
                {
                    classification = "<Const>";
                    prevTok = token;
                }
                else
                {
                    prevClass = "<var>";
                    output << token << "\t\t\t" << classification << "\t\t\t" << " " << "\t\t\t" << address << "\t\t\t" << segment << "\n";
                    if (firstZero)
                    {
                        firstZero = false;
                    }
                    else
                    {
                        address += 2;
                    }
                }
            }
            else if (classification == "$VAR")
            {
                nextClass = "<var>";
            }
            else if (classification == "<assignment>")
            {
               // prevClass == "<assignment>";
            }
            else if (classification == "<int>")
            {
                value = token;
                if (prevTok != "" && prevClass == "<Const>")
                {
                    output << prevTok << "\t\t\t" << prevClass << "\t\t\t" << value << "\t\t\t" << address << "\t\t\t" << segment << "\n";
                }
                else
                {
                    classification = "<Numeric Literal>";
                    output << token << "\t\t" << classification << "\t\t" << token << "\t\t\t" << address << "\t\t\t" << segment << "\n";
                }
                
                if (firstZero)
                {
                    firstZero = false;
                    address += 2;
                }
                else
                {
                    address += 2;
                    prevClass = "";
                }
            }
            else
            {
                
            }

        }
        token = "";
        classification = "";

        
        
    }
    
    input_file.close();
    output_file.close();
    input.close();
    output.close();
}

void analyzer()
{
    string reserved[13] = { "CONST", "IF", "VAR", "THEN", "PROCEDURE", "WHILE", "CALL", "DO", "ODD","CLASS","ELSE","GET","PUT"};
    char parser[21][21] = {

        {' ',';','=','+','-','(',')','*','/','I','T','O','E','N','>','<','G','F','{','}','C'},//0
        {';','<',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//; 1
        {'=','>',' ','<','<','<',' ','<','<',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //= 2
        {'+','>',' ','>','>','<','>','<','<',' ','>',' ','>','>','>','>','>','>',' ',' ',' '}, //+ 3
        {'-','>',' ','>','>','<','>','<','<',' ','>',' ','>','>','>','>','>','>',' ',' ',' '}, //- 4
        {'(',' ',' ','<','<','<','=','<','<',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //( 5 
        {')','>',' ','>','>',' ','>','>','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //) 6
        {'*','>',' ','>','>','<','>','>','>',' ','>',' ','>','>','>','>','>','>',' ',' ',' '}, //* 7
        {'/','>',' ','>','>','<','>','>','>',' ','>',' ','>','>','>','>','>','>',' ',' ',' '}, // /8
        {'I',' ',' ','<','<','<',' ','<','<',' ','=','<','<','<','<','<','<','<',' ',' ',' '}, //IF 9 
        {'T',' ','<',' ',' ',' ',' ',' ',' ','<',' ',' ',' ',' ',' ',' ',' ',' ','<',' ','<'}, //Then 10
        {'O',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //ODD 11
        {'E',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //== 12
        {'N',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //!= 13
        {'>',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //> 14
        {'<',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //< 15 
        {'G',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //>= 16
        {'F',' ',' ','<','<','<',' ','<','<',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //<= 17 
        {'{',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //{ 18
        {'}',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //} 19 
        {'C',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //Call 20
      //      D   =   +   -   (   )   *   /   If  Th  Od  ==  !=  >   <   >=  <=  {   }   Ca 
      //  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20
    };
    string fileName = ("C:/Users/Hadyn/source/repos/Compiler/output.txt");
    string outFile = ("C:/Users/Hadyn/source/repos/Compiler/outputQuads.txt");
    ifstream input_file(fileName);
    ofstream output_file(outFile);

    string sentence;
    
    string stack[20] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
    string tempStack[20] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
    int precOrder[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    char precStack[10] = { ' ',' ',' ',' ',' ', ' ',' ',' ',' ',' ' };
    string label[5] = { "L1","L2","L3","L4","L5" };
    int parenFixUp[5] = { -1,-1,-1,-1,-1 };
    string tempT = " ";
    int count = 0;
    string pastTok = "";
    string thenTok = "";
    int quadCount = 0;
    int precCount = 0;
    int ifCount = 0;
    int labelCount = 0;
    int leftPrenCount = 0;
    int mark;
    bool paren = false;
    bool pause = false;
    bool then = false;
    bool quadComplete = false;
    bool blockState = false;
    bool doubleLeft = false;
    

    while (getline(input_file, sentence))
    {
        string token = sentence.substr(0, sentence.find(" "));
        
        char tokChar = token.at(0);
        char charType = getType(tokChar);
        char prec;
        string T[10] = { "T1","T2","T3","T4","T5","T6","T7","T8","T9","T10"};
        
       
        
       
        
        for (int x = 0; x < 13; x++) // helps make the type usable in table
        {
            if (reserved[x] == token)
            {
                charType = 'R';
                if (token == reserved[3] || token == reserved[7] || token == reserved[10])
                {
                    charType = 'T';
                }
                else if (token == reserved[1] || token == reserved[5])
                {
                    charType = 'I';
                }
                else if (token == reserved[6])
                {
                    charType = 'C';
                }
                else if (token == reserved[8])
                {
                    charType = 'O';
                }
                else if (token == reserved[11])
                {
                    charType = 'A';
                }
                else if (token == reserved[12])
                {
                    charType = 'P';
                }
                
            }
        }
        if (token == "==") //helps 2 char tokens be more digestable
        {
            charType = 'E';
        }
        else if (token == "!=")
        {
            charType = 'N';
        }
        else if (token == "<=")
        {
            charType = 'F';
        }
        else if (token == ">=")
        {
            charType = 'G';
        }
       



        switch (charType)
        {
        case ';':
            
            if (!pause)
            {
                stack[count] = token;
                count++;
                quadComplete = true;
               
            }
            pause = false;

           
           
            

            break;
        case 'D':
           if (!pause)
            {
                stack[count] = token;
                count++;
            }

            break;
        case 'L':
            
            if (!pause)
            {
                stack[count] = token;
                count++;
            }

                break;
        case 'R':
            pause = true;
           
            break;
        case 'T':
            then = true;
            quadComplete = true;
            
            break;
        case 'I':
            if (!blockState)
            {
                if (ifCount > 0)
                {
                    thenTok = "";
                    for (int x = 0; x < ifCount; x++)
                    {
                        output_file << "L," << "L" << labelCount - x << ",?,?\n";
                    }
                    ifCount = 0;
                }
            }
            output_file << token << ",?," << "?,?\n";
            pause = false;
            quadCount++;
            ifCount++;
            labelCount++;
            
            break;
        case 'C':

            break;
        case 'O':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        case '*':
            
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        case '/':
           
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }

            break;
        case '+':
            
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        case '-':
         
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        case '=':
            
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        case ',':
            
            break;
        case '(':
            if (precCount > 0)
            {
                for (int x = 0; x < precCount; x++)
                {
                   
                        parenFixUp[leftPrenCount] = precOrder[x];
                        leftPrenCount++;
                        
                        if (pastTok == "(")
                        {
                            doubleLeft = true;
                            pastTok = "";
                        }
                        else
                        {
                            pastTok = "(";
                        }
                        
                    
                }
            }
            
            break;
        case ')':
            if (!pause)
            {
                paren = true;
                quadComplete = true;
            }
            break;
        case '{':
            blockState = true;
            break;
        case '}':
            if (ifCount > 0)
            {
                thenTok = "";
                for (int x = 0; x < ifCount; x++)
                {
                    output_file << "L," << "L" << labelCount - x << ",?,?\n";
                }
                ifCount = 0;
            }
            blockState = false;
            break;
        case 'E':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "NE";
            }
            break;
        case 'N':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "E";
            }
            break;
        case '>':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "LE";
            }
            break;
        case '<':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "GE";
            }
            break;
        case 'G':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "L";
            }
        case 'F':
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            if (ifCount > 0)
            {
                thenTok = "G";
            }
            break;
        case 'A':
        {
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        }
        case 'P':
        {
            if (!pause)
            {
                stack[count] = token;
                precOrder[precCount] = count;
                precStack[precCount] = charType;
                count++;
                precCount++;
            }
            break;
        }

            

        default:

            break;
        }
        if (quadComplete)
        {
           
            for (int x = precCount; x > -1; x--)  //entire loop helps sort //starts comparing from top of stack
            {

                for (int z = 1; z < 21; z++) //searchs for row our precedence operator is on
                {
                    if (precStack[x] == parser[z][0])
                    {
                        for (int w = precCount; w > -1; w--)
                        {
                            if (precStack[w] != precStack[x])
                            {
                                for (int y = 1; y < 21; y++)
                                {
                                    if (precStack[w] == parser[0][y])
                                    {
                                        prec = parser[z][y];
                                        int intTemp;
                                        char charTemp;
                                        switch (prec)
                                        {
                                        case '>':
                                            if (x > w)
                                            {
                                                intTemp = precOrder[x];
                                                charTemp = precStack[x];
                                                precOrder[x] = precOrder[w];
                                                precStack[x] = precStack[w];
                                                precOrder[w] = intTemp;
                                                precStack[w] = charTemp;
                                            }
                                            break;
                                        case '<':
                                            if (x < w)
                                            {
                                                intTemp = precOrder[x];
                                                charTemp = precStack[x];
                                                precOrder[x] = precOrder[w];
                                                precStack[x] = precStack[w];
                                                precOrder[w] = intTemp;
                                                precStack[w] = charTemp;
                                            }
                                            break;
                                        default:

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            } // operators in quad are now sorted

            if (leftPrenCount > 0)
            {

                for (int x = leftPrenCount - 1; x >= 0; x--)
                {
                    for (int y = 0; y < precCount; y++)
                    {
                        if (parenFixUp[x] == precOrder[y])
                        {

                            for (int w = y; w < precCount; w++)
                            {
                                precOrder[w] = precOrder[w + 1];

                            }

                        }
                    }
                    precOrder[precCount - 1] = parenFixUp[x];
                    parenFixUp[x] = -1;

                }

            }
            
            if (doubleLeft)
            {
                //precCount--;
               
            }

            if (paren)
            {
                precCount = precCount--;
            }
            
            for (int x = 0; x < precCount; x++)
            {
                string arg2 = "";
                int opAddress = precOrder[x];
                string op = stack[opAddress];
                string arg1;
                if (x == 0 && opAddress != 0)
                    arg1 = stack[opAddress - 1];
                else if (opAddress == 0)
                    arg1 = "?";
                else
                    arg1 = T[x - 1];

                arg2 = stack[opAddress + 1];
                
                if (precOrder[x + 2] == -1)
                {
                    if (!paren)
                    {
                        if (tempT != " ")
                        {
                            arg2 = stack[0];
                            arg1 = T[x-1];
                            if (arg1 != tempT)
                            {
                                arg1 = tempT;
                            }
                            tempT = "N";
                        }       
                        
                    }
                    else
                    {
                        tempT = T[x];
                    }
                }
                else if (precOrder[x] == -1)
                   break;
                
                if (tempT == " ")
                {
                    tempT = T[x];
                }
                if (precCount == 1)
                {
                    tempT = "N";
                    
                }
                
               

                output_file << op << "," << arg1 << "," << arg2 << "," << tempT << "\n";
                mark = x+1;
                if (tempT != " ")
                {
                    for (int y = 0; y < 7; y++)
                    {
                        if (tempT == T[y])
                        {
                            tempT = T[y];
                            break;
                        }
                    }
                }
               

            }
            //output_file << "\n";
            if (paren)
            {
                tempT = T[mark];
            }
            else
            {
                tempT = " ";
            }
            if (then)
            {
                output_file << token << ",L"<<  labelCount  << "," << thenTok <<",? \n";
                then = false;
                quadCount++;
            }
            for (int x = 0; x < precCount; x++) //wiping our stacks
            {
                //output_file << (precStack[x]) << " " << (precOrder[x]);
                precStack[x] = ' ';
                precOrder[x] = -1;
            }
            precCount++;
            if (paren)
            {
                
                precStack[0] = precStack[precCount-1];
                precOrder[0] = 1;
            }
            precCount = 0;
            if (paren)
            {
                precCount = 1;
            }
            
            
            for (int x = 0; x < count; x++)
            {
                if (paren)
                {
                    x++;
                }
                stack[x] = "";
            }
            count = 0;
            if (paren)
            {
                stack[1] = precStack[0];
                stack[2] = T[mark-1];
                mark = 0;
                count = 3;
            }
            leftPrenCount = 0;
            paren = false;
            quadComplete = false;
            //output_file << "\n";
            quadCount++;
        }
        
    }
    input_file.close();
    output_file.close();
}
void semantics()
{
    string fileName = ("C:/Users/Hadyn/source/repos/Compiler/outputQuads.txt");
    string outFile = ("C:/Users/Hadyn/source/repos/Compiler/outputMachine.txt");
    ifstream input_file(fileName);
    ofstream output_file(outFile);

    string sentence;
   
 
    bool isWhile = false;
    int whileLabel = 0;
    int putLabel = 1;
    int getLabel = 1;
    string tempLabel;
    while (getline(input_file, sentence))
    {
        string delimiter = ",";
        string quads[4];
        int x = 0;
        
        while (x < 4)
        {
            quads[x] = sentence.substr(0, sentence.find(delimiter));
            x++;
            sentence.erase(0, sentence.find(delimiter)+1);
        }
        if (quads[3] == "N")
        {
            quads[3] = quads[2];
        }
        
        if (quads[0] == "+")
        {
            output_file <<  "\t\tmov ax," << "[" << quads[1] << "]\n";
          
            output_file <<  "\t\tadd ax," << "[" << quads[2] << "]\n";
           
            output_file <<  "\t\tmov [" << quads[3] << "], " << "ax\n";
            
        }
        if (quads[0] == "-")
        {
            output_file << "\t\tmov ax," << "[" << quads[1] << "]\n";

            output_file << "\t\tsub ax," << "[" << quads[2] << "]\n";

            output_file << "\t\tmov [" << quads[3] << "], " << "ax\n";

        }
        else if (quads[0] == "=")
        {
            output_file << "\t\tmov ax," << "[" << quads[1] << "]\n";

            output_file << "\t\tmov [" << quads[2] << "], " << "ax\n";

        }
        else if (quads[0] == "*")
        {
            output_file << "\t\tmov ax," << "[" << quads[1] << "]\n";
            output_file << "\t\tmov ax," << "[" << quads[2] << "]\n";
            output_file << "\t\tmul ax\n";

            output_file << "\t\tmov [" << quads[3] << "], " << "ax\n";

        }
        else if (quads[0] == "/")
        {
            output_file << "\t\tmov dx,0\n";

            output_file << "\t\tmov ax, [" << quads[1] << "]\n";

            output_file << "\t\tmov bx, [" << quads[2] << "]\n";

            output_file << "\t\tdiv bx\n";

            output_file << "\t\tmov [" << quads[3] << "], " << "ax\n";

        }
        else if (quads[0] == ">=" || quads[0] == "<=" || quads[0] == ">" || quads[0] == "<" || quads[0] == "==")
        {
            if (isWhile)
            {
                whileLabel++;
                output_file << "\tW" << whileLabel << ":\tmov ax, [" << quads[1] << "]\n";
                isWhile = false;
            }
            else
            {
                output_file << "\t\tmov ax, [" << quads[1] << "]\n";
            }


            output_file << "\t\tcmp ax," << "[" << quads[2] << "]\n";

        }
        else if (quads[0] == "THEN")
        {
            output_file << "\t\tJ" << quads[2] << " " << quads[1] << "\n";

        }
        else if (quads[0] == "L")
        {
            if (quads[1] == tempLabel)
            {
                output_file << "\t\tjmp W" << whileLabel << "\n";
                tempLabel = "";
            }
            output_file << "\t" << quads[1] << ":\t NOP\n";

        }
        else if (quads[0] == "ELSE")
        {
            output_file << "\t\tJMP____" << quads[1] << " ELSE\n";

        }
        else if (quads[0] == "WHILE")
        {
            isWhile = true;
        }
        else if (quads[0] == "DO")
        {
            tempLabel = quads[1];
        }
        else if (quads[0] == "GET")
        {
            output_file << "\t\tpush ax\n";
            output_file << "\t\tpush dx\n";
            output_file << "\t\tmov eax, 4\n";
            output_file << "\t\tmov ebx, 1\n";
            output_file << "\t\tmov ecx, userMsg\n";
            output_file << "\t\tmov edx, lenUserMsg\n";
            output_file << "\t\tint 80h\n";
            output_file << "\t\tpop dx\n";
            output_file << "\t\tpop ax\n";
            output_file << "\t\tmov eax, sys_read\n";
            output_file << "\t\tmov ebx, stdin\n";
            output_file << "\t\tmov ecx, " << quads[2] << "\n";
            output_file << "\t\tmov edx, 4\n";
            output_file << "\t\tint 0x80\n";
            output_file << "\t\tmov ax, 0\n";
            output_file << "\t\tmov [ReadInt], ax\n";
            output_file << "\t\tmov ecx, " << quads[2] << "\n";
            output_file << "\t\tmov bx, 0\n";
            output_file << "\t\tmov bl, byte[ecx]\n";
            output_file << "\tNext" << getLabel<<":\t sub bl, '0'\n";
           
            output_file << "\t\tmov ax, [ReadInt]\n";
            output_file << "\t\tmov dx, 10\n";
            output_file << "\t\tmul dx\n";
            output_file << "\t\tadd ax, bx\n";
            output_file << "\t\tmov [ReadInt], ax\n";
            output_file << "\t\tmov bx, 0\n";
            output_file << "\t\tadd ecx, 1\n";
            output_file << "\t\tmov bl, byte[ecx]\n";
            output_file << "\t\tcmp bl, 0xA\n";
            output_file << "\t\tJNE Next" << getLabel <<"\n";
            getLabel++;
            output_file << "\t\tmov [ReadInt], ax\n";
            output_file << "\t\tcmp ax, 0\n";
            output_file << "\t\tJE fini\n";
        }
        else if (quads[0] == "PUT")
        {
             output_file << "\t\tmov ax, ["<< quads[2] << "]\n";
             output_file << "\t\tmov ebx, ResultValue + 4\n";
             output_file << "\tConvertLoop" << putLabel << ":\n";
             output_file << "\t\tsub dx,dx\n";
             output_file << "\t\tmov cx,10\n";
             output_file << "\t\tdiv cx\n";
             output_file << "\t\tadd dl,'0'\n";
             output_file << "\t\tmov [ebx], dl\n";
             output_file << "\t\tdec ebx\n";
             output_file << "\t\tcmp ebx, ResultValue\n";
             output_file << "\t\tJGE ConvertLoop" << putLabel <<"\n";
             putLabel++;
             output_file << "\t\tmov eax,4\n";
             output_file << "\t\tmov ebx,1\n";
             output_file << "\t\tmov ecx,Result\n";
             output_file << "\t\tmov edx,ResultEnd\n";
             output_file << "\t\tint 80h\n";


        }

        

    }
}


int main()
{
  scanner();
  analyzer();
  semantics();

}


