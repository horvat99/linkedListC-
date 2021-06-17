#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
void listakiiratas(void);
bool egyenlo_e(string szo);
bool torles(string szo);
void fileba_iras(char character);

struct szavak { // Definiáljuk a struck szerkezetét, amiben egy szavat és az előfordulását tároljuk
    string szo;
    int szam = 1;
    szavak *next;//Ez a következő lista elemre mutat, ugye igy lesz láncolt lista

} *start, *kov,*akt; //Erre a struckt-ra mutató pointerek

string szo_temp;
int szam_temp; // Később szükség lesz ezekre a változókra, hogy időlegesen tároljunk benne adatokat

int main() {
    int counter = 0; //Ebben tároljuk hány lista elem van, BubbleSortnak kell ez
    start = NULL;//A start pointert null-ra álítjuk
     ifstream file ("input_text.txt");


    while (!file.eof()) {//Végig megyünk a listán
        string szo_a_filebol;
        file>>szo_a_filebol; // Változóba olvassuk a szavat

        if (egyenlo_e(szo_a_filebol)) {//Ez a függvény megnézi hogy a listánkban szerepel e már az adott szó, ha nem akkor true ad vissza
            akt = new szavak();//létrehozünk egy struck-tot amiben a szavat tároljuk

            akt->szo = szo_a_filebol;//Bele tesszük a szavat
            akt->next = start;//A jelenlegi strucknak a next pointerjét a kezdő lista elemre állítjuk
            start = akt;//Majd a kezdő lista elem pointert az aktuálisra álíjuk
            //ezt akkor érted meg legkönnyebben ha lerajzolod, itt fordítva van felépítve a lista, a start_helper mindig az előző lista elemre mutat
            counter ++;//Számoljuk a lista elemeket
        }

    }
    file.close();

    int i = 0;  //szortizás
    akt = start;//Az akt pointert használjuk mindenhol hogy végig menjünk a listán ezért a start(kezdő) lista elemre álítjuk

    while(i < counter) {
        while(akt->next != NULL) {
            kov = akt->next; // A következő lista eleme
            if(akt->szo > kov->szo) { // Itt haszonlitjuk össze a két lista elem szavát és attól függően hogy melyik a nagyobb cseréljük ki a két lista elem tartalmát
                szo_temp = akt->szo;
                szam_temp = akt->szam;

                akt->szo = kov->szo;
                akt->szam = kov->szam;

                kov->szo = szo_temp;
                kov->szam = szam_temp;

                //Ez csak annyi hogy kicserélük a két lista elem tartalmát segédváltozók segitségével
            }

            akt = akt->next;//Következő lista elemre ugrunk
        }
        i++;
        akt = start;//A listán annyiszor megyünk végig ahány lista elem van, igy biztos sorba rendezi
    }

    listakiiratas();//Kiiratja a listát
}

void listakiiratas(void) {

    akt = start;//Szokásos h végig tudunk menni a listán

    cout <<setw(15)<<"Szavak"<<'\t';
    cout <<setw(15)<<"Gyakorisag"<<'\t';

    cout<<endl;
    cout<<endl;

    while(akt != NULL ) {
        cout <<setw(15)<<akt->szo<<'\t';
        cout <<setw(15)<<akt->szam<<'\t';

        cout << endl;
        akt = akt->next;
    }
    string delete_or_write;
    cout<<"Ha torolni akar, irja be hogy delete, ha fileba irni akkor write(vagy akarmit)"<<endl;
    cin>>delete_or_write;//Bekérjük mit szeretne a felhasználó csinálni
    if (delete_or_write == "delete") {
        string delete_word;
        cout<<"Irja be a torolni kivant szavat"<<endl;
        cin>>delete_word;
        //system("CLS");//törli a consoleban lévő szöveget
        if (torles(delete_word)) {//Törli az átadott szavat
            cout<<"Sikeres torles"<<endl;
        }
        else {
            cout<<"Nem talalhato ilyen szo a listaban"<<endl;
        }
    }
    else {
        char character;
        cout<<"Adja meg a kezdobetut, amivel kezdodo szavak mennek az uj fileba"<<endl;
        cin>>character;//bekérjük a kezdőbetűt
       // system("CLS");
        fileba_iras(character);//fájlba irás

    }
    listakiiratas();// meghívja a függvény saját magát, igy többször tudunk törölni a listából és fájlba irni


}

bool egyenlo_e(string szo) {
    szavak *akt_temp;
    akt_temp = start;

    while(akt_temp != NULL ) {
        if (akt_temp->szo == szo) {//Végig megyünk a listán és ha találunk olyan szavat
        	//ami megegyezik a avval amit átadtunk neki akkor megnöveli a szó előfordulását eggyel
        	//és return false; vagyis nem egyedi a lista elem és nem adjuk a listához újra
            akt_temp->szam ++;
            return false;
        }

        akt_temp = akt_temp->next;
    }
    return true;
}


bool torles(string szo) {//Töröl egy szavat a listából


    szavak *akt_temp;
    szavak *prev_temp = NULL;//Ez jelöli az előző lista elemet
    akt_temp =start;

    while(akt_temp != NULL ) {
        if (akt_temp->szo == szo) {//Szokásosan végig megyünk a listán és keressük azt szót amit törölni szeretnénk
            if (prev_temp != NULL) {// ha a lista elemnek van előzője
                prev_temp->next = akt_temp->next;//Az előzőnek a next pointerjét átálítjuk az aktuális pointer következőjére, evvel kihagyva a listából az aktuális lista elemet(ezt is rajzold le szerintem)
            }
            else {//Ha nincs előző vagyis az első lista elemet szeretnénk törölni akkor a start-ot a következőre álitjuk mivel ha kitöröljük az elsőt akkor már nem avvak fog indulni a lista
                start = akt_temp->next;
            }
            delete akt_temp;//csak töröljük az aktuális lista elemet miután elintéztük a pointerek álitgatását
            return true;
        }
        prev_temp = akt_temp;//Itt menjük az előzőt(következő iterációban ez lesz az előző igaz? :D)
        akt_temp = akt_temp->next;//Lépünk a következőre
    }
    return false;
}

void fileba_iras(char character) {
    ofstream new_file ("output_text.txt");//Fájl amibe irunk
    szavak *akt_temp;
    akt_temp = start;

    while(akt_temp != NULL ) {
        if (akt_temp->szo[0] == character) {//Végig megyünk a listán és keressük a megfellő betűvel kezdődő szavakat
            new_file<<akt_temp->szo<<" ";//Ha megvan az egyezés csak beleirjuk a fájlba.
        }
        akt_temp = akt_temp->next;//Következőre lépünk
    }
}
