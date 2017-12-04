#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

//gcc -o sdl1 main.c `sdl-config --cflags --libs` -lSDL_ttf -lmysqlclient -I/usr/local/mysql/include

int main(int argc, char *argv[]){
    
    /*
            Initialisation des variables
    */

    SDL_Event event;
    SDL_Surface *screen, *p1, *p2, *ball, *texte;
    SDL_Rect positionP1;
    SDL_Rect positionP2;
    SDL_Rect positionBall; 
    SDL_Rect positionText; 
    SDL_Color textcolor = {200, 200, 200};
    TTF_Font *police = NULL;
    Uint8 *keystate;
    char score[20] = "";
    int keypressed = 0;
    int xvar = 1;
    int yvar = 1;
    int xort = 2;
    int yort = 0;
    int continuer = 1;
    int scoreP1 = 0;
    int scoreP2 = 0;
    int newBall = 1;
    int ia = 0;
    /*
            Verification des valeurs entrés en parramètres
    */
    if(argc == 2){
        printf("%s\n", argv[1]);
        if(strcmp(argv[1],"-ia") == 0){
            ia = 1;
            printf("ia");
        }
        printf("%d\n",ia);
    }

    /*
            Verification de la présence de SDL
    */

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Impossible d'initialiser SDL :  %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(TTF_Init() < 0){
        printf("Impossible d'initialiser SDL_ttf : %s", TTF_GetError());
        return EXIT_FAILURE;
    }

    /*
            Attribution des valuers aux variables SDL
    */

    atexit( SDL_Quit ); 
    police = TTF_OpenFont("arial.ttf", 30);
    if (police == NULL){
        fprintf(stderr, "Police non trouvée\n");
        return EXIT_FAILURE;
    }
    screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE );
    p1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 120, 10, 0, 0, 0, 0);
    p2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 120, 10, 0, 0, 0, 0);
    ball = SDL_CreateRGBSurface(SDL_HWSURFACE, 15, 15, 10, 0, 0, 0, 0);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));


    /*
            Initialisaiton de la position des objets
    */

    positionP1.x = 50; 
    positionP1.y = 119;

    positionP2.x = 570; 
    positionP2.y = 119;

    positionBall.x = 310; 
    positionBall.y = 170;

    positionText.x = 280;
    positionText.y = 50;

    /*
            Placement initial des objets sur l'écrent
    */

    SDL_FillRect(p1, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); 
    SDL_BlitSurface(p1, NULL, screen, &positionP1);

    SDL_FillRect(p2, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); 
    SDL_BlitSurface(p2, NULL, screen, &positionP2);

    SDL_FillRect(ball, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); 
    SDL_BlitSurface(ball, NULL, screen, &positionBall);


    if(screen == NULL){
        printf( "Affichage impossible: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }   

    SDL_Flip(screen);

    /*
            Demarage de la boucle de jeu
    */

    while(continuer){

        if(newBall == 1){
            sleep(1);
            newBall = 0;
        }

        /*
            Gestion des colisions
        */

        if(positionBall.x <= 0){
            xvar = 1;
            scoreP2 +=1;
            newBall = 1;
            yort = 0;
            positionBall.x = 310; 
            positionBall.y = 170;
        }
        else if (positionBall.x >= 625){
            xvar = -1;
            scoreP1 +=1;
            newBall = 1;
            yort = 0;
            positionBall.x = 310; 
            positionBall.y = 170;
        }
        if(positionBall.y <= 0){
            yvar = 1;
        }
        else if (positionBall.y >= 465){
            yvar = -1;
        }
        if(positionBall.x >= 560 && positionBall.x <= (560)){
            if(xvar == 1){
                if(positionBall.y >= (positionP2.y-5) && positionBall.y <= (positionP2.y + 20)){
                    yvar = -1;
                    xort = 2;
                    yort = 2;
                    xvar = -1;
                }
                else if(positionBall.y >= (positionP2.y + 21) && positionBall.y <= (positionP2.y + 50)){
                    yvar = -1;
                    xort = 2;
                    yort = 1;
                    xvar = -1;
                }
                else if(positionBall.y >= (positionP2.y + 51) && positionBall.y <= (positionP2.y + 70)){
                    yvar = -1;
                    yort = 0;
                    xort = 2;
                    xvar = -1;
                }
                else if(positionBall.y >= (positionP2.y + 71) && positionBall.y <= (positionP2.y + 100)){
                    yvar = 1;
                    xort = 2;
                    yort = 1;
                    xvar = -1;
                }
                else if(positionBall.y >= (positionP2.y + 101) && positionBall.y <= (positionP2.y + 125)){
                    yvar = 1;
                    xort = 2;
                    yort = 2;
                    xvar = -1;
                }
            }
        }
        if(positionBall.x <= 60 && positionBall.x >= (60)){
            if(xvar == -1){
                if(positionBall.y >= (positionP1.y -5) && positionBall.y <= (positionP1.y + 20)){
                    yvar = -1;
                    xort = 2;
                    yort = 2;
                    xvar = 1;
                }
                else if(positionBall.y >= (positionP1.y + 21) && positionBall.y <= (positionP1.y + 50)){
                    yvar = -1;
                    xort = 2;
                    yort = 1;
                    xvar = 1;
                }
                else if(positionBall.y >= (positionP1.y + 51) && positionBall.y <= (positionP1.y + 70)){
                    yvar = -1;
                    yort = 0;
                    xort = 2;
                    xvar = 1;
                }
                else if(positionBall.y >= (positionP1.y + 71) && positionBall.y <= (positionP1.y + 100)){
                    yvar = 1;
                    xort = 2;
                    yort = 1;
                    xvar = 1;
                }
                else if(positionBall.y >= (positionP1.y + 101) && positionBall.y <= (positionP1.y + 125)){
                    yvar = 1;
                    xort = 2;
                    yort = 2;
                    xvar = 1;
                }
            }
        }
        positionBall.x += (xvar * xort);
        positionBall.y += (yvar * yort);
        if(ia == 1) {
            if(positionP2.y > positionBall.y-30){
                positionP2.y -= 2;
            }
            else if(positionP2.y < positionBall.y-32){
                positionP2.y += 2;
            }
            if ( positionP2.y < 0 ) {
                positionP2.y = 0;
            }
            else if ( positionP2.y > 480 -120 ) {
                positionP2.y = 480 -120;
            }
        }

        /*
            Recupération des évènements
        */

        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_KEYDOWN){
                keypressed = 1;
            }
            if(event.type == SDL_KEYUP){
                keypressed = 0;
            }
            if(event.type == SDL_QUIT){
                continuer = 0;
            }
        }
        if(keypressed = 1){
            keystate = SDL_GetKeyState(NULL);
            if(ia == 0){
                if (keystate[SDLK_UP]){
                    positionP2.y -= 2;
                }
                else if(keystate[SDLK_DOWN]){
                    positionP2.y += 2;
                }
            }
            if (keystate[SDLK_z]){
                positionP1.y -= 2;
            }
            else if(keystate[SDLK_s]){
                positionP1.y += 2;
            }

            if ( positionP1.y < 0 ) {
                positionP1.y = 0;
            }
            else if ( positionP1.y > 480-120) {
                positionP1.y = 480 -120;
            }
            if ( positionP2.y < 0 ) {
                positionP2.y = 0;
            }
            else if ( positionP2.y > 480 -120 ) {
                positionP2.y = 480 -120;
            }
        }

        /*
            Affichage du score
        */

        sprintf(score,"%d     %d", scoreP1, scoreP2); 
        texte = TTF_RenderText_Blended(police, score, textcolor);

        /*
            Rafréchissement des objets
        */

        SDL_FillRect(screen, NULL, 0x000000);
        SDL_BlitSurface(texte, NULL, screen, &positionText);
        SDL_BlitSurface(p1, NULL, screen, &positionP1);
        SDL_BlitSurface(p2, NULL, screen, &positionP2);
        SDL_BlitSurface(ball, NULL, screen, &positionBall);
        SDL_Flip(screen);
        SDL_Delay(12);
    }
    TTF_CloseFont(police); 
    TTF_Quit();

    /*     //Do Not work with windows shell   
    MYSQL mysql;
    if(mysql_init(&mysql)==NULL)
    {
        printf("MYSQL non initialisé\n");
    }
    //mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    if(mysql_real_connect(&mysql,"localhost","root","root",NULL,0,NULL,0)) {
        if(mysql_select_db(&mysql,"pong")==0){
            printf( "Database Selected\n");
        }
        else{
            printf( "Failed to connect to Database: Error: %s\n",
            mysql_error(&mysql));
        }
        char requete[150] = "";
        sprintf(requete, "INSERT INTO scores (p1, p2) VALUES('%d','%d')", scoreP1, scoreP2);
        if(mysql_query(&mysql,requete)==0){
            printf( "Record Added\n");
        }
        else{
            printf( "Failed to add records: Error: %s\n",
            mysql_error(&mysql));
        }
        mysql_close(&mysql);
    }
    else {
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
    */
    return EXIT_SUCCESS;
}
