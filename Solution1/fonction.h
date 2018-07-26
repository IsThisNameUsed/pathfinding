#ifndef fonction_h
#define fonction_h

#define H 20
#define W 20

void DisplayLabyrinthe(int tab[][W]);
int TestDirection(int t,int indice,int y);
int TestDirection2(int t,int indice,int y);
int Chemin(int tab [][W],int a, int b);
void ChoixDirection(int tab[][W],int *i,int *j,int y);
void Digaway(int tab[][W]);
void GenerateLabyrinthe(int w,int h,int tab[][w]);
void clearLab(int tab[][W]);
#endif
