/* Everaldo Gomes - 31/10/2012
 *
 * Jogo da Forca
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>


#define MAX 100
#define VENCEU 1
#define JOGANDO 0
#define PERDEU -1



typedef struct {
  char palavra[MAX + 1];
  char tentativas[MAX + 1];
  int num_acertos;
  int num_tentativas;
  int max_tentativas;
  int status;
} jogo_da_forca;



void inicializa(jogo_da_forca *forca);
void le_jogada(jogo_da_forca *forca);
void verifica_vencedor(jogo_da_forca *forca);
int fim_do_jogo(jogo_da_forca forca);
void imprime(jogo_da_forca forca);
void letras_digitadas(jogo_da_forca forca);
void mensagem(jogo_da_forca forca);

int main(void){
  jogo_da_forca forca;

  inicializa(&forca);

  do{
    le_jogada(&forca);
    verifica_vencedor(&forca);
    imprime(forca);

  }while(! fim_do_jogo(forca));
  
  mensagem(forca);

  return 0;
} 



void inicializa(jogo_da_forca *forca){
  int i;
  strcpy(forca->palavra, "banana");
  for(i = 0; i <= MAX; i++){
    forca->tentativas[i] = '\0';
  }
  forca->num_acertos = 0;
  forca->num_tentativas = 0;
  forca->max_tentativas = 7;
  forca->status = JOGANDO;
}

void le_jogada(jogo_da_forca *forca){
  char jogada;
  int valido = 0;
  int i;
  do{
    printf("Digite uma letra: ");
    scanf("%c", &jogada);
    while( getchar() != '\n'); //limpa buffer
    if( strchr(forca->tentativas, jogada) == NULL){
      valido = 1;
      forca->tentativas[strlen(forca->tentativas)] = jogada;
    }
    else{
      puts("Você já digitou esta letra antes. Tente novamente!!");
      letras_digitadas(*forca);
    }
  }while(! valido);
}

void verifica_vencedor(jogo_da_forca *forca){
  int i, tam_palavra, tam_tentativas, acerto;

  tam_palavra = strlen(forca->palavra);
  tam_tentativas = strlen(forca->tentativas);
  acerto = 0;
  for(i = 0; i < tam_palavra; i++){
    if (forca->palavra[i] == forca->tentativas[tam_tentativas - 1 ]){
      forca->num_acertos++;
      acerto = 1;
    }
  }

  if (! acerto ) forca->num_tentativas++;

  if(forca->num_acertos == tam_palavra)
    forca->status = VENCEU;
  else if (forca->num_tentativas > forca->max_tentativas)
    forca->status = PERDEU;

}

void imprime(jogo_da_forca forca){
  int i;
  int tam_palavra = strlen(forca.palavra);
  char letra;

  printf("Palavra escolhida: ");
  for(i = 0; i < tam_palavra ; i++){
    letra = '*';
    if(strchr(forca.tentativas, forca.palavra[i]) ){
      letra = forca.palavra[i]; 
    }
    printf("%c", letra);
  }
  letras_digitadas(forca);
  printf("\nTentativas: %d/%d\n", forca.num_tentativas, forca.max_tentativas);

}


int fim_do_jogo(jogo_da_forca forca){

  if (forca.status == VENCEU || forca.status == PERDEU){
    return 1;
  }
  else
    return 0;

}

void letras_digitadas(jogo_da_forca forca){
  int i, tam_tentativas ;
  tam_tentativas = strlen(forca.tentativas);

  printf("\nLetras já digitadas: ");
  for(i = 0; i < tam_tentativas; i++){
    printf("%c ", forca.tentativas[i]);
  }
  puts("");
}

void mensagem(jogo_da_forca forca){
  if (forca.status == VENCEU){
    puts("Parabéns, você venceu!!!");
  }
  else {
    puts("Infelizmente você perdeu. Tente novamente");
  }
}
