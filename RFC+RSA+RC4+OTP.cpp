#include <iostream>
#include <cmath>
#include <algorithm>
#include<cstdlib>
#include<winsock.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <bits/stdc++.h>

using namespace std;
int p, q,n,d,e,g,f,p1,q1,e1,d1,shift;
string asdf,plaintext;
char message[100];
// Fungsi untuk mencari nilai gcd (greatest common divisor) dari dua bilangan

void leftrotate(string &s, int d)
{
reverse(s.begin(), s.begin()+d);
reverse(s.begin()+d, s.end());
reverse(s.begin(), s.end());
}

void rightrotate(string &s, int d)
{
leftrotate(s, s.length()-d);
}

int gcd(int a, int b) 
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Fungsi untuk mencari nilai modulo dengan menggunakan algoritma eksponensial cepat
int mod(int base, int exponent, int modulus) 
{
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Fungsi untuk mencari nilai e yang cocok untuk kunci publik
int findE(int phi) {
    int e = 2;
    while (e < phi)
	{
        if (gcd(e, phi) == 1) return e;
        e++;
    }
    return 1;
}

// Fungsi untuk mencari nilai d yang cocok untuk kunci privat
int findD(int e, int phi) {
    int d = 1;
    while (d < phi) {
        if ((d * e) % phi == 1) return d;
        d++;
    }
    return 0;
}

// Fungsi untuk mengenkripsi pesan dengan menggunakan kunci publik
string encrypt(int e, int n, string ciphertext) {
    string encryptedMessage = "";
    for (char c : ciphertext) {
        int x = (int)c;
        int y = mod(x, e, n);
        encryptedMessage += to_string(y) + " ";
    }
    return encryptedMessage;
}

string encrypt1(int e, int n, string ciphertext) 
{
    string encryptedMessage1 = "";
    for (char c : ciphertext) {
        int x = (int)c;
        int y = mod(x, e, n);
        encryptedMessage1 += to_string(y) + "";
    }
    return encryptedMessage1;
}

string encryptRailFenceCipher(string plaintext, int k) {
  // Buat matriks untuk menyimpan pesan yang akan dienkripsi
  char matrix[k][plaintext.length()];

  // Inisialisasi matriks dengan karakter spasi
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < plaintext.length(); j++) {
      matrix[i][j] = ' ';
    }
  }

  // Isi matriks dengan karakter dari plaintext
  int direction = 1;
  int row = 0;
  for (int i = 0; i < plaintext.length(); i++) {
    matrix[row][i] = plaintext[i];

    // Ubah arah jika sudah mencapai ujung atas atau bawah matriks
    if (row == k - 1) {
      direction = -1;
    } else if (row == 0) {
      direction = 1;
    }

    // Geser ke baris berikutnya
    row += direction;
  }

  // Buat ciphertext dengan menggabungkan karakter di setiap baris
  string ciphertext = "";
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < plaintext.length(); j++) {
      if (matrix[i][j] != ' ') {
        ciphertext += matrix[i][j];
      }
    }
  }

  return ciphertext;
}


// Fungsi untuk mendekripsi pesan dengan menggunakan kunci privat

int enkripsi_kunci() 
{
	int k;
	cout<<"  *************************ENKRIPSI KUNCI**********************"<<endl;
    // Nilai p dan q yang akan digunakan untuk menghasilkan kunci publik dan privat
	cout<<"\tMasukkan Plaintext Kunci  :";
	cin.getline(message, 100);
    // Menghitung nilai n dan phi
    plaintext=message;
    cout<<"\tMasukkan pergeseran       :";
	cin>>k;
    rightrotate(plaintext,k);
    cout<<"\tMasukkan Prima Pertama    :";
    cin>>p;
    cout<<"\tMasukkan Prima Kedua      :";
    cin>>q;
    n = p * q;
    int phi = (p - 1) * (q - 1);
    // Mencari nilai e yang cocok untuk kunci publik
    e = findE(phi);
    // Mencari nilai d yang cocok untuk kunci privat
    d = findD(e, phi);
    // Pesan yang akan dienkripsi
    cout<<"\tPlaintext Right Shift K   : " <<plaintext<<endl;
    
// Iterasi melalui setiap karakter dalam string
// Inisialisasi variabel untuk menghitung jumlah ASCII dan jumlah karakter
int sum = 0;
int count = 0;
for (char c : plaintext) 
{
// Tambahkan nilai ASCII karakter ke variabel sum
sum += (int)c;
count++;
}

// Hitung rata-rata ASCII dengan membagi sum dengan jumlah karakter
double average = (double)sum / count;

// Pembulatan rata-rata ASCII ke atas atau ke bawah
int rounded_average;
if (average - (int)average >= 0.5) {
// Pembulatan ke atas
rounded_average = (int)round(average);
} else {
// Pembulatan ke bawah
rounded_average = (int)average;
}

// Cetak hasil
cout << "\tRata-rata ASCII string yang dibulatkan adalah: " << rounded_average << endl;
int largestDigit = 0;
    while (rounded_average > 0) 
	{
        int digit = rounded_average % 10;
        if (digit > largestDigit) {
            largestDigit = digit;
        }
        rounded_average /= 10;
    }
    cout << "\tAngka terbesar dari hasil rata-rata: " << largestDigit << endl;
    string ciphertext = encryptRailFenceCipher(plaintext, largestDigit);
    cout<<"\tHasil Enkripsi Rail Fence : " <<ciphertext<<endl;
    // Mengenkripsi pesan menggunakan kunci publik
    string encryptedMessage = encrypt(e, n, ciphertext);
    string encryptedMessage1 = encrypt1(e, n, ciphertext);
    cout <<"\tHasil Kunci Privat       : " <<d<< endl;
    cout <<"\tHasil Enkripsi Kunci     : " << encryptedMessage << endl;
    cout <<"\tKunci Pesan              : " << encryptedMessage1 << endl;
    // Mendekripsi pesan menggunakan kunci privat
    return 0;
    cout<<"  *************************************************************"<<endl;
}


string RC4(string str2, string str3)
{
    // Inisialisasi variabel
    int S[256], T[256];
    for (int i = 0; i < 256; i++)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + str3[i % str3.length()]) % 256;
        swap(S[i], S[j]);
    }
    int i = 0, k = 0;
    string hasil_enkripsi = "";
    for (int n = 0; n < str2.length(); n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        k = S[(S[i] + S[j]) % 256];
        hasil_enkripsi += char(k ^ str2[n]);
    }
    return hasil_enkripsi;
}

string encript(string pesan_enkripsi, string str3)
{
    // Create a result string the same size as the message
    string result(pesan_enkripsi.size(), ' ');

    // Loop through each character in the message
    for (int i = 0; i < pesan_enkripsi.size(); i++)
        {
        // Encrypt each character by XORing it with the corresponding character in the key
        result[i] = pesan_enkripsi[i] ^ str3[i];
    }

    return result;
}

string encript1(string ciphertext1, string str3)
{
    // Create a result string the same size as the message
    string result(ciphertext1.size(), ' ');
    // Loop through each character in the message
    for (int i = 0; i < ciphertext1.size(); i++)
        {
        // Encrypt each character by XORing it with the corresponding character in the key
        result[i] = ciphertext1[i] ^ str3[i];
    }

    return result;
}


int enkripsi_pesan()
{
cout<<"  *************************ENKRIPSI PESAN**********************"<<endl;
cout<<endl;
string str2,str3,str4,str5,str7, a,ciphertext1, ciphertext,decrypted,decrypted1,encryptedOneTimePad,text,b,kunci="",kuncibaru="",rev="",dekrip;
char input[64], rev_str[64], kunciascii; unsigned char * plaintextrc4;
unsigned char * kuncirc4;unsigned char * kuncirc42;  unsigned char * enkripsirc4;unsigned char * enkripsirc42;
unsigned char * dekripsirc4;unsigned char * dekripsirc42;
char key2[100];
cout<<"\tMasukkan Plaintext Pesan       : ";
cin>>str2;
cout<<"\tMasukkan Kunci Pesan           : ";
cin>>str3;
string pesan_enkripsi = RC4(str2, str3);
cout<<"\tHasil Enkripsi RC4             : " <<pesan_enkripsi<<endl;
cout<<endl;
cout<<"\tENKRIPSI MENGGUNAKAN OTP"<<endl;
ciphertext=encript(pesan_enkripsi, str3);
cout<<"\tEnkripsi OTP Putaran 1         : "<<ciphertext<<endl;
ciphertext1=encript1(ciphertext, str3);
cout<<"\tHasil Enkripsi Pesan           : "<<ciphertext1<<endl;
cout<<"  *************************************************************"<<endl;
}

string decript(string str4, string str5)
{
    // Decryption is the same as encryption, just XORing the ciphertext with the key
    return encript(str4, str5);
}

string RC4_decrypt(string decrypted1, string str5)
{
    // Inisialisasi variabel
    int S[256], T[256];
    for (int i = 0; i < 256; i++)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + str5[i % str5.length()]) % 256;
        swap(S[i], S[j]);
    }
    int i = 0, k = 0;
    string hasil_dekripsi = "";
    for (int n = 0; n < decrypted1.length(); n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        k = S[(S[i] + S[j]) % 256];
        hasil_dekripsi += char(k ^ decrypted1[n]);
    }
    return hasil_dekripsi;
}


int dekripsi_pesan()
{
string str2,str3,str4,str5,str7, a,ciphertext1, ciphertext,decrypted,decrypted1,encryptedOneTimePad,text,b,kunci="",kuncibaru="",rev="",dekrip;
char input[64], rev_str[64], kunciascii; unsigned char * plaintextrc4;
unsigned char * kuncirc4;unsigned char * kuncirc42;  unsigned char * enkripsirc4;unsigned char * enkripsirc42;
unsigned char * dekripsirc4;unsigned char * dekripsirc42;
char key2[100];
cout<<"  *************************DEKRIPSI PESAN**********************"<<endl;
cout<<"\tMasukkan Hasil enkripsi        : ";
cin>>str4;
cout<<"\tMasukkan Kunci Pesan           : ";
cin>>str5;
decrypted = decript(str4, str5);
decrypted1= decript(decrypted, str5);
cout<<"\tDekripsi OTP                   : "<<decrypted<<endl;
string pesan_dekripsi = RC4_decrypt(decrypted1, str5);
cout<<"\tDekripsi RC4 (Plaintext Pesan) : "<<pesan_dekripsi<<endl;
cout<<endl;
cout<<"  *************************************************************"<<endl;
}

string decrypt(int d1, int n, string encryptedMessage) 
{
	encryptedMessage+=" ";
    string decryptedMessage = "";
    string number = "";
    for (char c : encryptedMessage) 
	{
        if (c == ' ') {
            int x = stoi(number);
            int y = mod(x, d1, n);
            char z = (char)y;
            decryptedMessage += z;
            number = "";
        }
        else {
            number += c;
        }
    }
    return decryptedMessage;
}

// Fungsi untuk mendekripsi ciphertext menggunakan Rail Fence Cipher
string decryptRailFenceCipher(string decryptedMessage, int key) {
    // Buat matriks untuk menyimpan plaintext
    char matrix[key][decryptedMessage.length()];

    // Inisialisasi matriks dengan karakter spasi
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < decryptedMessage.length(); j++) {
            matrix[i][j] = ' ';
        }
    }

    // Isi matriks dengan ciphertext
    int row = 0, col = 0;
    bool down = true;
    for (int i = 0; i < decryptedMessage.length(); i++) {
        matrix[row][col] = '*';

        if (down) {
            row++;
            if (row == key) {
                row = key - 2;
                down = false;
            }
        } else {
            row--;
            if (row == -1) {
                row = 1;
                down = true;
            }
        }
        col++;
    }

    // Rekonstruksi plaintext dari matriks
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j <decryptedMessage.length(); j++) {
if (matrix[i][j] == '*') {
matrix[i][j] = decryptedMessage[index++];
}
}
}
// Buat string untuk menyimpan hasil dekripsi
string plaintext;
row = 0, col = 0;
down = true;
for (int i = 0; i < decryptedMessage.length(); i++) {
    plaintext += matrix[row][col];

    if (down) {
        row++;
        if (row == key) {
            row = key - 2;
            down = false;
        }
    } else {
        row--;
        if (row == -1) {
            row = 1;
            down = true;
        }
    }
    col++;
}

return plaintext;
}

int dekripsi_kunci()
{
	int key;
	string encryptedMessage;
	cout<<endl<<endl;
	cout<<"  *************************DEKRIPSI KUNCI**********************"<<endl;
	cout<<"\tMasukkan Cipherteks: ";
	getline(cin,encryptedMessage);
	cout<<"\tMasukkan bilangan Prima 1         : ";
    cin>>p;
    cout<<"\tMasukkan bilangan Prima 2         : ";
    cin>>q;
    cout<<"\tMasukkan kunci Privat             : ";
    cin>>d1;
    cout<<"\tMasukkan Pergeseran               : ";
    cin>>key;
	n =p*q;
    string decryptedMessage = decrypt(d1, n, encryptedMessage);
    cout <<"\tHasil Dekripsi Rail Fence        : " << decryptedMessage << endl;
    
    
// Iterasi melalui setiap karakter dalam string
// Inisialisasi variabel untuk menghitung jumlah ASCII dan jumlah karakter
int sum = 0;
int count = 0;
for (char c : decryptedMessage) 
{
// Tambahkan nilai ASCII karakter ke variabel sum
sum += (int)c;
count++;
}

// Hitung rata-rata ASCII dengan membagi sum dengan jumlah karakter
double average = (double)sum / count;

// Pembulatan rata-rata ASCII ke atas atau ke bawah
int rounded_average;
if (average - (int)average >= 0.5) 
{
// Pembulatan ke atas
rounded_average = (int)round(average);
} 
else 
{
// Pembulatan ke bawah
rounded_average = (int)average;
}
// Cetak hasil
cout << "\tRata-rata ASCII string yang dibulatkan adalah: " << rounded_average << endl;
int largestDigit = 0;
    while (rounded_average > 0) 
	{
        int digit = rounded_average % 10;
        if (digit > largestDigit) {
            largestDigit = digit;
        }
        rounded_average /= 10;
    }
    cout << "\tAngka terbesar dari hasil rata-rata: " << largestDigit << endl;
    string plaintext = decryptRailFenceCipher(decryptedMessage, largestDigit);
    cout<<"\tHasil shift                       : " <<plaintext<<endl;
	leftrotate(plaintext,key);
    cout <<"\tPlaintext AWal                   : " << plaintext << endl;
    getch();
    exit(0);
    cout<<"  *************************************************************"<<endl;
}
int selesai()
{
	 cout<<"  *************************************************************"<<endl;
     cout<<"                                SELESAI                        "<<endl;
     cout<<"  *************************************************************"<<endl;
}

int main(int argc, char *argv[])
{
int jawab;
menu:
     cout<<"  *************************************************************"<<endl;
     cout<<"               PROGRAM ALGORITMA RSA, OTP DAN RC4              "<<endl;
     cout<<"  *************************************************************"<<endl;
     cout<<"\t1.) Enkripsi Kunci\n";
     cout<<"\t2.) Enkripsi Pesan\n";
     cout<<"\t3.) Dekripsi Pesan\n";
     cout<<"\t4.) Dekripsi Kunci\n";
     cout<<"\t5.) Selesai\n";
     cout<<"\tSilahkan memilih menu sesuai nomor... "<<endl;
     cout<<"\tPilihan Anda:";
	 cin>>jawab;
     cin.ignore(); // mengabaikan input spasi yang terjadi ketika input jawab tadi
	switch(jawab)
	{
    case 1:
	{
		enkripsi_kunci();
		getch();
        system("cls");
        goto menu;
	}
    case 2:
    {
        enkripsi_pesan();
        getch();
        system("cls");
        goto menu;
	}
    case 3:
    {
        dekripsi_pesan();
        getch();
        system("cls");
        goto menu;
	}
    case 4:
    {
        dekripsi_kunci();
        getch();
        system("cls");
        goto menu;
	}
	case 5:
	{
		selesai();
        getch();
        system("cls");
        goto menu;
		}
	default:
        cout<<"\tPilihan Anda salah, silahkan coba kembali";
        system("cls");
        goto menu;
}
}


