#include <stdio.h>
#include <stdlib.h>


//doubly linked list kulland�m cunku  yerini bildigim  eleman�n bir onceki ve bir sonraki elemana O(1) surede ulasabiliyorum,
//ters cevirme islemi mant�ksal olarak daha kolay
//basa ve sona ekleme yaparken baslang�c ve bitisin adresini bildigim icin kolaylik sagliyor
//dongusel liste ozelligini play adl� fonksiyonumun icinde ekledim sadece orda kullandim 
FILE *fp;
FILE *fp2;
char komut[20]="",sub1[2]="",song1[51]="",song2[51]="";
typedef struct Node Node;
struct Node
{
    char data[51];
    Node *next;
    Node *prev;
};
Node *head=NULL,*tail=NULL;
Node *nowPlaying=NULL;

void ekle(char*HT,char* data2);
void yazdir(char*RF);
Node* bul(char* data3);
void sil(char* data4);
Node *kopart(Node *bulunan);
void play(char*NP);
void tersCevir();
void tasi(char* BA,char* data5 ,char* data6);


int main()
{
    fp=fopen("input.txt","a");
    fclose(fp);
    fp2=fopen("output.txt","w");
    fclose(fp2);
    //input dosyasi yoksa olsturur

    fp = fopen("input.txt", "r");
    if (fp == NULL){
         printf("input.txt dosyasi acilamadi...\n");
         exit(1);
    }

    while(fscanf(fp,"%s\t",komut)==1)
        {
            // !feof(fp)
            //fscanf(fp,"%s\t",komut);

            if (strcmp(komut, "ReversePlaylist") == 0)
            {
                tersCevir();
            }
            else if (strcmp(komut, "PrintPlaylist") == 0)
            {
                fscanf(fp,"%s",sub1);//okuma bitti
                yazdir(sub1);
            }
            else if (strcmp(komut, "PlaySong") == 0)
            {
                fscanf(fp,"%s",sub1);//okuma bitti
                play(sub1);
            }
            else if (strcmp(komut, "InsertSong") == 0)
            {
                fscanf(fp,"%s\t%s",sub1,song1);//okuma bitti
                ekle(sub1,song1);

            }
            else if (strcmp(komut, "MoveSong") == 0)
            {
                fscanf(fp,"%s\t%s\t%s",sub1,song1,song2);
                tasi(sub1,song1,song2);
            }
            else if (strcmp(komut, "RemoveSong") == 0)
            {
                fscanf(fp,"%s",song1);//okuma bitti
                sil(song1);
            }
            else
            {
                printf("hata");
            }

        }


    fclose(fp);

    //printf("Hello world!\n");
    return 1;
}

void ekle(char*HT,char* data2){
    Node *temp=(Node*)malloc(sizeof(Node));
    if(head==NULL){//hiç eleman yokssa
        head=temp;
        tail=temp;
        temp->next=NULL;
        temp->prev=NULL;
    }
    else if(strcmp(HT, "T") == 0)//eleman varsa
    {
        tail->next=temp;
        temp->prev=tail;
        temp->next=NULL;
        tail=temp;
    }
    else if(strcmp(HT, "H") == 0)//eleman varsa
    {
        head->prev=temp;
        temp->next=head;
        temp->prev=NULL;
        head=temp;
    }else {printf("hata");return;}
    strcpy(temp->data , data2);

}

void yazdir(char*RF){
    /*struct*/ Node* temp;
    if(strcmp(RF, "F") == 0){
        temp=head;
        if(temp==NULL)//liste boþ ise
        {
            fp2=fopen("output.txt","a");
            //yazdırma komutları
            fprintf(fp2,"No Songs To Print\n*****\n");
            fclose(fp2);
            return;
        }
        while(temp){

            fp2=fopen("output.txt","a");
            //yazdırma komutları
            fprintf(fp2,"%s\n",temp->data);
            fclose(fp2);
            temp=temp->next;
        }
        fp2=fopen("output.txt","a");
        fprintf(fp2,"*****\n");
        fclose(fp2);
    }
    else if(strcmp(RF, "R") == 0){
        temp=tail;
        if(temp==NULL)//liste boþ ise
        {

            fp2=fopen("output.txt","a");
            //yazdırma komutları
            fprintf(fp2,"No Songs To Print\n*****\n");
            fclose(fp2);
            return;
        }
        while(temp){
            fp2=fopen("output.txt","a");
            //yazdırma komutları
            fprintf(fp2,"%s\n",temp->data);
            fclose(fp2);
            temp=temp->prev;
        }
        fp2=fopen("output.txt","a");
        fprintf(fp2,"*****\n");
        fclose(fp2);
    }

}//yazdir sonu

Node *bul(char* data3){//
    Node* temp;
    temp=head;
    while(temp!=NULL){
        if(strcmp(data3, temp->data) == 0){
            return temp;// uyuþan veriye ilk rastlanýlan yerin adresini döndürür
        }
        temp=temp->next;
    }
    return NULL;//bulamaz ise null ççevirir
}//bul un sonu


Node *kopart(Node* bulunan){
    Node* temp=bulunan;//karışıklığı önlemek için bu işlemi yaptım
    //temp=bul(data4);önceki versiyon
    if(temp==head){//listenin ilk elemaný ise
        if(head==tail){//listede tek eleman varsa //       hata verebilir ****************dikkat
           tail=NULL;
           head=NULL;
           return temp;
        }
        head=head->next;//head artýk bir sonraki eleman
        head->prev=NULL;//yeni head in previni boþalt
        return temp;
    }
    else{// ortalardan bir düðüm ise
        temp->prev->next=temp->next;//kesinlikle yapýlacak
        if(temp==tail){//silinen son eleman ise
            tail=tail->prev;
            return temp;
        }
        temp->next->prev=temp->prev;
        return temp;
    }
}//kopart sonu

void tasi(char* BA,char* data5 ,char* data6){
    Node *islenen=bul(data5);
    Node *ref=bul(data6);
    Node *temp;//ref in bir sonraki veya  bir önceki elemanı
    kopart(islenen);
    if(strcmp(BA, "A") == 0){//refin önüne ekler
        temp=ref->next;

        ref->next=islenen;
        islenen->prev=ref;
        if(ref==tail){
            islenen->next=NULL;
            tail=islenen;
        }
        temp->prev=islenen;
        islenen->next=temp;
        return;
    }
    else if(strcmp(BA, "B") == 0){//refin arkasına ekler
        temp=ref->prev;

        islenen->next=ref;
        ref->prev=islenen;//kesin yapılacak işlemler
        if(ref==head){
            islenen->prev=NULL;
            head=islenen;
            return;
        }
        temp->next=islenen;
        islenen->prev=temp;
        return;
    }

}

void sil(char* data4){//tipi void olabilir
    Node* temp;
    temp=bul(data4);//
    if(temp==NULL){
        //printf("silinecek sarki bulunamadý yaz\n");//elemanlar uyuþmadý
        return ;
    }
    else if(nowPlaying==temp){
        fp2=fopen("output.txt","a");
        //yazdırma komutları
        fprintf(fp2,"Cannot Remove The Playing Song\n*****\n");
        fclose(fp2);
        return;
    }
    else if(temp){
        kopart(temp);//bağlantıları kestik
        free(temp);
    }

}//sil in sonu


void tersCevir(){
    if(head==NULL)return;//liste boþ ise fonksiyonu çalýþtýrmaz

    Node* current=head;
    Node* temp;

    current->prev=current->next;
    current->next=NULL;
    current=current->prev;
    //ilk node u çevirdik
    while(current){
        temp=current->prev;
        current->prev=current->next;
        current->next=temp;
        current=current->prev;
    }//prev ler ile headler yer deðiþti
    temp=head;
    head=tail;
    tail=temp;//tail ile head yer deðiþti
}//ters çevir sonu

void play(char*NP){
    if(nowPlaying==NULL&&head==NULL){//hiç calinmamis ve listtede eleman yok demek

        fp2=fopen("output.txt","a");
        //yazdırma komutları
        fprintf(fp2,"No Songs To Play\n*****\n");
        fclose(fp2);
        return;
    }
    else  if((strcmp(NP, "N") == 0)){//next i çal
        if(nowPlaying==NULL){nowPlaying=head;}//sona git
        else{
            nowPlaying=nowPlaying->next;
            if(nowPlaying==NULL){nowPlaying=head;}//
        }

        fp2=fopen("output.txt","a");
        //yazdirma komutlari
        fprintf(fp2,"Playing\t%s\n*****\n",nowPlaying->data);
        fclose(fp2);
    }
    else  if((strcmp(NP, "P") == 0)){// previ çal

        if(nowPlaying==NULL){nowPlaying=tail;}//sona git
        else{
            nowPlaying=nowPlaying->prev;
            if(nowPlaying==NULL){nowPlaying=tail;}//
        }
        fp2=fopen("output.txt","a");
        //yazdirma komutlari
        fprintf(fp2,"Playing\t%s\n*****\n",nowPlaying->data);
        fclose(fp2);
        //printf("Playing\t%s\n",nowPlaying->data);
    }
}
void outYildiz(){//output sablon
    fp2=fopen("output.txt","a");
    fprintf(fp,"*****\n");
    fclose(fp2);

}
