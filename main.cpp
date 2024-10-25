#include <iostream>
#include <vector>
#define EPS 1e-7
using namespace std;

void drukujMacierz(vector<vector<double>> matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
            cout << matrix[i][j] << "\t";
        cout << endl;
    }
}

void drukujX(vector<double> matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        cout << matrix[i] << "\t";
    }
    cout<<endl;
}

vector<vector<double>> utworzMacierz(int rozmiar){
    vector<vector<double>> wlasnaMacierz;
    cout << "Wpisz elementy macierzy: \n";
    for(int i = 0; i < rozmiar; i++)
    {
        vector<double> wiersz;
        for(int j = 0; j < rozmiar; j++)
        {
            cout << "Wpisz element pod indeksem [" << i << "][" << j << "]: ";
            double temp;
            cin >> temp;
            wiersz.push_back(temp);
        }
        wlasnaMacierz.push_back(wiersz);
    }
    return wlasnaMacierz;
}

vector<double> utworzWektorWyr(int rozmiar){
    cout << "Podaj wyraze wolne: \n";
    vector<double> wyrazyWolneW;
    for(int i = 0; i < rozmiar; i++)
    {
        cout << "Wpisz wyraz wolny pod indeksem [" << i << "]: ";
        double temp;
        cin >> temp;
        wyrazyWolneW.push_back(temp);
    }
    return wyrazyWolneW;
}

vector<vector<double>> eliminacjaPodstawowa(vector<vector<double>> tabA, vector<double> tabB, bool dzial){
    for (int i = 0; i<tabA.size(); i++) {
        tabA[i].push_back(tabB[i]);
    }
    for (int j = 1; j<tabA.size(); j++){
        if (tabA[j-1][j-1]!=0) {
            for (int i = j; i < tabA.size(); i++) {
                double p = tabA[i][j-1]/tabA[j-1][j-1];
                for (int k = 0; k < tabA[0].size(); k++) {
                    tabA[i][k] -= p*tabA[j-1][k];
                }
            }
        } else {
            dzial = false;
            break;
        }
    }
    return tabA;
}

vector<double> obliczX(vector<vector<double>> tabA, vector<double> tabB, bool mozliwe){
    if(tabA[tabA.size()-1][tabA.size()-1] != 0)
    {
        for (int i = (int)tabB.size()-1; i>=0; i--) {
            for (int j = i + 1; j<=tabB.size()-1; j++) {
                tabB[i] -= tabA[i][j]*tabB[j];
            }
            tabB[i] /= tabA[i][i];
        }
    } else {
        cout<<"Postepowanie odwrotne nie jest mozlive"<<endl;
        mozliwe = false;
    }
    return tabB;
}

vector<vector<double>> eliminacjaZWyboremMaxWKol(vector<vector<double>> tabA, vector<double> tabB, bool dzial){
    for(int i = 0; i < tabA.size(); i++) tabA[i].push_back(tabB[i]);
    
    for(int i = 0; i < tabA.size(); i++){
        int indeksMax = i;
        for(int j = i+1; j < tabA.size(); j++){
            if(abs(tabA[j][i]) > abs(tabA[indeksMax][i]))
                indeksMax = j;
        }
        if(abs(tabA[indeksMax][i]) < EPS){
            cout<<"Uklad nie ma dokladnie jednego rozwiazania\n";
            return {};
        }
        for(int j = 0; j < tabA[0].size(); j++){
            swap(tabA[i], tabA[indeksMax]);
        }

        for (int j = 1; j<tabA.size(); j++){
            if (tabA[j-1][j-1]!=0) {
                for (int i = j; i < tabA.size(); i++) {
                    double p = tabA[i][j-1]/tabA[j-1][j-1];
                    for (int k = 0; k < tabA[0].size(); k++) {
                        tabA[i][k] -= p*tabA[j-1][k];
                    }
                }
            } else {
                dzial = false;
                break;
            }
        }
    }
    return tabA;
}

vector<vector<double>> eliminacjaZWyboremMaxWWie(vector<vector<double>> tabA, vector<double> tabB, vector<pair<int, int>>& indeksyKolumn, bool dzial){
    for(int i = 0; i < tabA.size(); i++) tabA[i].push_back(tabB[i]);
    vector<pair<int, int>> paryKolumn;
    for(int i = 0; i < tabA.size(); i++){
        int indeksMax = i;
        for(int j = i+1; j < tabA.size(); j++){
            if(abs(tabA[i][j]) > abs(tabA[i][indeksMax]))
                indeksMax = j;
        }
        if(abs(tabA[i][indeksMax]) < EPS){
            cout<<"Uklad nie ma dokladnie jednego rozwiazania\n";
            return {};
        }
        if (i!=indeksMax) {
            paryKolumn.insert(paryKolumn.begin(), make_pair(i, indeksMax));
            for (int j = 0; j<tabA.size(); j++) {
                swap(tabA[j][i], tabA[j][indeksMax]);
            }
        }
        for (int j = 1; j<tabA.size(); j++){
            if (tabA[j-1][j-1]!=0) {
                for (int i = j; i < tabA.size(); i++) {
                    double p = tabA[i][j-1]/tabA[j-1][j-1];
                    for (int k = 0; k < tabA[0].size(); k++) {
                        tabA[i][k] -= p*tabA[j-1][k];
                    }
                }
            } else {
                dzial = false;
                break;
            }
        }
    }
    indeksyKolumn = paryKolumn;
    return tabA;
}

vector<vector<double>> eliminacjaZWyboremMax(vector<vector<double>> tabA, vector<double> tabB, vector<pair<int, int>>& indeksyKolumn, bool dzial){
    for(int i = 0; i < tabA.size(); i++) tabA[i].push_back(tabB[i]);
    vector<pair<int, int>> paryKolumn;
    for(int i = 0; i < tabA.size(); i++)
    {
        int maksI = i;
        int maksJ = i;
        for(int j = i; j < tabA.size(); j++)
        {
            for(int k = i; k < tabA.size(); k++)
            {
                if(abs(tabA[j][k]) > abs(tabA[maksI][maksJ]))
                {
                    maksI = j;
                    maksJ = k;
                }
            }
        }
        if(abs(tabA[maksI][maksJ]) < EPS){
            cout<<"Uklad nie ma dokladnie jednego rozwiazania\n";
            return {};
        }
        if (maksI != i) {
            for (int j = 0; j<tabA.size()+1; j++) {
                swap(tabA[i], tabA[maksI]);
            }
        }
        if(maksJ != i){
            paryKolumn.insert(paryKolumn.begin(), make_pair(i, maksI));
            for (int j = 0; j<tabA.size(); j++) {
                swap(tabA[j][i], tabA[j][maksJ]);
            }
        }
        if (tabA[i][i]!=0) {
            for (int j = i+1; j < tabA.size(); j++) {
                double p = tabA[j][i]/tabA[i][i];
                for (int k = 0; k < tabA[0].size()+1; k++) {
                    tabA[j][k] -= p*tabA[i][k];
                }
            }
        } else {
            dzial = false;
            break;
        }
        
    }
    indeksyKolumn = paryKolumn;
    return tabA;
}

int main(int argc, const char * argv[]) {
    vector<pair<int, int>> indeksyKolumn;
    vector<vector<double>> wlasnaMacierz;
    vector<double> wyrazyWolneW;
    vector<vector<double>> macierzPodst3 = {
        {14, -13, 3, -16, -42},
        {3.5, -18, 13, -23.75, -21},
        {3.5, 3, -5.25, 9.25, 10.5},
        {2, 14.5, -10.5, 18.5, 21},
        {1.5, 6.75, -9.25, 17, -10.5}
    };
    vector<double> wyrazyWolne3 = {-37, -5.5, 12.5, 23.5, -45.25};
    vector<vector<double>> macierzPodst1 =
                {
                        {1,1,0,-3},
                        {1,4,-1,-4},
                        {0.5, 0.5, -3, -5.5},
                        {1.5, 3, -5, -9}
                };
    vector<double> wyrazyWolne1 = {1, -2, 1.5, -0.5};

    vector<vector<double>> macierzPodst2 =
                {
                        {2.25, -2.5,4,-5.25},
                        {-3,-7.5,6.5,0},
                        {-6.25, -12.5,0.25, 5.25},
                        {9, 10, 7, -21}
                };
    vector<double> wyrazyWolne2 = {-1, 17, 24.25, -33};
    int metoda, dane;
    cout<<"Wybierz metode obliczenia:"<<endl
        <<"1) Podstawowa;"<<endl
        <<"2) Z wyborem elementu maksymalnego w kolumnie;"<<endl
        <<"3) Z wyborem elementu maksymalnego w wierszu"<<endl
        <<"4) Z pelnym wyborem elementu maksymalnego"<<endl;
    cin>>metoda;
    cout<<"Wybierz typ danych:"<<endl
        <<"1) Dane zawarte w programie;"<<endl
        <<"2) Wlasne dane"<<endl;
    cin>>dane;
    bool dzial = true;
    switch (metoda) {
        case 1:
        {
            switch (dane) {
                case 1:
                {
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(macierzPodst1);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolne1);
                    macierzPodst1 = eliminacjaPodstawowa(macierzPodst1, wyrazyWolne1, dzial);
                    for (int k = 0; k<macierzPodst1.size(); k++) {
                        if (macierzPodst1[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolne1.size(); i++) {
                            wyrazyWolne1[i] = macierzPodst1[i][macierzPodst1[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolne1 = obliczX(macierzPodst1, wyrazyWolne1, mozliwe);
                        if (mozliwe) {
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(macierzPodst1);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolne1);
                        }
                    }
                    break;
                }
                case 2:
                {
                    int rozmiar;
                    cout << "Wpisz rozmiar macierzy: ";
                    cin >> rozmiar;
                    wlasnaMacierz = utworzMacierz(rozmiar);
                    wyrazyWolneW = utworzWektorWyr(rozmiar);
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(wlasnaMacierz);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolneW);
                    wlasnaMacierz = eliminacjaPodstawowa(wlasnaMacierz, wyrazyWolneW, dzial);
                    for (int k = 0; k<wlasnaMacierz.size(); k++) {
                        if (wlasnaMacierz[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolneW.size(); i++) {
                            wyrazyWolneW[i] = wlasnaMacierz[i][wlasnaMacierz[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolneW = obliczX(wlasnaMacierz, wyrazyWolneW, mozliwe);
                        if (mozliwe) {
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(wlasnaMacierz);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolneW);
                        }
                    } else cout<<"Zero na przekatnej"<<endl;
                    break;
                    default:
                        cout<<"Niepoprawny wybor"<<endl;
                        break;
                }
                    }
            break;
        }
        case 2:{
            switch (dane) {
                case 1:
                {
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(macierzPodst2);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolne2);
                    macierzPodst2 = eliminacjaZWyboremMaxWKol(macierzPodst2, wyrazyWolne2, dzial);
                    for (int k = 0; k<macierzPodst2.size(); k++) {
                        if (macierzPodst2[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolne2.size(); i++) {
                            wyrazyWolne2[i] = macierzPodst2[i][macierzPodst2[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolne2 = obliczX(macierzPodst2, wyrazyWolne2, mozliwe);
                        if (mozliwe) {
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(macierzPodst2);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolne2);
                        }
                    } else cout<<"Zero na przekatnej"<<endl;
                    break;
                }
                case 2:
                {
                    int rozmiar;
                    cout << "Wpisz rozmiar macierzy: ";
                    cin >> rozmiar;
                    wlasnaMacierz = utworzMacierz(rozmiar);
                    wyrazyWolneW = utworzWektorWyr(rozmiar);
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(wlasnaMacierz);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolneW);
                    wlasnaMacierz = eliminacjaZWyboremMaxWKol(wlasnaMacierz, wyrazyWolneW, dzial);
                    for (int k = 0; k<wlasnaMacierz.size(); k++) {
                        if (wlasnaMacierz[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolneW.size(); i++) {
                            wyrazyWolneW[i] = wlasnaMacierz[i][wlasnaMacierz[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolneW = obliczX(wlasnaMacierz, wyrazyWolneW, mozliwe);
                        if (mozliwe) {
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(wlasnaMacierz);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolneW);
                        }
                        break;
                    } else cout<<"Zero na przekatnej"<<endl;
                    default:
                        cout<<"Niepoprawny wybor"<<endl;
                        break;
                }
                    }
            break;
        }
        case 3:{
            switch (dane) {
                case 1:
                {
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(macierzPodst2);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolne2);
                    macierzPodst2 = eliminacjaZWyboremMaxWWie(macierzPodst2, wyrazyWolne2, indeksyKolumn, dzial);
                    for (int k = 0; k<macierzPodst2.size(); k++) {
                        if (macierzPodst2[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolne2.size(); i++) {
                            wyrazyWolne2[i] = macierzPodst2[i][macierzPodst2[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolne2 = obliczX(macierzPodst2, wyrazyWolne2, mozliwe);
                        if (mozliwe) {
                            if (indeksyKolumn.size() > 0)
                            {
                                for(int i = 0; i < indeksyKolumn.size(); i++)
                                {
                                    swap(wyrazyWolne2[indeksyKolumn[i].first], wyrazyWolne2[indeksyKolumn[i].second]);
                                }
                            }
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(macierzPodst2);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolne2);
                        }
                    } else cout<<"Zero na przekatnej"<<endl;
                    break;
                }
                case 2:
                {
                    int rozmiar;
                    cout << "Wpisz rozmiar macierzy: ";
                    cin >> rozmiar;
                    wlasnaMacierz = utworzMacierz(rozmiar);
                    wyrazyWolneW = utworzWektorWyr(rozmiar);
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(wlasnaMacierz);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolneW);
                    wlasnaMacierz = eliminacjaZWyboremMaxWWie(wlasnaMacierz, wyrazyWolneW, indeksyKolumn, dzial);
                    for (int k = 0; k<wlasnaMacierz.size(); k++) {
                        if (wlasnaMacierz[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolneW.size(); i++) {
                            wyrazyWolneW[i] = wlasnaMacierz[i][wlasnaMacierz[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolneW = obliczX(wlasnaMacierz, wyrazyWolneW, mozliwe);
                        if (mozliwe) {
                            if (indeksyKolumn.size() > 0)
                            {
                                for(int i = 0; i < indeksyKolumn.size() ; i++)
                                {
                                    swap(wyrazyWolneW[indeksyKolumn[i].first], wyrazyWolneW[indeksyKolumn[i].second]);
                                }
                            }
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(wlasnaMacierz);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolneW);
                        }
                    } else cout<<"Zero na przekatnej"<<endl;
                    break;
                }
                default:
                    cout<<"Niepoprawny wybor"<<endl;
                    break;
            }
            break;
        }
        case 4:{
            switch (dane) {
                case 1:{
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(macierzPodst2);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolne2);
                    macierzPodst2 = eliminacjaZWyboremMax(macierzPodst2, wyrazyWolne2, indeksyKolumn, dzial);
                    for (int k = 0; k<macierzPodst2.size(); k++) {
                        if (macierzPodst2[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolne2.size(); i++) {
                            wyrazyWolne2[i] = macierzPodst2[i][macierzPodst2[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolne2 = obliczX(macierzPodst2, wyrazyWolne2, mozliwe);
                        if (mozliwe) {
                            if (indeksyKolumn.size() > 0)
                            {
                                for(int i = 0; i < indeksyKolumn.size() ; i++)
                                {
                                    swap(wyrazyWolneW[indeksyKolumn[i].first], wyrazyWolneW[indeksyKolumn[i].second]);
                                }
                            }
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(wlasnaMacierz);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolneW);
                        }
                    } else cout<<"Zero na przekatnej"<<endl;
                    break;
                }
                case 2:{
                    int rozmiar;
                    cout << "Wpisz rozmiar macierzy: ";
                    cin >> rozmiar;
                    wlasnaMacierz = utworzMacierz(rozmiar);
                    wyrazyWolneW = utworzWektorWyr(rozmiar);
                    cout<<"Macierz podstawowa:"<<endl;
                    drukujMacierz(wlasnaMacierz);
                    cout<<"Wektor wyrazow wolnych:"<<endl;
                    drukujX(wyrazyWolneW);
                    wlasnaMacierz = eliminacjaZWyboremMax(wlasnaMacierz, wyrazyWolneW, indeksyKolumn, dzial);
                    for (int k = 0; k<wlasnaMacierz.size(); k++) {
                        if (wlasnaMacierz[k][k] == 0) {
                            dzial = false;
                        }
                    }
                    if (dzial) {
                        for (int i = 0; i<wyrazyWolneW.size(); i++) {
                            wyrazyWolneW[i] = wlasnaMacierz[i][wlasnaMacierz[0].size()-1];
                        }
                        bool mozliwe = true;
                        wyrazyWolneW = obliczX(wlasnaMacierz, wyrazyWolneW, mozliwe);
                        if (mozliwe) {
                            if (indeksyKolumn.size() > 0)
                            {
                                for(int i = 0; i < indeksyKolumn.size(); i++)
                                {
                                    swap(wyrazyWolne2[indeksyKolumn[i].first], wyrazyWolne2[indeksyKolumn[i].second]);
                                }
                            }
                            cout<<"Wyniki eliminacji:"<<endl;
                            cout<<"Macierz po eliminacji:"<<endl;
                            drukujMacierz(wlasnaMacierz);
                            cout<<"Wektor rozwiazan ukladu rownan:"<<endl;
                            drukujX(wyrazyWolneW);
                        } else cout<<"Zero na przekatnej"<<endl;
                    }
                    break;
                }
                default:
                    cout<<"Niepoprawny wybor"<<endl;
                    break;
            }
            break;
        }
        default:
            cout<<"Niepoprawny wybor"<<endl;
            break;
    }
    return 0;
}
