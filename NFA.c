#include <stdio.h>
#include <simpio.h>
#include <string.h>

typedef struct automata
{
        char nfa[100];
}nfa;

typedef struct arcs
{
        char from[100];
        char to[100];
        char alphabet[100];
}edge;

nfa Buf[100];
int numberOfEdges, numberOfStates, numberOfAlphabets, numberOfInitialStates, numberOfFinalStates;
edge edges[100];
nfa states[100];
nfa alphabets[100];
nfa initialStates[100];
nfa finalStates[100];

//Check if state is initial
int isInitial(char nfa[])
{

    for(int i = 0 ; i< numberOfInitialStates ; i++)
    {
            if(strcmp(nfa , initialStates[i].nfa) == 0)
            {
               return 1;
            }
    }
    return 0;
}

//Check if state is final
int isFinal(char nfa[])
{

    for(int i = 0 ; i< numberOfFinalStates ; i++)
    {
            if(strcmp(nfa , finalStates[i].nfa) == 0)
            {
               return 1;
            }
    }
    return 0;
}

void GetInput()
{
	int i;
	char from[100], to[100], alphabet[100], help[100], *token;
	FILE *InputFile;
	char inputFileName[30];

	while (TRUE){
        printf("Insert input file's name: ");
        printf("\n");
        gets(inputFileName);
        InputFile=fopen(inputFileName, "r");
        if (InputFile!=NULL) break;
        printf("Cant find the input file %s. Please, try again...\n", inputFileName);
    }

	// get initial states
	fgets(help, 255, InputFile);
	i = 0;
	token = strtok(help , ",");
	while(token != NULL)
	{
         strcpy(initialStates[i].nfa, token); i++;
         token = strtok(NULL , ",");
    }
    token = strtok(initialStates[i-1].nfa , "\n");
    strcpy(initialStates[i-1].nfa, token);

    numberOfInitialStates = i;

    // get final states
    fscanf(InputFile, "%s\0", help);
    i = 0;
	token = strtok(help , ",");
	while(token != NULL)
	{
         strcpy(finalStates[i].nfa, token); i++;
         token = strtok(NULL , ",");
    }
    token = strtok(finalStates[i-1].nfa , "\n");
    strcpy(finalStates[i-1].nfa, token);

	numberOfFinalStates = i;

	// get automaton edges
	i = -1;
	while(!feof(InputFile))
	{
           i++;
           fscanf(InputFile, "%s %s %s", edges[i].from, edges[i].to , edges[i].alphabet);
    }
    numberOfEdges = i;
    fclose(InputFile);
}

//Print all edges of the automaton
void printEdges()
{
     printf("\nAutomaton Edges: \n");
     printf("Number of Edges: %d \n", numberOfEdges);
     for(int i = 0; i<=numberOfEdges ; i++)
     {
             printf("(%s) ---(%s)---> (%s)\n", edges[i].from, edges[i].to , edges[i].alphabet);
     }
}

//Add states and alphabets
void getAutomaton()
{

     int si = 0, ai = 0, b, j;
     //adding states
     strcpy(states[0].nfa ,   edges[0].from);
     numberOfStates = 1;
     si = 1;
     for(int i = 0; i<=numberOfEdges ; i++)
     {

             b = 0;
             for(j = 0; j< numberOfStates; j++)
             {
                   if(strcmp(edges[i].from , states[j].nfa) == 0)
                   {
                      b = 1;

                   }
             }
             if(b == 0)
             {

                   strcpy(states[si].nfa ,   edges[i].from);
                   si++;
                   numberOfStates++;
             }

              b = 0;
             for(j = 0; j< numberOfStates; j++)
             {
                   if(strcmp(edges[i].to , states[j].nfa) == 0)
                   {
                      b = 1;
                   }
             }
             if(b == 0)
             {

                   strcpy(states[si].nfa ,   edges[i].to);
                   si++;
                   numberOfStates++;
             }
     }
     //adding alphabets
     strcpy(alphabets[0].nfa ,   edges[0].alphabet);
     numberOfAlphabets = 1;
     ai = 1;
     for(int i = 0; i<=numberOfEdges ; i++)
     {
             b = 0;
             for(j = 0; j< numberOfAlphabets; j++)
             {
                   if(strcmp(edges[i].alphabet , alphabets[j].nfa) == 0)
                   {
                      b = 1;

                   }
             }
             if(b == 0)
             {
                   strcpy(alphabets[ai].nfa ,   edges[i].alphabet);
                   ai++;
                   numberOfAlphabets++;
             }

     }
}

//Ask user for characters
void insertCharacters()
{
     char choice;

     do {
         printf("\nInsert characters: \n");
         fgets(Buf, sizeof(Buf), stdin);

         check();

         //Ask user if wants insert another word
         printf("\nWant you insert more characters?(Y/N) ");
         choice = getchar();
         getchar();
    }
    while(choice=='y' || choice=='Y');

}

//Test insert characters on Automaton
void check()
{
    for (int i=0; i<strlen(Buf); i++){
        //for (int j=0; j<numberOfFinalStates; j++){
             if (isFinal(Buf[i].nfa) == 1){
                 printf("This automaton terminates on a final state!\n");
                 break;
             }
             else{
                 printf("This automaton terminates on a non-final state!\n");
                 break;
             }
       // }
    }


}

//Get and print automaton
void getAndPrintAutomaton()
{
      int j;
      GetInput(); //Get automaton description from input file
      getAutomaton(); //Get the automaton
      printEdges(); //Print all edges

      //Print number of states
      printf("\n number of states : %d\n", numberOfStates);
      //Print all states
      for(j = 0; j< numberOfStates; j++){
            //Print initial states
            if(isInitial(states[j].nfa) == 1 && isFinal(states[j].nfa) == 1)
            {
                printf("This is initial and final state: ");
                printf("[->%s<-]\n",states[j].nfa);
            }
            else
            {
                if(isInitial(states[j].nfa) == 1)
                {
                   printf("This is initial state: ");
                   printf("[->%s]\n",states[j].nfa);
                }
                else
                {
                    //Print final states
                    if(isFinal(states[j].nfa) == 1)
                    {
                        printf("This is final state: ");
                        printf("[%s<-]\n",states[j].nfa);
                    }
                    else
                    {
                        printf("[%s]\n",states[j].nfa);
                    }

                }
            }
      }

      //Print number of alphabets
      printf("\n number of alphabets : %d", numberOfAlphabets);
      //Print all alphabets
      for(j = 0; j< numberOfAlphabets; j++)
      {
                printf("\n|%s|",alphabets[j].nfa);
      }

      insertCharacters(); //Ask user for characters
}

//Main Program
main()
{
      //Get and print automaton
      getAndPrintAutomaton();
}

