#include <iostream>
#include <cmath>

using namespace std;

struct Donthuc{
    int n; //so mu
    double a; // he so
};

struct Dathuc{
    int m; //so don thuc trong da thuc
    Donthuc dt[101];
};

void Sapxepdonthuc (Dathuc &d){
    for (int i=0; i < d.m - 1; i++){
        for (int j=0; j < d.m - i - 1; j++){
            //Neu so mu don thuc hien tai < so mu don thuc tiep theo thi doi cho
            if (d.dt[j].n < d.dt[j+1].n){
                int temp = d.dt[j].n;
                double tempo1 = d.dt[j].a;

                d.dt[j].n = d.dt[j+1].n;
                d.dt[j].a = d.dt[j+1].a;

                d.dt[j+1].n = temp;
                d.dt[j+1].a = temp1;
            }
        }
    }
}

void Congdonthuc(Dathuc &d){ //Rut gon da thuc
    int i=0;
    while (i < d.m-1){
        if (d.dt[i].n == d.dt[i+1].n){
            d.dt[i].a += d.dt[i+1].a; // Cong don thuc hien tai voi don thuc tiep theo neu cung so mu
            //Xoa don thuc phia sau don thuc hien tai sau khi da thuc hien phep cong
            for (int j=i+1; j < d.m-1; j++){
                d.dt[j].a = d.dt[j+1].a;
                d.dt[j].n = d.dt[j+1].n;
            }
            d.m -= 1;
            continue;
        }
        i++;
    }
    //Xoa phan tu 0 o dau da thuc
    int new_m = 0;
    for(int k = 0; k < d.m; k++){
        // Kiem tra xem he so don thuc co khac 0 hay khong
        if (abs(d.dt[k].a) > 1e-9){
            d.dt[new_m] = d.dt[k];
            new_m++;
        }
    }
    d.m = new_m;
}

void XuatDaThuc (Dathuc d){
    bool dathucdautien = true;
    for (int i=0; i<d.m; i++){
        double hs = d.dt[i].a;
        int sm = d.dt[i].n;
        //Neu he so don thuc dau tien = 0 -> Tiep tuc xet he so don thuc tiep theo
        if (hs == 0) continue;
        //Neu he so don thuc duong va don thuc khong phai don thuc dau tien thi in "+"
        if (hs > 0 && dathucdautien == false)
            cout << "+";
        //Neu he so don thuc am thi in "-"
        if (hs < 0)
            cout << "-";
        //Neu he so don thuc khac +1, -1 hoac so mu don thuc bang 0 thi in tri tuyet doi cua he so don thuc
        if (abs(hs) != 1 || sm == 0){
             cout << abs(hs);
        }
        //Neu so mu don thuc > 0 thi in "x"
        if (sm > 0){
            cout << "x";
            //Neu so mu don thuc > 1 thi in "^so mu"
            if (sm > 1){
                cout << "^" << sm;
            }
        }
        //Dat lai bien "dathucdautien" thanh false khi da thuc hien xong cau lenh hs==0
        dathucdautien = false;
    }
    //Neu toan bo he so cua tat ca don thuc trong da thuc bang 0 thi in "0"
    if (dathucdautien){
        cout << 0;
    }
}
double TinhTheoX (Dathuc d){
    double x;
    cin >> x;
    double ketqua=0;
    for (int i=0; i<d.m; i++){
        //Cong tung don thuc trong da thuc
        ketqua += d.dt[i].a * pow(x, d.dt[i].n);
    }
    return ketqua;
}

void Daohamcap1 (Dathuc d){
    Dathuc t;
    t.m = d.m;
    for (int i=0; i<t.m; i++){
        //Sao chep da thuc vao mot da thuc tam thoi
        t.dt[i].a = d.dt[i].a;
        t.dt[i].n = d.dt[i].n;
    }
    for (int i=0; i<t.m; i++){
        //Su dung cong thuc tong quat cua phep dao ham so mu
        t.dt[i].a *= t.dt[i].n;
        t.dt[i].n -= 1;
    }

    XuatDaThuc(t);
}

void Tonghaidathuc (Dathuc A, Dathuc B){
    Dathuc t;
    t.m = A.m+B.m;
    for (int i=0; i<A.m; i++){
        t.dt[i].a = A.dt[i].a;
        t.dt[i].n = A.dt[i].n;
    }
    for (int i=A.m, j=0; j<B.m; i++,j++){
        t.dt[i].a = B.dt[j].a;
        t.dt[i].n = B.dt[j].n;
    }
    Sapxepdonthuc(t);
    Congdonthuc(t);
    XuatDaThuc(t);
}

void Hieuhaidathuc (Dathuc A, Dathuc B){
    Dathuc t;
    t.m = A.m+B.m;
    for (int i=0; i<A.m; i++){
        t.dt[i].a = A.dt[i].a;
        t.dt[i].n = A.dt[i].n;
    }
    for (int i=A.m, j=0; j<B.m; i++,j++){
        t.dt[i].a = -B.dt[j].a;
        t.dt[i].n = B.dt[j].n;
    }
    Sapxepdonthuc(t);
    Congdonthuc(t);
    XuatDaThuc(t);
}

void Tichhaidathuc (Dathuc A, Dathuc B){
    Dathuc t;
    t.m = A.m*B.m;
    int i=0;
    for (int j=0; j<A.m; j++){
        for (int k=0; k<B.m; k++){
            t.dt[i].a = A.dt[j].a * B.dt[k].a;
            t.dt[i].n = A.dt[j].n + B.dt[k].n;
            i++;
        }
    }
    Sapxepdonthuc(t);
    Congdonthuc(t);
    XuatDaThuc(t);
}

void Thuonghaidathuc (Dathuc A, Dathuc B){
    Dathuc t; //Thuong cua hai da thuc
    t.m=0;
    Dathuc du;//Da thuc du cua phep chia hai da thuc
    Dathuc temp;
    for (int i=0; i<A.m; i++){
        du.dt[i].a = A.dt[i].a;
        du.dt[i].n = A.dt[i].n;
    }
    du.m = A.m;
    int i=0;
    while (du.dt[0].n >= B.dt[0].n && du.m > 0){
        t.dt[i].a = du.dt[0].a / B.dt[0].a;
        t.dt[i].n = du.dt[0].n - B.dt[0].n;
        t.m++;
        temp.m = B.m;
        int o=0;
        for (int j=0; j<B.m; j++){
            temp.dt[o].a = B.dt[j].a * t.dt[t.m-1].a;
            temp.dt[o].n = B.dt[j].n + t.dt[t.m-1].n;
            o++;

        }
        int old_du_m = du.m;
        for (int j=old_du_m, k=0; k<temp.m; j++,k++){
            du.dt[j].a = -temp.dt[k].a;
            du.dt[j].n = temp.dt[k].n;
        }
        du.m = old_du_m + temp.m;
        Sapxepdonthuc(du);
        Congdonthuc(du);
        i++;
    }
    cout << "Thuong cua hai da thuc: "; XuatDaThuc(t); cout << endl;
    cout << "Du: "; XuatDaThuc(du); cout << endl;
}

int main(){
    Dathuc A;
    cin >> A.m;
    for (int i=0; i<A.m; i++){
        cin >> A.dt[i].a >> A.dt[i].n;
    }
    Sapxepdonthuc(A); //Sap xep so mu cac don thuc trong da thuc theo thu tu giam dan

    Congdonthuc(A); //Cong cac don thuc cung so mu trong da thuc
    XuatDaThuc(A);
    cout << "Tinh da thuc theo " << TinhTheoX(A) << endl;
    cout << "Da thuc sau khi dao ham cap 1: "; Daohamcap1(A); cout << endl;
    //Khai bao da thuc B
    Dathuc B;
    cout << "Nhap so don thuc trong da thuc B va nhap cac don thuc: ";
    cin >> B.m;
    for (int i=0; i<B.m; i++){
        cin >> B.dt[i].a >> B.dt[i].n;
    }
    Sapxepdonthuc(B);

    Congdonthuc(B);
    cout << "Tong hai da thuc A va B: "; Tonghaidathuc(A, B); cout << endl;
    cout << "Hieu hai da thuc A va B: "; Hieuhaidathuc(A, B); cout << endl;
    cout << "Tich hai da thuc A va B: "; Tichhaidathuc(A, B); cout << endl;
    //
    if (A.dt[0].n >= B.dt[0].n){
        cout << "Thuong hai da thuc A va B: "; Thuonghaidathuc(A, B); cout << endl;
    }else{
        cout << "Thuong hai da thuc B va A: "; Thuonghaidathuc(B, A); cout << endl;
    }
    return 0;
}
