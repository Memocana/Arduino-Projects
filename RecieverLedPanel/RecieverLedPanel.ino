//reciever Ardiuno
int getter = 0; //0 yerine en üstteki soldakinin yerini yazın
void setup () {
  pinMode(5,INPUT);
  pinMode(6,INPUT);
}

void loop() {
  if(digitalRead(5)){
    digitalWrite(getter, digitalRead(6)); //en üst 4 sıradakileri arka arkaya bağlarsak çok kolay olur burası
    getter++;
    if (getter == 4) { //initial value + 4 burası
      getter = 0; //initial value
      digitalWrite(/*en alttaki sıra 1*/,digitalRead(/*bi üstündeki*/));
      digitalWrite(/*en alttaki sıra 2*/,digitalRead(/*bi üstündeki*/));
      digitalWrite(/*en alttaki sıra 3*/,digitalRead(/*bi üstündeki*/));
      digitalWrite(/*en alttaki sıra 4*/,digitalRead(/*bi üstündeki*/));
      digitalWrite(/*en alttaki sıra üstü 1*/,digitalRead(/*bi üstündeki*/));
      digitalWrite(/*en alttaki sıra üstü 2*/,digitalRead(/*bi üstündeki*/));
      //...
      // böyle devam eder...  veya bi for loop nasıl bağladığına bağlı olarak panelleri
    }
  }
}
