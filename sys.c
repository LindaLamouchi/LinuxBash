#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
  #include <stdio.h>
#include <pthread.h>
       #include <readline/readline.h>
       #include <readline/history.h>
#define TAILLE_MAX 1000
int ls(){
struct dirent *d;
DIR *dir;
if((dir=opendir("."))==NULL) return 0;
while((d=readdir(dir))){printf("%s\n",d->d_name);}
}

/////print la dir
void printDr(){
char cwd[1024];
getcwd(cwd,sizeof(cwd));
printf("\n>>>Dir : %s>>>",cwd);}
////////////////thread
void *thread_1(void *arg)

{

printf("\n>>>ls Result...\n");
ls();
printDr();
    /* Pour enlever le warning */
 (void) arg;
    pthread_exit(NULL);

}
/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void)
{
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;

    /* On fork() tant que l'erreur est EAGAIN */
    do {
	pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));

    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/* La fonction son_process effectue les actions du processus fils */
void son_process(char *arg[])
{
    if (execv("/usr/bin/atom", arg) == -1) {
  	perror("execv");
	exit(EXIT_FAILURE);
    }
}

/* La fonction father_process effectue les actions du processus père */
void father_process(void)
{
    printf("\nVotre programme se lance separamment!\n");
}
//init shell
void initsh(){
  char cwd[1024],s[1024];
  const char * path = getenv( "PATH" );
  FILE* fichier = NULL;
printf("\033[01;34m\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
printf("\n ");
printf("\n>>-------------------------------------------Welcome--------------------------------------------------------->>\033[00m\n");
printDr();
getcwd(cwd,sizeof(cwd));
strcpy(s,"PATH = ");
strcat(s,path);
strcat(s,"\nHOME = ");
strcat(s,cwd);
   fichier = fopen("profile.txt", "w");
   if (fichier != NULL)

   {
       fputs(s, fichier);
       fclose(fichier);
   }
printf("\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////MAIN
//appel avec cc sys.c -lreadline -lpthread
int main(int argc, char *argv){
system("clear");
char cmd[100];
initsh();
int choix;
char line[1024];
int count = 0;

printf("\033[00;31m\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
printf("-------------------Tapper le num de la cmd : \n");
printf("\n >> 0 : exit| 1 : liste| 2 : dir| 3 : clear| 4 : pipe| 5 : creer un dossier| 6 : lancer un code d'un fichier >>\n");
printf("\n >> 7 : creer des aleas | 8 : redirection | 9 : lancer un programme externe >>\n");
printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[00m\n");

scanf("%d",&choix);
do{
switch(choix){
case 0:{printf("\n GoodBye!!!\n");exit(0);}
case 1:{system("clear");ls();}break;
case 2:{system("clear"); printDr();}break;
case 3:{system("clear");}break;
case 4:{
//char m01,a,m1[30],m2[20];u
system("clear");
printf("\ninser ta ligne de commande SVP : liste() || mkdir() || prtdr() \n");

    char* buf;
    char part[30];
    char *suiteprt2=NULL;
    char part1[30],part2[30];
    int i,l11=0,l=0;
    char cmd1[l11],cmd2[10];

    buf = readline("\n>>> ");

    printf("traitement en cours >>> %s",buf);
    suiteprt2=strchr(buf,'|');
    strcpy(part2,suiteprt2);

    //l2=strlen(part2); //longeur de pt2
   //part1
   i=0;
   while(buf[i]!='|'){
   part1[i]=buf[i];
   i++;}
   printf("\n%s\n",part1);
   //partionner la partie 1
   l=i; //taille de part1
   i=0;
   while(part1[i]!=' '){
   cmd1[i]=part1[i];
   i++;}
   l11=i; //taille de cmd1
   printf("\n%s\n",cmd1);
   i=0;
   while(i!=l11){printf("\nresultat en cours de chargement ...\n");i++; }
   if(strcmp(cmd1,"liste")){
    pthread_t thread1;
    printf("Avant la création du thread.\n");
    if (pthread_create(&thread1, NULL, thread_1, NULL)) {
    perror("pthread_create");
    return EXIT_FAILURE;
    }
    if (pthread_join(thread1, NULL)) {
    perror("pthread_join");
    return EXIT_FAILURE; }
    printf("Après la création du thread.\n");


    }
   //part2
   part2[0]=' ';
   printf("\npart deux : %s\n",part2);
   i=0;
   while(part2[i+1]!=' '){
   cmd2[i]=part2[i+1];
   i++;}
   printf("\n%s\n",cmd2);



}break;
case 5:{
char ex[10]; printf("donner le nom du dossier :"); scanf("%s",ex);mkdir(ex,0777); ls();
}break;
case 6:{
FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    fichier = fopen("text.txt", "r");
    if (fichier != NULL)

    {
        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        printf("%s", chaine); // On affiche la chaîne
        fclose(fichier);
        if(strcmp(chaine,"liste")) ls(); printDr();
     }

}break;
case 7:{
  char *aleas,z='N';
  char *ptr,*test;
  char cmd[10];
   int init_size,a=0;
system("clear");
printf("\n\033[00;31m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
printf("-------------------Tapper la chaine sous la forme (Nom-aleas cmd) : \n");
printf("\033[00m\n\n");
aleas = readline("\n>>> ");
printf(">>>Enregistrement de l'entree en cours : ( %s ) \n",aleas);
init_size = strlen(aleas);
ptr = strtok(aleas, " ");
while(ptr != NULL)
{
  if(((strcmp(ptr,"liste"))!=0)&&((strcmp(ptr,"printDr"))!=0)) {printf("\nvotre nouvelle cmd est : '%s' \n",ptr); strcpy(cmd,ptr);}
  printf("'%s'\n", ptr);

  if(strcmp(ptr,"liste")) {printf("\nvotre cmd remplacée est : \n");a=1;}
  else if(strcmp(ptr,"printDr")) {printf("\nvotre cmd remplacée est : \n");a=2;}
  ptr = strtok(NULL, " ");
}
printf("Essayez votre nouvelle cmd :");
test = readline("\n>>> ");
printf("\n resultat de %s",test);
if(strcmp(test,cmd)==0 && a==1)
{
goto n;
}
else if(strcmp(test,cmd)==0 && a==2)
{
  goto s;
}
else break;
n:
printDr();
goto e;
s:
ls();
e:break;


}break;
case 8:{
  FILE* fichier = NULL;
  char *line;
  char *ptr,*test;
  char cmd[10];
  struct dirent *d;
  DIR *dir;
   int init_size,a=0;
system("clear");
printf("\n\033[00;31m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
printf("-------------------Tapper la chaine sous la forme (Nom>file.txt) : \n");
printf("\033[00m\n\n");
line = readline("\n>>> ");
printf(">>>Verification de l'entree en cours : ( %s ) \n",line);
init_size = strlen(line);
ptr = strtok(line, ">");
strcat(cmd,ptr);
printf("votre commande est : '%s'",cmd);

  if((strcmp(ptr,"liste"))==0){

    fichier = fopen("liste.txt", "w");
    if((dir=opendir("."))==NULL) return 0;
    if (fichier != NULL)

    {


    while((d=readdir(dir))){
      fputs(d->d_name, fichier);
    }
        fclose(fichier);
      }
}

}break;
case 9:{
char *arg[] = { "atom", NULL, NULL };
char *line;
line = readline("\n>>> ");
    pid_t pid = create_process();

    switch (pid) {
    /* Si on a une erreur irrémédiable (ENOMEM dans notre cas) */
    case -1:
	perror("fork");
	return EXIT_FAILURE;
	break;
    /* Si on est dans le fils */
    case 0:
	son_process(arg);
	break;
    /* Si on est dans le père */
    default:
	father_process();
	break;
    }
}break;
default:break;
}
printf("\n\033[00;31m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
printf("-------------------Tapper le num de la cmd : \n");
printf("\n >> 0 : exit| 1 : liste| 2 : dir| 3 : clear| 4 : pipe| 5 : creer un dossier| 6 : lancer un code d'un fichier >>\n");
printf("\n >> 7 : creer des aleas | 8 : redirection | 9 : lancer un programme externe>>\n");
printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[00m\n\n");
scanf("%d",&choix);
}while(choix!=-1);
 return 0;
}
