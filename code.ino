#include <LiquidCrystal.h>



const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

boolean bouton1 = false;
boolean bouton2 = false;
boolean bouton3 = false;
int curseur=10000;
int inuse=00000;
int find=37;

int morse [37] = {
// lettres
12000,21110,21210,21100,10000,11210,22100,11110,11000,12220,21200,12110,22000,21000,22200,12210,22120,12100,11100,20000,11200,11120,12200,21120,21220,22110,
// chiffres
12222,11222,11122,11112,11111,21111,22111,22211,22221,22222,00000
};
char lettres [37] = {
// lettres  
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'1','2','3','4','5','6','7','8','9','0','*'
};


byte smile[8] =
  {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b10001,
  0b01110,
  0b00000,
  0b00000,
  };



void setup() {
  Serial.begin(9600);
  Serial.println ("Start !");
  lcd.begin(16, 2);
  lcd.clear();
  lcd.createChar(1, smile);

  lcd.setCursor(0, 0);
  lcd.print("arduino@bread:~$");

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);

  bouton1=digitalRead(8);
  bouton2=digitalRead(9);
  bouton3=digitalRead(10);

  delay(1000);

  

}

void search(){
  for(int i=0; i<=36; i++){
    if(inuse==morse[i]){
    find=i;
    Serial.println (lettres[find]);

    }

  }
}

void loop() {

  bouton1=digitalRead(8);
  bouton2=digitalRead(9);
  bouton3=digitalRead(10);


if (!bouton1){

if (curseur<1)
{
  inuse=0;
  curseur=10000;

} 

inuse+=curseur;
curseur/=10;



}

if (!bouton2){

if (curseur<1)
{
  inuse=0;
  curseur=10000;

} 

inuse+=curseur*2;
curseur/=10;


}




if (!bouton3){

curseur=10000;
search();
inuse=0;



}

  lcd.clear();
  lcd.setCursor(0, 0);
  if (inuse==0){
    lcd.print("00000");
  }
  else{
  lcd.print(inuse);
  }
  lcd.setCursor(0, 1);
  lcd.print(lettres[find]);
  delay(500);
}





