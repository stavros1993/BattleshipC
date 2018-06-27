//Stavros Lioulias ,2025201100042,cst11042@uop.gr
//Fotis Stamatopoulos,2025201000011,cst10011@uop.gr

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct ship { //domh pou anaparista ena ploio.Periexei tis 8eseis pou katalamvanei,thn 8esh ths plwrhs(pinakas 2 stoixeiwn,to prwto einai h grammh kai to deftero h sthlh, 
    int pos; //thn katef8unsh,tous pontous kai to arxiko sumvolo...Dhmiourgountai kai twn 2 paixtwn ta ploia katef8eian mazi me thn dhlwsh ths domhs
    int bow[2];
    char dir;
    int points;
    char symbol;
    int damage;
} a1, a2, b1, b2, s1, s2, d1, d2, c1, c2;

struct players { //domh pou anaparita ena paixth.
    //periexei to score,to onoma tou paixth,to tamplo me ta alhthina stoixeia kai to tamplo pou fainetai otan einai h seira tou allou paixth..
    int score;
    char name[50];
    struct ship * sh[5];
    char **real_table; // exei kanonika ploia gia sigrisi
    char **table;

} p1, p2;


int placeShip(struct ship* s, struct players* p, int rows, int cols, int random);
void print(struct players p, int m, int n, int real);
void sinking(struct ship s, int player);
void showResults(int m, int n);
void help(struct players the_player, int m, int n);
int convertToInt(char input[]);
void endgame_check(int m, int n);
void free_function(int m, int n);
int processPCMove(struct players* p, struct players* opponent, int m, int n, int rows, int cols);

char **help_table, **result_table1, **result_table2;

int main(int argc, char** argv) {
    int turns, turn_choice, i, j, p2_choice, ii, jj, p1_place_ships, i1, j1, place_result, p2_random_placing, first_player, current_turn, successful_hit, ai_row, ai_col, successful_AI_hit;
    char input[3];
    char *pp;
    //turns:anaparista ton ari8mo twn gurwn,turn_choice:an einai 1,o xrhsths eisagei ton guro twn ari8mwn alliws to paixnidi paizetai mexri telous
    //i,j:diastaseis kai twn 4 pinakwn,p2_choice:an einai 1 o paixths paizei enantion enos allou paixth,alliws enantion tou computer kai aftomatopoietai to onoma tou p2 ws pc
    //p1_place_ships :an h epilogh tou player 1 einai 1,topo8etountai kanonika ta ploia,alliws aftomata.To antistrofo ginetai gia to p2_random_placing(0 gia tuxaia topo8ethsh)
    //ta i1 kai j1 xrhsimopoiountai sthn epanalhpsh opou oi 4 disdiastatoi pinakes arxikopoiountai me teleies
    //to place_result xrhsimopoieitai ws metavlhth epistrofhs gia oles tis klhseis ths sunarthshs pou topo8etei ta ploia.An einai 0 apotugxanei h topo8ethsh kai 
    //ksanakaleitai h sunarthsh alliws an einai 1 sunexizei sth topo8ethsh tou epomenou ploiou
    ii = 0;
    jj = 0;
    p2_random_placing = 1;
    printf("Do you want to play the game until the end?If yes press 1,otherwise press any other number\n");
    scanf("%d", &turn_choice);
    if (turn_choice == 1) {
        turns = 100000;
    } else {
        fflush(stdin);
        printf("Enter the number of the turns\n");
        scanf("%d", &turns);
    }
    printf("Are you going to play against a human?If yes press 1,otherwise press any other number\n");
    scanf("%d", &p2_choice);

    if (p2_choice == 1) {
        printf("Enter your names");
        scanf("%s", &p1.name);
        printf("\n"); //allagh grammhs...
        scanf("%s", &p2.name);
    } else {
        printf("\nEnter you name\n");
        scanf("%s", &p1.name);
        strcpy(p2.name, "PC");
    }


    printf("Enter the size of the players' board.First enter the number of the rows and then the numbers of the columns\n");
    printf("\nEnter the rows' number\n");
    scanf("%d", &i); //Ekxwrhsh timhs sth grammh
    printf("\n");
    while ((i < 5) || (i > 26)) { //elegxos
        printf("\n Enter a correct number for the rows\n");
        scanf("%d", &i);
    }

    do {
        printf("\nEnter a correct column number");
        scanf("%d", &j);
    } while ((j < 5) || (j > 30));

    p1.real_table = (char**) malloc(i * sizeof (char *));
    for (ii = 0; ii < i; ii++) {
        p1.real_table[ii] = (char*) malloc(j * sizeof (char));
    }
    if (p1.real_table == NULL) {
        printf("\nProblem with memory allocating\n");
        exit(0);
    }

    p2.real_table = (char**) malloc(i * sizeof (char *));
    for (ii = 0; ii < i; ii++) {
        p2.real_table[ii] = (char*) malloc(j * sizeof (char));
    }
    if (p2.real_table == NULL) {
        printf("\nProblem with memory allocating\n");
        exit(0);
    }

    p1.table = malloc(i * sizeof (char *));
    for (ii = 0; ii < i; ii++) {
        p1.table[ii] = (char*) malloc(j * sizeof (char));
    }
    if (p1.table == NULL) {
        printf("\nProblem with memory allocating\n");
        exit(0);
    }

    p2.table = malloc(i * sizeof (char *));
    for (ii = 0; ii < i; ii++) {
        p2.table[ii] = (char*) malloc(j * sizeof (char));
    }
    if (p2.table == NULL) {
        printf("\nProblem with memory allocating\n");
        exit(0);
    }

    help_table = malloc(i * sizeof (char*));
    for (ii = 0; ii < i; ii++) {
        help_table[ii] = (char*) malloc(j * sizeof (char));
    }
    if (help_table == NULL) {
        printf("\nProblem with memory allocating\n");
        exit(0);
    }


    for (ii = 0; ii < i; ii++) { //arxikopoihsh twn pinakwn
        for (jj = 0; jj < j; jj++) {
            p1.real_table[ii][jj] = '.';
            p2.real_table[ii][jj] = '.';
            p1.table[ii][jj] = '.';
            p2.table[ii][jj] = '.';
        }
    }

    //ekxwrhsh twn arxikwn sumvolwn sta ploia ...
    a1.pos = 5;
    a1.points = 1;
    a1.symbol = 'A';
    a2.pos = 5;
    a2.points = 1;
    a2.symbol = 'A';
    b1.pos = 4;
    b1.points = 2;
    b1.symbol = 'B';
    b2.pos = 4;
    b2.points = 2;
    b2.symbol = 'B';
    s1.pos = 3;
    s1.points = 4;
    s1.symbol = 'S';
    s2.pos = 3;
    s2.points = 4;
    s2.symbol = 'S';
    d1.pos = 3;
    d1.points = 4;
    d1.symbol = 'D';
    d2.pos = 3;
    d2.points = 4;
    d2.symbol = 'D';
    c1.pos = 2;
    c1.points = 5;
    c1.symbol = 'C';
    c2.pos = 2;
    c2.points = 5;
    c2.symbol = 'C';

    a1.damage = 0;
    a2.damage = 0;
    b1.damage = 0;
    b2.damage = 0;
    s1.damage = 0;
    s2.damage = 0;
    d1.damage = 0;
    d2.damage = 0;
    c1.damage = 0;
    c2.damage = 0;

    p1.sh[0] = &a1;
    p1.sh[1] = &b1;
    p1.sh[2] = &c1;
    p1.sh[3] = &d1;
    p1.sh[4] = &s1;

    p2.sh[0] = &a2;
    p2.sh[1] = &b2;
    p2.sh[2] = &c2;
    p2.sh[3] = &d2;
    p2.sh[4] = &s2;
    p1.score = 0;
    p2.score = 0;

    srand(time(NULL)); //xrhsimopoietai gia na arxikopoietai h gennhtria twn tuxaiwn ari8mwn ka8e fora pou kaleitai h rand()

    printf("\n%s do you want to place your ships?If yes,press 1,otherwise press 0\n", p1.name);
    //Topo8ethsh twn ploiwn tou p1 sto antipalo tamplo.Rwtatai an 8a ta topo8ethsei aftos.
    //Oi parametroi ths sunarthshs 8a ekshgh8oun meta alla to vasikotero einai oti h teleftaia parametros ekfrazei thn tuxaiothta
    // (0 an topo8etountai kanonika,1 an topo8etountai tuxaia)
    scanf("%d", &p1_place_ships);
    printf("p1 place=%d\n", p1_place_ships);
    if (p1_place_ships == 1) {
        printf("\n Aircraft carrier...");
        place_result = placeShip(&a1, &p2, i, j, 0);
        while (place_result == 0) { //ka8e fora ginetai elegxos gia na einai alh8hs h tmh epistrofhs
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&a1, &p2, i, j, 0);
        }

        printf("\nBattleship...");
        place_result = placeShip(&b1, &p2, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&b1, &p2, i, j, 0);
        }

        printf("\n Submarine...");
        place_result = placeShip(&s1, &p2, i, j, 0);

        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&s1, &p2, i, j, 0);
        }
        printf("\n Destroyer...");
        place_result = placeShip(&d1, &p2, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&d1, &p2, i, j, 0);
        }

        printf("\n Cruiser...");
        place_result = placeShip(&c1, &p2, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&c1, &p2, i, j, 0);
        }
    } else if (p1_place_ships == 0) { //tuxaia topo8ethsh

        place_result = placeShip(&a1, &p2, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&a1, &p2, i, j, 1);
        }
        place_result = placeShip(&b1, &p2, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&b1, &p2, i, j, 1);
        }
        place_result = placeShip(&s1, &p2, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&s1, &p2, i, j, 1);
        }
        place_result = placeShip(&d1, &p2, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&d1, &p2, i, j, 1);
        }
        place_result = placeShip(&c1, &p2, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&c1, &p2, i, j, 1);
        }
    }

    //ligo diaforetiko apthn periptwsh tou player1 ,ka8ws arxika elegxetai an o paixths einai o to pc h oxi.        
    p2_random_placing = 0;

    if (p2_choice == 1) {
        printf("%s,are you going to place the ships manually?Press 1 if yes", p2.name);
        scanf("%d", &p2_random_placing);
    }

    if ((p2_random_placing != 1) || (p2_choice == 0)) {
        place_result = placeShip(&a2, &p1, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&a2, &p1, i, j, 1);
        }
        place_result = placeShip(&b2, &p1, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&b2, &p1, i, j, 1);
        }
        place_result = placeShip(&s2, &p1, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&s2, &p1, i, j, 1);
        }
        place_result = placeShip(&d2, &p1, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&d2, &p1, i, j, 1);
        }
        place_result = placeShip(&c2, &p1, i, j, 1);
        while (place_result == 0) {
            place_result = placeShip(&c2, &p1, i, j, 1);
        }
    }



    if (p2_random_placing == 1) {
        place_result = placeShip(&a2, &p1, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&a2, &p1, i, j, 0);
        }
        place_result = placeShip(&b2, &p1, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&b2, &p1, i, j, 0);
        }
        place_result = placeShip(&s2, &p1, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&s2, &p1, i, j, 0);
        }
        place_result = placeShip(&d2, &p1, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&d2, &p1, i, j, 0);
        }
        place_result = placeShip(&c2, &p1, i, j, 0);
        while (place_result == 0) {
            printf("Invalid location.Please try again\n");
            place_result = placeShip(&c2, &p1, i, j, 0);
        }
    }
    print(p1, i, j, 1);
    print(p2, i, j, 1);

    //......................................MAIN GAME......................................................................

    current_turn = 0;

    first_player = rand() % 10 + 1;
    if (first_player <= 5) {
        printf("\n%s plays first!\n", p1.name);
        for (i1 = 0; i1 < turns; i1++) {
            printf("\nTurn:%d\n", current_turn);
            print(p2, i, j, 0);
            printf("\n%s,Enter your move!You have %d points\n", p1.name, p1.score);
            scanf("%s", input);
            while ((input != "x")&&(input != "h")&&(convertToInt(input) > i)&&(atoi(input) - 1) > j) {
                printf("\nWrong move!Please try again.");
                scanf("%s", &input);
            }
            if (strcmp(input, "x") == 0) {
                showResults(i, j);
                exit(0);
            } else if (strcmp(input, "h") == 0) {
                help(p2, i, j);

            } else {
                successful_hit = processMove(&p1, &p2, i, j, input, 1);
                while (successful_hit == 1) {
                    successful_hit = processMove(&p1, &p2, i, j, input, 1);
                }
            }
            print(p1, i, j, 0);
            if (p2_choice == 1) {
                printf("\n%s ,enter you move!You have %d points\n", p2.name, p2.score);
                scanf("%s", input);
                while ((input != "x")&&(input != "h")&&(convertToInt(input) > i)&&(atoi(input) - 1) > j) {
                    printf("\nWrong move!Please try again.");
                    scanf("%s", &input);
                }
                if (strcmp(input, "x") == 0) {
                    showResults(i, j);
                    exit(0);
                } else if (strcmp(input, "h") == 0) {
                    help(p2, i, j);

                } else {
                    successful_hit = processMove(&p2, &p1, i, j, input, 2);
                    while (successful_hit == 1) {
                        successful_hit = processMove(&p2, &p1, i, j, input, 2);
                    }
                }
            } else {
                ai_row = rand() % i;
                ai_col = rand() % j;
                successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col);
                while (successful_AI_hit == 1) {
                    if ((ai_row + 1 > 0 && ai_row + 1 < i) && (ai_col > 0 && ai_col < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row + 1, ai_col);
                    } else if ((ai_row - 1 > 0 && ai_row - 1 < i) && (ai_col > 0 && ai_col < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row - 1, ai_col);
                    } else if ((ai_row > 0 && ai_row < i) && (ai_col - 1 > 0 && ai_col - 1 < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col - 1);
                    } else
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col + 1);



                }


            }
            current_turn = current_turn + 1;
            if(current_turn==turns) showResults(i,j);
        }

    } else if (first_player > 5) {
        printf("%s plays first!\n", p2.name);
        for (i1 = 0; i1 < turns; i1++) {
            printf("\nCurrent turn:%d\n", current_turn);
            if (p2_choice == 1) {
                printf("\n%s ,enter you move!You have %d points\n", p2.name, p2.score);
                scanf("%s", input);
                while ((input != "x")&&(input != "h")&&(convertToInt(input) > i)&&(atoi(input) - 1) > j) {
                    printf("\nWrong move!Please try again.");
                    scanf("%s", &input);
                }
                if (strcmp(input, "x") == 0) {
                    showResults(i, j);
                    exit(0);
                } else if (strcmp(input, "h") == 0) {
                    help(p2, i, j);

                } else {
                    successful_hit = processMove(&p2, &p1, i, j, input, 2);
                    while (successful_hit == 1) {
                        successful_hit = processMove(&p2, &p1, i, j, input, 2);
                    }
                }
            } else {

                ai_row = rand() % i;
                ai_col = rand() % j;
                successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col);
                while (successful_AI_hit == 1) {
                    if ((ai_row + 1 > 0 && ai_row + 1 < i) && (ai_col > 0 && ai_col < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row + 1, ai_col);
                    } else if ((ai_row - 1 > 0 && ai_row - 1 < i) && (ai_col > 0 && ai_col < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row - 1, ai_col);
                    } else if ((ai_row > 0 && ai_row < i) && (ai_col - 1 > 0 && ai_col - 1 < j)) {
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col - 1);
                    } else
                        successful_AI_hit = processPCMove(&p2, &p1, i, j, ai_row, ai_col + 1);
                }
            }
            print(p2, i, j, 0);
            printf("\n%s,Enter your move!You have %d points\n", p1.name, p1.score);
            scanf("%s", input);
            *pp = input[1];
            while ((input != "x")&&(input != "h")&&(convertToInt(input) > i)&&(atoi(pp) - 1) > j) {
                printf("\nWrong move!Please try again.");
                scanf("%s", &input);
            }
            if (strcmp(input, "x") == 0) {
                showResults(i, j);
            } else if (strcmp(input, "h") == 0) {
                help(p2, i, j);

            } else {
                successful_hit = processMove(&p1, &p2, i, j, input, 2);
                endgame_check(i, j);
                while (successful_hit == 1) {
                    printf("\nEnter a new move!\n");
                    scanf("%s", &input);
                    while ((convertToInt(input) > i)&&(atoi(pp) - 1) > j) {
                        printf("\nWrong move!Please try again.");
                        scanf("%s", &input);
                    }
                    successful_hit = processMove(&p1, &p2, i, j, input, 2);
                    endgame_check(i, j); //
                }
            }

            current_turn = current_turn + 1;
            if(current_turn==turns) showResults(i,j);
        }
    }

    showResults(i, j);

}

int placeShip(struct ship* s, struct players* p, int rows, int cols, int random) {
    //sunarthsh pou exei ws parametrous to ploio gia to opoio 8a ginei prospa8eia na eisax8ei,thn domh tou antipalou paixth,tis grammes kai tis sthles tou tamplo kai 
    //mia parametro random h opoia ekfrazei thn tuxaiothta,dhladh an einai 1 to ploio topo8eteitai tuxaia
    char dir; //katef8unsh 
    int i = 0;
    int j = 0;
    int free_pos, r, c, rand_dir;
    free_pos = 0; //r kai c:grammes kai sthles pou dinei o xrhsths,i kai j xrhsimopoiountai stis epanalhpseis
    //to free_pos metra tis elef8eres 8eseis panw h deksia tou ploiou analoga me thn topo8ethsh tou kai prepei na nai iso me to ship.pos gia na eisax8ei to ploio
    //printf("Positioning %s\n", p->name);
    if (random == 0) { //An 8elei o xrhsths na to topo8ethsei kanonika...
        printf("\nEnter the direction of the ship for %s.Enter H for Horizontal or V for vertical", p->name);
        scanf("%c", &dir);

        while ((dir != 'V')&&(dir != 'H')) { //elegxos or8othtas timhs ths katef8unshs
            printf("Enter a correct direction!\n");
            scanf("%c", &dir);
        }

        printf("\nEnter the position of the bow.Enter the row first and then the column");
        printf("\nRows:");
        scanf("%d", &r);
        while (r >= rows) { //elegxos gia na mhn vgei ektos pinaka 
            printf("Invalid row,please try again");
            scanf("%d", &r);
        }
        printf("\nColumns:");
        scanf("%d", &c);
        while (c >= cols) { //elegxos gia na mhn vgei ektos pinaka 
            printf("\nInvalid column,please try again");
            scanf("%d", &c);
        }
    }
    if (random == 1) { //tuxaia topo8ethsh...
        r = rand() % rows;
        c = rand() % cols;
        rand_dir = rand() % 2 + 1;

        if (rand_dir == 1) {
            dir = 'V';
        } else dir = 'H';
    }

    if (dir == 'V') {
        // printf("Vertical\n");
        if (s->symbol == 'A') {
            if (r + 5 >= rows) return 0;
            for (i = r; i < r + 5; i++) {

                if (p->real_table[i][c] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'B') {
            if (r + 4 >= rows) return 0;
            for (i = r; i < r + 4; i++) {
                if (p->real_table[i][c] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'S') {
            if (r + 3 >= rows) return 0;
            for (i = r; i < r + 3; i++) {
                if (p->real_table[i][c] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'D') {
            if (r + 3 >= rows) return 0;
            for (i = r; i < r + 3; i++) {
                if (p->real_table[i][c] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else {
            if (r + 2 >= rows) return 0;
            for (i = r; i < r + 2; i++) {
                if (p->real_table[i][c] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        }

        //Horizontal       
    } else if (dir == 'H') {
        //  
        if (s->symbol == 'A') {
            if (c + 5 >= cols) return 0;
            for (j = c; j < c + 5; j++) {
                if (p->real_table[i][j] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'B') {
            if (c + 4 >= cols) return 0;
            for (j = c; j < c + 4; j++) {
                if (p->real_table[i][j] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'S') {
            if (c + 3 >= cols) return 0;
            for (j = c; j < c + 3; j++) {
                if (p->real_table[i][j] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else if (s->symbol == 'D') {
            if (c + 3 >= cols) return 0;
            for (j = c; j < c + 3; j++) {
                if (p->real_table[i][j] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        } else {
            for (j = c; j < c + 2; j++) {
                if (c + 2 >= cols) return 0;
                if (p->real_table[r][j] == '.') {
                    free_pos = free_pos + 1;
                } else return 0;
            }
        }
    }
    i = r;
    // if(s.pos=free_pos){
    if (dir == 'V') {
        for (i = r; i < r + s->pos; i++) {
            p->real_table[i][c] = s->symbol;

        }
    } else if (dir == 'H') {
        for (j = c; j < c + s->pos; j++) {
            p->real_table[r][j] = s->symbol;
        }
    }
    s->bow[0] = r;
    s->bow[1] = c;
    return 1; // }  
}

void print(struct players p, int m, int n, int real) {
    int i, j;

    printf("   ");
    for (i = 0; i < n; i++) {
        printf("%d  ", i + 1);
    }

    printf("\n");

    for (i = 0; i < n + 3; i++) printf("---");

    printf("\n");

    for (i = 0; i < m; i++) {
        printf("%c| ", 'A' + i);
        for (j = 0; j < n; j++) {
            if (real == 1) {
                if (j < 10) printf("%c  ", p.real_table[i][j]);
                else printf("  %c", p.real_table[i][j]);
            } else if (real == 0) {
                if (j < 10) printf("%c  ", p.table[i][j]);
                else printf("  %c", p.table[i][j]);
            } else if (real == 2) {
                if (j < 10) printf("%c  ", result_table1[i][j]);
                else printf("  %c", result_table1[i][j]);
            } else {
                if (j < 10) printf("%c  ", result_table2[i][j]);
                else printf("  %c", result_table2[i][j]);
            }
        }
        printf("\n");
    }

}

int processMove(struct players* p, struct players* opponent, int m, int n, char input[3], int who_plays) {
    int rows = convertToInt(input);
    char *p1 = &input[1];
    int cols = atoi(p1) - 1;
    if ((opponent->real_table[rows][cols] == '.')&&(opponent->table[rows][cols] = '.')) {
        printf("\n You have hit no targets \n");
        opponent->table[rows][cols] = 'o';
        return 0;
    } else if ((opponent->real_table[rows][cols] == '.')&&(opponent->table[rows][cols] = 'o')) {
        printf("You have already chosen this position\n");
        opponent->table[rows][cols] = 'o';
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'A')&&(opponent->table[rows][cols] == '.')) {
        printf("You have hit a target!\n");
        opponent->table[rows][cols] = 'x';
        if (who_plays == 1) {
            a2.damage = a2.damage + 1;
            if (a2.damage == a2.points) {
                p->score = p->score + 1;
                printf("\nAn aircraft Carrier has just sunk!\n");
                printf("\nYou get one more extra move!\n");
            }
            return 1;
        } else {
            a1.damage = a1.damage + 1;
            if (a1.damage == a1.points) {
                p->score = p->score + 1;
                printf("\nAn aircraft Carrier has just sunk!\n");
                printf("\nYou get one more extra move!\n");
            }
            return 1;
        }

    } else if ((opponent->real_table[rows][cols] == 'B')&&(opponent->table[rows][cols] == '.')) {
        printf("You have hit a target!\n");
        opponent->table[rows][cols] = 'x';
        if (who_plays == 1) {
            b2.damage = b2.damage + 1;
            if (b2.damage == b2.points) {
                p->score = p->score + 2;
                printf("\nA Battleship has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        } else {
            b1.damage = b1.damage + 1;
            if (b1.damage == b1.points) {
                p->score = p->score + 2;
                printf("\nA Battleship has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        }

    } else if ((opponent->real_table[rows][cols] == 'C')&&(opponent->table[rows][cols] == '.')) {
        printf("You have hit a target!\n");
        opponent->table[rows][cols] = 'x';
        if (who_plays == 1) {
            c2.damage = c2.damage + 1;
            if (c2.damage == c2.points) {
                p->score = p->score + 5;
                printf("\nA Cruiser has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;

        } else {
            c1.damage = c1.damage + 1;
            if (c1.damage == c1.points) {
                p->score = p->score + 5;
                printf("\nA Cruiser has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        }
    } else if ((opponent->real_table[rows][cols] == 'D')&&(opponent->table[rows][cols] == '.')) {
        printf("You have hit a target!\n");
        opponent->table[rows][cols] = 'x';
        if (who_plays == 1) {
            d2.damage = d2.damage + 1;
            if (d2.damage == d2.points) {
                p->score = p->score + 4;
                printf("\nA Destroyer has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        } else {
            d1.damage = d1.damage + 1;
            if (d1.damage == d1.points) {
                p->score = p->score + 4;
                printf("\nA Cruiser has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        }

    } else if ((opponent->real_table[rows][cols] == 'S')&&(opponent->table[rows][cols] == '.')) {
        printf("You have hit a target!\n");
        opponent->table[rows][cols] = 'x';
        if (who_plays == 1) {
            s2.damage = s2.damage + 1;
            if (s2.damage == s2.points) {
                p->score = p->score + 4;
                printf("\nA Submarine has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        } else {
            s1.damage = s1.damage + 1;
            if (s1.damage == s1.points) {
                p->score = p->score + 4;
                printf("\nA submarine has just sunk!\n");
            }
            printf("You get one more extra move!");
            return 1;
        }
    } else if ((opponent->real_table[rows][cols] == 'A')&&(opponent->table[rows][cols] == 'x')) {
        printf("You have already hit this target!Try hitting a near position next time! \n");
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'B')&&(opponent->table[rows][cols] == 'x')) {
        printf("You have already hit this target!Try hitting a near position next time! \n");
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'C')&&(opponent->table[rows][cols] == 'x')) {
        printf("You have already hit this target!Try hitting a near position next time! \n");
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'D')&&(opponent->table[rows][cols] == 'x')) {
        printf("You have already hit this target!Try hitting a near position next time! \n");
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'S')&&(opponent->table[rows][cols] == 'x')) {
        printf("You have already hit this target!Try hitting a near position next time! \n");
        return 0;
    }

}

void help(struct players the_player, int m, int n) {
    int size;
    int i = 0, j, random, x, y, len;
    int i1 = 0, j1 = 0;
    char ships[5];
    struct ship* s;

    char **h_table;

    h_table = (char**) malloc(m * sizeof (char*));

    for (i = 0; i < m; i++) {
        h_table[i] = (char*) malloc(n * sizeof (char));
    }

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            h_table[i][j] = the_player.table[i][j];

    for (i = 0; i < 5; i++)
        if (the_player.sh[i]->damage == 0) {

            s = the_player.sh[i];

            break;
        }

    x = s->bow[0]; //grammi
    y = s->bow[1];
    len = s->pos;

    //printf("found %c at (%d, %d) len=%d\n", s->symbol, x, y, len);

    if (s->dir == 'H') {
        for (i = y; i < y + len; i++) {
            h_table[x][i] = s->symbol + 32;
        }
    } else {
        for (i = x; i < x + len; i++) {
            h_table[i][y] = s->symbol + 32;
        }
    }


    // print
    printf("   ");
    for (i = 0; i < n; i++) {
        printf("%d  ", i + 1);
    }

    printf("\n");

    for (i = 0; i < n + 3; i++) printf("---");

    printf("\n");

    for (i = 0; i < m; i++) {
        printf("%c| ", 'A' + i);
        for (j = 0; j < n; j++) {
            printf("%c  ", h_table[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < m; i++)free(h_table[i]);
    free(h_table);
}

int convertToInt(char input[]) {
    char c = 'A';
    int i = 0;
    while (c < input[0]) {
        c = c + 1;
        i = i + 1;
    }
    return i;
}

void endgame_check(int m, int n) {
    int i, j, sum = 0, sum2 = 0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (p1.table[i][j] == 'x') sum = sum + 1;
        }
    }
    if (sum == 17) {
        printf("\n%s wins!!!!\n", p2.name);
        showResults(m, n);
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (p2.table[i][j] == 'x') sum2 = sum2 + 1;
        }
    }

    if (sum2 == 17) {
        printf("\n%s wins!!!!\n", p1.name);
        showResults(m, n);
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (p2.table[i][j] == 'x') sum2 = sum2 + 1;
        }
    }

    return;
}

void showResults(int m, int n) {
    printf("\n            ENDGAME!                  \n");
    printf("\n            RESULTS!                  \n");
    int i = 0, j = 0;
    result_table1 = (char**) malloc(m * sizeof (char*));
    result_table2 = (char**) malloc(m * sizeof (char*));
    for (i = 0; i < m; i++) {
        result_table1[i] = (char*) malloc(n * sizeof (char));
    }

    for (i = 0; i < m; i++) {
        result_table2[i] = (char*) malloc(n * sizeof (char));
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            result_table1 = p1.table;
        }
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            result_table2 = p1.table;
        }
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (p1.real_table[i][j] == 'A') {
                if (a1.damage = 0) result_table1[i][j] = 'a';
                else result_table1[i][j] = 'A';
            } else if (p1.real_table[i][j] == 'B') {
                if (a1.damage = 0) result_table1[i][j] = 'B';
                else result_table1[i][j] = 'b';
            } else if (p1.real_table[i][j] == 'C') {
                if (a1.damage = 0) result_table1[i][j] = 'C';
                else result_table1[i][j] = 'c';

            } else if (p1.real_table[i][j] == 'D') {
                if (a1.damage = 0) result_table1[i][j] = 'd';
                else result_table1[i][j] = 'D';
            } else if (p1.real_table[i][j] == 'S') {
                if (a1.damage = 0) result_table1[i][j] = 's';
                else result_table1[i][j] = 'S';

            }
        }
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (p2.real_table[i][j] == 'A') {
                if (a2.damage = 0) result_table2[i][j] = 'a';
                else result_table2[i][j] = 'A';
            } else if (p2.real_table[i][j] == 'B') {
                if (a2.damage = 0) result_table2[i][j] = 'B';
                else result_table2[i][j] = 'b';
            } else if (p2.real_table[i][j] == 'C') {
                if (a2.damage = 0) result_table2[i][j] = 'C';
                else result_table2[i][j] = 'c';

            } else if (p2.real_table[i][j] == 'D') {
                if (a2.damage = 0) result_table2[i][j] = 'd';
                else result_table2[i][j] = 'D';
            } else if (p1.real_table[i][j] == 'S') {
                if (a1.damage = 0) result_table1[i][j] = 's';
                else result_table1[i][j] = 'S';

            }
        }
    }
    printf("\n%s's table: \n", p1.name);
    print(p1, m, n, 2);
    printf("\n%s's table: \n", p2.name);
    print(p2, m, n, 3);

    printf("\n\n\n");

    printf("%s's points:%d", p1.name, p1.score);
    printf("%s's points:%d", p2.name, p2.score);

    if (p1.score > p2.score) {
        printf("\n %s wins!!!Congratulations!\n", p1.name);
    } else if (p1.score < p2.score) {
        printf("\n %s wins!!!Congratulations!\n", p2.name);
    } else printf("The game ended in a draw!");

    free_function(m, n);
    exit(0);
}

void free_function(int m, int n) {
    int i = 0, j = 0;

    for (i = 0; i < m; i++)free(p1.table[i]);
    free(p1.table);
    for (i = 0; i < m; i++)free(p1.table[i]);
    free(p1.table);
    for (i = 0; i < m; i++)free(p2.table[i]);
    free(p2.table);
    for (i = 0; i < m; i++)free(p2.table[i]);
    free(p2.table);
    for (i = 0; i < m; i++)free(result_table1[i]);
    free(result_table1);
    for (i = 0; i < m; i++)free(result_table2[i]);
    free(result_table2);
}

int processPCMove(struct players* p, struct players* opponent, int m, int n, int rows, int cols) {
    if ((opponent->real_table[rows][cols] == '.')&&(opponent->table[rows][cols] = '.')) {
        printf("\n PC has hit no targets! \n");
        opponent->table[rows][cols] = 'o';
        return 0;
    } else if ((opponent->real_table[rows][cols] == '.')&&(opponent->table[rows][cols] = 'o')) {
        opponent->table[rows][cols] = 'o';
        return 0;
    } else if ((opponent->real_table[rows][cols] == 'A')&&(opponent->table[rows][cols] == '.')) {
        printf("PC has hit a target!\n");
        opponent->table[rows][cols] = 'x';
        a1.damage = a1.damage + 1;
        if (a1.damage == a1.points) {
            p->score = p->score + 1;
            printf("\nAn aircraft Carrier has just sunk!\n");
            printf("\nYou get one more extra move!\n");
        }
        return 1;
    } else if ((opponent->real_table[rows][cols] == 'B')&&(opponent->table[rows][cols] == '.')) {
        printf("PC has hit a target!\n");
        opponent->table[rows][cols] = 'x';
        b1.damage = b1.damage + 1;
        if (b1.damage == b1.points) {
            p->score = p->score + 2;
            printf("\nA Battleship has just sunk!\n");
        }
        printf("PC gets one more extra move!");
        return 1;
    } else if ((opponent->real_table[rows][cols] == 'C')&&(opponent->table[rows][cols] == '.')) {
        printf("PC has hit a target!\n");
        opponent->table[rows][cols] = 'x';
        c1.damage = c1.damage + 1;
        if (c1.damage == c1.points) {
            p->score = p->score + 5;
            printf("\nA Cruiser has just sunk!\n");
        }
        printf("PC gets one more extra move!");
        return 1;
    } else if ((opponent->real_table[rows][cols] == 'D')&&(opponent->table[rows][cols] == '.')) {
        printf("PC has hit a target!\n");
        opponent->table[rows][cols] = 'x';
        {
            d1.damage = d1.damage + 1;
            if (d1.damage == d1.points) {
                p->score = p->score + 4;
                printf("\nA Cruiser has just sunk!\n");
            }
            printf("PC gets one more extra move!");
            return 1;
        }
    } else if ((opponent->real_table[rows][cols] == 'S')&&(opponent->table[rows][cols] == '.')) {
        printf("PC has hit a target!\n");
        opponent->table[rows][cols] = 'x';
        {
            s1.damage = s1.damage + 1;
            if (s1.damage == s1.points) {
                p->score = p->score + 4;
                printf("\nA submarine has just sunk!\n");
            }
            printf("PC gets one more extra move!");
            return 1;
        }
    } else if ((opponent->real_table[rows][cols] == 'A')&&(opponent->table[rows][cols] == 'x')) return 0;
    else if ((opponent->real_table[rows][cols] == 'B')&&(opponent->table[rows][cols] == 'x')) return 0;
    else if ((opponent->real_table[rows][cols] == 'C')&&(opponent->table[rows][cols] == 'x')) return 0;
    else if ((opponent->real_table[rows][cols] == 'D')&&(opponent->table[rows][cols] == 'x')) return 0;
    else if ((opponent->real_table[rows][cols] == 'S')&&(opponent->table[rows][cols] == 'x')) return 0;
}
