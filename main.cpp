// Bugra Bilge Celik - 202803004
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <time.h>

using namespace std;

void sayiAtama(vector<double>& sayilar, int& hedef){
    srand(time(NULL));
    cout << "\t\"Bir Islem\" Arayuzune Hos Geldiniz!" << endl;
    for(int i = 0; i < 5; i++){
        int x;
        x = rand() % 9 + 1;
        cout << "\n\tUretilen " << i + 1 << ". tek haneli sayimiz =\t" << x << endl;
        sayilar.push_back((double)x);
    }
    int x = (rand() % 9 + 1) * 10;
    cout << "\n\t10'nun kati olan cift haneli sayimiz =  " << x <<endl;
    sayilar.push_back((double)x);
    cout << "\n\tUlasilmasini istediginiz 3 basamakli sayiyi giriniz: ";
    cin >> hedef;
    sort(sayilar.begin(), sayilar.end());
    cout << "\n\t*------------------------------------------------------*\n\n";
}

void hesapla(vector<double>& sayilar, int hedef, vector<string>& cozumler, vector<int>& isaretler, vector<string>& isaretlerString, int& sayac) {
    if(isaretler.size() + 1 < sayilar.size()) {
        for(int i = 0; i < 4; i++) {
            isaretler.push_back(i);
            hesapla(sayilar, hedef, cozumler, isaretler, isaretlerString, sayac);
            isaretler.pop_back();
        }
        //Olusturulan 6 sayinin tamaminin kullanilmasi zorunlulugunu istersek bir alt satirdaki returnu yorum satirindan cıkartabiliriz.
        //return;
    }
    double araDeger = sayilar[0];
    for(int i = 0; i < isaretler.size(); i++) {
        switch(isaretler[i]) {
            case 0:
                araDeger += sayilar[i+1];
                break;
            case 1:
                araDeger -= sayilar[i+1];
                break;
            case 2:
                araDeger *= sayilar[i+1];
                break;
            case 3:
                if(sayilar[i+1] == 0) return;
                araDeger /= sayilar[i+1];
                break;
        }
    }
    if(abs(araDeger - hedef) < .00000000001) {
        string cozum = std::to_string((int)sayilar[0]);

        for(int i = 0; i < isaretler.size(); i++){
            cozum += isaretlerString[isaretler[i]];
            cozum += std::to_string((int)sayilar[i+1]);
        }

        if (std::find(cozumler.begin(), cozumler.end(), cozum) == cozumler.end()) {
            cozumler.push_back(cozum);
            sayac++;
            cout << "\t\t" << sayac << ". cozum  " << cozum << " = " << hedef << endl << endl;
        }
    }
}

int main() {
    vector<string> isaretlerString = {" + ", " - ", " * ", " / "};
    vector<string> cozumler;
    int hedef;
    int sayac = 0;
    while(true) {
        vector<int> isaretler;
        vector<double> sayilar;
        sayiAtama(sayilar, hedef);
        do {
            hesapla(sayilar, hedef, cozumler, isaretler, isaretlerString, sayac);
        } while(next_permutation(sayilar.begin(), sayilar.end()));
        sayac = 0;
        cout << "\tOlasi tum cozumler listelenmistir.\n\tEger bir cozum goremiyorsaniz, verilen degerler ile hedefe ulasan bir cozum bulunmamaktadir.\n";
        cout << "\tBaska uretilen degerlerle denemek icin \"ENTER\" tusuna basiniz...\n";
        cout << "\n\t*------------------------------------------------------*\n\n";
        getchar();
        getchar();
    }
    return 0;
}