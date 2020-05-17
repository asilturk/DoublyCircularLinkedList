#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

/// Kullanilacak Node yapisini tanimliyoruz
struct node {
    int info;
    struct node *next;
    struct node *prev;
}

*start, *last;
int counter = 0;


/// Create, Read, Delete islemlerinin yapilacagi sinifi tanimliyoruz
class DoubleCircularList {

    /// public parametreler
    public:
        node *createNewNode(int);

        void insertNewElement();
        void searchElement();
        void displayList();
        void reverseList();
        void sortList();
        void sortListFromEndToBeginning();
        void sortListFromBeginningToEnd();
        void displayElementCount();
        void deleteItemForIndex(int pos);
        int getPositionForElement(int value);
        void deleteElement();

        /// constructor - yapici metot. Siniftan ilk obje olusturuldugunda, ikili listenin once ve sonrasindaki elemanlara deafult olarak bos (null) deger atadik.
        DoubleCircularList() {
            start = NULL;
            last = NULL;
        }
};


int displayUserChoiceMenu();

/// Uygulama ilk calistiginda tetiklenen metot,
int main() {

    displayUserChoiceMenu();
    return 0;
}

///  Konsol uzerinden kullaniciya feedback verip, kullanici girdilerini burdan yonetiyoruz, kullanici secimine bagli olarak bagil listeyi duzenliyoruz
int displayUserChoiceMenu() {
    int userChoice; /// kullanicinin node uzerinden yapmak istedigi islemin, konsoldan yaptigi secimini bu degiskende tutacagiz,

    DoubleCircularList doubleCircularListObject;

    while (1) {

        cout<<"[1] - Yeni sayi ekleme"<<endl;
        cout<<"[2] - Sayi arama"<<endl;
        cout<<"[3] - Elemanlari duz listele"<<endl;
        cout<<"[4] - Elemanlari tersten listele"<<endl;
        cout<<"[5] - Eleman sayisini ogrenme"<<endl;
        cout<<"[6] - Eleman Silme"<<endl;
        cout<<"[7] - Cikis"<<endl;
        cout<< endl;
        cout<<"Seciminiz: ";

        cin >> userChoice; /// cin metotu ile kullanicinin girdigi int degerini userChoice degiskenine aktariyoruz.

        /// kullanici secimlerine gore node islemlerini gerceklestiriyoruz
        switch(userChoice) {

        case 1:
            doubleCircularListObject.insertNewElement();
            break;

        case 2:
            doubleCircularListObject.searchElement();
            break;

        case 3:
            doubleCircularListObject.sortListFromBeginningToEnd();
            break;

        case 4:
            doubleCircularListObject.sortListFromEndToBeginning();
            break;

        case 5:
            doubleCircularListObject.displayElementCount();
            break;

        case 6:
            doubleCircularListObject.deleteElement();
            break;

        case 7:
            doubleCircularListObject.displayList();
            break;

        case 8:
            doubleCircularListObject.reverseList();
            break;

        case 9:
            exit(1);

        default:
            cout<<"Yanlis secim yaptiniz, lutfen menudeki sayilara gore seciminizi gerceklestirin."<<endl;
        }
    }
}


/// Bu metot aldigi value degerine gore yeni bir node olusturur
node* DoubleCircularList::createNewNode(int value) {

    counter++;
    struct node *temp;

    temp = new(struct node);
    temp->info = value;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

/// Bu metot listenin sonuna eleman ekler
void DoubleCircularList::insertNewElement() {

    int value;
    cout<<"Liteye eklenecek sayiyi giriniz:  ";
    cin>>value;

    struct node *temp;

    temp = createNewNode(value);

    /// liste bos ise ilk eleman olarak eklenir.
    if (start == last && start == NULL) {
        start = last = temp;
        start->next = last->next = NULL;
        start->prev = last->prev = NULL;
    }

    /// liste dolu ise, sona eklenir
    else {
        last->next = temp;
        temp->prev = last;
        last = temp;
        start->prev = last;
        last->next = start;
    }
}


/// kullanici tarafindan girilen sayinin, listede varsa silinmesini saglar.
void DoubleCircularList::deleteElement() {
    int value;

    cout << "Silinecek sayi: ";
    cin >> value;

    int position = getPositionForElement(value);
    if (position < 0) {
        cout << "Sayi listede bulunamadi";
        return;
    } else {
        deleteItemForIndex(position);
    }
}


/// bu metot, silinecek elemanin hangi index'te oldugunu donderir.
int DoubleCircularList::getPositionForElement(int value) {

    int pos = 0, i;
    struct node *s;

    /// bos listede arama yapilirsa, ekranda aranan sayi yok yazar.
    if (start == last && start == NULL) {
        return -1; // sayi yoksa -1 doner.
    }

    s = start;

    /// aranan elemanin pozisyonunu soyler.
    for (i = 0;i < counter;i++) {
        pos++;

        if (s->info == value) {
            /// pos - silinecek eleman pozisyonu
            return pos;
        }

        s = s->next;
    }
}

/// ilgili index'teki elemani siler.
void DoubleCircularList::deleteItemForIndex(int pos) {

    int i;
    node *ptr, *s;

    if (start == last && start == NULL) {
        cout << "Liste bos" << endl;
        return;
    }

    if (counter < pos) {
        return;
    }

    s = start;

    if(pos == 1) {
        counter--;
        last->next = s->next;
        s->next->prev = last;
        start = s->next;
        free(s);
        // eleman silindi
        return;
    }

    for (i = 0;i < pos - 1;i++ ) {
        s = s->next;
        ptr = s->prev;
    }

    ptr->next = s->next;
    s->next->prev = ptr;
    if (pos == counter) {
        last = ptr;
    }

    counter--;
    free(s);
    // eleman silindi
}

/// Listede girilen elemanin olup olmadigi bilgisini kullaniciya donderir.
void DoubleCircularList::searchElement() {

    int pos = 0, value, i;
    bool flag = false;
    struct node *s;

    /// bos listede arama yapilirsa, ekranda aranan sayi yok yazar.
    if (start == last && start == NULL) {
        cout<<"ARANAN SAYI YOK"<<endl;
        return;

    }

    cout<<endl<<"Aranacak sayiyi giriniz: ";

    cin>>value;
    s = start;

    /// aranan elemanin pozisyonunu soyler.
    for (i = 0;i < counter;i++) {
        pos++;

        if (s->info == value) {
            cout << "ARANAN SAYI VAR" << endl;
            flag = true;
        }

        s = s->next;
    }

    if (!flag)
        cout<<"ARANAN SAYI YOK"<<endl;

}


/// Listede girilen elemanin olup olmadigi bilgisini kullaniciya donderir.
void DoubleCircularList::displayElementCount() {

    int i, elementCount;
    struct node *s;

    if (start == last && start == NULL) {
        cout<<"Eleman sayisi: 0"<<endl;
        return;
    }

    s = start;

    for (i = 0;i < counter-1;i++) {
        s = s->next;
        elementCount += 1;
    }

    cout<<"Eleman Sayisi: "<< elementCount+1 << endl << endl;
}

/// listeyi baston sona siralayarak sekilde ekrana basar.
void DoubleCircularList::sortListFromBeginningToEnd() {
    sortList();
    displayList();
}

/// listeyi sondan basa siralayarak ekrana basar
void DoubleCircularList::sortListFromEndToBeginning() {
    reverseList();
    displayList();
}


/// bu metot elemanlari duz listeler.
void DoubleCircularList::sortList() {

    struct node *temp, *s;
    int value, i;

    /// liste bos ise kullaniciya bos bilgisi donderilir.
    if (start == last && start == NULL) {
        cout<<"Liste bos, listelenecek eleman bulunamadi."<<endl;
        return;
    }

    s = start;

    for (i = 0;i < counter;i++) {
        temp = s->next;

        while (temp != start) {
            if (s->info > temp->info) {
                value = s->info;
                s->info = temp->info;
                temp->info = value;
            }

            temp = temp->next;
        }

        s = s->next;
    }

}


/// listelenen elemanlari ekranda yazar.
void DoubleCircularList::displayList() {
    int i;
    struct node *s;

    if (start == last && start == NULL) {
        cout<<"Liste bos, listelenecek eleman bulunamadi."<<endl;
        return;
    }

    s = start;

    for (i = 0;i < counter-1;i++) {
        cout<<s->info<<"<->";
        s = s->next;
    }

    cout<<s->info<<endl;
}

/// bu metot elemanlari ters cevirir
void DoubleCircularList::reverseList() {

    // liste bos ise doner.
    if (start == last && start == NULL) {
        return;
    }

    /// sondan basa node olusturulur.
    struct node *p1, *p2;
    p1 = start;
    p2 = p1->next;
    p1->next = NULL;
    p1->prev = p2;

    /// listedeki node'lar sondan baslanarak sirasiyla basa dogru donderilir.
    while (p2 != start) {
        p2->prev = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p2->prev;
    }

    last = start;
    start = p1;
    cout<<"Liste ters donderildi."<<endl;
}