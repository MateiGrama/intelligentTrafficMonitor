
//SENZORII: denumiti dupa formula : s + <<indice sens>> + _ + <<indice de ordine>>
int s1_1=A0;
int s1_2=A1;
int s1_3=2;
int sd1_1=3;
int sd1_2=4;
int s2_1=5;
int s2_3=6;
int s3_1=7;
int s3_3=8;
int s4_1=9;
int s4_3=10;
int read1; //variabilele cu valorile senzorilor
int read2; 
int read3; 
int read4; 
int read5; 
int read6; 
int read7; 
int read8; 
int read9; 
int read10;
int read11;  

//LEDURI: denummiri: r/g+ (1(=s1+s3) || 2(=s2+s4))
int g=13;
int r1=12;
int r2=11;
int v1=10;
int v2=9;

//Semafor:
int stare=1;
int stare_galben=1;
int conditieValidare;
unsigned long last_millis=0;
int timp=5000;//intervalul de timp pe care il are semaforul pana la urmatoarea schmbare
           // Acesta din urma se va actualiza la fiecare schimbare in funnctie de nr-ul de masini

// Matrice timpi: Nr masini: | 0 |  1-2 | 3-5 | 6-10 | 11-15 | 16-20 | 20+ |
//                     Timp: | 0 |   5  |  10 |  20  |   30  |   40  |  50 | *1000
int timpi[]={0,5000,5000,10000,10000,10000,20000,20000,20000,20000,20000,30000,30000,30000,30000,30000,40000,40000,40000,40000,40000,50000,50000,50000,50000,50000};

//Contoare:
int masina_noua1=1; //variabilele care dau acceptul pentru re-in/decrementare 
int masina_noua2=1; //corespund cu variabilele read
int masina_noua3=1;
int masina_noua4=1;
int masina_noua5=1;
int masina_noua6=1;
int masina_noua7=1;
int masina_noua8=1;

int Masini1=0; //Contoarele Finale
int Masini2=0;
int masini1=0; //Contoarele per fiecare sens
int masini2=0;
int masini3=0;
int masini4=0;

//Cronometru:
int cronometru1=0;
int cronometru2=0;
unsigned long start_crono1;
unsigned long start_crono2;

void setup() {
   pinMode(s1_3, INPUT);
   pinMode(sd1_1, INPUT);
   pinMode(sd1_2, INPUT);
   pinMode(s2_1, INPUT);
   pinMode(s2_3, INPUT);
   pinMode(s3_1, INPUT);
   pinMode(s3_3, INPUT);
   pinMode(s4_1, INPUT);
   pinMode(s4_3, INPUT);
   
   pinMode(g, OUTPUT);
   pinMode(r1, OUTPUT);
   pinMode(r2, OUTPUT);
   pinMode(v1, OUTPUT);
   pinMode(v2, OUTPUT);

   digitalWrite(g,160);//begin semafor
   
   Serial.begin(115200);
}

void loop() {
  //////////////////////////////CITIRE VALORI SENZORI//////////////////////////////////////
  read1 = analogRead(s1_1);
  read2 = analogRead(s1_2);
  read3 = analogRead(s1_3);
  read4 = analogRead(sd1_1);
  read5 = analogRead(sd1_2);
  read6 = analogRead(s2_1);
  read7 = analogRead(s2_3);
  read8 = analogRead(s3_1);
  read9 = analogRead(s3_3);
  read10 = analogRead(s4_1);
  read11 = analogRead(s4_3);

//PROBA: (verificare senzori)

//  Serial.print("read1(s1_1): ");
//  Serial.print(read1);
//  Serial.print("  read2(s1_2): ");
//  Serial.print(read2);
//  Serial.print("  read1(s1_3): ");
//  Serial.println(read3);
//  return;
  
  //////////////////////////////CONTOARE MASINI////////////////////////////////////////////
  //S1
  if(read1>100 && masina_noua1){                       //A se modifica( conditia la sesnsor reaing) in caz de nevoie
      masini1++;
      if(Masini1 < masini1)
        Masini1=masini1;
      masina_noua1=0;
  }
  else if(read1<100)
    masina_noua1=1;                                   //A se modifica in caz de nevoie
   
  if(read3>100 && masina_noua2){                       //A se modifica in caz de nevoie
      if(masini1>0)
        masini1--;
      if(masini1 > masini3)
        Masini1=masini1;
      else
        Masini1=masini3;
      masina_noua2=0;
  }    
  else if(read3<100)                                 //A se modifica in caz de nevoie
    masina_noua2=1;

  //S2
  if(read6>100 && masina_noua3){                       //A se modifica( conditia la sesnsor reaing) in caz de nevoie
      masini2++;
      if(Masini2 < masini2)
        Masini2 = masini2;
      masina_noua3=0;
  }
  else if(read6<100)
    masina_noua3=1;                                   //A se modifica in caz de nevoie
   
  if(read7>100 && masina_noua4){                       //A se modifica in caz de nevoie
      if(masini2>0)
        masini2--;
      if(masini2 > masini4)
        Masini2=masini2;
      else
        Masini2=masini4;
      masina_noua4=0;
  }    
  else if(read7<100)                                 //A se modifica in caz de nevoie
    masina_noua4=1;
  
  //S3
  if(read8>100 && masina_noua5){                       //A se modifica( conditia la sesnsor reaing) in caz de nevoie
      masini3++;
      if(Masini1 < masini3)
        Masini1 = masini3;
      masina_noua5=0;
  }
  else if(read8<100)
    masina_noua5=1;                                   //A se modifica in caz de nevoie
   
  if(read9>100 && masina_noua6){                       //A se modifica in caz de nevoie
      if(masini3>0)
        masini3--;
      if(masini3 > masini1)
        Masini1=masini3;
      else
        Masini1=masini1;
      masina_noua6=0;
  }    
  else if(read9<100)                                 //A se modifica in caz de nevoie
    masina_noua6=1;
     
  //S4
  if(read10>100 && masina_noua7){                       //A se modifica( conditia la sesnsor reaing) in caz de nevoie
      masini4++;
      if(Masini2 < masini4)
        Masini2 = masini4;
      masina_noua7=0;
  }
  else if(read10<100)                                  //A se modifica in caz de nevoie
    masina_noua7=1; 
   
  if(read11>100 && masina_noua8){                       //A se modifica in caz de nevoie
      if(masini4>0)
        masini2--;
      if(masini4 > masini2)
        Masini2=masini4;
      else
        Masini2=masini2;
      masina_noua8=0;
  }    
  else if(read11<100){                                 //A se modifica in caz de nevoie
    masina_noua8=1; 
  }

//PROBE:
//   Serial.print("nr masini pe sensul1: ");
//   Serial.println(masini1);
//   return;

  //////////////////////////////CRONOMETRE/////////////////////////////////////////////////
  
  ////////////////CRONOMETRUL1
  if(!cronometru1){
    if(read1 >100){                                 //A se modifica in caz de nevoie
//      Serial.println("Cronometru 1 on");
      start_crono1 = millis();
      cronometru1 = 1;
    }
  }
  else{
    if(read2 > 100){                                //A se modifica in caz de nevoie
      cronometru1 = 0;
      //COD DE TEST///////////////////////////
//      Serial.print("Cronometru 1 off:");
//      Serial.println(millis()-start_crono1);
//      Serial.print("Millis1= "); 
//      Serial.print(millis());
//      Serial.print(" start1= ");
//      Serial.println(start_crono1);
      ///////////////////////////////////////
      if(millis()-start_crono1 > 120){                             //
        //<FUNCTIE CAMERA>
        Serial.println("1");
      }
    }
  }
  
  //////////CRONOMETRU2
  if(!cronometru2){
    if(read4 >100 ){    
      //Serial.println("Cronometru 2 on");
      start_crono2 = millis();
      cronometru2 = 1;
    }
  }
  else{
    if(read5 >100 ){
      cronometru2 = 0;
      if(millis()-start_crono2) > 120){
        //<FUNCTIE CAMERA>
        Serial.println("Limita depasita 2");
      //PROBA:
//      Serial.print("Cronometru 2 off:");
//      Serial.println(millis()-start_crono2);
//
//      Serial.print("Millis2= "); 
//      Serial.print(millis());
//      Serial.print(" start2= ");
//      Serial.println(start_crono2);
      }
    }
  }

  //////////////////////////SEMAFOARE/////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(stare_galben){
    if(millis()- last_millis >2000){ 
      if(stare==1){
        if(Masini2> 25)
          timp= 50000;
        else
        timp= timpi[Masini2];
        stare= stare*(-1);
        stare_galben=0;
        digitalWrite(r2,160);
        digitalWrite(v1,160);
        digitalWrite(g,0);
        last_millis= millis();
//        Serial.println("  Acum se stinge galben, se aprinde 2");
      }
      else{
        if(Masini1> 25)
          timp= 50000;
        else      
        timp= timpi[Masini1];
        stare= stare*(-1);
        stare_galben=0;
        digitalWrite(r1,160);
        digitalWrite(v2,160);
        digitalWrite(g,0);
        last_millis= millis();
//        Serial.println("Acum se stinge galben, se aprinde 1");
      }
    }
  }
  else{
    if(stare==-1)
      conditieValidare=Masini2;
    else
      conditieValidare=Masini1;
    if(millis()-last_millis>timp && conditieValidare){
      digitalWrite(r1,0);
      digitalWrite(r2,0);
      digitalWrite(v1,0);
      digitalWrite(v2,0);
      digitalWrite(g,160);
      stare_galben=1;
      last_millis= millis();
      
//      Serial.println("Galben acum.");
    }
  }
  delay(10);
}
