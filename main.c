#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#define maxi(x,y) (x<y)?y:x

//donnons à chaque piece un numero utile pour manipuler les pieces
#define kingAselect 1
#define dameA1 2
#define dameA2 3
#define dameA3 4
#define dameA4 5
#define dameA5 6
#define dameA6 7
#define dameA7 8
#define dameA8 9
#define dameB1 10
#define dameB2 11
#define dameB3 12
#define dameB4 13
#define dameB5 14
#define dameB6 15
#define dameB7 16
#define dameB8 17
#define kingBselect 18
#define pionA1 101
#define pionA2 102
#define pionA3 103
#define pionA4 104
#define pionA5 105
#define pionA6 106
#define pionA7 107
#define pionA8 108
#define pionA9 109
#define pionA10 110
#define pionA11 111
#define pionA12 112
#define pionA13 113
#define pionA14 114
#define pionA15 115
#define pionB1 116
#define pionB2 117
#define pionB3 118
#define pionB4 119
#define pionB5 120
#define pionB6 121
#define pionB7 122
#define pionB8 123
#define pionB9 124
#define pionB10 125
#define pionB11 126
#define pionB12 127
#define pionB13 128
#define pionB14 129
#define pionB15 130

//arguments shortcut pour reduire l'entet de quelque fonctions
#define arguments_supp_manger damesA,damesB,pionsA,pionsB
#define arguments_supp_manger_prototype SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB

//constantes permettant detection rapide des possibilite de deplacement
#define up_const 2
#define down_const 3
#define left_const 5
#define right_const 7
#define all_direction_const 210
#define no_direction_const 11// constan represente pas de possibilité de déplacement
//des positions en plus pour les pions et dames
#define up_left_const 2
#define up_right_const 7
#define down_left_const 5
#define down_right_const 3
/*
NB:possibilités de mouvement comme suite
up equivalent devisible par 2
down equivalent devisile par 3
left equivalent defvisible par 5
right equivalent devisible par 7
*/

typedef struct {
    int ligne; //ligne et colone permet de se localiser dans une matrice utile pour le jeu
    int colone;
    int possibilities;
    int poss_supp;//positions supplementaires pour les dames et pions
    int first_time_pion; //indique si le 1er mouvement pour le pion =1 (vrai)ou 0 (faux)
    int table_possibilties[7] = {11, 11, 11, 11, 11, 11, 11};//indique les possibilite pour lesdames ou parfois les pions 11 c'est no_direction
}position_matrice_etat;



void afficher_entourage_roi(SDL_Renderer** r, SDL_Rect posking, int chemins_valables);// affiche en vers les endroites accessibles pour le roi
void mouse_move_king(SDL_Rect *posking, position_matrice_etat* king_matrice);
void mouse_move_pion(SDL_Rect *pos_pion, SDL_Texture** tex, SDL_Texture* vert_pion_ref, SDL_Texture* hor_pion_ref, position_matrice_etat* pion_matrice, arguments_supp_manger_prototype);
void mouse_move_dame(SDL_Rect *posdame , SDL_Texture** tex, SDL_Texture* vert_dame_ref, SDL_Texture* hor_dame_ref, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype);
void move_dame_verticaly_y(int y, SDL_Rect *posdame, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype);
void move_dame_horizentaly_y(int y, SDL_Rect *posdame, position_matrice_etat* dame_matrice);
void move_dame_horizentaly_x(int x, SDL_Rect *posdame, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype);
void move_dame_verticaly_x(int x, SDL_Rect *posdame, position_matrice_etat* dame_matrice);
void move_dame_Vert2Hor(int x, int y, SDL_Rect *posdame, SDL_Texture** tex, SDL_Texture* hor_dame_ref, position_matrice_etat* dame_matrice);
void move_dame_Hor2Vert(int x, int y, SDL_Rect *posdame, SDL_Texture** tex, SDL_Texture* vert_dame_ref, position_matrice_etat* dame_matrice);

int check_mouse_clicked(int x, int y, SDL_Rect poskingA, SDL_Rect poskingB, SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB);
int check_on_kings(int x, int y, SDL_Rect poskingA, SDL_Rect poskingB);
int check_on_dames(int x, int y, SDL_Rect* damesA, SDL_Rect* damesB);
int check_on_pions(int x, int y, SDL_Rect* pionsA, SDL_Rect* pionsB);
int check_inborders(int x, int y);
int hor_ou_vert(int y);//verifie le y choisi s'agit d'une position vertical ou horizentale

void initialisation_matrice_jeu();
int matrice_de_jeu[15][15]; //declaration de matrice de jeu comme variable globale pour le projet
void visualisation();

void initialisation_positions_dans_matrice(position_matrice_etat* kingA_matrice, position_matrice_etat* kingB_matrice, position_matrice_etat* damesA_matrice, position_matrice_etat* damesB_matrice, position_matrice_etat* pionsA_matrice, position_matrice_etat* pionsB_matrice);
int verifie_possibilities_king(position_matrice_etat king_matrice);
void verifie_possibilities_dame(position_matrice_etat* dame_matrice);
void verifie_possibilities_supp(position_matrice_etat* dame_p_matrice);
void verifie_possibilities_pion(position_matrice_etat* pion_matrice);
void rectifie_dame_possibilities(int* table_poss_dame, int is_verticale);
void remove_friendlyfire(position_matrice_etat* dame_matrice);


void move_pion_verticaly_y(int y, SDL_Rect *posdame, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype);
void move_pion_verticaly_x(int x, SDL_Rect *posdame, position_matrice_etat* dame_matrice);
void move_pion_horizentaly_y(int y, SDL_Rect *posdame, position_matrice_etat* dame_matrice);
void move_pion_horizentaly_x(int x, SDL_Rect *posdame, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype);
void eaten(position_matrice_etat old_position , position_matrice_etat new_position, SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB);
void manger_piece(int i,int j, SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB);

int welcome(SDL_Renderer** r);
int echec_et_mat(position_matrice_etat king_matrice); //verifie l'echec et mat
int chercher_autour_roi(int valeur_cherche); //utile pour echec et mat
void gameover(SDL_Renderer** r, int numro_roi, Mix_Chunk* winner);


int convert2dame(position_matrice_etat matrice_pion, SDL_Rect* pion_coord, position_matrice_etat* matrice_des_dames, SDL_Rect * damesA);


int main(int argc, char *argv[]){
    restart:   //point de branchement

    position_matrice_etat kingA_matrice, kingB_matrice;//declaration variables de structure des rois dans la matrice de jeu puis les dames et pions
    position_matrice_etat damesA_matrice[8], damesB_matrice[8];
    position_matrice_etat pionsA_matrice[15], pionsB_matrice[15];

    initialisation_matrice_jeu();

    initialisation_positions_dans_matrice(&kingA_matrice, &kingB_matrice, damesA_matrice, damesB_matrice, pionsA_matrice, pionsB_matrice);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)//initialisation de SDL
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }


      //initialisation des parametres de mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
            fprintf(stderr,"Mix_OpenAudio: %s\n", Mix_GetError());
                exit(EXIT_FAILURE);
        }
        Mix_Music *intro_music = Mix_LoadMUS("sounds/intro_music.mp3");
        Mix_Music *background_music = Mix_LoadMUS("sounds/back_music.mp3");
        Mix_Chunk *clic = Mix_LoadWAV("sounds/clic.wav");
        Mix_Chunk *winner = Mix_LoadWAV("sounds/applod.wav");
        Mix_PlayMusic(intro_music, -1); //set introduction music




    //creation du window
    SDL_Window *screen=NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture_board;
    SDL_Surface *board = NULL;

	screen = SDL_CreateWindow("BULLTRICKER BY RIDDA & MOUACHI",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,640,SDL_WINDOW_SHOWN);
	if (screen == NULL) // Si l'ouverture a echoue, on le note et on arrete
    {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //creation de l'icon
	SDL_Surface* iconSurface;
	iconSurface = SDL_LoadBMP("images/icon.bmp");
	SDL_SetWindowIcon(screen, iconSurface);
	SDL_FreeSurface(iconSurface);


    //affichage de fond background
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    board = SDL_LoadBMP("images/board.bmp");
    texture_board = SDL_CreateTextureFromSurface(renderer, board);
    SDL_FreeSurface(board);
    SDL_Rect posPR{0, 0, 640, 640};
    SDL_RenderCopy(renderer, texture_board, NULL, &posPR);


    //creation de roi (coordonnee, image...)et liberationn des surface
    SDL_Surface *kingA=NULL,*kingB=NULL;
    kingA = SDL_LoadBMP("images/kingA.bmp");
    kingB = SDL_LoadBMP("images/kingB.bmp");

    SDL_Rect poskingA;
    poskingA.x = 292; poskingA.y = 497; poskingA.w = 54; poskingA.h = 54;
    SDL_Rect poskingB;
    poskingB.x = 292; poskingB.y = 88; poskingB.w = 54; poskingB.h = 54;
    SDL_Texture *kingAtex = SDL_CreateTextureFromSurface(renderer, kingA), *kingBtex = SDL_CreateTextureFromSurface(renderer, kingB);
    SDL_FreeSurface(kingA); SDL_FreeSurface(kingB);



    //creation des dames meme facon de kings sauf qu'il s'agit de des tableaux pour les variables
    int i = 0;
    SDL_Texture *damesAtex[8], *damesBtex[8], *damesBtexVertRef, *damesBtexHorRef, *damesAtexVertRef, *damesAtexHorRef;
    SDL_Surface *dameA = SDL_LoadBMP("images/dameVertA.bmp"), *dameB = SDL_LoadBMP("images/dameVertB.bmp");
    SDL_Surface *dameAhor = SDL_LoadBMP("images/dameHorA.bmp"), *dameBhor = SDL_LoadBMP("images/dameHorB.bmp");
    SDL_Rect damesA[8], damesB[8];
    for(i = 0; i < 8; i++){
        //mouvement suivant x ou y par +- 68 pour bien placer les dames
        damesA[i].x = 75 + i*68; damesA[i].y = 498; damesA[i].w = 14; damesA[i].h = 52;
        damesB[i].x = 75 + i*68; damesB[i].y = 90; damesB[i].w = 14; damesB[i].h = 52;
    }
    damesAtexVertRef = SDL_CreateTextureFromSurface(renderer, dameA);
    damesBtexVertRef = SDL_CreateTextureFromSurface(renderer, dameB);
    damesAtexHorRef = SDL_CreateTextureFromSurface(renderer, dameAhor);
    damesBtexHorRef = SDL_CreateTextureFromSurface(renderer, dameBhor);
    for (i = 0; i < 8; i++ ){
        damesAtex[i] = damesAtexVertRef;
        damesBtex[i] = damesBtexVertRef;
    }
    SDL_FreeSurface(dameAhor);
    SDL_FreeSurface(dameBhor);
    SDL_FreeSurface(dameA);
    SDL_FreeSurface(dameB);




    //creation des pions meme procedure que dames
    SDL_Texture *pionsAtex[15], *pionsBtex[15], *pionsBtexVertRef, *pionsBtexHorRef, *pionsAtexVertRef, *pionsAtexHorRef;
    SDL_Surface *pionA = SDL_LoadBMP("images/pionVertA.bmp"), *pionB = SDL_LoadBMP("images/pionVertB.bmp");
    SDL_Surface *pionAhor = SDL_LoadBMP("images/pionHorizA.bmp"), *pionBhor = SDL_LoadBMP("images/pionHorizB.bmp");
    SDL_Rect pionsA[15], pionsB[15];//les premier sont les horizentales
    for(i = 7; i < 15; i++){
        //mouvement suivant x ou y par +- 68
        pionsA[i].x = 75 + (i-7)*68; pionsA[i].y = 498 - 68; pionsA[i].w = 14; pionsA[i].h = 52;
        pionsB[i].x = 75 + (i-7)*68; pionsB[i].y = 90 + 68; pionsB[i].w = 14; pionsB[i].h = 52;
    }
    for( i=0;i<7;i++){
        pionsA[i].x = 90 +i*68; pionsA[i].y = 484; pionsA[i].w = 52; pionsA[i].h = 14;
        pionsB[i].x = 90 +i*68; pionsB[i].y = 144; pionsB[i].w = 52; pionsB[i].h = 14;
    }
    pionsAtexVertRef = SDL_CreateTextureFromSurface(renderer, pionA);
    pionsBtexVertRef = SDL_CreateTextureFromSurface(renderer, pionB);
    pionsAtexHorRef = SDL_CreateTextureFromSurface(renderer, pionAhor);
    pionsBtexHorRef = SDL_CreateTextureFromSurface(renderer, pionBhor);
    for (i = 7; i < 15; i++ ){
        pionsAtex[i] = pionsAtexVertRef;
        pionsBtex[i] = pionsBtexVertRef;
    }
    for( i=0;i<7;i++){
        pionsAtex[i] = pionsAtexHorRef;
        pionsBtex[i] = pionsBtexHorRef;
    }
    SDL_FreeSurface(pionAhor);
    SDL_FreeSurface(pionBhor);
    SDL_FreeSurface(pionA);
    SDL_FreeSurface(pionB);






    //creeation des filtre indiquant la selection des roi en vert
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);

    //welcome page
    int running=welcome(&renderer);

    //setting background music

    Mix_FreeMusic(intro_music);
    Mix_PlayMusic(background_music, -1);




    //main loop
    int selection;//variable qui stock la selection
    position_matrice_etat old_pos; //variable stock la position precedent de la piece deplacé
    int dame_converti_pion;
    int continuer = running;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {

            case SDL_QUIT:
                continuer = 0; break;
            case SDL_KEYDOWN://press s to end music in the background
                if(event.key.keysym.sym == SDLK_s)
                	Mix_FreeMusic(background_music);
            case SDL_MOUSEBUTTONDOWN:
                Mix_PlayChannel(-1, clic, 0);
                visualisation();
                selection = check_mouse_clicked(event.motion.x, event.motion.y,poskingA, poskingB, damesA, damesB, pionsA, pionsB);//cherche ce qui est selectionner
                if(selection == kingAselect){//kingA est selectionnee
                                kingA_matrice.possibilities = verifie_possibilities_king(kingA_matrice);//verifie ses positions valables
                                afficher_entourage_roi(&renderer, poskingA, kingA_matrice.possibilities);//afficher ses possibilites
                                mouse_move_king(&poskingA, &kingA_matrice); //mover le king
                                }
                else {  if(selection == kingBselect){ //kingB est selectionnee
                                kingB_matrice.possibilities = verifie_possibilities_king(kingB_matrice);
                                afficher_entourage_roi(&renderer, poskingB, kingB_matrice.possibilities);
                                mouse_move_king(&poskingB, &kingB_matrice);
                        }
                        else{   if((selection - dameA1)*(selection - dameA8) <=0 ){ //dameA est selectionee si selection entre valeur du dameA1 et dameA8
                                verifie_possibilities_dame(&(damesA_matrice[selection-dameA1]));
                                old_pos=damesA_matrice[selection-dameA1]; //sauvgardant sa position avant de le deplacer
                                mouse_move_dame(&(damesA[selection-dameA1]), &(damesAtex[selection-dameA1]), damesAtexVertRef, damesAtexHorRef, &(damesA_matrice[selection-dameA1]), arguments_supp_manger);
                                eaten(old_pos, damesA_matrice[selection-dameA1], damesA, damesB, pionsA, pionsB);//utilise la position corant et precedent pour chercher ce qu'il a pris

                                }else{  if((selection - 10)*(selection - 17) <= 0){//dameB selectionee
                                        verifie_possibilities_dame(&(damesB_matrice[selection-dameB1]));
                                        old_pos = damesB_matrice[selection-dameB1];
                                        mouse_move_dame(&(damesB[selection-10]), &(damesBtex[selection-10]), damesBtexVertRef, damesBtexHorRef, &(damesB_matrice[selection-10]), arguments_supp_manger);
                                        eaten(old_pos, damesB_matrice[selection-dameB1], damesA, damesB, pionsA, pionsB);

                                        }else{ if( (selection - pionA1)*(selection - pionA15) <= 0){//pionA
                                                verifie_possibilities_pion(&(pionsA_matrice[selection-pionA1]));
                                                old_pos = pionsA_matrice[selection-pionA1];
                                                mouse_move_pion(&(pionsA[selection-101]), &(pionsAtex[selection-101]), pionsAtexVertRef, pionsAtexHorRef, &(pionsA_matrice[selection-101]), arguments_supp_manger);
                                                eaten(old_pos, pionsA_matrice[selection-pionA1], damesA, damesB, pionsA, pionsB);
                                                if(pionsA_matrice[selection-pionA1].ligne == 0){
                                                        dame_converti_pion=convert2dame(pionsA_matrice[selection-pionA1], &(pionsA[selection-101]), damesA_matrice, damesA);
                                                        if(dame_converti_pion != -1)damesAtex[dame_converti_pion] = damesAtexHorRef;
                                                }

                                                }else{ if((selection - pionB1)*(selection - pionB15) <= 0){//pionB
                                                        verifie_possibilities_pion(&(pionsB_matrice[selection-116]));
                                                        old_pos=pionsB_matrice[selection-pionB1];
                                                        mouse_move_pion(&(pionsB[selection-116]), &(pionsBtex[selection-116]), pionsBtexVertRef, pionsBtexHorRef, &(pionsB_matrice[selection-116]), arguments_supp_manger);
                                                        eaten(old_pos, pionsB_matrice[selection-pionB1], damesA, damesB, pionsA, pionsB);
                                                        if(pionsB_matrice[selection-pionB1].ligne == 14){
                                                            dame_converti_pion = convert2dame(pionsB_matrice[selection-pionB1], &(pionsB[selection-pionB1]), damesB_matrice, damesB);
                                                                if(dame_converti_pion != -1)damesBtex[dame_converti_pion] = damesBtexHorRef;
                                                        }

                                                        }
                                                }
                                            }
                                        }
                            }
                    }


        }

    //affichage des pieces
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_board, NULL, &posPR);
    for(i = 0; i < 15; i++){
        SDL_RenderCopy(renderer, pionsAtex[i], NULL, &pionsA[i]);
        SDL_RenderCopy(renderer, pionsBtex[i], NULL, &pionsB[i]);
    }
    for(i = 0; i < 8; i++){
        SDL_RenderCopy(renderer, damesAtex[i], NULL, &damesA[i]);
        SDL_RenderCopy(renderer, damesBtex[i], NULL, &damesB[i]);
        }
    SDL_RenderCopy(renderer, kingAtex, NULL, &poskingA);
    SDL_RenderCopy(renderer, kingBtex, NULL, &poskingB);
    SDL_RenderPresent(renderer);
    if(echec_et_mat(kingA_matrice)){
            continuer = 0;
            gameover(&renderer, 1, winner);
    }
    if(echec_et_mat(kingB_matrice)){
            continuer = 0;
            gameover(&renderer, 2, winner);
    }

    }

    for( i = 0; i < 8; i++ ){
        SDL_DestroyTexture(damesAtex[i]);
        SDL_DestroyTexture(damesAtex[i]);
    }
    for(i=0;i<15;i++){
        SDL_DestroyTexture(pionsAtex[i]);
        SDL_DestroyTexture(pionsBtex[i]);
    }
    SDL_DestroyTexture(damesAtexVertRef);
    SDL_DestroyTexture(damesBtexVertRef);
    SDL_DestroyTexture(damesAtexHorRef);
    SDL_DestroyTexture(damesBtexHorRef);
    SDL_DestroyTexture(texture_board);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(background_music);
    Mix_FreeChunk(clic);
    Mix_FreeChunk(winner);

    SDL_DestroyWindow(screen);
    SDL_Quit();


    if(running ==1)goto restart;

    return EXIT_SUCCESS;
}
int check_on_kings(int x, int y, SDL_Rect poskingA, SDL_Rect poskingB){
    if (x > poskingA.x && x < poskingA.x + 54) //x du clic entre les x du roiA
        if (y > poskingA.y && y < poskingA.y + 54){

            return kingAselect; //retourne son numero
            }
    if (x > poskingB.x && x < poskingB.x + 54)
        if(y > poskingB.y && y < poskingB.y + 54){

            return kingBselect;
        }
    return -1;
}
int check_on_dames(int x, int y, SDL_Rect* damesA, SDL_Rect* damesB){
    int i = 0;
    for( i = 0; i < 8 ; i++){
    if (x > damesA[i].x && x < damesA[i].x + damesA[i].w)
        if (y > damesA[i].y && y < damesA[i].y + damesA[i].h){
                return i + 2;
        }
    if (x > damesB[i].x && x < damesB[i].x + damesB[i].w)
        if (y > damesB[i].y && y < damesB[i].y + damesB[i].h){
                return i + 10;
        }

    }
    return -1;
}

int check_on_pions(int x, int y, SDL_Rect* pionsA, SDL_Rect* pionsB){
    int i = 0;
    for( i = 0; i < 15 ; i++){
    if (x > pionsA[i].x && x < pionsA[i].x + pionsA[i].w)
        if (y > pionsA[i].y && y < pionsA[i].y + pionsA[i].h){
                return i + 101;
        }
    if (x > pionsB[i].x && x < pionsB[i].x + pionsB[i].w)
        if (y > pionsB[i].y && y < pionsB[i].y + pionsB[i].h){
                return i + 116;
        }

    }
    return -1;
}



int check_mouse_clicked(int x,int y,SDL_Rect poskingA,SDL_Rect poskingB,SDL_Rect* damesA,SDL_Rect* damesB,SDL_Rect* pionsA, SDL_Rect* pionsB){
    if ((( x%68 - 20 ) * ( x%68 - 74 ) < 0) && (( y%68 - 21 ) * ( y%68 - 75 ) < 0))//optimisation decider du premier si on a cliquer sur une case royale
        return check_on_kings(x, y, poskingA, poskingB);
    if(check_inborders(x,y) == 0){//si clic en dehor de table de jeu routourner
            return -2;
    }
    int out = -2;
    out = maxi(check_on_dames(x, y, damesA, damesB), out);//s il trouve le numero d'une dame il est superieur à -2 out egale à ce numero
    out = maxi(check_on_pions(x, y, pionsA, pionsB), out);
    return out;
}


void afficher_entourage_roi(SDL_Renderer** r, SDL_Rect posking, int chemins_valables){
        SDL_Rect roi_selected{0}; //cree une rectangle
        roi_selected.w = 54;
        roi_selected.h = 54;

        if(chemins_valables%right_const == 0){//si ce deplacement permis il entre
            roi_selected.x = posking.x + 68; //donne au rectangle les coordonnee convenables
            roi_selected.y = posking.y;
            if(check_inborders(roi_selected.x, roi_selected.y)) //verfie qu'il s'agit d'un rectagle de la table de jeu
                SDL_RenderFillRect(*r, &roi_selected);
        }
        if(chemins_valables%left_const == 0){
            roi_selected.x = posking.x - 68;
            roi_selected.y = posking.y;
            if(check_inborders(roi_selected.x, roi_selected.y))
                SDL_RenderFillRect(*r, &roi_selected);
        }
        if(chemins_valables%down_const == 0){
        roi_selected.x = posking.x;
        roi_selected.y = posking.y + 68;
            if(check_inborders(roi_selected.x, roi_selected.y))
            SDL_RenderFillRect(*r, &roi_selected);
        }
        if(chemins_valables%up_const == 0){
            roi_selected.x = posking.x;
            roi_selected.y = posking.y - 68;
            if(check_inborders(roi_selected.x, roi_selected.y))
                SDL_RenderFillRect(*r,&roi_selected);
            }
        SDL_RenderPresent(*r);//afficher les rectangles cree
}
/*void afficher_entourage_dame(SDL_Renderer** r,SDL_Rect posdame){

        SDL_Rect dame_selected{0};
        dame_selected.w = posdame.w;
        dame_selected.h = posdame.h;
        dame_selected.x = posdame.x+68;
        dame_selected.y = posdame.y;
        if(check_inborders(dame_selected.x,dame_selected.y))
            SDL_RenderFillRect(*r,&dame_selected);
        dame_selected.x = posdame.x-68;
        dame_selected.y = posdame.y;
        if(check_inborders(dame_selected.x,dame_selected.y))
            SDL_RenderFillRect(*r,&dame_selected);
        dame_selected.x = posdame.x;
        dame_selected.y = posdame.y+68;
        if(check_inborders(dame_selected.x,dame_selected.y))
            SDL_RenderFillRect(*r,&dame_selected);
        dame_selected.x = posdame.x;
        dame_selected.y = posdame.y-68;
        if(check_inborders(dame_selected.x,dame_selected.y))
            SDL_RenderFillRect(*r,&dame_selected);
        SDL_RenderPresent(*r);
}*/
void mouse_move_king(SDL_Rect *posking, position_matrice_etat* king_matrice){
    SDL_Event eventm;
    while(1){
    SDL_WaitEvent(&eventm);
    if (eventm.type == SDL_MOUSEBUTTONDOWN){
                if( (eventm.motion.x - (*posking).x ) * ( eventm.motion.x - ( (*posking).x+54 ) ) < 0 ){//x entra les deux x
                    if( (eventm.motion.y - (*posking).y ) * (eventm.motion.y - ( (*posking).y - 68) ) < 0 ){
                        if((*king_matrice).possibilities% up_const == 0){
                                (*posking).y -= 68;
                                matrice_de_jeu[(*king_matrice).ligne-2][(*king_matrice).colone] = matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone];
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone] = -1;
                                (*king_matrice).ligne -= 2;
                                (*king_matrice).possibilities = verifie_possibilities_king((*king_matrice));
                                return;
                        }
                        else{
                        return ;}
                        }
                    else { if((eventm.motion.y - ( (*posking).y +68 ) ) * (eventm.motion.y -( (*posking).y + 2*68 )) < 0)
                            {
                         if((*king_matrice).possibilities% down_const ==0){
                                (*posking).y += 68;
                                matrice_de_jeu[(*king_matrice).ligne + 2][(*king_matrice).colone] = matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone];
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone] = -1;
                                (*king_matrice).ligne += 2;
                                (*king_matrice).possibilities = verifie_possibilities_king((*king_matrice));
                                return;
                        }else
                        return;
                        }
                    else
                        return;
                        }
                }
                else if((eventm.motion.y - (*posking).y ) * ( eventm.motion.y - ((*posking).y + 54)) < 0 ){
                    if( (eventm.motion.x - ((*posking).x-14 )) * (eventm.motion.x - ( (*posking).x - 68 )) < 0 ){
                         if((*king_matrice).possibilities% left_const ==0){
                                (*posking).x -= 68;
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone - 2] = matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone];
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone] = -1;
                                (*king_matrice).colone -= 2;
                                (*king_matrice).possibilities = verifie_possibilities_king((*king_matrice));
                                return;
                        }
                        return;
                        }
                    else if((eventm.motion.x - ((*posking).x + 68) ) * (eventm.motion.x - (*posking).x - 2*68 ) < 0){
                         if((*king_matrice).possibilities% right_const == 0){
                                (*posking).x += 68;
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone + 2] = matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone];
                                matrice_de_jeu[(*king_matrice).ligne][(*king_matrice).colone] = -1;
                                (*king_matrice).colone += 2;
                                (*king_matrice).possibilities = verifie_possibilities_king((*king_matrice));

                                return;
                        }
                    return;
                    }
                else
                    return;
                }
                else
                    return;
            }


    }
}




//test move dame
void mouse_move_dame(SDL_Rect *posdame ,SDL_Texture** tex,SDL_Texture* vert_dame_ref,SDL_Texture* hor_dame_ref,position_matrice_etat* dame_matrice,arguments_supp_manger_prototype){

        SDL_Event eventm;
        int HorOuVert=hor_ou_vert((*posdame).y); //NB peut engedrer erreur (antre 20 et 24 ver)
        while(1){
        SDL_WaitEvent(&eventm);
        if (eventm.type == SDL_MOUSEBUTTONDOWN){
            int x = eventm.motion.x;
            int y = eventm.motion.y;
            if(check_inborders(x,y)==0){return ;}
            if(HorOuVert){ //si vertical
                if( (x - (*posdame).x ) * ( x - ( (*posdame).x + 12 ) ) < 0 ){
                    move_dame_verticaly_y(y,posdame,dame_matrice,arguments_supp_manger);
                    return ;
                    }

                else {
                        if((y - (*posdame).y ) * ( y - ((*posdame).y + 52)) < 0 ){
                            move_dame_verticaly_x(x,posdame,dame_matrice);
                            return ;
                            }

                        else {
                                if( (x - ( (*posdame).x +68 ))*(x -( (*posdame).x - 54 )) < 0 ){
                                    if((y - ( (*posdame).y + 68 ))*(y-( (*posdame).y - 14 )) < 0 ){
                                        move_dame_Vert2Hor(x, y, posdame, tex, hor_dame_ref, dame_matrice);
                                        return;
                                        }
                                    else return;
                                }
                            else return;
                        }
            }
            }
            else
                {//si hor
                    if( (x - (*posdame).x ) * ( x - ( (*posdame).x + 54 ) ) < 0 ) {
                    move_dame_horizentaly_y(y, posdame, dame_matrice);
                    return ;
                    }

                    else{    if((y - (*posdame).y ) * ( y - ((*posdame).y + 14)) < 0 ){
                            move_dame_horizentaly_x(x, posdame, dame_matrice, arguments_supp_manger);
                            return ;
                            }

                            else {
                                    if( (x - ( (*posdame).x +68 ))*(x -( (*posdame).x - 14 )) < 0 ){
                                    if((y - ( (*posdame).y + 68+14 ))*(y-( (*posdame).y - 68 )) < 0 ){
                                        move_dame_Hor2Vert(x, y, posdame, tex, vert_dame_ref, dame_matrice);
                                        return;
                                        }
                                    else return;
                                    }
                                else return;
                                }
                                }
                    }
                }
            }
        }
//test constructions here

void mouse_move_pion(SDL_Rect *pos_pion, SDL_Texture** tex, SDL_Texture* vert_pion_ref, SDL_Texture* hor_pion_ref, position_matrice_etat* pion_matrice, arguments_supp_manger_prototype){

        SDL_Event eventm;
        int HorOuVert = hor_ou_vert((*pos_pion).y); //NB peut engedrer erreur (antre 20 et 24 ver)
        while(1){
        SDL_WaitEvent(&eventm);
        if (eventm.type == SDL_MOUSEBUTTONDOWN){
            int x = eventm.motion.x;
            int y = eventm.motion.y;
            if(check_inborders(x, y) == 0){
                    return ;
            }
            if(HorOuVert){ //si vertical
                if( (x - (*pos_pion).x ) * ( x - ( (*pos_pion).x + 12 ) ) < 0 ){
                    move_dame_verticaly_y(y,pos_pion,pion_matrice,arguments_supp_manger);
                    return ;
                    }

                else {
                        if((y - (*pos_pion).y ) * ( y - ((*pos_pion).y + 52)) < 0 ){
                            move_dame_verticaly_x(x,pos_pion,pion_matrice);
                            return ;
                            }

                        else {
                                if( (x - ( (*pos_pion).x +68 ))*(x -( (*pos_pion).x - 54 )) < 0 ){
                                    if((y - ( (*pos_pion).y + 68 ))*(y-( (*pos_pion).y - 14 )) < 0 ){
                                        move_dame_Vert2Hor(x, y, pos_pion, tex, hor_pion_ref, pion_matrice);
                                        return;
                                        }
                                    else return;
                                }
                            else return;
                        }
            }
            }
            else
                {//si hor
                    if( (x - (*pos_pion).x ) * ( x - ( (*pos_pion).x + 54 ) ) < 0 ) {
                    move_dame_horizentaly_y(y,pos_pion,pion_matrice);
                    return ;
                    }

                    else{    if((y - (*pos_pion).y ) * ( y - ((*pos_pion).y + 14)) < 0 ){
                            move_dame_horizentaly_x(x, pos_pion, pion_matrice, arguments_supp_manger);
                            return ;
                            }

                            else {
                                    if( (x - ( (*pos_pion).x +68 ))*(x -( (*pos_pion).x - 14 )) < 0 ){
                                    if((y - ( (*pos_pion).y + 68+14 ))*(y-( (*pos_pion).y - 68 )) < 0 ){
                                        move_dame_Hor2Vert(x, y, pos_pion, tex, vert_pion_ref, pion_matrice);
                                        return;
                                        }
                                    else return;
                                    }
                                else return;
                                }
                                }
                    }
                }
            }
        }


//subrotines
/*
void move_pion_verticaly_y(int y,SDL_Rect *posdame,position_matrice_etat* dame_matrice,arguments_supp_manger_prototype){
                        int xymove=(y -(*posdame).y);
                        (xymove<0)?xymove=-1:xymove=1;
                        (*posdame).y+=xymove*68;
                        if(matrice_de_jeu[(*dame_matrice).ligne+xymove*2][(*dame_matrice).colone]!=-1){
                            manger_piece((*dame_matrice).ligne+xymove*2,(*dame_matrice).colone,arguments_supp_manger);
                        }
                        matrice_de_jeu[(*dame_matrice).ligne+xymove*2][(*dame_matrice).colone]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).ligne += (xymove*2);
                        return ;

}
void move_pion_verticaly_x(int x,SDL_Rect *posdame,position_matrice_etat* dame_matrice){
                        int xymove=(x -(*posdame).x);
                        (xymove<0)?xymove=-1:xymove=1;
                        (*posdame).x+=xymove*68;
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).colone += (xymove*2);
                        return ;

}
void move_pion_horizentaly_y(int y,SDL_Rect *posdame,position_matrice_etat* dame_matrice){
                         int xymove=(y -(*posdame).y);
                        if((*dame_matrice).first_time_pion==1){
                           (*dame_matrice).first_time_pion=0;
                            (xymove<0)?xymove-=68:xymove+=0;
                            xymove /=68;
                            if(xymove<=-2)xymove=-2;
                            else { if(xymove>=2)xymove=2;
                                    else {if(xymove>0)xymove=1;
                                    else xymove=-1;
                                    }
                            }

                        }else{
                        (xymove<0)?xymove=-1:xymove=+1;
                        }
                        (*posdame).y+=xymove*68;
                        matrice_de_jeu[(*dame_matrice).ligne+xymove*2][(*dame_matrice).colone]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).ligne += (xymove*2);
                        return ;
}
void move_pion_horizentaly_x(int x,SDL_Rect *posdame,position_matrice_etat* dame_matrice,arguments_supp_manger_prototype){
                        int xymove=(x -(*posdame).x);
                        (xymove<0)?xymove=-1:xymove=1;
                        (*posdame).x+=xymove*68;
                        if(matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2]!=-1){
                            manger_piece((*dame_matrice).ligne,(*dame_matrice).colone+xymove*2,arguments_supp_manger);
                        }
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).colone += (xymove*2);
                        return ;
}



*/
//end constructions

void move_dame_verticaly_y(int y, SDL_Rect *posdame, position_matrice_etat* dame_matrice, arguments_supp_manger_prototype){
                        int xymove=(y -(*posdame).y);//horizentaly x vertically y
                        (xymove<0) ? xymove -= 68 : xymove += 0;
                        xymove /= 68;
                        if(xymove == 0)return;
                        if(xymove < 0 && (*dame_matrice).table_possibilties[-1*xymove - 1]%up_const != 0)return;
                        if(xymove > 0 && (*dame_matrice).table_possibilties[xymove - 1]%down_const != 0)return;
                        (*posdame).y += xymove*68;
                        if(matrice_de_jeu[(*dame_matrice).ligne + xymove*2][(*dame_matrice).colone] != -1){
                           manger_piece((*dame_matrice).ligne + xymove*2, (*dame_matrice).colone, arguments_supp_manger);
                        }
                        matrice_de_jeu[(*dame_matrice).ligne + xymove*2][(*dame_matrice).colone] = matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone] = -1;
                        (*dame_matrice).ligne += (xymove*2);
                        return ;

}
void move_dame_verticaly_x(int x, SDL_Rect *posdame, position_matrice_etat* dame_matrice){
                        int xymove=(x -(*posdame).x);
                        (xymove<0) ? xymove -= 68: xymove += 0;
                        xymove /= 68;
                        if(xymove < 0 && (*dame_matrice).table_possibilties[-1*xymove - 1]%left_const != 0)return;
                        if(xymove > 0 && (*dame_matrice).table_possibilties[xymove - 1]%right_const != 0)return;
                        (*posdame).x += xymove*68;
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2] = matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone] = -1;
                        (*dame_matrice).colone += (xymove*2);
                        return ;

}
void move_dame_horizentaly_y(int y,SDL_Rect *posdame,position_matrice_etat* dame_matrice){
                         int xymove = (y -(*posdame).y);
                        (xymove<0) ? xymove -= 68 : xymove += 0;
                        xymove /= 68;
                        if(xymove < 0 && (*dame_matrice).table_possibilties[-1*xymove - 1]%up_const != 0)return;
                        if(xymove > 0 && (*dame_matrice).table_possibilties[xymove - 1]%down_const != 0)return;
                        (*posdame).y += xymove*68;
                        matrice_de_jeu[(*dame_matrice).ligne+xymove*2][(*dame_matrice).colone]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).ligne += (xymove*2);
                        return ;
}
void move_dame_horizentaly_x(int x,SDL_Rect *posdame,position_matrice_etat* dame_matrice,arguments_supp_manger_prototype){
                        int xymove=(x -(*posdame).x);
                        (xymove<0)?xymove-=68:xymove+=0;
                        xymove /=68;
                        if(xymove < 0 && (*dame_matrice).table_possibilties[-xymove-1]%left_const!=0)return;
                        if(xymove > 0 && (*dame_matrice).table_possibilties[xymove-1]%right_const!=0)return;
                        (*posdame).x+=xymove*68;
                        if(matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2]!=-1){

                            manger_piece((*dame_matrice).ligne,(*dame_matrice).colone+xymove*2,arguments_supp_manger);
                        }
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+xymove*2]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                        matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                        (*dame_matrice).colone += (xymove*2);
                        return ;
}

void move_dame_Vert2Hor(int x,int y ,SDL_Rect *posdame,SDL_Texture** tex,SDL_Texture* hor_dame_ref,position_matrice_etat* dame_matrice ){
        if( (x - (*posdame).x ) * (x - ( (*posdame).x - 54 ) ) < 0 ){//x entra les deux x de gauche
                            if((y - (*posdame).y ) * (y - ( (*posdame).y - 14 ) ) < 0){
                                if((*dame_matrice).poss_supp%up_left_const!=0)return;
                                 (*posdame).x -= 54;
                                 (*posdame).x += 1;
                                 (*posdame).y -= 14;
                                 matrice_de_jeu[(*dame_matrice).ligne-1][(*dame_matrice).colone-1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne -=1;
                                 (*dame_matrice).colone -=1 ;
                                (*posdame).h = 14;
                                (*posdame).w = 52;
                                *tex=hor_dame_ref;
                                 //left up
                                return;
                                }
                            else if((y - ((*posdame).y +54)) * (y - ( (*posdame).y +68 ) ) < 0){
                                if((*dame_matrice).poss_supp%down_left_const!=0)return;
                                (*posdame).x -=  54;
                                (*posdame).x +=  1;
                                (*posdame).y +=  54;
                                matrice_de_jeu[(*dame_matrice).ligne+1][(*dame_matrice).colone-1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne +=1;
                                 (*dame_matrice).colone -=1 ;
                                (*posdame).h = 14;
                                (*posdame).w = 52;
                                *tex=hor_dame_ref;
                                //left down
                                return;
                                }
                                else return;

                    } else if( (x - ( (*posdame).x + 14 ) ) * (x - ( (*posdame).x + 68 ) ) < 0 ){//x entra les deux x de droite
                            if((y - (*posdame).y ) * (y - ( (*posdame).y - 14 ) ) < 0){
                                 if((*dame_matrice).poss_supp%up_right_const!=0)return;
                                 (*posdame).x +=  14;
                                 (*posdame).x +=  1;
                                 (*posdame).y -= 14;
                                 matrice_de_jeu[(*dame_matrice).ligne-1][(*dame_matrice).colone+1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne -=1;
                                 (*dame_matrice).colone +=1 ;
                                 (*posdame).h = 14;
                                (*posdame).w = 52;
                                *tex=hor_dame_ref;
                                //right up
                                return;
                                }
                            else if((y - ((*posdame).y +54)) * (y - ( (*posdame).y +68 ) ) < 0){
                                if((*dame_matrice).poss_supp%down_right_const!=0)return;
                                (*posdame).x +=  14;
                                (*posdame).x +=  1;
                                (*posdame).y +=  54;
                                matrice_de_jeu[(*dame_matrice).ligne+1][(*dame_matrice).colone+1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne +=1;
                                 (*dame_matrice).colone +=1 ;
                                (*posdame).h = 14;
                                (*posdame).w = 52;
                                *tex=hor_dame_ref;
                                //right down
                                return;
                                }
                                else return;

                    }
}
void move_dame_Hor2Vert(int x, int y, SDL_Rect *posdame, SDL_Texture** tex, SDL_Texture* vert_dame_ref,position_matrice_etat* dame_matrice){
        if( (x - (*posdame).x ) * (x - ( (*posdame).x - 14 ) ) < 0 ){//x entra les deux x de gauche
                            if(( y - (*posdame).y ) * (y - ( (*posdame).y - 54 ) ) < 0){
                                if((*dame_matrice).poss_supp%up_left_const!=0)return;
                                 (*posdame).x -=  14;
                                 (*posdame).x -=  1;
                                 (*posdame).y -= 54;
                                 matrice_de_jeu[(*dame_matrice).ligne-1][(*dame_matrice).colone-1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne -=1;
                                 (*dame_matrice).colone -=1 ;
                                 (*posdame).h = 54;
                                (*posdame).w = 14;
                                *tex=vert_dame_ref;
                                 //left up
                                return;
                                }
                            else if((y - ((*posdame).y +14)) * (y - ( (*posdame).y +68 ) ) < 0){
                                if((*dame_matrice).poss_supp%down_left_const!=0)return;
                                (*posdame).x -=  14;
                                (*posdame).x -=  1;
                                (*posdame).y +=  14;
                                matrice_de_jeu[(*dame_matrice).ligne+1][(*dame_matrice).colone-1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne +=1;
                                 (*dame_matrice).colone -=1 ;
                                 (*posdame).h = 54;
                                (*posdame).w = 14;
                                *tex=vert_dame_ref;
                                //left down
                                return;
                                }
                                else return;

                    } else if( (x - ( (*posdame).x + 14 ) ) * (x - ( (*posdame).x + 68 ) ) < 0 ){//x entra les deux x de droite
                            if((y - (*posdame).y ) * (y - ( (*posdame).y - 54 ) ) < 0){
                                 if((*dame_matrice).poss_supp%up_right_const!=0)return;
                                 (*posdame).x +=  54;
                                 (*posdame).x -=  1;
                                 (*posdame).y -= 54;
                                 matrice_de_jeu[(*dame_matrice).ligne-1][(*dame_matrice).colone+1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne -=1;
                                 (*dame_matrice).colone +=1 ;
                                 (*posdame).h = 54;
                                (*posdame).w = 14;
                                *tex=vert_dame_ref;
                                 //right up
                                return;
                                }
                            else if((y - ((*posdame).y +14)) * (y - ( (*posdame).y +68 ) ) < 0){
                                if((*dame_matrice).poss_supp%down_right_const!=0)return;
                                (*posdame).x +=  54;
                                (*posdame).x -=  1;
                                (*posdame).y +=  14;
                                matrice_de_jeu[(*dame_matrice).ligne+1][(*dame_matrice).colone+1]=matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone];
                                 matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone]=-1;
                                 (*dame_matrice).ligne +=1;
                                 (*dame_matrice).colone +=1 ;
                                 (*posdame).h = 54;
                                (*posdame).w = 14;
                                *tex=vert_dame_ref;

                                //right down
                                return;
                                }
                                else return;

                    }
}

int check_inborders(int x,int y){
    if (x > 75 && x < 565 && y > 74 && y < 565 )//75+7*68+14=565
        return 1;
    return 0;
}

int hor_ou_vert(int y){
        if ( ( y%68 - 20 ) * ( y%68 -24 ) < 0)
            return 1;
        else return 0;
}




void initialisation_matrice_jeu(){
    int i,j,k=10;
    for(i=0;i<15;i++){
    for(j=0;j<15;j++){
        if(i==1 && j%2 == 0){
            matrice_de_jeu[i][j]=k++;
            }
            else{ if(i==13 && j%2 == 0){
                    matrice_de_jeu[i][j]=(k++)-16;
            }
            else{   if((i==2 && j%2 == 1) || (i==12 && j%2 == 1) ||(i==3 && j%2 != 1) || (i==11 && j%2 != 1)){
                        if(i==2)matrice_de_jeu[i][j]=116+j/2;
                        if(i==3)matrice_de_jeu[i][j]=123+j/2;
                        if(i==12)matrice_de_jeu[i][j]=101+j/2;
                        if(i==11)matrice_de_jeu[i][j]=108+j/2;
                    }
            else
                matrice_de_jeu[i][j]=-1;
            }
            }
    }
    }
    matrice_de_jeu[1][7] = kingBselect;
    matrice_de_jeu[13][7] = kingAselect;

    return ;
}
void visualisation(){int i,j;
    for(i=0;i<15;i++){
            printf("\n");
    for(j=0;j<15;j++){
        printf("%d ",matrice_de_jeu[i][j]);
    }
    }
    }


void initialisation_positions_dans_matrice(position_matrice_etat* kingA_matrice,position_matrice_etat* kingB_matrice,position_matrice_etat* damesA_matrice,position_matrice_etat* damesB_matrice,position_matrice_etat* pionsA_matrice,position_matrice_etat* pionsB_matrice){
    (*kingA_matrice).ligne=13;
    (*kingA_matrice).colone=7;
    (*kingA_matrice).possibilities=no_direction_const;
    (*kingB_matrice).ligne=1;
    (*kingB_matrice).colone=7;
    (*kingB_matrice).possibilities=no_direction_const;
    int i;
    for(i = 0; i < 8; i++ ){
        damesA_matrice[i].ligne = 13;
        damesA_matrice[i].colone = 2*i;
        damesA_matrice[i].poss_supp = down_left_const*down_right_const;
        damesA_matrice[i].possibilities = 0;
        damesB_matrice[i].ligne = 1;
        damesB_matrice[i].colone = 2*i;
        damesB_matrice[i].poss_supp = up_left_const*up_right_const;
        damesB_matrice[i].possibilities=0;

    }
        damesA_matrice[7].poss_supp /=down_right_const;
        damesA_matrice[0].poss_supp /=down_left_const;
        damesB_matrice[0].poss_supp /=up_left_const;
        damesB_matrice[7].poss_supp /=up_right_const;

    for(i=0;i<7;i++){
        pionsA_matrice[i].ligne = 12 ;
        pionsA_matrice[i].colone= 2*i+1;
        pionsA_matrice[i].poss_supp=no_direction_const;
        pionsA_matrice[i].possibilities=down_const*up_const;
        pionsA_matrice[i].first_time_pion=1;
        pionsB_matrice[i].ligne=2;
        pionsB_matrice[i].colone=2*i+1;
        pionsB_matrice[i].poss_supp=no_direction_const;
        pionsB_matrice[i].possibilities=down_const*up_const;
        pionsB_matrice[i].first_time_pion=1;

    }
    pionsA_matrice[3].possibilities =down_const;
    pionsB_matrice[3] .possibilities =up_const;
    for(i=7;i<15;i++){
        pionsA_matrice[i].ligne = 11 ;
        pionsA_matrice[i].colone= 2*(i-7);
        pionsA_matrice[i].poss_supp=up_left_const*up_right_const;
        pionsA_matrice[i].possibilities=up_const;
        pionsA_matrice[i].first_time_pion=1;
        pionsB_matrice[i].ligne=3;
        pionsB_matrice[i].colone=2*(i-7);
        pionsB_matrice[i].poss_supp=down_left_const*down_right_const;
        pionsB_matrice[i].possibilities=down_const;
        pionsB_matrice[i].first_time_pion=1;
    }
        damesA_matrice[14].poss_supp /=up_right_const;
        damesA_matrice[7].poss_supp /=up_left_const;
        damesB_matrice[7].poss_supp /=down_left_const;
        damesB_matrice[14].poss_supp /=down_right_const;


}

int verifie_possibilities_king(position_matrice_etat king_matrice){
    int x=1;//cadrement dans 15
    if(king_matrice.ligne-2 > 0  ){
    if((matrice_de_jeu[king_matrice.ligne-1][king_matrice.colone] == -1 )&& (matrice_de_jeu[king_matrice.ligne-2][king_matrice.colone] == -1) )
        x*=up_const;
        }
    if(king_matrice.ligne+2 < 15){
    if((matrice_de_jeu[king_matrice.ligne+1][king_matrice.colone] == -1 )&& (matrice_de_jeu[king_matrice.ligne+2][king_matrice.colone] == -1) )
        x*=down_const;
        }
    if(king_matrice.colone-2 > 0){
    if((matrice_de_jeu[king_matrice.ligne][king_matrice.colone-1] == -1 )&& (matrice_de_jeu[king_matrice.ligne][king_matrice.colone-2] == -1) )
        x*=left_const;
        }
    if(king_matrice.colone+2 < 15){
    if((matrice_de_jeu[king_matrice.ligne][king_matrice.colone+1] == -1 )&& (matrice_de_jeu[king_matrice.ligne][king_matrice.colone+2] == -1) )
        x*=right_const;
        }
    if(x==1)
        x=11;
    return x;
}

void eaten(position_matrice_etat old_position , position_matrice_etat new_position,SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB){

                if((old_position.ligne!=new_position.ligne)||(old_position.colone!=new_position.colone)){
                if(old_position.ligne==new_position.ligne){
                        if(old_position.colone<new_position.colone){
                            for(int j=old_position.colone+1;j<new_position.colone;j++){
                                if(matrice_de_jeu[old_position.ligne][j]!=-1)
                                       manger_piece(old_position.ligne,j,damesA,damesB,pionsA,pionsB);
                            }
                        }else{
                            for(int j=old_position.colone-1;j>new_position.colone;j--){
                                if(matrice_de_jeu[old_position.ligne][j]!=-1)
                                      manger_piece(old_position.ligne,j,damesA,damesB,pionsA,pionsB);
                            }
                            }
                }
                else{
                    if(old_position.colone==new_position.colone){
                            if(old_position.ligne<new_position.ligne){
                                for(int i=old_position.ligne+1;i<new_position.ligne;i++){
                                        if(matrice_de_jeu[i][old_position.colone]!=-1)
                                        manger_piece(i,old_position.colone,damesA,damesB,pionsA,pionsB);
                                }

                            }else {
                                for(int i=old_position.ligne-1;i>new_position.ligne;i--){
                                        if(matrice_de_jeu[i][old_position.colone]!=-1)
                                        manger_piece(i,old_position.colone,damesA,damesB,pionsA,pionsB);
                                }

                            }

                    }
                    else
                    return;
                }
}
}


void manger_piece(int i, int j, SDL_Rect* damesA, SDL_Rect* damesB, SDL_Rect* pionsA, SDL_Rect* pionsB){

        int N=matrice_de_jeu[i][j]; //numero du piece a eliminer
        matrice_de_jeu[i][j]=-1;
        if((N-dameA1)*(N-dameA8) <= 0 ){//piece a eliminer est une dame de A
                damesA[N-dameA1]={0,0,0,0};
        }
        if((N-dameB1)*(N-dameB8) <= 0 ){
                damesB[N-dameB1]={0,0,0,0};
        }
        if((N-pionA1)*(N-pionA15) <= 0 ){
                pionsA[N-pionA1]={0,0,0,0};
        }
        if((N-pionB1)*(N-pionB15) <= 0 ){
                pionsB[N-pionB1]={0,0,0,0};
        }

}
void verifie_possibilities_dame(position_matrice_etat* dame_matrice){
            int i;
            for(i=0;i<7;i++)
                (*dame_matrice).table_possibilties[i]=1;
            i=1;
            while((*dame_matrice).ligne + 2*i < 15){
                    if(matrice_de_jeu[(*dame_matrice).ligne+2*i][(*dame_matrice).colone]==-1 && matrice_de_jeu[(*dame_matrice).ligne+2*i-1][(*dame_matrice).colone]==-1)
                        (*dame_matrice).table_possibilties[i-1] *= down_const;
                    i++;
            }

            i=1;
            while((*dame_matrice).ligne-2*i>=0){
                 if(matrice_de_jeu[(*dame_matrice).ligne-2*i][(*dame_matrice).colone]==-1 && matrice_de_jeu[(*dame_matrice).ligne-2*i+1][(*dame_matrice).colone]==-1)
                        (*dame_matrice).table_possibilties[i-1] *= up_const;
                    i++;
            }
            i=1;
            while((*dame_matrice).colone+2*i<15){
                if(matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+2*i]==-1 && matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone+2*i-1]==-1)
                        (*dame_matrice).table_possibilties[i-1] *= right_const;
                    i++;
            }
            i=1;
            while((*dame_matrice).colone-2*i>=0){
                if(matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone-2*i]==-1 && matrice_de_jeu[(*dame_matrice).ligne][(*dame_matrice).colone-2*i+1]==-1)
                        (*dame_matrice).table_possibilties[i-1] *= left_const;
                    i++;
            }
            for(i=0;i<7;i++){
                if((*dame_matrice).table_possibilties[i]==1)
                (*dame_matrice).table_possibilties[i]=11;
            }

            int is_verticale=(*dame_matrice).ligne%2;//1 signifie vertical sinon 0

            rectifie_dame_possibilities((*dame_matrice).table_possibilties,is_verticale);
            verifie_possibilities_supp(dame_matrice);
            //possibilité supp
            remove_friendlyfire(dame_matrice);

}
void remove_friendlyfire(position_matrice_etat* dame_matrice){
        int i=0,is_verticale=(*dame_matrice).ligne%2;
        int l=(*dame_matrice).ligne,c=(*dame_matrice).colone;
        int A_ou_B=chercher_autour_roi(matrice_de_jeu[l][c]);
        if(is_verticale==1){
            //cas verticale haut
            while((*dame_matrice).table_possibilties[i]%up_const==0){
                  i++;
                  }
            if(l-2*i >= 0 && chercher_autour_roi(matrice_de_jeu[l-2*i][c])==A_ou_B)(*dame_matrice).table_possibilties[--i]/=up_const;
            //cas verticale bas
            i=0;
            while((*dame_matrice).table_possibilties[i]%down_const==0) i++;

            if(l+2*i < 15 && chercher_autour_roi(matrice_de_jeu[l+2*i][c])==A_ou_B)(*dame_matrice).table_possibilties[--i]/=down_const;



        }
        else{
            //cas hrizontale left
            i=0;
            while((*dame_matrice).table_possibilties[i]%left_const==0){
                  i++;
                  }
            if(c-2*i>=0 && chercher_autour_roi(matrice_de_jeu[l][c-2*i])==A_ou_B)(*dame_matrice).table_possibilties[--i]/=left_const;
            //cas horizontale right
            i=0;
            while((*dame_matrice).table_possibilties[i]%right_const==0){
                  i++;
                  }
            if(c+2*i <15 && chercher_autour_roi(matrice_de_jeu[l][c+2*i])==A_ou_B)(*dame_matrice).table_possibilties[--i]/=right_const;


        }
}





void verifie_possibilities_supp(position_matrice_etat* dame_p_matrice){
    (*dame_p_matrice).poss_supp=1;
    if(matrice_de_jeu[(*dame_p_matrice).ligne+1][(*dame_p_matrice).colone+1]==-1){
        (*dame_p_matrice).poss_supp*=down_right_const;
    }
    if(matrice_de_jeu[(*dame_p_matrice).ligne-1][(*dame_p_matrice).colone+1]==-1){
        (*dame_p_matrice).poss_supp*=up_right_const;
    }
    if(matrice_de_jeu[(*dame_p_matrice).ligne+1][(*dame_p_matrice).colone-1]==-1){
        (*dame_p_matrice).poss_supp*=down_left_const;
    }
    if(matrice_de_jeu[(*dame_p_matrice).ligne-1][(*dame_p_matrice).colone-1]==-1){
        (*dame_p_matrice).poss_supp*=up_left_const;
    }

    if((*dame_p_matrice).poss_supp==1){
        (*dame_p_matrice).poss_supp=no_direction_const;
    }

}

void rectifie_dame_possibilities(int* table_poss_dame,int is_verticale){
    int i=0;
    if(is_verticale==1){
            printf("c1");
            //possibilite das coloes
        while(table_poss_dame[i]%up_const == 0 && i<7){
            i++;
        }
        if(i<7){
        table_poss_dame[i]*=up_const;
        i++;}
        while(i<7){
            if(table_poss_dame[i]%up_const == 0)
               table_poss_dame[i]/=up_const ;
            i++;
        }
        i=0;
        while(table_poss_dame[i]%down_const==0 && i<7){
            i++;
        }
        if(i<7){
        table_poss_dame[i]*=down_const;
        i++;}
        while(i<7){
            if(table_poss_dame[i]%down_const==0)
               table_poss_dame[i]/=down_const ;
            i++;
        }
        //verifie left rongee
        i=0;//si 1er vide ou 1er non vide
        while( i<6 && (table_poss_dame[i+1]%left_const==0 || table_poss_dame[i]%left_const==0 ) ){
            i++;
        }
        int ver=table_poss_dame[6];
        while(i<7){
            if(table_poss_dame[i]%left_const==0)
               table_poss_dame[i]/=left_const ;
            i++;
        }
        if(table_poss_dame[6]==1 || ver%left_const==0)table_poss_dame[6]*=left_const;
        //verifie right rongee
        i=0;
       while( i<6 && (table_poss_dame[i+1]%right_const==0 || table_poss_dame[i]%right_const==0 ) ){
            i++;
        }
        ver=table_poss_dame[6];
        while(i<7){
            if(table_poss_dame[i]%right_const==0)
               table_poss_dame[i]/=right_const ;
            i++;
        }
        if(table_poss_dame[6]==1 || ver%right_const==0)table_poss_dame[6]*=right_const;










    }
    else{
            i=0;
            while(table_poss_dame[i]%left_const==0 && i<7){
                    i++;
                }
                if(i<7){
                table_poss_dame[i]*=left_const;
                i++;}
                while(i<7){
                    if(table_poss_dame[i]%left_const==0)
                       table_poss_dame[i]/=left_const ;
                    i++;
        }
        i=0;
        while(table_poss_dame[i]%right_const==0 && i<7){
                    i++;
                }
                if(i<7){
                table_poss_dame[i]*=right_const;
                i++;}
                while(i<7){
                    if(table_poss_dame[i]%right_const==0)
                       table_poss_dame[i]/=right_const ;
                    i++;
        }

               i=0;//si 1er vide ou 1er non vide
        while( i<6 && (table_poss_dame[i+1]%up_const==0 || table_poss_dame[i]%up_const==0 ) ){
            i++;
        }
        int ver=table_poss_dame[6];
        while(i<7){
            if(table_poss_dame[i]%up_const==0)
               table_poss_dame[i]/=up_const ;
            i++;
        }
        if( table_poss_dame[6]==1 || ver%up_const==0 )table_poss_dame[6]*=up_const;
        //verifie down rongee
        i=0;
       while( i<6 && (table_poss_dame[i+1]%down_const==0 || table_poss_dame[i]%down_const==0 ) ){
            i++;
        }
        ver=table_poss_dame[6];
        while(i<7){
            if(table_poss_dame[i]%down_const==0)
               table_poss_dame[i]/=down_const ;
            i++;
        }
        if(table_poss_dame[6]==1 || ver%down_const==0)table_poss_dame[6]*=down_const;

    }
}




void verifie_possibilities_pion(position_matrice_etat* pion_matrice){
    int up_or_down,i,k=matrice_de_jeu[(*pion_matrice).ligne][((*pion_matrice).colone)];//numero du pion
    verifie_possibilities_dame(pion_matrice);

    //rectification adaptation pour les pions
    if((k-pionA1)*(k-pionA15)<=0 )up_or_down=up_const;//orientation possible
    if((k-pionB1)*(k-pionB15)<=0 )up_or_down=down_const;
    for(i = 0; i < 7; i++){
        if((*pion_matrice).table_possibilties[i]%up_or_down==0){
            (*pion_matrice).table_possibilties[i]=up_or_down;
            }
        else{
            (*pion_matrice).table_possibilties[i]=no_direction_const;// ne garder que orientaztion possible up or down
        }
    }
    //eliminant les pas multiples sauf si on est dans cas de prendre les piece de l'autre
    int is_verticale=(*pion_matrice).ligne%2;
    if(is_verticale==1){
            (*pion_matrice).table_possibilties[0]=up_or_down;
            (*pion_matrice).table_possibilties[1]=up_or_down;
            for(i=1;i<7;i++){
                (*pion_matrice).table_possibilties[i]=no_direction_const;
                }
            }else{//si horizental
                i=0;
                if(((*pion_matrice).table_possibilties[i]%up_or_down != 0 )&& ((*pion_matrice).table_possibilties[i+1]%up_or_down == 0)){//cas de prise
                i=2;
                while(i<6 &&((*pion_matrice).table_possibilties[i]%up_or_down != 0 )&& ((*pion_matrice).table_possibilties[i+1]%up_or_down == 0)){
                    i=i+2;
                }
                while(i<7)(*pion_matrice).table_possibilties[i++]=no_direction_const;

                }else{ if((*pion_matrice).table_possibilties[i]%up_or_down == 0){
                    i=1;
                   if((*pion_matrice).table_possibilties[1]%up_or_down == 0 && (*pion_matrice).first_time_pion==1){
                        i=2;
                        (*pion_matrice).first_time_pion=0;
                   }


             /*       for(i;i<7;i++)
                        (*pion_matrice).table_possibilties[i]=no_direction_const;*/


                }else{
                    for(i=0;i<7;i++)
                        (*pion_matrice).table_possibilties[i]=no_direction_const;
                }
                }

            }




    verifie_possibilities_supp(pion_matrice);
    //eliminer les mouvements supp en arriere
    if((k-pionA1)*(k-pionA15)<0 ) {//si un pion de A
        if((*pion_matrice).poss_supp%down_left_const==0)(*pion_matrice).poss_supp /=down_left_const;
        if((*pion_matrice).poss_supp%down_right_const==0)(*pion_matrice).poss_supp /=down_right_const;
    }
    if((k-pionB1)*(k-pionB15)<0){//si un pion de B
        if((*pion_matrice).poss_supp%up_left_const==0)(*pion_matrice).poss_supp /=up_left_const;
        if((*pion_matrice).poss_supp%up_right_const==0)(*pion_matrice).poss_supp /=up_right_const;
    }
}


int chercher_autour_roi(int valeur_cherche){//cherche ou appartient une piece 1 si appartient à A
int numero_des_pieceA[23]={2,3,4,5,6,7,8,9,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115};
int numero_des_pieceB[23]={10,11,12,13,14,15,16,17,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130};
int compteur;
for(compteur=0;compteur<23;compteur++){
    if(numero_des_pieceA[compteur]==valeur_cherche)return 1;
    if(numero_des_pieceB[compteur]==valeur_cherche)return 2;
}
return -1;
}



int echec_et_mat(position_matrice_etat king_matrice){
    if(king_matrice.possibilities==no_direction_const){
        int i=king_matrice.ligne,j=king_matrice.colone;
        if(matrice_de_jeu[i][j]==kingAselect){
        if(chercher_autour_roi(matrice_de_jeu[i+1][j])==2)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i][j+1])==2)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i-1][j])==2)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i][j-1])==2)return 1;
        }else{//king B
        if(chercher_autour_roi(matrice_de_jeu[i+1][j])==1)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i][j+1])==1)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i-1][j])==1)return 1;
        if(chercher_autour_roi(matrice_de_jeu[i][j-1])==1)return 1;
        }

    }
    return 0;
}
void gameover(SDL_Renderer** r,int numro_roi,Mix_Chunk* winner){
    SDL_Surface *gameoverSurface = NULL,*gameoverSurface2 = NULL,*gameoverSurface3 = NULL, *outroS = NULL;
    SDL_Rect position{120,220,400,200},posPR{0,0,640,640};
    if(numro_roi==1){
        gameoverSurface=SDL_LoadBMP("images/kingBwin.bmp");
        gameoverSurface2=SDL_LoadBMP("images/kingBwin2.bmp");
        gameoverSurface3=SDL_LoadBMP("images/kingBwin3.bmp");
        }else{
            gameoverSurface=SDL_LoadBMP("images/kingAwin.bmp");
            gameoverSurface2=SDL_LoadBMP("images/kingAwin2.bmp");
            gameoverSurface3=SDL_LoadBMP("images/kingAwin3.bmp");
        }
    outroS=SDL_LoadBMP("images/outro.bmp");
    SDL_Texture *texture_gameover=SDL_CreateTextureFromSurface(*r,gameoverSurface),
    *texture_gameover2=SDL_CreateTextureFromSurface(*r,gameoverSurface2),
    *texture_gameover3=SDL_CreateTextureFromSurface(*r,gameoverSurface3),
    *texture_outro=SDL_CreateTextureFromSurface(*r,outroS);

    SDL_FreeSurface(gameoverSurface);
    SDL_FreeSurface(gameoverSurface2);
    SDL_FreeSurface(gameoverSurface3);
    SDL_FreeSurface(outroS);
    Mix_PlayChannel(-1,winner,0);
    SDL_RenderCopy(*r,texture_gameover,NULL,&position);
    SDL_RenderPresent(*r);
    SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover2,NULL,&position);
    SDL_RenderPresent(*r);
    SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover3,NULL,&position);
    SDL_RenderPresent(*r);
    SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover2,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover2,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover3,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover2,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover2,NULL,&position);
    SDL_RenderPresent(*r);
        SDL_Delay(250);
    SDL_RenderCopy(*r,texture_gameover3,NULL,&position);
    SDL_RenderPresent(*r);
    SDL_RenderCopy(*r,texture_outro,NULL,&posPR);
    SDL_RenderPresent(*r);
    SDL_Delay(7000);
    SDL_DestroyTexture(texture_gameover);

}



int welcome(SDL_Renderer** r){
    SDL_Surface *welcomeSurface = NULL, *lancer_une_partieS=NULL, *quitterS=NULL;
    SDL_Rect position{0,0,640,640},lancer_une_part{80,197,480,137},quitter{210,345,215,79};
    welcomeSurface=SDL_LoadBMP("images/welcome.bmp");
    lancer_une_partieS=SDL_LoadBMP("images/lancer_une_partie.bmp");
    quitterS=SDL_LoadBMP("images/quitter.bmp");

    SDL_Texture *texture_welcome=SDL_CreateTextureFromSurface(*r,welcomeSurface);
    SDL_Texture *texture_quitter=SDL_CreateTextureFromSurface(*r,quitterS);
    SDL_Texture *texture_lancer=SDL_CreateTextureFromSurface(*r,lancer_une_partieS);

    SDL_FreeSurface(welcomeSurface);
    SDL_FreeSurface(quitterS);
    SDL_FreeSurface(lancer_une_partieS);

    SDL_RenderCopy(*r,texture_welcome,NULL,&position);
    SDL_RenderPresent(*r);
    int c=1;//gif
    SDL_Event ev;
    while(c){

            SDL_WaitEvent(&ev);
            if(( ev.motion.x -80 )*( ev.motion.x -650 ) < 0 && ( ev.motion.y -197 )*( ev.motion.y -334)<0 ){
                     SDL_RenderCopy(*r,texture_lancer,NULL,&lancer_une_part);
                     SDL_RenderPresent(*r);
                }else{
            if(( ev.motion.x -210 )*( ev.motion.x -425 )<0 && ( ev.motion.y -345 )*( ev.motion.y - 424 )<0){
                    SDL_RenderCopy(*r,texture_quitter,NULL,&quitter);
                    SDL_RenderPresent(*r);
                }
                else {
                    SDL_RenderCopy(*r,texture_welcome,NULL,&position);
                    SDL_RenderPresent(*r);
                }
            }

            if(ev.type==SDL_MOUSEBUTTONDOWN){
                if((ev.motion.x -80)*(ev.motion.x -650)<0 && (ev.motion.y -197)*(ev.motion.y -334)<0){
                    SDL_DestroyTexture(texture_welcome);
                    SDL_DestroyTexture(texture_quitter);
                    SDL_DestroyTexture(texture_lancer);
                    return 1;
                }
                if((ev.motion.x - 210)*(ev.motion.x - 425) <0 && (ev.motion.y -345)*(ev.motion.y -424)<0){
                    SDL_DestroyTexture(texture_welcome);
                    SDL_DestroyTexture(texture_quitter);
                    SDL_DestroyTexture(texture_lancer);
                    return 0;
                }
            }


    }


}



int convert2dame(position_matrice_etat matrice_pion, SDL_Rect* pion_coord, position_matrice_etat* matrice_des_dames, SDL_Rect *dames){
    int i=0;
    while(i < 7){
        if(dames[i].w == 0)break;
        i++;
    }
    if(i == 7)return -1;
    if(i<7){
        (*pion_coord)={0,0,0,0};
        dames[i].x=75 +15+ (matrice_pion.colone/2)*68;
        if(matrice_de_jeu[matrice_pion.ligne][matrice_pion.colone] < 116){
                dames[i].y=75;
                matrice_de_jeu[matrice_pion.ligne][matrice_pion.colone] = i+dameA1;

        } else {
                matrice_de_jeu[matrice_pion.ligne][matrice_pion.colone] = i+dameB1;
                dames[i].y=75+7*68;
        }
        dames[i].h = 14;
        dames[i].w = 52;
        matrice_des_dames[i].colone = matrice_pion.colone;
        matrice_des_dames[i].ligne = matrice_pion.ligne;
        verifie_possibilities_dame(&(matrice_des_dames[i]));
        return i;
    }
    return -1;
}
